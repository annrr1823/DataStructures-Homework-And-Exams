# Week 15 homework

[TOC]

## 贪吃蛇大作战

> # Description
>
> Gromah 最近沉迷于一款叫做“贪吃蛇大作战”的游戏。
>
> 给定一个 n×m*n*×*m* 的地图，其中有些格子是空的，有些格子上有食物。初始时贪吃蛇的头在地图中的某个格子上，每次 Gromah 会控制贪吃蛇的头朝着上下左右四个方向中的一个方向移动一个单位，如果贪吃蛇的头撞到了墙（即坐标不在 (1,1)∼(n,m)(1,1)∼(*n*,*m*) 范围内），则其立即死亡；否则如果贪吃蛇的头所到达的格子上有一个食物，则贪吃蛇会吃掉这个食物，当然一个食物被吃掉之后就会消失。此外，贪吃蛇的头可以和自己的身体重合，贪吃蛇的身体在本题并不重要，保证贪吃蛇的初始位置上不存在食物。
>
> 现给定地图，贪吃蛇的头的初始位置，移动序列。如果贪吃蛇中道崩殂，则输出 “GG”；否则如果贪吃蛇最后依然存活，输出贪吃蛇吃掉的食物数量。
>
> # Format
>
> ## Input
>
> 第一行两个整数 n,m*n*,*m*，表示地图大小。
>
> 接下来 n*n* 行，每行一个长为 m*m* 的只包含 “.”, “o” 和 “@” 的字符串 s*s*，表示地图。其中 “.” 表示没有食物，“o” 表示有一个食物，“@” 表示贪吃蛇的头的初始位置。
>
> 接下来一行一个只包含 “W”，“A”，“S”，“D” 的字符串 t*t*，表示操作序列，其中 “W” 表示向上，“A” 表示向左，“S” 表示向下，“D” 表示向右。
>
> 保证地图中有且仅有一个 “@”。
>
> ## Output
>
> 如果贪吃蛇中道崩殂，则输出 “GG”；否则输出一个整数，表示贪吃蛇吃掉的食物数量。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 4 5
> .oo..
> .o@.o
> ..o..
> .oo..
> WASDSSAD
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 6
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 4 5
> .oo..
> .o@.o
> ..o..
> .oo..
> WASDSSADDDWWWDA
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> GG
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n,m≤4001≤*n*,*m*≤400，1≤∣t∣≤1051≤∣*t*∣≤105。

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    vector<vector<char>> play_map(n,vector<char>(m));
    int head_p_i=0;
    int head_p_j=0;
    for(int i=0;i<n;i++)
    {
        string s;
        cin>>s;
        for(int j=0;j<m;j++)
        {
            play_map[i][j]=s[j];
            if(s[j]=='@')
            {
                head_p_i=i;
                head_p_j=j;
            }
        }
    }
    //cout<<head_p_i+1<<" "<<head_p_j+1<<endl;
    string ops;
    cin>>ops;
    long long food_count=0;
    for(int i=0;i<(int)ops.size();i++)
    {
        char op=ops[i];
        if(op=='D')
        {
            head_p_j++;
        }
        else if(op=='S')
        {
            head_p_i++;
        }
        else if(op=='A')
        {
            head_p_j--;
        }
        else if(op=='W')
        {
            head_p_i--;
        }
        //cout<<head_p_i+1<<" "<<head_p_j+1<<endl;
        if(head_p_i<0 ||head_p_i>=n || head_p_j<0 ||head_p_j>=m)
        {
            cout<<"GG"<<endl;
            return 0;
        }
        if(play_map[head_p_i][head_p_j]=='o')
        {
            food_count++;
            play_map[head_p_i][head_p_j]='.';
        }
    }
    cout<<food_count<<endl;
    return 0;
}
```



## 探照灯

> #### 【题目描述】
>
> 让每个探照灯都被照亮，这是计划的一部分。
>
> 在一条直线上，有 n*n* 个探照灯，每个探照灯有一个照射方向。具体的，第 i*i* 个探照灯用 di*d**i* 表示它的照射方向，方向只有 LL 和 RR 两种，分别表示照射左边和照射右边。
>
> 当 di=L*d**i*=L 的时候，第 i*i* 个探照灯可以照亮它左边的所有探照灯，也就是照亮编号为 1,2,⋯i−11,2,⋯*i*−1 的探照灯。
>
> 当 di=R*d**i*=R 的时候，第 i*i* 个探照灯可以照亮它右边的所有探照灯，也就是照亮编号为 i+1,i+2,⋯n*i*+1,*i*+2,⋯*n* 的探照灯。
>
> 现在我们已经知道了每个灯的朝向。但是我们注意到，有可能有的灯没有被任何一盏灯照亮，比如方向为 `LR` 的两盏灯，它们背对背，都没有被照亮。
>
> 如果存在这样的情况，你有一次机会，可以选择两个相邻的探照灯，交换它们的位置，然后使得所有探照灯都被照亮。形式化的说，你可以选择一个 i(1≤i<n)*i*(1≤*i*<*n*) ，然后交换 di*d**i* 和 di+1*d**i*+1 的值，使得一次操作后所有探照灯都被照亮。
>
> 现在，你需要判断是否需要操作，如果需要操作，输出你的操作。
>
> #### 【输入格式】
>
> 第一行，一个整数 n*n* 。
>
> 第二行，一个长度为 n*n* 的字符串，由字符 L,RL,R 组成。
>
> #### 【输出格式】
>
> 输出一行，一个整数表示答案。
>
> 如果所有灯已经被照亮，那么输出 00 。
>
> 否则，如果可以通过一次题目描述中的交换操作把所有灯照亮，输出交换发生的数字的下标。（即，如果交换 di*d**i* 与 di+1*d**i*+1 ，请输出 i*i*）。**如果有多种合法方案，请输出下标最小的方案**。
>
> 否则，如果没有合法的方案在一次操作就达成目标，输出 −1−1 。
>
> #### 【样例】
>
> 【输入1】
>
> ```none
> 2
> LR
> ```
>
> [Copy](javascript:;)
>
> 【输出1】
>
> ```none
> 1
> ```
>
> [Copy](javascript:;)
>
> 【输入2】
>
> ```none
> 3
> RLL
> ```
>
> [Copy](javascript:;)
>
> 【输出2】
>
> ```none
> 0
> ```
>
> [Copy](javascript:;)
>
> #### 【提示】
>
> 对于 30% 的数据，满足 n≤10*n*≤10
>
> 对于 70% 的数据，满足 n≤1000*n*≤1000
>
> 对于 100% 的数据，满足 n≤100000*n*≤100000 。
>
> 【时空限制】
>
> 1000ms 256MB

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    string s;
    cin>>s;
    bool all_right=true;
    bool all_left=true;
    int L_most_right=-1;
    int R_most_left=n;
    for(int i=0;i<n;i++)
    {
        if(s[i]=='L')
        {
            all_right=false;
            L_most_right=i;
        }
        if(s[i]=='R')all_left=false;
    }
    for(int i=n-1;i>=0;i--)
    {
        if(s[i]=='R')R_most_left=i;
    }
    if(all_left || all_right)
    {
        cout<<-1<<endl;
        return 0;
    }
    if(L_most_right>R_most_left)cout<<0<<endl;
    else cout<<R_most_left<<endl;
    return 0;
}
```



## 这就是俄国

> ## 题目描述
>
> 众所周知，俄国的克格勃力量很强大，而且对乌克兰虎视眈眈。因此决定派遣间谍进入乌克兰。乌克兰有 n*n* 座城市，克格勃在乌克兰的每座城市都成功插入间谍，现在他们需要建立通讯线，使得任意两座城市的间谍都能直接或者通过其他多人转发间接联系得上。已知第 i*i* 座城市乌克兰的警戒值为 ai*a**i* ，要在城市 u*u* 和城市 v*v* 建立通信线需要花费代价 au+av*a**u*+*a**v* 。但是苏联留下了一些遗产，已知有 m*m* 条苏联克格勃留下的通信线，只需要花费代价 wi*w**i* 即能重启该通信线。现在克格勃需要花费最小代价建立或者重启通信线，使得任意两座城市之间的间谍都能相互联系得上，请问最小代价为多少。
>
> ## 输入格式
>
> 第一行包括两个数 n*n* 和 m*m* ，表示乌克兰城市数量和苏联留下的通信线路数量。
>
> 第二行包括 n*n* 个数，表示每座城市乌克兰的警戒值 ai*a**i* 。
>
> 接下来 m*m* 行，每行包括三个数 ui,vi,wi*u**i*,*v**i*,*w**i* ，表示苏联留下的第 i*i* 条通信线连接城市 ui*u**i* 和城市 vi*v**i* ，重启代价为 wi*w**i* 。
>
> ## 输出格式
>
> 一个整数，表示克格勃建立或者重启通信线使得任意两座城市之间的间谍都能相互联系得上的最小代价。
>
> ## 样例
>
> 输入样例1
>
> ```none
> 3 2
> 1 3 3
> 2 3 5
> 2 1 1
> ```
>
> [Copy](javascript:;)
>
> 输出样例1
>
> ```none
> 5
> ```
>
> [Copy](javascript:;)
>
> 输入样例2
>
> ```none
> 4 0
> 1 3 3 7
> ```
>
> [Copy](javascript:;)
>
> 输出样例2
>
> ```none
> 16
> ```
>
> [Copy](javascript:;)
>
> 输入样例3
>
> ```none
> 5 4
> 1 2 3 4 5
> 1 2 8
> 1 3 10
> 1 4 7
> 1 5 15
> ```
>
> [Copy](javascript:;)
>
> 输出样例3
>
> ```none
> 18
> ```
>
> [Copy](javascript:;)
>
> ## 数据范围与提示
>
> 1≤n,m≤2∗1051≤*n*,*m*≤2∗105
>
> 1≤ai,wi≤10121≤*a**i*,*w**i*≤1012

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
private:
    vector<int> parent;

public:
    UnionFind(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false;
        parent[rootY] = rootX;
        return true;
    }
};

struct Edge {
    int u, v;
    long long w;
    
    Edge(int _u, int _v, long long _w) : 
        u(_u), v(_v), w(_w) {}
    
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<Edge> edges;
    
    // 初始化状态: 所有节点连接到最小警戒值的节点
    auto min_a_p = min_element(a.begin() + 1, a.end());
    int min_a_index=min_a_p-a.begin();
    long long min_a = *min_a_p;
    for (int i = 1; i <= n; ++i) {
        if (i!=min_a_index) {
            edges.emplace_back(i, min_a_index, a[i] + min_a);
        }
    }

    // 读取原有边
    for (int i = 1; i <= m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.emplace_back(u, v, w);
    }

    // 排序边并进行Kruskal算法
    sort(edges.begin(), edges.end());
    
    UnionFind uf(n);
    long long total_cost = 0;
    int edge_count = 0;

    for (auto& edge : edges) {
        if (uf.unite(edge.u, edge.v)) {
            total_cost += edge.w;
            edge_count++;
            if (edge_count == n - 1) break;
        }
    }

    cout << total_cost << endl;
    return 0;
}
```



## 这就是法国

> # Description
>
> 众所周知，法国是一个经常罢工的国家。在20xx年，由于对工资过低且工作时间过长表示不满，工会决定在每个城市进行罢工要求政府提高福利待遇。法国政府决定派遣军队镇压罢工活动。已知法国有n*n*座城市，第i*i*座城市的坐标为(xi,yi)(*x**i*,*y**i*)。法国军队要镇压所有城市罢工活动，法国可以空降军队到城市i*i*镇压罢工，这样会伤亡ci*c**i*人。法国还可以派遣相邻的罢工活动已经镇压的城市i*i*的军队到该城市j*j*,这样会伤亡(ki+kj)×(∣xi−xj∣+∣yi−yj∣)(*k**i*+*k**j*)×(∣*x**i*−*x**j*∣+∣*y**i*−*y**j*∣)人。军队可以在已经被镇压的城市间任意行动不会有任何伤亡。法国军队想要用最小的伤亡镇压所有罢工行为，请问最小伤亡人数为多少？
>
> # Format
>
> ## Input
>
> 第一行有一个整数n*n*，表示城市的数量
>
> 接下来n*n*行，每行有两个整数，xi*x**i*和yi*y**i*表示城市的坐标
>
> 接下来一行n*n*个整数,c1,c2,...,cn*c*1,*c*2,...,*c**n*，表示法国空降军队到城市i*i*的伤亡人数
>
> 接下来一行n*n*个整数,k1,k2,...,kn*k*1,*k*2,...,*k**n*，表示法国派遣军队到相邻城市的伤亡系数（伤亡人数如题目描述中所示）。
>
> ## Output
>
> 输出一个整数，表示最小的伤亡人数。
>
> # Samples
>
> 输入样例1
>
> ```none
> 3
> 2 3
> 1 1
> 3 2
> 3 2 3
> 3 2 3
> ```
>
> [Copy](javascript:;)
>
> 输出样例1
>
> ```none
> 8
> ```
>
> [Copy](javascript:;)
>
> 输入样例2
>
> ```none
> 3
> 2 1
> 1 2
> 3 3
> 23 2 23
> 3 2 3
> ```
>
> [Copy](javascript:;)
>
> 输出样例2
>
> ```none
> 27
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤20001≤*n*≤2000
>
> 1≤xi,yi≤1061≤*x**i*,*y**i*≤106
>
> 1≤ci,ki≤1091≤*c**i*,*k**i*≤109

```c++
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

struct Node {
    int city;
    long long cost;
    Node(int c, long long co) : city(c), cost(co) {}
    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

long long compute_distance(int i, int j, const vector<int>& x, const vector<int>& y, const vector<int>& k) {
    return (long long)(k[i] + k[j]) * (abs(x[i] - x[j]) + abs(y[i] - y[j]));
}

long long min_loss(int n, const vector<int>& x, const vector<int>& y, const vector<int>& c, const vector<int>& k) {
    vector<long long> min_cost(n, LLONG_MAX);   // 存储每个城市的最小伤亡
    vector<bool> in_tree(n, false);             // 标记城市是否已被镇压
    priority_queue<Node, vector<Node>, greater<Node>> pq;  // 优先队列，存储城市及其伤亡值
    
    // 初始化，空降到每个城市的伤亡
    for (int i = 0; i < n; ++i) {
        min_cost[i] = c[i];
        pq.push(Node(i, c[i]));
    }
    
    long long total_cost = 0;  // 总伤亡

    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();

        int u = node.city;
        long long current_cost = node.cost;

        // 如果城市 u 已经被镇压，跳过
        if (in_tree[u]) continue;

        // 将当前城市 u 加入已镇压的城市
        in_tree[u] = true;
        total_cost += current_cost;

        // 现在需要检查与城市 u 相邻的城市，更新它们的伤亡值
        for (int v = 0; v < n; ++v) {
            if (u == v || in_tree[v]) continue;  // 不考虑自己或已被镇压的城市

            long long new_cost = compute_distance(u, v, x, y, k);
            if (new_cost < min_cost[v]) {
                min_cost[v] = new_cost;
                pq.push(Node(v, new_cost));
            }
        }
    }

    return total_cost;
}

int main() {
    int n;
    cin >> n;

    vector<int> x(n), y(n), c(n), k(n);

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    for (int i = 0; i < n; ++i) {
        cin >> k[i];
    }

    cout << min_loss(n, x, y, c, k) << endl;

    return 0;
}

```



## 最小过路费

> ## 题目背景
>
> 小思来到了博学国，这里有 n*n* 个城市。
>
> 城市与城市之间有许多道路，具体而言一共有 m*m* 条双向道路。其中第 i*i* 条道路连接了城市 ai*a**i* 和 bi*b**i* ，并且这条道路的过路费为 ci*c**i* ，意味着通过这条道路（无论是从哪个方向）将花费 ci*c**i* 个卿云币。因为博学国只修建两种道路，过路费只有两种可能：免费，或 11 个卿云币，即： ci∈{0,1}*c**i*∈{0,1} 。
>
> 博学国的城市是连通的，这意味着从任何一个城市出发都存在路径到达任何一个城市。
>
> 我们定义 cost(x,y)*cos**t*(*x*,*y*) 表示从城市 x*x* 出发走到城市 y*y* 所消耗的最少过路费。
>
> 接下来，小思有 Q*Q* 次询问，每次询问会给你一个起点 S*S* ，表示询问 ∑x=1ncost(S,x)∑*x*=1*n**cos**t*(*S*,*x*) 的值。
>
> 请你回答一下小思的询问吧！
>
> ## 输入格式
>
> 第一行包含两个整数 n,m*n*,*m* 分别表示城市数量和道路数量。
>
> 接下来的 m*m* 行种，第 i*i* 行包含 33 个整数 ai,bi,ci*a**i*,*b**i*,*c**i* ，表示道路连接的城市和过路费。
>
> 接下来一行，一个整数 Q*Q* 表示小思的询问次数。
>
> 接下来的 Q*Q* 行，每行一个整数 S*S* 表示询问的起点。
>
> ## 输出格式
>
> 输出 Q*Q* 行，每行一个整数，表示对应的答案。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 5 7
> 1 2 0
> 1 3 1
> 1 4 1
> 1 5 1
> 2 4 1
> 2 3 0
> 3 5 0
> 5
> 1
> 2
> 3
> 4
> 5
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 1
> 1
> 1
> 4
> 1
> ```
>
> [Copy](javascript:;)
>
> ## 数据范围与提示
>
> 对于 10% 的测试数据满足 n,m≤10*n*,*m*≤10
>
> 对于 40% 的测试数据满足 n≤1000*n*≤1000
>
> 对于 70% 的测试数据满足 Q≤3*Q*≤3
>
> 对于 100% 的测试数据满足 1≤n≤105, 1≤m≤2×105, 1≤Q≤501≤*n*≤105, 1≤*m*≤2×105, 1≤*Q*≤50。 1≤ai,bi,S≤n, ci∈{0,1}1≤*a**i*,*b**i*,*S*≤*n*, *c**i*∈{0,1}
>
> 注意到，测试数据中，两座城市之间可能存在多条道路。

```c++
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int MAXN = 1e5 + 10;

// 使用邻接表存储图
vector<pair<int, int>> graph[MAXN];

// Dijkstra算法求最短路径
vector<int> dijkstra(int start, int n) {
    vector<int> dist(n + 1, INT_MAX);
    dist[start] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int curr_dist = pq.top().first;
        int curr_node = pq.top().second;
        pq.pop();
        
        // 如果当前距离大于已知最短距离，跳过
        if (curr_dist > dist[curr_node]) continue;
        
        // 遍历当前节点的所有邻接边
        for (auto& edge : graph[curr_node]) {
            int next_node = edge.first;
            int edge_cost = edge.second;
            
            // 尝试更新距离
            if (dist[curr_node] + edge_cost < dist[next_node]) {
                dist[next_node] = dist[curr_node] + edge_cost;
                pq.push({dist[next_node], next_node});
            }
        }
    }
    
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    // 清空图
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
    }
    
    // 读取道路信息
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});  // 双向道路
    }
    
    int Q;
    cin >> Q;
    
    // 处理每个询问
    for (int i = 1; i <= Q; i++) {
        int S;
        cin >> S;
        
        // 计算从S出发到其他所有城市的最短路径
        vector<int> shortest_paths = dijkstra(S, n);
        
        // 计算最短路径总和
        int total_cost = 0;
        for (int j = 1; j <= n; j++) {
            total_cost += shortest_paths[j];
        }
        
        cout << total_cost << '\n';
    }
    
    return 0;
}
```

