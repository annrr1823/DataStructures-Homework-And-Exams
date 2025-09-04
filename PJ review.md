# PJ review

[TOC]

## 实验要求

​	本次项目的目标是将C++ 后端的地图数据处理和路径计算功能与 JavaScript 前端的交互和地图渲染结合实现一个基于地图数据的路径规划系统。

​	我在基本的要求的基础上还另外实现了（1）支持区分行人和车辆模式、（2）支持地图上任一点的选取。最后系统通过读取地图数据绘制了节点、道路信息和建筑物，在用户点击地图上任意两点后基于所选择模式与上述数据计算从起点到终点的最短路径并显示。

​	在初步完成地图路径规划项目以后，课程设置了pj展示。再观看了其他同学的pj演示以后，我发现自己当前所实现的地图还是太简陋了，于是在询问了助教后，我又在原本所完成的基础上通过调用百度地图的api进一步丰富了我的前端实现。同时，由于百度地图的前端已经提供了整个中国的数据，所以升级后的数据量也扩大了。

## 实现思路

​	本次项目的实现思路主要可以分为以下几个关键部分：数据获取、路径计算、前后端交互、前端界面以及性能考虑和最终扩展。

### 数据获取

​	本次项目所需要的地图数据均从OSM（OpenStreetMap）网站获取，以 **XML** 格式的地图数据下载至本地。本次地图数据我选择了我的家（上海宝山）附近一带的地图数据。这些数据包含了地图的节点（如 GPS 坐标）、道路（如连接节点的路径）以及建筑物信息（封闭回路的way）。具体步骤如下：

- **加载地图数据**：通过 `TinyXML` 解析器从 XML 文件中加载地图数据，并提取其中的节点和道路信息。每个节点有一个唯一的 ID，并包含经纬度信息。

- **构建邻接图**：通过解析每条道路的节点连接关系，构建 **邻接图**，该图将每个节点与它相邻的节点连接起来。为了支持行人和车辆两种不同的交通模式，我分别构建了两个邻接图：`pedestrianAdjacencyMap`（行人模式）和 `vehicleAdjacencyMap`（车辆模式）。

  这两种模式的区分在后端依靠`isPedestrianAccessible`函数和`isVehicleAccessible`函数完成。

  ```c++
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
  ```

  ```c++
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
  ```

  其中，关于如何根据道路的节点来判断行人/车辆能否通行，我的主要依据是[OpenStreetMap Wiki上有关于highway的解释](https://wiki.openstreetmap.org/wiki/Key:highway)。

- **道路标签分析**：每条道路都有一组标签，用于标识该道路是否适合行人或车辆通行。例如，如果某条道路标记为 "highway=footway"，则表示该道路适合行人通行。通过分析这些标签，我们可以决定某条道路是否应被添加到行人或车辆的邻接图中。

------

### 路径计算

路径计算是本次项目的核心功能，具体为后端文件中的findShortestPath函数，目标是根据用户选择的起点和终点，计算最短路径。为了实现这一功能，我使用了 **Dijkstra 算法的堆优化方法**。具体细节如下：

- **Dijkstra 算法**：Dijkstra 算法 用于计算从起点到终点的最短路径。为了提高算法的效率，本次项目采用了 **堆优化**（即优先队列）来加速 Dijkstra 算法的执行过程。

  1. **Dijkstra 算法基本思想**

     Dijkstra 算法的核心思想是通过贪心策略，逐步寻找当前节点到源节点的最短路径。在每一次迭代中，它选择当前已知最短路径的节点，并扩展到它的邻居节点，直到遍历完所有可达节点或找到目标节点

     其步骤如下：

     1. 初始化：每个节点的距离设置为正无穷大，起点的距离设置为 0。
     2. 使用优先队列（堆）来存储和处理当前最短路径已知的节点。每次从队列中取出距离最小的节点，更新该节点的邻居的最短距离。
     3. 重复步骤 2，直到队列为空或者目标节点的最短路径被确定。

  2. **堆优化的引入**

     ​	堆是一个可以高效获取最小（或最大）元素的数据结构。在 Dijkstra 算法中，堆用于动态获取当前已知的最短路径节点。本次项目使用 最小堆来存储所有节点和它们的当前最短距离，堆的根节点总是距离最短的节点。每次从堆中弹出距离最短的节点，并更新邻居的最短距离。

     ​	堆优化使得 Dijkstra 算法的时间复杂度从原来的 **O(V²)**（如果用数组存储距离）或者 **O(VE)**（如果使用邻接表）降低到了 **O((V + E) log V)**。

  3. 在本次代码中该算法的**具体实现**如下：

     1. 优先队列（堆）的初始化

        在 Dijkstra 算法中，堆优化的核心是使用 优先队列 来存储和获取当前已知的最短路径节点。这里使用了 C++ 标准库中的 `priority_queue`，它是一个默认的最大堆（大根堆），但通过自定义比较器 `greater<>()`，将其转化为最小堆，从而保证每次弹出的是最短距离的节点。

        ```c++
        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<>> pq;
        ```

        - `pair<double, string>`：`pair` 中的 `double` 表示当前节点的最短距离，`string` 表示节点的 ID。
        - `greater<>`：C++ 中的 `greater` 比较器，用来构建最小堆。默认情况下，`priority_queue` 是一个最大堆（最大元素在堆顶），`greater<>()` 将堆按升序排列，从而使得每次弹出的元素是当前最小的元素。

     2. 初始化距离数组

        在算法开始时，所有节点的最短路径距离初始化为无穷大，表示未知距离。只有起点的距离初始化为 0。然后将起点加入优先队列中。

        ```c++
        map<string, double> distances;
        map<string, string> previous;
        // 初始化所有节点的距离为无穷大
        for (const auto& node : nodes.getMemberNames()) {
            distances[node] = numeric_limits<double>::infinity();
        }
        // 起点的距离设为 0
        distances[startId] = 0;
        // 将起点加入优先队列
        pq.push({0, startId});
        ```

        - `distances`：存储每个节点的当前最短路径。
        - `previous`：用于记录每个节点的前驱节点，以便在找到终点时反向构建路径。
        - `pq.push({0, startId})`：将起点（距离为 0）加入到优先队列中。

     3. 从优先队列中获取最短路径节点

        进入主循环，每次从优先队列中弹出当前最短路径的节点（堆顶节点），然后检查它的邻居节点并进行松弛操作（即更新邻居节点的最短路径）。

        ```c++
        while (!pq.empty()) {
            double currentDist = pq.top().first;  // 当前节点的距离
            string currentNode = pq.top().second; // 当前节点的 ID
            pq.pop(); // 从堆中弹出当前节点
            if (currentNode == endId) break; // 如果已经找到终点，退出循环
            // 遍历当前节点的邻居节点
            for (const auto& neighbor : adjacencyMap[currentNode]) {
                string neighborId = neighbor.first; // 邻居节点的 ID
                double edgeWeight = neighbor.second; // 边的权重（即距离）
                double newDist = currentDist + edgeWeight; // 计算到邻居节点的新距离
        
                if (newDist < distances[neighborId]) {  // 如果发现更短的路径
                    distances[neighborId] = newDist;  // 更新距离
                    previous[neighborId] = currentNode; // 更新前驱节点
                    pq.push({newDist, neighborId});  // 将邻居节点重新加入优先队列
                }
            }
        }
        ```

        - **松弛操作**：对于当前节点的每个邻居，计算通过当前节点到达邻居的距离 `newDist`，如果 `newDist` 小于原有的距离，就更新该邻居的最短距离，并将邻居节点重新加入优先队列。

     4. ------

        具体例子解释：

        <img src="C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241201225559174.png" alt="image-20241201225559174" style="zoom: 50%;" />

        - **初始化**：
        
        ```
        distances:
        A: 0
        B: ∞
        C: ∞
        D: ∞
        E: ∞
        
        priority_queue (堆)：
        [(0, A)]
        ```

        - **从 A 节点开始**：

          当前节点是 **A**，距离是 **0**。

          更新 **A** 的邻居：**B**（2）、**C**（3）、**D**（5）。

          更新队列：`[(2, B), (3, C), (5, D)]`。

        - **从 B 节点开始**（队列中距离最小的是 **B**）：

          当前节点是 **B**，距离是 **2**。

          更新 B的邻居：D（4）和 E（1）。

          **D** 的新距离 = 2 + 4 = 6（原先是 5，但不更新，因为 6 > 5）。

          **E** 的新距离 = 2 + 1 = 3。

          更新队列：`[(3, C), (3, E), (5, D)]`。

        - **从 C 节点开始**（队列中距离最小的是 **C**）：

          当前节点是 **C**，距离是 **3**。

          更新 C 的邻居：D（5）。

          **D** 的新距离 = 3 + 5 = 8（原先是 5，但不更新，因为 8 > 5）。

          队列不变：`[(3, E), (5, D)]`。

        - **从 E 节点开始**（队列中距离最小的是 **E**）：

          当前节点是 **E**，距离是 **3**。

          **E** 没有未处理的邻居，所以队列不变：`[(5, D)]`。

        - **从 D 节点开始**（队列中距离最小的是 **D**）：

          当前节点是 **D**，距离是 **5**。
        
          **D** 没有未处理的邻居，所以队列为空，算法结束。
     
     

- ------

  **路径计算参数**：路径的权重是基于相邻节点之间的距离，本次项目中距离的计算使用 **哈弗辛公式**，这是一个考虑地球曲率的地理距离计算方法。

  Haversine公式的具体形式为：
$$
a = \sin^2\left(\frac{\Delta\phi}{2}\right) + \cos(\phi_1) \cdot \cos(\phi_2) \cdot \sin^2\left(\frac{\Delta\lambda}{2}\right)
$$

$$
c=2⋅atan2( 
  a
  ​
   , 
  1−a
  ​
   )
$$

$$
d=R⋅c
$$

  其中：

  - Δϕ 是两点纬度差（弧度），
  - Δλ是两点经度差（弧度），
  - R 是地球半径（单位为米），
  - d是两点之间的距离。

  具体实现如下：

  ```c++
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
  ```

- ------

  **返回结果**

  一旦算法找到终点节点（或者堆为空时没有找到路径），我们通过 `previous` 数组反向构建从起点到终点的最短路径，并将路径以 JSON 格式传递给前端显示。

  ```c++
  Json::Value path;
  if (distances[endId] == numeric_limits<double>::infinity()) {
      return path; // 如果没有路径，返回空路径
  }
  
  // 从终点反向构建路径
  string currentNode = endId;
  while (currentNode != startId) {
      if (previous.find(currentNode) == previous.end()) {
          path.clear(); // 如果没有有效路径，清空并返回
          return path;
      }
      Json::Value pathNode;
      pathNode["id"] = currentNode;
      pathNode["lat"] = nodes[currentNode]["lat"];
      pathNode["lon"] = nodes[currentNode]["lon"];
      path.append(pathNode);
      currentNode = previous[currentNode];
  }
  
  // 将起点加入路径
  Json::Value startNode;
  startNode["id"] = startId;
  startNode["lat"] = nodes[startId]["lat"];
  startNode["lon"] = nodes[startId]["lon"];
  path.append(startNode);
  
  // 反转路径，因为我们是从终点开始构建的
  std::reverse(path.begin(), path.end());
  return path;
  ```



------

### 前后端交互

​	在本项目中，前端和后端通过 JavaScript 和 WebAssembly (Wasm) 实现交互，前端通过 Emscripten 提供的绑定接口调用后端 C++ 实现的功能，后端则根据请求进行处理，并将结果返回给前端。这部分主体是在示例代码的基础上进行的修改。

​	数据格式主要采用 JSON，后端使用 Json::Value 存储数据，并通过 `Json::StreamWriterBuilder` 将数据转化为字符串发送给前端。前端通过 `JSON.parse()` 解析字符串，并在页面中显示。

- **数据请求与加载**

  - 前端启动时，通过调用 `Module.load()` 函数请求加载后端数据。`load()` 函数会从 XML 文件（中解析节点（`node`）和道路（`way`）信息，存储在后端的 JSON 数据结构中。

  - 加载完成后，前端通过调用 `Module.getNodes()`, `Module.getWays()` 和 `Module.getBuildings()` 函数来获取地图中的节点、道路和建筑物信息，并用这些数据进行图形的绘制。

- **数据结构与交互**

  前端和后端之间使用 JSON 格式 作为数据交换格式，后端将解析后的数据通过 `Json::Value` 类型存储，在调用接口时，前端通过 Emscripten 的绑定机制，将这些数据转化为 JSON 字符串 发送给前端，前端再解析这些 JSON 字符串并进行相应的展示和操作。

- **后端获取节点数据：**

  ```c++
  string getNodes() {
      Json::StreamWriterBuilder builder;
      return Json::writeString(builder, nodes);
  }
  ```


  - **前端处理节点数据：**

    ```javascript
    var nodesJson = Module.getNodes();
    var nodesData = JSON.parse(nodesJson);
    ```

    解析返回的 JSON 数据，并将节点信息绘制在地图上。


- **路径规划与计算**

  - 前端调用后端提供的 `getShortestPath()` 函数，传入起点、终点以及行驶模式（步行或驾车）等参数。

    ```javascript
    var pathJson = Module.getShortestPath(startId, endId, isPedestrianMode);
    var pathData = JSON.parse(pathJson);
    ```

  - 后端使用 Dijkstra 算法 根据图的邻接表计算最短路径，并将结果（路径）返回给前端。

    ```c++
    string getShortestPath(const string& startId, const string& endId, bool isPedestrian) {
        Json::StreamWriterBuilder builder;
        Json::Value path = findShortestPath(startId, endId, isPedestrian);
        return Json::writeString(builder, path);
    }
    ```



------


### 前端界面

本次项目的前端界面设计实现了地图浏览、路径规划、模式选择等功能。主要包括以下几个模块：

- **地图显示模块**：用于展示城市地图，并在上面标出起点、终点及路径。

  地图区域是界面的核心部分，占据整个页面的主要空间。地图区域支持：

  - **交互式缩放和拖动**：用户可以通过鼠标滚轮、点击和拖动地图来查看不同区域。
  - **节点标记**：在地图上，用户可以自由选择的起点和终点。若用户选择的点不在所提供的点上，则系统会自动将该点并到最近的一个节点上，然后规划路径。
  - **路径展示**：计算出的最短路径将通过绿色路线在地图上展示。
  - **模式切换**：允许用户在步行模式和驾车模式之间进行切换。在界面顶部放置一个明显的按钮，允许用户选择步行模式或驾车模式。按钮切换后，界面会自动更新路径规划的规则。

- **信息展示模块**：显示路径信息、计算结果等。

  信息展示模块位于页面的右下部，用于显示当前路径的相关信息。

  - **起点与终点的详细信息**：坐标、序号等。

  - **路径信息**：包括总路径规划花费的时间。

  - **错误提示**：如果无法找到路径，系统会弹出信息框提示用户“没有可达路径”。

    

------


### 性能考虑

1. **时间复杂度分析**

   本次最短路径规划采取的关键算法为Dijkstra 算法的堆优化版本。

   Dijkstra 算法的时间复杂度主要由两部分组成：

   - 邻接表遍历：对于每个节点，其所有相邻节点都需要被检查，因此在最坏情况下，遍历的时间复杂度为 O(E)，其中 E 是图中边的数量。
   - 优先队列操作：Dijkstra 算法使用优先队列来选择最短路径节点，优先队列的插入和删除操作时间复杂度为 O(log V)，其中 V 是节点数。因此，Dijkstra 算法的总体时间复杂度为 O((V + E) * log V)，适用于稀疏图。

2. **空间复杂度分析**

   1. 本次存储节点和边主要采用的方法为邻接表存储（`map<string, vector<pair<string, double>>>`）。

      邻接表的存储复杂度为 O(V + E)，其中 V 是节点数，E 是边数。相比于邻接表的 O(V²) 存储，邻接表在处理稀疏图时具有更高的存储效率。

   2. 最短路径辅助存储使用了：

      - `distances` 数组：存储每个节点到起点的最短距离。需要 O(V) 空间。
      - `previous` 数组：存储每个节点的前驱节点，用于重建最短路径。需要 O(V) 空间。

   3. Dijkstra 算法使用一个优先队列来处理当前未访问节点，并按最短距离排序。队列中的元素个数最多为 V，因此需要 O(V) 空间。

   总体的空间复杂度为 O(V + E)。

3. ------

   **性能瓶颈与优化**

   ​	由于本次项目老师在课上要求使用的规划方法为Dijkstra算法的堆优化版本，故本次项目的主体即采用此算法，但是实际上还可以进一步进行优化。同时，受限于我自己电脑的性能以及代码的能力，很多地方的性能都并没有达到充分的快，故在此部分我将对本次项目中的性能瓶颈进行分析，并且尝试对其优化。
   
   ​	随着节点和边数的增加，图的规模将直接影响算法的执行时间和空间需求。对于非常大的图，Dijkstra 算法的性能会受到影响。但是，由于OSM网站对于下载量的限制以及我自己电脑CPU性能的限制（在尝试下载更大的地图数据后运行程序对于内存不足的报错），采用Dijkstra来应对我本次项目中较小的数据量仍然是可行的。然而，在现实情况下，设计足以应对大规模数据的算法仍然是十分必要的，故以下我将讨论几种设想的解决办法以及具体实现。

------


#### 采用 **Fibonacci 堆**

​	通过采用 **Fibonacci 堆**（`FibonacciHeap`）替代堆实现的优先队列（`priority_queue`），可以在 Dijkstra 算法中更加高效地选择下一个最短路径节点。

​	斐波那契堆是基于斐波那契数列（Fibonacci sequence）的一种堆结构，它由一个由树组成的集合（树的根节点）和一些支持的操作组成。与其他堆不同的是，斐波那契堆中的树是无序的，而且树的结构是通过懒惰合并策略进行延迟调整的，从而降低了时间复杂度。例如下图：

<img src="https://images0.cnblogs.com/i/497634/201404/111642221538159.jpg" alt="img" style="zoom: 50%;" />

斐波那契堆的特点：

- **松散结构**：斐波那契堆由一组根节点树组成，并且每棵树的结构并不严格。树的数量可以很多，树的形状不完全平衡，因此操作上可以灵活处理。
- **延迟合并**：与其他堆相比，斐波那契堆更注重“懒”更新，很多操作并不是立刻进行，而是推迟到必须进行的时候才去做。这种延迟策略使得某些操作的平均时间复杂度降低。

本次所需要的斐波那契堆的操作：

1. **插入（Insert）**：插入一个新的元素时，首先创建一个包含该元素的新树并将其添加到根节点集合中。这个操作的时间复杂度是 **O(1)**。
2. **最小元素查找（Find-Min）**：找到堆中最小的元素（即最小根节点）。由于堆是由一组树组成的，每次查询时直接检查根节点即可。时间复杂度是 **O(1)**。
3. **删除最小元素（Delete-Min）**：删除堆中的最小元素，并将其所有子节点加入堆中。此操作的时间复杂度为 **O(log n)**。这是因为需要重新合并堆中的树，确保堆的性质。

​	该部分代码我通过参考网上的资料另外实现了，和本次项目主体代码的唯一区分就是Dijkstra算法中的优先队列由自己实现的斐波那契堆替代了。

最后效果示例如下，由于整体数据量较小，故性能提升的差异并不大。

<img src="C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241203101528117.png" alt="image-20241203101528117" style="zoom:25%;" />

本次优化实现斐波那契堆的关键代码如下：

```c++
class FibNode
{
public:
    int key;            // 关键字(键值)
    int degree;         // 度数
    std::string name;   // 节点名称
    FibNode* left;      // 左兄弟
    FibNode* right;     // 右兄弟
    FibNode* child;     // 第一个孩子节点
    FibNode* parent;    // 父节点
    bool marked;        // 是否被删除第一个孩子

    FibNode(int key, std::string n)
    {
        this->key = key;
        this->degree = 0;
        this->name = n;
        this->marked = false;
        this->left = this;
        this->right = this;
        this->parent = nullptr;
        this->child = nullptr;
    }
};

class FibHeap {
private:
    int keyNum;         // Total number of nodes in the heap
    FibNode* min;       // Pointer to the minimum node (root of the heap)

public:
    // Constructor initializing keyNum and min
    FibHeap() : keyNum(0), min(nullptr) {}
    
    public: bool empty()
    {
    	return !this->keyNum;
	}

    // Method to remove a node from a doubly linked list
    private: void removeNode(FibNode* node) {
        node->left->right = node->right;
        node->right->left = node->left;
    }

    // Method to add a node to the root list
    private: void addNode(FibNode* node, FibNode* root) {
        node->left = root->left;
        root->left->right = node;
        node->right = root;
        root->left = node;
    }

    // Method to insert a node into the Fibonacci heap
    private: void insert(FibNode* node) {
        if (keyNum == 0)
            min = node;
        else {
            addNode(node, min);
            if (node->key < min->key)
                min = node;
        }
        keyNum++;
    }

    // Method to insert a node with a specific key and name
    public: void insert(int key, std::string n) {
        FibNode* node = new FibNode(key, n);
        if (node == nullptr) return;
        insert(node);
    }

    // Method to concatenate two doubly linked lists
    private: void catList(FibNode* a, FibNode* b) {
        FibNode* tmp = a->right;
        a->right = b->right;
        b->right->left = a;
        b->right = tmp;
        tmp->left = b;
    }

    // Method to extract the minimum node from the heap
    private: FibNode* extractMin() {
        FibNode* p = min;
        if (p == p->right)
            min = nullptr;
        else {
            removeNode(p);
            min = p->right;
        }
        p->left = p->right = p;
        return p;
    }

    // Method to link two nodes in the heap
    private: void link(FibNode* node, FibNode* root) {
        removeNode(node);
        if (root->child == nullptr)
            root->child = node;
        else
            addNode(node, root->child);

        node->parent = root;
        root->degree++;
        node->marked = false;
    }

    // Method to consolidate the heap and merge trees of the same degree
    private: void consolidate() {
	    int maxDegree = (int)std::floor(std::log(keyNum) / std::log(2.0));
	    int D = maxDegree + 1;
	    std::vector<FibNode*> cons(D + 1, nullptr); // Vector initialized with nullptr
	
	    while (min != nullptr) {
	        FibNode* x = extractMin();
	        int d = x->degree;
	        while (cons[d] != nullptr) {
	            FibNode* y = cons[d];
	            if (x->key > y->key) {
	                std::swap(x, y);
	            }
	            link(y, x);
	            cons[d] = nullptr;
	            d++;
	        }
	        cons[d] = x;
	    }
	
	    min = nullptr;
	    for (int i = 0; i < D; i++) {
	        if (cons[i] != nullptr) {
	            if (min == nullptr)
	                min = cons[i];
	            else {
	                addNode(cons[i], min);
	                if (cons[i]->key < min->key)
	                    min = cons[i];
	            }
	        }
	    }
	}


    // Method to remove the minimum node and return its value
    public: std::pair<double, std::string> removeMin() {
        if (min == nullptr)
            return std::pair<double, std::string>(-1, "");

        FibNode* m = min;
        double tmpkey = m->key;
        std::string tmpn = m->name;

        while (m->child != nullptr) {
            FibNode* child = m->child;
            removeNode(child);
            if (child->right == child)
                m->child = nullptr;
            else
                m->child = child->right;

            addNode(child, min);
            child->parent = nullptr;
        }

        removeNode(m);
        if (m->right == m)
            min = nullptr;
        else {
            min = m->right;
            consolidate();
        }
        keyNum--;

        return std::pair<double, std::string>(tmpkey, tmpn);
    }

    // Method to get the minimum key in the heap
    public: int minimum() {
        if (min == nullptr)
            return -1;
        return min->key;
    }

    // Method to destroy the heap
    private: void destroyNode(FibNode* node) {
        if (node == nullptr) return;

        FibNode* start = node;
        do {
            destroyNode(node->child);
            node = node->right;
            node->left = nullptr;
        } while (node != start);
    }

    // Destroy the whole heap
    public: void destroy() {
        destroyNode(min);
    }
};
```

------

#### 采用 **A\* 算法**

​	通过采用 **A\* 算法**（基于启发式搜索）替代 Dijkstra 算法，尤其是在大规模图中，通过启发式函数可以减少不必要的路径搜索，可以大大提高最短路径搜索的时间效率。

​	A*（A-star）算法是一种用于图形搜索和路径规划的启发式搜索算法，它能够高效地找到从起点到终点的最短路径。它结合了 **广度优先搜索**（BFS）和 **贪婪最佳优先搜索**（Greedy Best-First-Search）的优点，通过合理的启发式函数来引导搜索，避免了盲目遍历。 这个算法的核心思想是，每次选择一个“最有前途”的节点进行扩展，即优先选择估计总代价最小的节点。

​	其**核心概念**有：

- 实际代价（`gScore[n]`）:

  - 从起点到当前节点 `n` 的最短已知路径代价。
  - 初始值为无穷大（`Infinity`），起点的 `gScore[start]` 设置为 0。

- 估算代价（`h(n)`）:

  - 启发式函数，估算从当前节点 `n` 到目标节点的代价。
  - 常见的 `h(n)` 是欧几里得距离或曼哈顿距离。

- 总代价（`fScore[n]`）:

  - 表示从起点经过当前节点到终点的总代价估算。A*算法通过不断扩展最小 **f(n)** 的节点，最终找到从起点到终点的最优路径。
    $$
    f(n)=gScore[n]+h(n)
    $$

  - `fScore[start]` 初始化为 `h(start)`。

- 开放集（`openSet`）:

  - 存储所有待处理的节点，优先处理总代价估算最小的节点。

  - 实现时通常用最小堆（min-heap）或优先队列。本次用`priority_queue`实现。

    

  其**大致流程**为：

  1. 初始化

     - 定义 `openSet`，只包含起点 `start`。
     - 定义 `cameFrom`，记录每个节点的前驱节点，初始化为空。
     - 初始化 `gScore`，起点的 `gScore[start] = 0`，其他节点为无穷大。
     - 初始化 `fScore`，起点的 `fScore[start] = h(start)`，其他节点为无穷大。

  2. 主循环

     当 `openSet` 不为空时，执行以下操作：

     a. 从开放集中选择总代价最小的节点

     - 从 `openSet` 中取出 `fScore` 值最小的节点，称为当前节点 `current`。

     - 如果 `current`

        是目标节点 `goal`：

       - 调用 `reconstruct_path(cameFrom, current)` 返回路径。
       - 算法结束。

     b. 从开放集中移除当前节点

     - 当前节点 `current` 处理完毕，从 `openSet` 中移除。

     c. 遍历当前节点的所有邻居

     对于每个邻居 `neighbor`：

     1. 计算从起点到邻居 `neighbor` 的临时实际代价：
        $$
        tentative=gScore[current]+d(current,neighbor)
        $$
        

        - `d(current, neighbor)` 是当前节点和邻居节点之间边的权重。

     2. 比较 `tentative_gScore` 和当前记录的 `gScore[neighbor]`：

        - 如果 
          $$
          tentative < gScore[neighbor]
          $$

          - 更新 `gScore[neighbor]` 为 `tentative_gScore`。

          - 更新 `fScore[neighbor]` 为：
            $$
            fScore[neighbor]=gScore[neighbor]+h(neighbor)
            $$

          - 更新 `cameFrom[neighbor]`，记录邻居的前驱节点为 `current`。

     3. 如果邻居 `neighbor` 不在 `openSet` 中：

        - 将邻居加入 `openSet`。

  3. 搜索失败

     如果 `openSet` 为空且未找到路径：

     - 返回失败（`failure`）。

  4. 路径重建

     当找到目标节点后，通过 `cameFrom` 记录的前驱节点回溯，重建从起点到终点的路径。

A*算法的伪代码：

```matlab
function reconstruct_path(cameFrom, current)
    total_path := {current}
    while current in cameFrom.Keys:
        current := cameFrom[current]
        total_path.prepend(current)
    return total_path

// A* finds a path from start to goal.
// h is the heuristic function. h(n) estimates the cost to reach goal from node n.
function A_Star(start, goal, h)
    // The set of discovered nodes that may need to be (re-)expanded.
    // Initially, only the start node is known.
    // This is usually implemented as a min-heap or priority queue rather than a hash-set.
    openSet := {start}

    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from the start
    // to n currently known.
    cameFrom := an empty map

    // For node n, gScore[n] is the currently known cost of the cheapest path from start to n.
    gScore := map with default value of Infinity
    gScore[start] := 0

    // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current best guess as to
    // how cheap a path could be from start to finish if it goes through n.
    fScore := map with default value of Infinity
    fScore[start] := h(start)

    while openSet is not empty
        // This operation can occur in O(Log(N)) time if openSet is a min-heap or a priority queue
        current := the node in openSet having the lowest fScore[] value
        if current = goal
            return reconstruct_path(cameFrom, current)

        openSet.Remove(current)
        for each neighbor of current
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            tentative_gScore := gScore[current] + d(current, neighbor)
            if tentative_gScore < gScore[neighbor]
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                fScore[neighbor] := tentative_gScore + h(neighbor)
                if neighbor not in openSet
                    openSet.add(neighbor)

    // Open set is empty but goal was never reached
    return failure
```

------

**具体例子解释：**

<img src="C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241203160746589.png" alt="image-20241203160746589" style="zoom: 67%;" />

节点的坐标如下（用于计算启发式距离）：

```
A: (0, 0), B: (1, 0), C: (2, 0), D: (2, 1), E: (3, 1)
```

我们希望从节点 `A` 找到节点 `E` 的最短路径。

1. 初始化

- 起点 `A`：

  - $$
    gScore[A]=0
    $$

    起点到自身的代价为 0

  - 启发式距离（为易于理解使用欧几里得距离作为启发式函数）：
    $$
    h(A) = \sqrt{(3 - 0)^2 + (1 - 0)^2} \approx 3.16
    $$

  - $$
    fScore[A] = gScore[A] + h(A) = 0 + 3.16 = 3.16
    $$

- 将 A 加入 `openSet`：

  ```
  openSet = { (3.16, "A") }
  ```

2. 第一次迭代

- 选择当前节点 `A`（`fScore` 最小）。

- 扩展邻居：

  - 邻居 B：权重 1

    - $$
      tentativeGScore[B] = gScore[A] + d(A, B) = 0 + 1 = 1
      $$

    - 启发式距离：
      $$
      h(B) = \sqrt{(3 - 1)^2 + (1 - 0)^2} \approx 2.24
      $$

    - $$
      fScore[B] = gScore[B] + h(B) = 1 + 2.24 = 3.24
      $$

    - 更新 `gScore` 和 `fScore`，并将 B 加入 `openSet`。

  - 邻居 C：权重 3

    - $$
      tentativeGScore[C] = gScore[A] + d(A, C) = 0 + 3 = 3
      $$

    - 启发式距离：
      $$
      h(C) = \sqrt{(3 - 2)^2 + (1 - 0)^2} = 1.41
      $$

    - $$
      fScore[C] = gScore[C] + h(C) = 3 + 1.41 = 4.41
      $$

    - 更新 `gScore` 和 `fScore`，并将 C 加入 `openSet`。

- 更新 `openSet`：

  ```
  openSet = { (3.24, "B"), (4.41, "C") }
  ```

- 将 A 加入 `closedSet`。

3. 第二次迭代

- 选择当前节点 `B`（`fScore` 最小）。

- 扩展邻居：

  - 邻居 C：权重 1

    - $$
      tentativeGScore[C] = gScore[B] + d(B, C) = 1 + 1 = 2
      $$

    - $$
      tentativeGScore[C] < gScore[C]
      $$

      ，更新：

      - $$
        gScore[C]=2
        $$

      - $$
        fScore[C]=gScore[C]+h(C)=2+1.41=3.41
        $$

  - 邻居 D：权重 2

    - $$
      tentativeGScore[D]=gScore[B]+d(B,D)=1+2=3
      $$

    - 启发式距离：
      $$
      h(D) = \sqrt{(3 - 2)^2 + (1 - 1)^2} = 1
      $$

    - $$
      fScore[D]=gScore[D]+h(D)=3+1=4
      $$

    - 更新 `gScore` 和 `fScore`，并将 D加入 `openSet`。

- 更新 `openSet`：

  ```
  openSet = { (3.41, "C"), (4, "D") }
  ```

- 将 B 加入 `closedSet`。

4. 第三次迭代

- 选择当前节点 `C`。

- 扩展邻居：

  - 邻居 D：权重 1

    - $$
      tentativeGScore[D]=gScore[C]+d(C,D)=2+1=3
      $$

    - $$
      tentativeGScore[D]>=gScore[D]
      $$

      跳过。

  - 邻居 E：权重 5

    - $$
      tentativeGScore[E]=gScore[C]+d(C,E)=2+5=7
      $$

    - 启发式距离： 
      $$
      h(E) = \sqrt{(3 - 3)^2 + (1 - 1)^2} = 0
      $$

    - $$
      fScore[E]=gScore[E]+h(E)=7+0=7
      $$

    - 更新 `gScore` 和 `fScore`，并将 E加入 `openSet`。

- 更新 `openSet`：

  ```
  openSet = { (4, "D"), (7, "E") }
  ```

- 将 C 加入 `closedSet`。

5. 第四次迭代

- 选择当前节点 `D`。

- 扩展邻居：

  - 邻居 E：权重 2

    - $$
      tentativeGScore[E]=gScore[D]+d(D,E)=3+2=5
      $$

    - $$
      tentativeGScore[E]<gScore[E]
      $$

      ，更新：

      - $$
        gScore[E]=5
        $$

      - $$
        fScore[E]=gScore[E]+h(E)=5+0=5
        $$

- 更新 `openSet`：

  ```
  openSet = { (5, "E") }
  ```

- 将 D 加入 `closedSet`。

6. 第五次迭代

- 选择当前节点 `E`。

- 发现目标节点，算法结束。

- 通过 `previous` 字典回溯路径：

  最终路径为：

  ```
  A -> B -> D -> E
  ```

  总代价为 1+2+2=5

------

**与Dijkstra算法的比较**

- Dijkstra算法计算源点到其他所有点的最短路径长度，A*关注点到点的最短路径(包括具体路径)。
- Dijkstra算法的实质是广度优先搜索，是一种发散式的搜索，所以空间复杂度和时间复杂度都比较高。对路径上的当前点，A*算法不但记录其到源点的代价，还计算当前点到目标点的期望代价，是一种启发式算法，也可以认为是一种深度优先的算法。
- 由第一点，当目标点很多时，A *算法会带入大量重复数据和复杂的估价函数，所以如果对于许多个目标点且不要求获得具体路径而只比较路径长度时，Dijkstra算法会成为更好的选择。但是本次项目中只有一个目标点，故A *算法的效率会更高。



​	该部分代码我同样通过参考网上的资料另外实现了，和本次项目主体代码的区分体现于原本的`findShortedPath`函数被`findShortestPathAStar`函数所替代，其余部分保持不变，同时A*算法中的优先队列依旧采用的是STL库中堆实现的优先队列`priority_queue`。

最后效果示例如下，相较于原本的堆优化的Dijkstra算法以及采用Fibonacci堆的Dijkstra算法查找的时间效率有了非常显著的提升。

<img src="C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241203142203267.png" alt="image-20241203142203267" style="zoom:25%;" />

本次实现A*算法的函数代码如下：

```c++
Json::Value findShortestPathAStar(const string& startId, const string& endId, bool isPedestrian) {
    auto& adjacencyMap = isPedestrian ? pedestrianAdjacencyMap : vehicleAdjacencyMap;
    
    // 使用 unordered_set 替代 set
    unordered_set<string> closedSet;
    
    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<>> openSet;
    
    map<string, double> gScore; // 从起点到当前节点的实际代价
    map<string, double> fScore; // 估算总代价
    map<string, string> previous;

    // 初始化起点
    gScore[startId] = 0;
    fScore[startId] = calculateDistance(
        nodes[startId]["lat"].asDouble(), 
        nodes[startId]["lon"].asDouble(),
        nodes[endId]["lat"].asDouble(), 
        nodes[endId]["lon"].asDouble()
    );
    openSet.push({fScore[startId], startId});

    while (!openSet.empty()) {
        string currentNode = openSet.top().second;
        openSet.pop();

        if (currentNode == endId) {
            // 重建路径
            Json::Value path;
            while (currentNode != startId) {
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

        // 注意：使用 unordered_set 时，判断是否存在的方法略有不同
        closedSet.insert(currentNode);

        for (const auto& neighbor : adjacencyMap[currentNode]) {
            string neighborId = neighbor.first;
            double edgeWeight = neighbor.second;

            // 使用 count() 判断是否在 closedSet 中
            if (closedSet.count(neighborId) > 0) continue;

            double tentativeGScore = gScore[currentNode] + edgeWeight;

            if (gScore.count(neighborId) == 0 || tentativeGScore < gScore[neighborId]) {
                // 找到更好的路径
                previous[neighborId] = currentNode;
                gScore[neighborId] = tentativeGScore;
                
                // 估算到终点的启发式距离
                double heuristic = calculateDistance(
                    nodes[neighborId]["lat"].asDouble(), 
                    nodes[neighborId]["lon"].asDouble(),
                    nodes[endId]["lat"].asDouble(), 
                    nodes[endId]["lon"].asDouble()
                );
                
                fScore[neighborId] = gScore[neighborId] + heuristic;
                openSet.push({fScore[neighborId], neighborId});
            }
        }
    }

    // 没有找到路径
    return Json::Value();
}
```

------

#### 多线程和并行计算

​	本次项目当我尝试扩大地图数据时收到了对于cpu容量不足的报错，由于我代码水平有限，故此处只进行理论上的分析，不给出实际代码实现。

​	为了提升路径规划的效率，特别是在处理较大地图数据集时，可以引入了多线程和并行计算的优化策略。

1. 在数据加载阶段，使用线程池对节点和道路数据的解析进行分块处理

   大致思路：

   - 将地图的 XML 数据按区域或文件大小分块，每个线程负责解析一个块。

   - 采用线程池（`std::thread` 和 `std::async`）管理多线程任务，避免线程频繁创建和销毁带来的开销。

   ```c++
   void loadMapData(const std::string& mapFile) {
       // 读取 XML 数据并分块
       auto blocks = divideIntoBlocks(mapFile);
       // 创建线程池并分配任务
       std::vector<std::future<void>> tasks;
       for (auto& block : blocks) {
           tasks.emplace_back(std::async(std::launch::async, [this, &block]() {
               parseBlock(block);
           }));
       }
       // 等待所有线程完成
       for (auto& task : tasks) {
           task.get();
       }
   }
   ```

2. 两种邻接图（`pedestrianAdjacencyMap` 和 `vehicleAdjacencyMap`）采用多线程分别处理

   例如可以将两种邻接表的构建函数封装为一个，然后采用多线程

   ```c++
   void constructAdjacencyMaps() {
       std::thread pedestrianThread(&MapData::constructPedestrianAdjacencyMap, this);
       std::thread vehicleThread(&MapData::constructVehicleAdjacencyMap, this);
       pedestrianThread.join();
       vehicleThread.join();
   }
   void constructPedestrianAdjacencyMap() {
       // 遍历节点和道路，根据行人模式规则构建邻接表
   }
   void constructVehicleAdjacencyMap() {
       // 遍历节点和道路，根据车辆模式规则构建邻接表
   }
   ```

3. 对于起点的邻居节点，分配多个线程分别计算从这些邻居到目标节点的最短路径，最终合并结果

   在路径计算中，使用了堆优化的 Dijkstra 算法。如果节点数量巨大，可以利用多源路径并行计算的思想，对于起点的邻居节点，分配多个线程分别计算从这些邻居到目标节点的最短路径，最终合并结果。

   ```c++
   std::vector<std::future<void>> tasks;
   void parallelDijkstra(const std::string& startId, const std::string& endId) {
       auto neighbors = adjacencyMap[startId];
       for (const auto& neighbor : neighbors) {
           tasks.emplace_back(std::async(std::launch::async, [this, &neighbor, endId]() {
               calculatePartialPath(neighbor.first, endId);
           }));
       }
       for (auto& task : tasks) {
           task.get();
       }
   }
   void calculatePartialPath(const std::string& startId, const std::string& endId) {
       // 使用 Dijkstra 算法计算从 startId 到 endId 的路径
       // 将结果存入线程安全的全局数据结构中
   }
   ```



### 最终扩展

​	在初步完成地图路径规划项目以后，课程设置了pj展示。在观看了其他同学的pj演示以后，我发现自己当前所实现的地图还是太简陋了，只有点和线，没有详细的地点以及道路表示。于是在询问了助教后，我又在原本所完成的基础上通过调用百度地图的api进一步丰富了我的前端实现。同时，由于百度地图的前端已经提供了整个中国的数据，所以升级后的数据量也扩大了。

​	由于修改升级前端代码时已经处在期末季，故完成的较为简陋，完整代码见关键代码部分，以下仅列举关键部分。

**`<head>`部分**：

- 引入了百度地图的SDK脚本。通过`<script>`标签加载百度地图API。

  此处的API key需要自己在百度的开发者平台上申请。同时，要注意应用类别需要选择浏览器端，因为最后是要在网页上打开的。一开始我选择的时服务端，无法使用API。申请好以后界面如下：

  ![image-20241219112318801](C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241219112318801.png)

- 设置了页面的基本样式，包含了页面布局、控件的样式、地图的容器等。

**`<body>`部分**：

- **地图容器**（`#map-container`）：地图的显示区域。我创建了一个百度地图实例，并设置地图的中心为复旦大学位置（经纬度：`121.503584, 31.296426`）并设置了缩放级别为15。这里我一开始是直接使用的度数为单位的经纬度，发现展示的中心并不是复旦，于是重新在网上查询了复旦经纬度的小数形式。
- **控件区**（`.controls`）：包括了两个按钮来切换模式（行走和驾驶模式）。这两个按钮和之前实现的是一样的。
- **信息显示区**（`.info-display`）：用于显示所选坐标点、路径计算时间和图例（地图上不同颜色的标记含义）。这部分也和之前实现的是一样的。
- **路径计算**（`calculateRoute`）：根据当前的模式（步行或驾驶）来计算从起点到终点的路径。路径计算的时间会被记录并显示在页面上。



## 实验结果

如下图：

- 初始界面

<img src="C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241202190005298.png" alt="image-20241202190005298" style="zoom: 25%;" />

- 随机点击一个点

<img src="C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241202190027286.png" alt="image-20241202190027286" style="zoom: 25%;" />

- 再随机点击一个点，得到最短路径

<img src="C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241202190046238.png" alt="image-20241202190046238" style="zoom: 25%;" />

最终前端升级后：

由于数据量明显增大，我这里路径计算的时间明显从几十毫秒增加到了几百毫秒。尤其是但我把地图的缩放级别调低时，两个距离远的路径规划的时间甚至达到了几千毫秒。

![image-20241219114411516](C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241219114411516.png)

![image-20241219114545096](C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241219114545096.png)



## 关键代码

由于本次项目文件较多，故此处只附上后端`test.cpp`文件和前端`index.html`文件

### 后端文件：`test.cpp`

```c++
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
```



### 前端文件：`index.html`

```javascript
<!doctype html>
<html>
<head>
    <style>
        .controls {
            position: absolute;
            top: 10px;
            right: 10px;
            background: rgba(255, 255, 255, 0.8);
            padding: 12px;
            border-radius: 5px;
            border: 1px solid #ccc;
        }
        .mode-switch {
            display: flex;
            gap: 10px;
            margin-bottom: 10px;
        }
        .mode-btn {
            padding: 8px 16px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-weight: bold;
        }
        .mode-btn.active {
            background: #4CAF50;
            color: white;
        }
        .mode-btn:not(.active) {
            background: #f0f0f0;
            color: #666;
        }
        .info-display {
            position: absolute;
            bottom: 10px;
            right: 10px;
            background: rgba(255, 255, 255, 0.8);
            padding: 12px;
            border-radius: 5px;
            border: 1px solid #ccc;
            font-size: 14px;
        }
        .legend {
            margin-top: 10px;
            font-size: 12px;
        }
        .legend-item {
            display: flex;
            align-items: center;
            margin-bottom: 4px;
        }
        .legend-color {
            width: 20px;
            height: 3px;
            margin-right: 8px;
        }
    </style>
</head>
<body>
    <canvas id="test" width="1600" height="900" style="border: 1px solid black;"></canvas>

    <div class="controls">
        <div class="mode-switch">
            <button class="mode-btn active" id="pedestrianMode">walking</button>
            <button class="mode-btn" id="vehicleMode">driving</button>
        </div>
        <div>click_please</div>
    </div>

    <div class="info-display">
        <div id="coordinatesDisplay">Selected Nodes: None</div>
        <div id="timingDisplay" style="margin-top: 4px; color: #666;">Path computation time: -- ms</div>
        <div class="legend">
            <div class="legend-item">
                <div class="legend-color" style="background: blue;"></div>
                <span>points</span>
            </div>
            <div class="legend-item">
                <div class="legend-color" style="background: red;"></div>
                <span>choosen</span>
            </div>
            <div class="legend-item">
                <div class="legend-color" style="background: #4CAF50;"></div>
                <span>plan_route</span>
            </div>
        </div>
    </div>

    <script>
        var nodes = [];
        var selectedNodes = [];
        var isPedestrianMode = true;

        function switchMode(mode) {
            isPedestrianMode = mode === 'pedestrian';
            document.getElementById('pedestrianMode').classList.toggle('active', isPedestrianMode);
            document.getElementById('vehicleMode').classList.toggle('active', !isPedestrianMode);
            
            // 清除已选择的点和路线
            resetSelection();
        }

        function resetSelection() {
            selectedNodes = [];
            updateCoordinatesDisplay();
            redrawMap();
        }

        function redrawMap() {
            let test = document.getElementById("test");
            let ctx = test.getContext("2d");
            ctx.clearRect(0, 0, test.width, test.height);

            // 重新绘制建筑物
            let buildingsJson = Module.getBuildings();
            let buildingsData = JSON.parse(buildingsJson);
            drawBuildings(buildingsData);

            // 重新绘制路网
            let waysJson = Module.getWays();
            let waysData = JSON.parse(waysJson);
            for (let data in waysData) {
                draw(waysData[data]);
            }
        }

        var scale = function (point) {
            return [Math.round((point.lon - 121.438) * 15000), Math.round((point.lat - 31.366) * 14500)];
        }

        var nodesInWays = new Set(); // 记录在道路中出现的节点

        var draw = function (data) {
            let points = data.nodes;
            let tags = data.tags;

            let test = document.getElementById("test");
            let way = test.getContext("2d");
            way.lineWidth = 0.5;
            way.strokeStyle = "#000000";
            way.beginPath();

            // 记录道路中的节点
            for (let i = 0; i < points.length; i++) {
                nodesInWays.add(points[i].id);
            }

            for (let i = 0; i < points.length; i++) {
                let point = scale(points[i]);
                
                // 只添加在道路中的节点
                let nodeExists = nodes.some(node => node.id === points[i].id);
                if (!nodeExists) {
                    nodes.push({x: point[0], y: point[1], id: points[i].id});
                }
                
                way.moveTo(point[0], point[1]);

                way.beginPath();
                way.arc(point[0], point[1], 3, 0, 2 * Math.PI);
                way.fillStyle = "blue";
                way.fill();
                way.closePath();
            }

            way.beginPath();
            let firstPoint = scale(points[0]);
            way.moveTo(firstPoint[0], firstPoint[1]);
            for (let i = 1; i < points.length; i++) {
                let point = scale(points[i]);
                way.lineTo(point[0], point[1]);
            }
            way.closePath();
            way.stroke();
        }

        

        var drawSelectedPoint = function (x, y) {
            let test = document.getElementById("test");
            let ctx = test.getContext("2d");

            ctx.beginPath();
            ctx.arc(x, y, 3, 0, 2 * Math.PI);
            ctx.fillStyle = "red";
            ctx.fill();
            ctx.closePath();
        }

        var drawBuildings = function(data) {
            let test = document.getElementById("test");
            let ctx = test.getContext("2d");

            ctx.lineWidth = 0.5;
            ctx.strokeStyle = "rgba(255, 255, 0, 0.3)";
            ctx.fillStyle = "rgba(255, 255, 0, 0.1)";

            for (let buildingId in data) {
                let building = data[buildingId];
                let points = building.nodes;

                if (points.length > 1) {
                    ctx.beginPath();
                    let firstPoint = scale(points[0]);
                    ctx.moveTo(firstPoint[0], firstPoint[1]);

                    for (let i = 1; i < points.length; i++) {
                        let point = scale(points[i]);
                        ctx.lineTo(point[0], point[1]);
                    }
                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();
                }
            }
        };

        var startId, endId; // 在外部声明这两个变量，以便在函数中使用

        var drawShortestPath = function (pathData) {
            let infoDisplay = document.getElementById("coordinatesDisplay");
            
            console.log(`Drawing path. Start: ${startId}, End: ${endId}`);
            console.log(`Path data received: `, pathData);

            if (pathData && pathData.length > 0) {
                // 原有的路径绘制逻辑
                infoDisplay.innerHTML = `Start Node: ${startId}<br>End Node: ${endId}`;

                let test = document.getElementById("test");
                let ctx = test.getContext("2d");

                ctx.lineWidth = 2;
                ctx.strokeStyle = "#4CAF50";
                ctx.beginPath();

                let startPoint = scale(pathData[0]);
                ctx.moveTo(startPoint[0], startPoint[1]);

                for (let i = 1; i < pathData.length; i++) {
                    let point = scale(pathData[i]);
                    ctx.lineTo(point[0], point[1]);
                }

                ctx.stroke();
            } else {
                // 明确显示没有找到路径
                infoDisplay.innerHTML = `No path found between nodes:<br>Start: ${startId}<br>End: ${endId}<br>Mode: ${isPedestrianMode ? 'Walking' : 'Driving'}`;
                
                // 弹出提示
                alert(isPedestrianMode ? "无可行的步行路径" : "无可行的驾驶路径");
                
                // 重置选择
                resetSelection();
            }
        };



        var updateCoordinatesDisplay = function () {
            let display = document.getElementById("coordinatesDisplay");
            if (selectedNodes.length === 0) {
                display.innerHTML = `Selected Nodes: None`;
            } else if (selectedNodes.length === 1) {
                display.innerHTML = `Selected Nodes: (${selectedNodes[0].x}, ${selectedNodes[0].y})`;
            } else {
                display.innerHTML = `Selected Nodes: (${selectedNodes[0].x}, ${selectedNodes[0].y}) and (${selectedNodes[1].x}, ${selectedNodes[1].y})`;
            }
        }

        var updateTimingDisplay = function (time) {
            let timingDisplay = document.getElementById("timingDisplay");
            timingDisplay.innerHTML = `Path computation time: ${time.toFixed(2)} ms`;
        }

        var isPointNear = function (clickX, clickY, nodeX, nodeY, radius = 5) {
            let dist = Math.sqrt((clickX - nodeX) ** 2 + (clickY - nodeY) ** 2);
            return dist <= radius;
        }

        var findNearestNodeInNetwork = function(clickX, clickY) {
            let minDistance = Infinity;
            let nearestNode = null;

            for (let node of nodes) {
                if (nodesInWays.has(node.id)) {
                    let distance = Math.sqrt((clickX - node.x) ** 2 + (clickY - node.y) ** 2);
                    if (distance < minDistance) {
                        minDistance = distance;
                        nearestNode = node;
                    }
                }
            }

            return { node: nearestNode, distance: minDistance };
        }

        var Module = {
            onRuntimeInitialized: function () {
                Module.load();

                // 重置 nodes 数组，但不要完全清空它
                nodes = [];
                nodesInWays = new Set();

                let buildingsJson = Module.getBuildings();
                let buildingsData = JSON.parse(buildingsJson);
                drawBuildings(buildingsData);

                let waysJson = Module.getWays();
                let waysData = JSON.parse(waysJson);
                for (let data in waysData) {
                    draw(waysData[data]);
                }
            }
        };

        

        // 修改点击事件处理程序中的相关部分
        document.getElementById("test").addEventListener("click", function (event) {
            let rect = this.getBoundingClientRect();
            let x = event.clientX - rect.left;
            let y = event.clientY - rect.top;

            // 添加视觉反馈
            let ctx = this.getContext("2d");
            
            // 绘制临时点击位置的标记
            ctx.beginPath();
            ctx.arc(x, y, 6, 0, 2 * Math.PI);
            ctx.fillStyle = "rgba(255, 0, 0, 0.5)";
            ctx.fill();
            ctx.closePath();

            // 查找最近的路网节点
            let { node: nearestNode, distance } = findNearestNodeInNetwork(x, y);

            if (nearestNode) {
                // 如果距离太远，显示提示
                if (distance > 20) {
                    ctx.font = "12px Arial";
                    ctx.fillStyle = "red";
                    ctx.fillText("Nearest network point", nearestNode.x + 10, nearestNode.y);
                }

                if (selectedNodes.length === 2) {
                    selectedNodes = [];
                    redrawMap();
                }

                selectedNodes.push({
                    x: nearestNode.x, 
                    y: nearestNode.y, 
                    id: nearestNode.id
                });

                // 高亮显示吸附的节点
                ctx.beginPath();
                ctx.arc(nearestNode.x, nearestNode.y, 8, 0, 2 * Math.PI);
                ctx.fillStyle = "rgba(0, 255, 0, 0.7)";
                ctx.fill();
                ctx.strokeStyle = "green";
                ctx.lineWidth = 2;
                ctx.stroke();
                ctx.closePath();

                // 绘制连接线，显示"吸附"效果
                ctx.beginPath();
                ctx.moveTo(x, y);
                ctx.lineTo(nearestNode.x, nearestNode.y);
                ctx.strokeStyle = "rgba(0, 255, 0, 0.5)";
                ctx.lineWidth = 2;
                ctx.setLineDash([5, 5]); // 虚线
                ctx.stroke();
                ctx.setLineDash([]); // 重置虚线
                ctx.closePath();

                updateCoordinatesDisplay();

                if (selectedNodes.length === 2) {
                    startId = selectedNodes[0].id;
                    endId = selectedNodes[1].id;
                    
                    console.log(`Searching path from ${startId} to ${endId}`);
                    console.log(`Is in road network: 
                        Start: ${nodesInWays.has(startId)}, 
                        End: ${nodesInWays.has(endId)}`);
                    
                    const startTime = performance.now();
                    
                    let pathJson = Module.getShortestPath(startId, endId, isPedestrianMode);
                    
                    console.log('Raw pathJson:', pathJson); // 额外的调试日志
                    
                    // 如果pathJson为null，直接在前端报错
                    if (pathJson === null) {
                        alert("路径查找失败：内部错误（pathJson为null）");
                        console.error(`Path finding failed for start: ${startId}, end: ${endId}, mode: ${isPedestrianMode ? 'pedestrian' : 'vehicle'}`);
                        resetSelection();
                        return;
                    }
                    
                    // 添加健壮性检查
                    let pathData = [];
                    try {
                        if (pathJson && pathJson.trim() !== '') {
                            pathData = JSON.parse(pathJson);
                        }
                    } catch (error) {
                        console.error('JSON parsing error:', error);
                        console.error('Problematic JSON:', pathJson);
                        alert("路径解析错误：无法处理返回的路径数据");
                        resetSelection();
                        return;
                    }
                    
                    const endTime = performance.now();
                    const timeElapsed = endTime - startTime;
                    
                    updateTimingDisplay(timeElapsed);
                    
                    console.log(`Path data length: ${pathData.length}`);
                    
                    // 始终调用 drawShortestPath
                    drawShortestPath(pathData);
                }
            }
        });


        // 添加模式切换按钮事件监听
        document.getElementById('pedestrianMode').addEventListener('click', () => switchMode('pedestrian'));
        document.getElementById('vehicleMode').addEventListener('click', () => switchMode('vehicle'));
    </script>

    <script src="test.js"></script>
</body>
</html>
```



### 升级后前端文件：`index.html`

```javascript
<!doctype html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Enhanced Map Interface</title>
    <style>
        body, html {
            width: 100%;
            height: 100%;
            margin: 0;
            font-family: system-ui, -apple-system, sans-serif;
        }
        .controls {
            position: absolute;
            top: 10px;
            right: 10px;
            background: rgba(255, 255, 255, 0.9);
            padding: 12px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            z-index: 1000;
        }
        .mode-switch {
            display: flex;
            gap: 10px;
            margin-bottom: 10px;
        }
        .mode-btn {
            padding: 8px 16px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-weight: bold;
            transition: all 0.2s ease;
        }
        .mode-btn.active {
            background: #4CAF50;
            color: white;
        }
        .mode-btn:not(.active) {
            background: #f0f0f0;
            color: #666;
        }
        .mode-btn:hover:not(.active) {
            background: #e0e0e0;
        }
        .info-display {
            position: absolute;
            bottom: 20px;
            right: 20px;
            background: rgba(255, 255, 255, 0.9);
            padding: 15px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            z-index: 1000;
            max-width: 300px;
        }
        .legend {
            margin-top: 12px;
            font-size: 13px;
        }
        .legend-item {
            display: flex;
            align-items: center;
            margin-bottom: 6px;
        }
        .legend-color {
            width: 24px;
            height: 4px;
            margin-right: 10px;
            border-radius: 2px;
        }
        #map-container {
            position: relative;
            width: 100%;
            height: 100vh;
        }
        .coordinates-label {
            position: absolute;
            background: rgba(255, 255, 255, 0.9);
            padding: 4px 8px;
            border-radius: 4px;
            font-size: 12px;
            pointer-events: none;
            z-index: 1001;
        }
    </style>
    <!-- Load Baidu Map SDK -->
    <script src="https://api.map.baidu.com/api?v=3.0&ak=AtogmfxNZD6B9yQJWbn4MNO9c0kBo804"></script>
</head>
<body>
    <div id="map-container"></div>

    <div class="controls">
        <div class="mode-switch">
            <button class="mode-btn active" id="pedestrianMode">Walking</button>
            <button class="mode-btn" id="vehicleMode">Driving</button>
        </div>
        <div>Click to set start and end points</div>
    </div>

    <div class="info-display">
        <div id="coordinatesDisplay">Selected Points: None</div>
        <div id="timingDisplay" style="margin-top: 6px; color: #666;">Path calculation: -- ms</div>
        <div class="legend">
            <div class="legend-item">
                <div class="legend-color" style="background: blue;"></div>
                <span>Network Points</span>
            </div>
            <div class="legend-item">
                <div class="legend-color" style="background: red;"></div>
                <span>Selected Points</span>
            </div>
            <div class="legend-item">
                <div class="legend-color" style="background: #4CAF50;"></div>
                <span>Planned Route</span>
            </div>
        </div>
    </div>

    <script>
        // Initialize Baidu Map
        var map = new BMap.Map("map-container");
        map.centerAndZoom(new BMap.Point(121.503584, 31.296426), 15); // Center the map on Shanghai Fudan

        var isPedestrianMode = true;
        var selectedPoints = [];
        var hoverLabel = null;

        // Create marker for selected points
        function createMarker(point, color) {
            var marker = new BMap.Marker(point);
            marker.setIcon(new BMap.Icon('http://app.baidu.com/map/jsdemo/img/marker_red.png', new BMap.Size(20, 25)));
            map.addOverlay(marker);
            return marker;
        }

        // Handle mousemove for displaying coordinates
        map.addEventListener('mousemove', function(e) {
            var mouseX = e.clientX;
            var mouseY = e.clientY;

            if (hoverLabel) {
                hoverLabel.style.left = (mouseX + 10) + "px";
                hoverLabel.style.top = (mouseY + 10) + "px";
                hoverLabel.textContent = `Lat: ${e.point.lat}, Lng: ${e.point.lng}`;
            }
        });

        // Mouse click to select points
        map.addEventListener("click", function(e) {
            if (selectedPoints.length >= 2) {
                selectedPoints = []; // Clear previous points if 2 points are already selected
                map.clearOverlays();
            }

            selectedPoints.push(e.point);
            createMarker(e.point, 'red');
            document.getElementById("coordinatesDisplay").textContent = `Selected Points: (${e.point.lat}, ${e.point.lng})`;

            if (selectedPoints.length === 2) {
                calculateRoute(selectedPoints);
            }
        });

        // Calculate route between selected points
        function calculateRoute(points) {
            var start = points[0];
            var end = points[1];

            var driving = new BMap.DrivingRoute(map, {
                renderOptions: { map: map, autoViewport: true },
                onSearchComplete: function() {
                    var endTime = new Date().getTime();
                    var duration = endTime - startTime;
                    document.getElementById("timingDisplay").textContent = `Path calculation: ${duration} ms`;
                }
            });

            var walking = new BMap.WalkingRoute(map, {
                renderOptions: { map: map, autoViewport: true },
                onSearchComplete: function() {
                    var endTime = new Date().getTime();
                    var duration = endTime - startTime;
                    document.getElementById("timingDisplay").textContent = `Path calculation: ${duration} ms`;
                }
            });

            var startTime = new Date().getTime(); // Start time before calling the search function
            var routeType = isPedestrianMode ? walking : driving;

            routeType.search(start, end);
        }

        // Mode switch event
        document.getElementById("pedestrianMode").addEventListener("click", function() {
            isPedestrianMode = true;
            this.classList.add("active");
            document.getElementById("vehicleMode").classList.remove("active");
        });

        document.getElementById("vehicleMode").addEventListener("click", function() {
            isPedestrianMode = false;
            this.classList.add("active");
            document.getElementById("pedestrianMode").classList.remove("active");
        });
    </script>
</body>
</html>
```



## 实验遇到的问题与解决方法

1. 在运行了示例代码以后得到预期画面，但是换成自己在OSM上下载的数据后就完全不能跑了，只有一片空白。

   **解决办法：**在询问了助教以后知道了需要调整一下html文件中scale函数的具体参数。其中，这个参数的调整和一开始在OSM上选取的四个坐标点有很大关系。再反复尝试几次以后成功得到了想要的画面。

2. 在完成了初步的代码撰写以后想要查看运行的效率，但是不知道怎么把后端代码的速度传到前端。

   **解决办法：**在询问了助教以后知道了前端也有可以直接调用的函数用来计时，于是直接修改前端代码。

3. 初步代码中对于way不加以区分，但是实际上OSM的数据中way既可以用来表示建筑，也可以用来表示道路，不加以区分会导致道路规划错误。

   **解决办法：**在询问了助教以后知道way的这两个种类并不需要考虑tag，可以直接以way是否闭合这一点进行区分。于是在后端加入buildings这一概念，向前端传输的除了节点、道路还有建筑。

4. 在初步完成地图路径规划项目以后，课程设置了pj展示。在观看了其他同学的pj演示以后，我发现自己当前所实现的地图还是太简陋了，页面展示的并不是地图，更像是草图。

   **解决办法：**在询问了助教后，我了解到还可以直接调用现有的api来进一步丰富了前端实现。于是，在查阅了百度地图官方给出了文档以及查阅资料以后，我进一步给我的前端进行了升级。

   

## 实验心得

​	通过本次实验，我对路径规划的理论算法和实际开发流程有了更为全面的理解。这不仅让我提前学习了最短路径算法（如Dijkstra算法）及其优化（堆优化、斐波那契堆），还让我首次尝试将这些算法应用于实际问题，为我打开了从理论到实践的新视野。

​	本次实验从数据获取、路径计算到前后端交互，各个模块划分明确且紧密协作。在数据获取方面，我通过获取OpenStreetMap（OSM）的真实地图数据，学会了如何提取有效的节点和道路信息并构建邻接表。尽管起初对本次实验复杂感到畏惧，但示例代码提供了良好的基础框架，帮助我快速入门。在示例代码的基础上，通过反复阅读示例代码、查阅相关资料并借助GPT等工具的帮助，我成功地将一个静态的长方形转变为一个可交互的路径规划地图。这一过程中，我深刻感受到了理论转化为实践的挑战，同时也为最终实现目标收获了满满的成就感。

​	在路径规划功能初步实现后，我进一步尝试了两种优化方法：使用斐波那契堆提升Dijkstra算法的效率，以及引入启发式A* 算法。虽然在小规模数据集上性能差异有限，但这些优化思路为处理大规模地图数据的需求奠定了重要基础。同时，这两种优化方法尤其是A*算法对时间效率的惊人提升让我更直观地体会到选择合适数据结构和算法的重要性。

​	实验过程中，我也遇到了许多挑战。例如由于对JavaScript不够熟悉导致初期在实现前后端交互时感到无从下手、地图数据格式与预期不符导致需要仔细分析数据并调整处理逻辑以及实现代码过程中的各种神奇BUG，等等。这些问题的逐一克服，不仅加深了我对整个项目结构和逻辑的理解，也显著提升了我的调试能力和面对问题的耐心。

​	在完成实验的过程中，我还尝试在基本要求的基础上加入拓展功能。例如，我尝试在地图交互功能的基础上加入模式切换功能，为用户提供更加直观的操作体验；同时将系统的功能从只能选择给定的节点拓展到了可以选择地图上的任意节点，让用户的选择更加丰富。

​	在实验的最后，通过调用百度地图的API，我进一步丰富了自己的前端界面。通过结合百度地图的各类功能，我为用户提供了详细精细的地图页面、不同颜色的标记解释，使得页面更加直观、易懂。

​	总的来说，这次实验让我深刻认识到数据结构与算法在实际开发中的作用，并通过解决实际问题积累了宝贵的经验，增强了我面对未来开发挑战的信心。我期待能够将这些经验应用到更大规模、更复杂的项目中，不断提升自己的能力。

实验过程中的各种迂回：

![image-20241219122437657](C:\Users\18238\AppData\Roaming\Typora\typora-user-images\image-20241219122437657.png)

## 参考资料

本次编写代码的过程中遇到了很多困难，最后好多都是询问助教以后得到的的解决方向，感谢助教！

本次代码中所有涉及前端以及前后端交互的部分都是由[ChatGPT](https://chatgpt.com/)和[Claude](https://claude.ai/)这两个大语言模型所撰写的，感谢它们！

本次对前端升级的部分是通过调用百度地图的API实现的，感谢百度地图愿意提供免费额度！

本次性能优化中Fibonacci堆部分代码参考了cnblogs网站上luanxm的文章[数据结构——斐波那契堆](https://www.cnblogs.com/luanxm/p/10848032.html)中对斐波那契堆的讲解以及部分功能的实现。

本次性能优化中A* 算法部分代码参考了[维基百科]([搜索算法-维基百科，自由的百科全书 --- A* search algorithm - Wikipedia](https://en.wikipedia.org/wiki/A*_search_algorithm#))上对A*算法的讲解以及对应的伪代码。

本次代码中最终拓展升级部分的前端代码参考了CSDN网站上[王同学要努力](https://wcaicai.blog.csdn.net/)的文章[百度地图API的使用教程以及案例](https://blog.csdn.net/m0_46374969/article/details/118295186)。