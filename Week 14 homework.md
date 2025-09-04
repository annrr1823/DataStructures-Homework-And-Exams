# Week 14 homework

[TOC]

## 最短路

> ## 说明
>
> 给你一张无向图，每条边都有正权值，请你求出1到n的**最短路。**
>
> ## 输入格式
>
> 第一行，两个数n,m分别表示点的数量和边的数量。
>
> 后面m行每行表示一条边的情况，每行三个数，a,b,c,表示a，b之间有一条边，权值是c。
>
> 1≤n,a,b,c≤1000,0<m≤50001≤*n*,*a*,*b*,*c*≤1000,0<*m*≤5000
>
> ## 输出格式
>
> 输出1到n的最短路，如果无法从1到n输出“Unreachable”
>
> ## 样例
>
> ## 输入数据 1
>
> ```input1
> 2 1
> 1 2 3
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 3
> ```

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
    map<int,vector<pair<int,int>>> adjmap;
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        adjmap[a].push_back({b,c});
        adjmap[b].push_back({a,c});
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    map<long long,int> distance;//dist id
    for(int i=1;i<=n;i++)distance[i]=INT_MAX;
    distance[1]=0;
    pq.push({0,1});
    while(!pq.empty())
    {
        int cur_dist=pq.top().first;
        int cur_node=pq.top().second;
        pq.pop();
        if(cur_node==n){
            cout<<distance[n]<<endl;
            return 0;
        }
        for(auto neighbor:adjmap[cur_node])
        {
            int neighbor_id=neighbor.first;
            int neighbor_dist=neighbor.second;
            long long new_dist = neighbor_dist+cur_dist;
            if(new_dist < distance[neighbor_id])
            {
                distance[neighbor_id]=new_dist;
                pq.push({new_dist,neighbor_id});
            }
        }
    }
    if(distance[n]!=INT_MAX)cout<<distance[n]<<endl;
    else cout<<"Unreachable"<<endl;
    return 0;
}
```



## 【模板】Floyd

> ## 题目描述
>
> 给出一张由 n*n* 个点 m*m* 条边组成的无向图。
>
> 求出所有点对 (i,j)(*i*,*j*) 之间的最短路径。
>
> ## 输入格式
>
> 第一行为两个整数 n,m*n*,*m*，分别代表点的个数和边的条数。
>
> 接下来 m*m* 行，每行三个整数 u,v,w*u*,*v*,*w*，代表 u,v*u*,*v* 之间存在一条边权为 w*w* 的边。
>
> ## 输出格式
>
> 输出 n*n* 行每行 n*n* 个整数。
>
> 第 i*i* 行的第 j*j* 个整数代表从 i*i* 到 j*j* 的最短路径。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 4 4
> 1 2 1
> 2 3 1
> 3 4 1
> 4 1 1
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 0 1 2 1
> 1 0 1 2
> 2 1 0 1
> 1 2 1 0
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 对于 100%100% 的数据，n≤100*n*≤100，m≤4950*m*≤4950，任意一条边的权值 w*w* 是正整数且 1⩽w⩽10001⩽*w*⩽1000。
>
> 保证任意两点相互联通。

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
    vector<vector<long long>> adjmap(n+1,vector<long long>(n+1,INT_MAX));
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adjmap[u][v]=w;
        adjmap[v][u]=w;
    }
    for(int i=1;i<=n;i++)adjmap[i][i]=0;
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(adjmap[i][j]>adjmap[i][k]+adjmap[k][j])
                {
                    adjmap[i][j]=adjmap[i][k]+adjmap[k][j];
                }
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<adjmap[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```



## 构造无环图

> ## 题目描述
>
> 愚蠢的TA在机考题上把数据造出问题了！题目要求输入数据的有向图不能存在环，可是他的数据居然存在环！真破落！
>
> 为了彰显TA的愚蠢，你决定向他展示如何造出一张无环无重边的有向图！
>
> ## 输入格式
>
> 第一行输入两个整数 n,m*n*,*m* ，分别表示图的结点数和边数。
>
> ## 输出格式
>
> 输出 m*m* 行，第 i*i* 行输出两个整数 ui,vi*u**i*,*v**i* ，表示建立一条从 ui*u**i* 指向 vi*v**i* 的有向边。
>
> 你必须保证 ui≠vi*u**i*=*v**i* 并且图中不会出现重复边，即 ∀1≤i<j≤m∀1≤*i*<*j*≤*m* 不能出现 ui=uj*u**i*=*u**j* 且 vi=vj*v**i*=*v**j* 的情况。
>
> 你还需要保证图中不能存在有向环。
>
> 如果有多种合法的构造方式，请输出任意一种。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 3 3
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 2 1
> 2 3
> 3 1
> ```
>
> [Copy](javascript:;)
>
> ## 数据范围与提示
>
> 1≤n≤105,0≤m≤min⁡(2×105,n(n−1)2)1≤*n*≤105,0≤*m*≤min(2×105,2*n*(*n*−1))

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
    int times=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            if(times==m)return 0;
            cout<<i<<" "<<j<<endl;
            times++;
        }
    }
    return 0;
}
```



## 最短路计数

> ### 题目背景
>
> 给出一张具有 n*n* 个结点，m*m* 条边的有向无环图。每条边的边权为 11 。
>
> 保证从结点 11 出发，能够到达任何一个结点。现在，请你输出 n*n* 个值，其中第 i(1≤i≤n)*i*(1≤*i*≤*n*) 个值表示从结点 11 出发走到结点 i*i* 有多少条不同的最短路径。
>
> > 两条路径不同，当且仅当他们的组成边序列不同。
>
> ### 输入格式
>
> 第一行，22 个整数 n,m*n*,*m* ，分别表示结点数和边数。
>
> 接下来 m*m* 行，每行 22 个整数 u,v(1≤u,v≤n)*u*,*v*(1≤*u*,*v*≤*n*)，表示结点 u*u* 向结点 v*v* 连有一条距离为 11 的单向边。
>
> 数据保证从 11 出发，对任意目标结点能至少存在一条路径够到达。数据中两个点之间可能存在多条单向边，但计算最短路径数时，应当把他们视为不同的边。
>
> 保证图中不存在环。
>
> ### 输出格式
>
> 输出一行，n*n* 个整数用空格隔开，第 i*i* 个整数表示结点 11 到结点 i*i* 的最短路径数量。
>
> 答案可能很大，会造成整数溢出，因此你需要输出模 998244353998244353 意义下的结果。即，如果第 i*i* 个答案是 ansi*an**s**i* ，那么你需要输出的实际是 ansi mod 998244353*an**s**i*mod998244353 的结果。
>
> ### 样例 #1
>
> #### 样例输入 #1
>
> ```none
> 5 7
> 1 2
> 1 3
> 1 4
> 3 5
> 4 5
> 4 3
> 1 2
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #1
>
> ```none
> 1 2 1 1 2
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> 1≤n≤105,1≤m≤2×1051≤*n*≤105,1≤*m*≤2×105 .

```c++
#include<bits/stdc++.h>
using namespace std;
const long long mod=998244353;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    map<int,vector<int>> adjmap;//each dist == 1
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        adjmap[u].push_back(v);
    }
    vector<long long> dist(n+1,INT_MAX);
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    vector<long long> dp(n+1,1);
    dist[1]=0;
    pq.push({0,1});
    while(!pq.empty())
    {
        long long cur_dist=pq.top().first;
        int cur_node=pq.top().second;
        pq.pop();
        for(auto neighbor:adjmap[cur_node])
        {
            if(cur_dist + 1 < dist[neighbor])
            {
                dist[neighbor]=cur_dist+1;
                dp[neighbor]=dp[cur_node];
                pq.push({dist[neighbor],neighbor});
            }
            else if(cur_dist + 1 == dist[neighbor])
            {
                dp[neighbor]+=dp[cur_node];
                dp[neighbor] %= mod;
            }
        }
    }
    for(int i=1;i<=n;i++)cout<<dp[i]%mod<<" ";
    return 0;
}
```



## 奇怪的最小生成树

> ### 题目背景
>
> 有 n*n* 个结点，m*m* 条无向边，每条边具有边权。具体的，第 i(1≤i≤m)*i*(1≤*i*≤*m*) 条边的边权为 wi*w**i* 。
>
> 你需要选出 n−1*n*−1 条边生成一棵树使得每两个点可以相互到达。
>
> 这棵树的代价计算比较奇怪，具体来说定义如下：
>
> - 首先，将这棵生成树以 11 为根挂起。对于每个结点 u(1≤u≤n)*u*(1≤*u*≤*n*) ，定义 size(u)*s**i**ze*(*u*) 表示 u*u* 的子树结点个数（包括自己，以及自己的所有后代结点）。
> - 然后，考虑这棵树的每条边，不妨设这条边连接了结点 u,v*u*,*v* ，且其边权为 w*w* ，那么这条边的代价定义为 w×min⁡{size(u),size(v)}*w*×min{*s**i**ze*(*u*),*s**i**ze*(*v*)} 。
> - 于是，整棵树的代价定义为，所有边的代价之和。
>
> 你需要找到最优代价的生成树使得其代价尽可能小，请输出最小代价。
>
> ### 输入格式
>
> 第一行，22 个整数 n,m*n*,*m* ，分别表示树的结点个数和边个数。
>
> 接下来 m*m* 行，第 i*i* 行包含 33 个整数 ui,vi,wi*u**i*,*v**i*,*w**i* ，表示存在一条连接结点 ui,vi*u**i*,*v**i* 的边，其边权为 wi*w**i* 。
>
> 数据保证生成树一定存在。
>
> ### 输出格式
>
> 输出一行，一个整数，表示生成树的最小代价。注意数据范围。
>
> ### 样例 #1
>
> #### 样例输入 #1
>
> ```none
> 4 6
> 1 2 3
> 1 3 1
> 1 4 4
> 2 3 1
> 2 4 5
> 3 4 9
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #1
>
> ```none
> 7
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> 1≤n≤105,1≤m≤2×105,1≤wi≤1061≤*n*≤105,1≤*m*≤2×105,1≤*w**i*≤106 .
>
> 数据保证不存在自环，但可能存在重边。

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    map<int, vector<pair<int, int>>> adjmap;

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        adjmap[u].push_back({v, w});
        adjmap[v].push_back({u, w});
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq; // {dist, node}
    vector<bool> visit(n + 1, 0);
    long long sum = 0;

    pq.push({0, 1}); // Start with node 1
    int times = 0;

    while (!pq.empty() && times < n) {
        long long cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();
        if (visit[cur_node]) continue; // Skip visited nodes
        //cout<<cur_node<<" "<<cur_dist;
        visit[cur_node] = 1;
        times++;
        sum += cur_dist;

        for (auto neighbor : adjmap[cur_node]) {
            if (!visit[neighbor.first]) {
                pq.push({neighbor.second+cur_dist, neighbor.first});
                //cout<<" Push: "<<neighbor.first<<" ";
            }
        }
        //cout<<endl;
    }

    cout << sum << "\n";
    return 0;
}
```

