# Week 11 homework

[TOC]

## 树的重心

> # Background
>
> #### 题目描述
>
> 树的重心被定义为：树中的一个节点，删除该点后，使得形成的多棵树中节点数最大的树的节点数最小。求树的重心。
>
> # Format
>
> ## Input
>
> 第一行包含一个整数 n*n*，表示树节点的个数。
>
> 接下来 n−1*n*−1 行，每行两个数，表示一条边的两个节点。
>
> 节点编号从 1 到 n*n*。
>
> ## Output
>
> 输出树的重心。如果有多个重心，则按编号从小到大依次输出。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 6
> 1 2
> 2 3
> 2 5
> 3 4
> 3 6
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 2 3
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤5×1041≤*n*≤5×104。

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=50010;
int cur_size[MAXN];
int weight[MAXN];
vector<int> s[MAXN];
int centroid[2]={0,0};
int n;

void getcentroid(int cur,int fa)
{
    cur_size[cur]=1;
    weight[cur]=0;
    for(auto child:s[cur])
    {
        if(child == fa)continue;
        getcentroid(child,cur);
        cur_size[cur]+=cur_size[child];
        weight[cur] = max(weight[cur],cur_size[child]);
    }
    weight[cur] = max(weight[cur],n-cur_size[cur]);
    if(weight[cur]<=(n/2))centroid[centroid[0]!=0]=cur;
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        s[a].push_back(b);
        s[b].push_back(a);
    }
    getcentroid(1,0);
    if(centroid[0]<centroid[1])
    {
        if(centroid[0]==0)cout<<centroid[1]<<endl;
        else cout<<centroid[0]<<" "<<centroid[1]<<endl;
    }
    else
    {
        if(centroid[1]==0)cout<<centroid[0]<<endl;
        else cout<<centroid[1]<<" "<<centroid[0]<<endl;
    }
    return 0;
}
```



## 有多远？

> # Description
>
> 村子里有 n*n* 座房子，一些双向的道路把它们连接起来。
>
> 每天人们都喜欢问这样的问题：“从 A 家到 B 家要走多远?”
>
> 神奇的是，在这个村子里，答案总是独特的，因为每两幢房子之间都有只有一条简单路径（“简单”的意思是你不能两次去一个地方）。你的任务就是回答所有这些好奇的人。
>
> # Format
>
> ## Input
>
> 在第一行中有两个数字 n*n* 和 m*m* 表示房子的数量和查询的数量。
>
> 接下来下面 n−1*n*−1 行，每一行由三个数字 x,y,c*x*,*y*,*c* 组成，用一个空格隔开，表示有一条路连接 x*x* 和 y*y* 家，长度为 c*c*。房子的标号从 1 到 n*n*。
>
> 接下来的 m*m* 行每一行都有不同的整数 a*a* 和 b*b*，你要回答房子 a*a* 和房子 b*b* 之间的距离。
>
> ## Output
>
> 输出 m*m* 行，每行一个整数，表示每个查询的答案。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 3 2
> 1 2 10
> 3 1 15
> 1 2
> 2 3
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 10
> 25
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 2 2
> 1 2 100
> 1 2
> 2 1
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> 100
> 100
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤400001≤*n*≤40000，1≤m≤2001≤*m*≤200，1≤c≤400001≤*c*≤40000。

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=40010;
const int MAXLOG=17;
vector<pair<int,int>> s[MAXN];
int fa[MAXN][MAXLOG];
int dist_from_root[MAXN];
int depth[MAXN];
void dfs(int node,int par,int d,int dist)
{
    dist_from_root[node]=dist;
    depth[node]=d;
    fa[node][0]=par;
    
    for(int i=1;i<MAXLOG;i++)
    {
        if(fa[node][i-1]!=-1)
        {
            fa[node][i]=fa[fa[node][i-1]][i-1];
        }
    }

    for(auto edge:s[node])
    {
        int neighbor=edge.first;
        int weight=edge.second;
        if(neighbor != par)
        {
            dfs(neighbor,node,d+1,dist+weight);
        }
    }

    return;
}

int lca(int u,int v)
{
    if(depth[u]<depth[v])swap(u,v);
    for(int i=MAXLOG-1;i>=0;i--)
    {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = fa[u][i];
        }
    }
    if(u==v)return u;
    for(int i=MAXLOG-1;i>=0;i--)
    {
        if(fa[u][i] != fa[v][i])
        {
            u=fa[u][i];
            v=fa[v][i];
        }
        
    }
    return fa[u][0];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n-1;i++)
    {
        int x,y,c;
        cin>>x>>y>>c;
        s[x].push_back({y,c});
        s[y].push_back({x,c});
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<MAXLOG;j++)
        {
            fa[i][j]=-1;
        }
    }
    dfs(1,-1,0,0);

    while(m--)
    {
        int a,b;
        cin>>a>>b;
        int share_ancester=lca(a,b);
        int ans=dist_from_root[a]+dist_from_root[b]-2*dist_from_root[share_ancester];
        cout<<ans<<endl;
    }

    return 0;
}
```



## Phone List

> # Description
>
> 给定 **n** 个长度不超过 **10** 的数字串，问其中是否存在两个数字串 **S,T**，使得 **S** 是 **T** 的前缀，多组数据。
>
> # 输入格式
>
> 第一行一个整数 **T**，表示数据组数。
>
> 对于每组数据，第一行一个数 **n**，接下来 **n** 行输入 **n** 个数字串。
>
> # 输出格式
>
> 对于每组数据，若存在两个数字串 **S**，**T**，使得 **S** 是 **T** 的前缀，则输出 `NO` ，否则输出 `YES` 。
>
> **请注意此处结果与输出的对应关系！**
>
> # Samples
>
> ## 输入数据 1
>
> ```input1
> 2
> 3
> 911
> 97625999
> 91125426
> 5
> 113
> 12340
> 123440
> 12345
> 98346
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> NO
> YES
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 对于 **100%** 的数据，1≤T≤40,1≤n≤1041≤*T*≤40,1≤*n*≤104。

```c++
#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* next[10];
    bool isEnd;
    Node() : isEnd(false) {
        fill(begin(next), end(next), nullptr);
    }
};

struct TrieTree {
    Node* root;

    TrieTree() {
        root = new Node();
    }

    bool insert(const string& word) {
        Node* cur = root;
        
        for (int i = 0; i < (int)word.size(); ++i) {
            int index = word[i] - '0';

            if (!cur->next[index]) {
                cur->next[index] = new Node();
            }

            cur = cur->next[index];

            if (cur->isEnd && i != (int)word.size() - 1) {
                return true;
            }
        }
        if (cur->isEnd) {
            return true;
        }

        cur->isEnd = true;

        for (int i = 0; i < 10; ++i) {
            if (cur->next[i]) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        TrieTree tree;
        bool hasPrefix = false;

        for (int i = 0; i < n; ++i) {
            string word;
            cin >> word;

            if (tree.insert(word)) {
                hasPrefix = true;
            }
        }

        if (hasPrefix) {
            cout << "NO" << endl; 
        } else {
            cout << "YES" << endl;
        }
    }

    return 0;
}

```



## 树德遍历

> # Description
>
> SDZX 可以看作是一棵树，他有 n*n* 个结点，有 n−1*n*−1 条边将他们相连。QiangBro 开着卡丁车，想把每个结点都访问至少一次，但是他每经过一条边，都会消耗1块钱的电费！
>
> 请为他规划起点和开车的路线，使得拜访每个结点至少一次，且消耗尽可能少的电。
>
> 输出他最少需消耗的电费。
>
> # Format
>
> ## Input
>
> 第一行，一个正整数 n*n*。
>
> 接下来 n−1*n*−1 行，每行两个整数 u,v*u*,*v* ，表示结点 u,v*u*,*v* 之间存在一条边将他们相连。
>
> 保证给出的边构成一棵合法的树。
>
> ## Output
>
> 输出一行，一个整数，最少的电费开销！
>
> # Samples
>
> ## 输入数据 1
>
> ```input1
> 5
> 1 2
> 1 3
> 1 4
> 1 5
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 6
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤1051≤*n*≤105

```c++
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100011;
vector<int> s[MAXN];
int n;
pair<int,int> bfs(int start) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    int farthest_node = start;
    int max_distance = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : s[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > max_distance) {
                    max_distance = dist[v];
                    farthest_node = v;
                }
            }
        }
    }

    return {farthest_node,max_distance};
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n; 
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        s[u].push_back(v);
        s[v].push_back(u);
    }
    pair<int,int> result1=bfs(1);
    int tmp=result1.first;
    pair<int,int> result2=bfs(tmp);
    int diameter=result2.second;

    
    cout << 2 * n - 2 - diameter << endl;

    return 0;
}
```



## 傻瓜和道路

> # Description
>
> 在伯兰这个国家，有 n*n* 座城市，每座城市都通过道路联通。由于傻瓜太多，因此每两个城市之间只有一条简单路径。（简单路径指的是一条路径上没有重复的城市）
>
> 不同城市之间的傻瓜们会参观其他城市，他们到另一个城市拜访只会走简单路径。
>
> 现在给出这个国家傻瓜们所在的城市和要去参观的城市，请计算每条路径有多少个傻瓜经过。
>
> 城市编号 11 到 n*n*。
>
> # Format
>
> ## Input
>
> 第一行包括一个整数 n*n* 表示城市数量。
>
> 接下来 n−1*n*−1 行表示 n−1*n*−1 条道路，每行两个整数 u,v*u*,*v*，表示城市 u*u* 和城市 v*v* 之间有道路相连。
>
> 接下来一个整数 k*k*，表示傻子的个数。
>
> 接下来 k*k* 行，每行两个整数 a,b*a*,*b*，表示傻子要从城市 a*a* 到城市 b*b*。
>
> ## Output
>
> 输出 n−1*n*−1 个整数，第 i*i* 个整数表示第 i*i* 条边有多少个傻子经过。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 5
> 1 2
> 1 3
> 2 4
> 2 5
> 2
> 1 4
> 3 5
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 2 1 1 1
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 5
> 3 4
> 4 5
> 1 4
> 2 4
> 3
> 2 3
> 1 3
> 3 5
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> 3 1 1 1
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n,k≤1051≤*n*,*k*≤105。

```c++
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int parent[MAXN][17], depth[MAXN];
int subtreeContribution[MAXN];
int edgeCount[MAXN];
map<pair<int, int>, int> edgeIndex;
int n, k;

void dfs(int u, int p, int d) {
    parent[u][0] = p;
    depth[u] = d;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

void preprocess() {
    for (int j = 1; (1 << j) < n; j++) {
        for (int i = 1; i <= n; i++) {
            if (parent[i][j - 1] != -1) {
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    for (int i = 16; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }
    if (u == v) return u;

    for (int i = 16; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

void dfsCount(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfsCount(v, u);
            subtreeContribution[u] += subtreeContribution[v];

            int idx = edgeIndex[{min(u, v), max(u, v)}];
            edgeCount[idx] = subtreeContribution[v];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edgeIndex[{min(u, v), max(u, v)}] = i - 1;
    }

    memset(parent, -1, sizeof(parent));
    dfs(1, -1, 0);
    preprocess();

    cin >> k;
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        int l = lca(a, b);
        subtreeContribution[a]++;
        subtreeContribution[b]++;
        subtreeContribution[l] -= 2;
    }

    dfsCount(1, -1);

    for (int i = 0; i < n - 1; i++) {
        cout << edgeCount[i] << " ";
    }
    cout << endl;

    return 0;
}
```

