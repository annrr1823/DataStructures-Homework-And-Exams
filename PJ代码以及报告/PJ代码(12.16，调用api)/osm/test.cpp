#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <queue>
#include <cmath>
#include "tinyxml/tinyxml.h"
#include "jsoncpp/json/json.h"
#include <emscripten/bind.h>
#include <chrono>

using namespace emscripten;
using namespace std;
using namespace std::chrono;

// Store nodes and ways as JSON data
Json::Value nodes;
Json::Value ways;
Json::Value buildings;

// Separate adjacency maps for pedestrians and vehicles
map<string, vector<pair<string, double>>> pedestrianAdjacencyMap;
map<string, vector<pair<string, double>>> vehicleAdjacencyMap;

// Function to determine if a way is accessible to pedestrians
bool isPedestrianAccessible(const Json::Value& tags) {
    if (tags.empty()) return true; // Default to accessible if no tags

    string highway = tags.get("highway", "").asString();
    string footway = tags.get("footway", "").asString();
    string pedestrian = tags.get("pedestrian", "").asString();
    string access = tags.get("access", "").asString();
    
    // Pedestrian-specific paths
    if (footway == "yes" || pedestrian == "yes" ||
        highway == "footway" || highway == "pedestrian" || 
        highway == "path" || highway == "steps" ||
        highway == "crossing" || highway == "sidewalk") {
        return true;
    }

    // Pedestrian-allowed in mixed traffic zones
    if ((highway == "residential" || highway == "living_street" || 
        highway == "service" || highway == "track") && 
        access != "no" && access != "private") {
        return true;
    }

    // Further check for restricted areas (if specified by tags)
    if (tags.isMember("no_exit") || tags.isMember("dead_end")) {
        return false;
    }

    return false;
}


// Function to determine if a way is accessible to vehicles
bool isVehicleAccessible(const Json::Value& tags) {
    if (tags.empty()) return true; // Default to accessible if no tags

    string highway = tags.get("highway", "").asString();
    string motor_vehicle = tags.get("motor_vehicle", "").asString();
    string access = tags.get("access", "").asString();
    
    // Check if motor vehicle access is explicitly denied
    if (motor_vehicle == "no" || access == "no" || access == "private") return false;

    // Vehicle-specific roads (public roads typically accessible to vehicles)
    if (highway == "motorway" || highway == "trunk" ||
        highway == "primary" || highway == "secondary" ||
        highway == "tertiary" || highway == "residential" ||
        highway == "service" || highway == "unclassified" ||
        highway == "living_street") {
        return true;
    }

    // Allow vehicle access if road type is not specifically restricted
    if (highway == "track" && motor_vehicle != "no") {
        return true;
    }

    // Further check for restricted areas like private roads or areas marked for certain vehicle types
    if (tags.isMember("access") && (access == "destination" || access == "customer")) {
        return true;
    }

    return false;
}


// Calculate distance between two points (Haversine formula)
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371e3;
    double phi1 = lat1 * M_PI / 180;
    double phi2 = lat2 * M_PI / 180;
    double deltaPhi = (lat2 - lat1) * M_PI / 180;
    double deltaLambda = (lon2 - lon1) * M_PI / 180;

    double a = sin(deltaPhi / 2) * sin(deltaPhi / 2) +
               cos(phi1) * cos(phi2) * sin(deltaLambda / 2) * sin(deltaLambda / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return R * c;
}

void load() {
    TiXmlDocument tinyXmlDoc("map");
    tinyXmlDoc.LoadFile();
    TiXmlElement *root = tinyXmlDoc.RootElement();

    // Load nodes
    TiXmlElement *nodeElement = root->FirstChildElement("node");
    for (; nodeElement; nodeElement = nodeElement->NextSiblingElement("node")) {
        Json::Value node;
        string id = nodeElement->Attribute("id");
        double lon = stod(nodeElement->Attribute("lon"));
        double lat = stod(nodeElement->Attribute("lat"));

        node["id"] = id;
        node["lon"] = lon;
        node["lat"] = lat;
        nodes[id] = node;
    }

    // Load ways
    TiXmlElement *wayElement = root->FirstChildElement("way");
    for (; wayElement; wayElement = wayElement->NextSiblingElement("way")) {
        Json::Value way;
        string wayId = wayElement->Attribute("id");
        way["id"] = wayId;

        Json::Value wayNodes;
        TiXmlElement *childNode = wayElement->FirstChildElement("nd");
        vector<string> nodeRefs;

        // Gather nodes in the way
        for (; childNode; childNode = childNode->NextSiblingElement("nd")) {
            string ref = childNode->Attribute("ref");
            nodeRefs.push_back(ref);
            wayNodes.append(nodes[ref]);
        }

        // Check if it's a building
        if (!nodeRefs.empty() && nodeRefs.front() == nodeRefs.back()) {
            way["nodes"] = wayNodes;
            Json::Value wayTags;
            TiXmlElement *childTag = wayElement->FirstChildElement("tag");
            for (; childTag; childTag = childTag->NextSiblingElement("tag")) {
                wayTags[childTag->Attribute("k")] = childTag->Attribute("v");
            }
            way["tags"] = wayTags;
            buildings[wayId] = way;
            continue;
        }

        way["nodes"] = wayNodes;

        // Process tags
        Json::Value wayTags;
        TiXmlElement *childTag = wayElement->FirstChildElement("tag");
        for (; childTag; childTag = childTag->NextSiblingElement("tag")) {
            wayTags[childTag->Attribute("k")] = childTag->Attribute("v");
        }
        way["tags"] = wayTags;

        // Add edges to appropriate adjacency maps
        for (size_t i = 0; i < nodeRefs.size() - 1; ++i) {
            string from = nodeRefs[i];
            string to = nodeRefs[i + 1];
            double dist = calculateDistance(
                nodes[from]["lat"].asDouble(), nodes[from]["lon"].asDouble(),
                nodes[to]["lat"].asDouble(), nodes[to]["lon"].asDouble()
            );

            if (isPedestrianAccessible(wayTags)) {
                pedestrianAdjacencyMap[from].push_back({to, dist});
                pedestrianAdjacencyMap[to].push_back({from, dist});
            }
            
            if (isVehicleAccessible(wayTags)) {
                vehicleAdjacencyMap[from].push_back({to, dist});
                vehicleAdjacencyMap[to].push_back({from, dist});
            }
        }

        ways[wayId] = way;
    }
}

// Find shortest path using specified adjacency map
Json::Value findShortestPath(const string& startId, const string& endId, bool isPedestrian) {
    auto& adjacencyMap = isPedestrian ? pedestrianAdjacencyMap : vehicleAdjacencyMap;
    
    // 额外的调试信息
    cout << "Finding path from " << startId << " to " << endId 
         << " (Pedestrian mode: " << isPedestrian << ")" << endl;
    
    // 检查起点终点是否存在于adjacencyMap
    if (adjacencyMap.find(startId) == adjacencyMap.end()) {
        cout << "Start node " << startId << " not found in adjacency map" << endl;
        return Json::Value();
    }
    
    if (adjacencyMap.find(endId) == adjacencyMap.end()) {
        cout << "End node " << endId << " not found in adjacency map" << endl;
        return Json::Value();
    }
    
    // 检查起点和终点的邻接节点
    cout << "Start node " << startId << " neighbors: " << adjacencyMap[startId].size() << endl;
    cout << "End node " << endId << " neighbors: " << adjacencyMap[endId].size() << endl;

    
    map<string, double> distances;
    map<string, string> previous;
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<>> pq;

    for (const auto& node : nodes.getMemberNames()) {
        distances[node] = numeric_limits<double>::infinity();
    }
    distances[startId] = 0;
    pq.push({0, startId});

    while (!pq.empty()) {
        double currentDist = pq.top().first;
        string currentNode = pq.top().second;
        pq.pop();

        if (currentNode == endId) break;

        for (const auto& neighbor : adjacencyMap[currentNode]) {
            string neighborId = neighbor.first;
            double edgeWeight = neighbor.second;
            double newDist = currentDist + edgeWeight;

            if (newDist < distances[neighborId]) {
                distances[neighborId] = newDist;
                previous[neighborId] = currentNode;
                pq.push({newDist, neighborId});
            }
        }
    }

    Json::Value path;
    if (distances[endId] == numeric_limits<double>::infinity()) {
        // No path found
        return path;
    }

    string currentNode = endId;
    while (currentNode != startId) {
        if (previous.find(currentNode) == previous.end()) {
            // No valid path exists
            path.clear();
            return path;
        }
        Json::Value pathNode;
        pathNode["id"] = currentNode;
        pathNode["lat"] = nodes[currentNode]["lat"];
        pathNode["lon"] = nodes[currentNode]["lon"];
        path.append(pathNode);
        currentNode = previous[currentNode];
    }
    
    Json::Value startNode;
    startNode["id"] = startId;
    startNode["lat"] = nodes[startId]["lat"];
    startNode["lon"] = nodes[startId]["lon"];
    path.append(startNode);

    std::reverse(path.begin(), path.end());
    return path;
}

string getShortestPath(const string& startId, const string& endId, bool isPedestrian) {
    Json::StreamWriterBuilder builder;
    Json::Value path = findShortestPath(startId, endId, isPedestrian);
    return Json::writeString(builder, path);
}

string getNodes() {
    Json::StreamWriterBuilder builder;
    return Json::writeString(builder, nodes);
}

string getWays() {
    Json::StreamWriterBuilder builder;
    return Json::writeString(builder, ways);
}

string getBuildings() {
    Json::StreamWriterBuilder builder;
    return Json::writeString(builder, buildings);
}

EMSCRIPTEN_BINDINGS() {
    emscripten::function("load", &load);
    emscripten::function("getNodes", &getNodes);
    emscripten::function("getWays", &getWays);
    emscripten::function("getBuildings", &getBuildings);
    emscripten::function("getShortestPath", &getShortestPath);
}
