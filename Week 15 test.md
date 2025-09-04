# Week 15 test

[TOC]

## A. 最短路计数

略



## K步能到几个点？

> ### 题目背景
>
> 给出 n*n* 个结点，以及 n×n*n*×*n* 的 01矩阵 Wn×n*W**n*×*n*，其中 Wi,j=1*W**i*,*j*=1 则表示存在从 i*i* 走向 j*j* 的边；而 Wi,j=0*W**i*,*j*=0 则表示不存在从 i*i* 走向 j*j* 的边。特别的，如果 Wi,i=1,(1≤i≤n)*W**i*,*i*=1,(1≤*i*≤*n*) 则表示存在从 i*i* 走到 i*i* 自己的自环。
>
> 现在，有 m*m* 次询问，其中第 i*i* 次询问会给出两个值 xi,ki*x**i*,*k**i* ，询问的内容是，如果从 xi*x**i* 结点出发，走恰好 ki*k**i* 步（每步经过一条可以走的边），请问最后停下来时所在的结点有多少种不同的可能？
>
> ### 输入格式
>
> 第一行，22 个整数 n,m*n*,*m* ，分别表示结点数量和询问数量。
>
> 接下来 n*n* 行，每行 n*n* 个整数（00 或 11），用空格隔开，表示矩阵 Wn×n*W**n*×*n* 。其中第 i*i* 行第 j*j* 列的整数表示 Wi,j*W**i*,*j* 。
>
> 接下来 m*m* 行，每行两个整数 xi,ki*x**i*,*k**i* 表示一次询问。
>
> ### 输出格式
>
> 输出 m*m* 行，回答每组询问的答案。
>
> ### 样例 #1
>
> #### 样例输入 #1
>
> ```none
> 3 3
> 1 1 0
> 1 1 0
> 1 1 1
> 1 3
> 2 2
> 3 1
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #1
>
> ```none
> 2
> 2
> 3
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> 1≤n≤70,1≤m≤5000,1≤xi,ki≤n1≤*n*≤70,1≤*m*≤5000,1≤*x**i*,*k**i*≤*n* .

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
    vector<vector<int>> adjmap(n+1,vector<int>(n+1));
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cin>>adjmap[i][j];
        }
    }
    vector<vector<vector<int>>> dp(n+1,vector<vector<int>>(n+1,vector<int>(n+1)));
    for(int i=1;i<=n;i++)
    {
        dp[0][i][i]=1;
    }
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                if(adjmap[i][j]==1)
                {
                    for(int p=1;p<=n;p++)
                    {
                        if(dp[k-1][j][p]==1)dp[k][i][p]=1;
                    }
                }
            }
        }
    }
    vector<vector<int>> ans(n+1,vector<int>(n+1,0));
    for(int k=1;k<=n;k++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                ans[k][i]+=dp[k][i][j];
            }
        }
    }
    while(m--)
    {
        int x,k;
        cin>>x>>k;
        cout<<ans[k][x]<<endl;
    }
    return 0;
}
```



## 这就是英国

> ## 题目描述
>
> 众所周知，英国地铁的历史非常悠久，这导致地铁站的环境非常糟糕。现在英国政府决定修缮伦敦的地铁站。伦敦有 n*n* 个地点和 m*m* 条地铁，每条地铁联通两个地铁站。每个地铁站客流量为 vi*v**i*。由于英国没有那么庞大的工程队伍，因此他们只能一个一个地铁站修。修理一个地点的地铁站会导致其他还没完成修缮地铁站的人非常不满，不满政府为什么不先修他们平时乘坐的地铁站，造成不满度为 vf1+vf2+...+vfk*v**f*1+*v**f*2+...+*v**f**k*，其中 f1,f2,...,fk*f*1,*f*2,...,*f**k* 表示与该地点有地铁相连但尚未修缮的地铁站。现在英国政府需要减少不满度，请问不满度最小为多少？
>
> ## 输入格式
>
> 第一行包括两个数 n*n* 和 m*m*
>
> 第二行包括 n*n* 个数 v1,v2,...,vn*v*1,*v*2,...,*v**n*，表示 n*n* 个地点的客流量。
>
> 接下来 m*m* 行，每行两个数 xi,yi*x**i*,*y**i*，表示 xi*x**i* 地铁站与 yi*y**i* 地铁站相连。
>
> ## 输出格式
>
> 一个整数，表示最小的不满度
>
> ## 样例
>
> 输入样例1
>
> ```none
> 4 3
> 10 20 30 40
> 1 4
> 1 2
> 2 3
> ```
>
> [Copy](javascript:;)
>
> 输出样例1
>
> ```none
> 40
> ```
>
> [Copy](javascript:;)
>
> 输入样例2
>
> ```none
> 4 4
> 100 100 100 100
> 1 2
> 2 3
> 2 4
> 3 4
> ```
>
> [Copy](javascript:;)
>
> 输出样例2
>
> ```none
> 400
> ```
>
> [Copy](javascript:;)
>
> 输入样例2
>
> ```none
> 7 10
> 40 10 20 10 20 80 40
> 1 5
> 4 7
> 4 5
> 5 2
> 5 7
> 6 4
> 1 6
> 1 3
> 4 3
> 1 4
> ```
>
> [Copy](javascript:;)
>
> 输出样例3
>
> ```none
> 160
> ```
>
> [Copy](javascript:;)
>
> ## 数据范围与提示
>
> 1≤n≤1000,1≤m≤20001≤*n*≤1000,1≤*m*≤2000
>
> 1≤vi≤1051≤*v**i*≤105
>
> 第一个样例解释：
>
> 英国政府首先修缮 3 号地铁站，2 号地铁站尚未修缮且与 3 号地铁站有地铁相连，造成的不满度为 2020
>
> 然后修缮 2 号地铁站，1 号和 3 号地铁站与 2 号地铁站有地铁相连，由于 3 号地铁站已经修缮完成，因此造成的不满度为 1010

```c++
#include<bits/stdc++.h>
using namespace std;
struct station{
    int num;
    int weight;
    station(int a,int b):num(a),weight(b){}
    bool operator<(station other)const{
        return weight<other.weight;
    }
};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    unordered_multiset<int> adjmap[n+1];
    priority_queue<station> pq;
    vector<int> v(n+1);
    for(int i=1;i<=n;i++)
    {
        int vi;
        cin>>vi;
        pq.push(station(i,vi));
        v[i]=vi;
    }
    while(m--)
    {
        int x,y;
        cin>>x>>y;
        adjmap[x].insert(y);
        adjmap[y].insert(x);
    }
    long long ans=0;
    while(!pq.empty())
    {
        station cur=pq.top();
        pq.pop();
        for(int neighbor:adjmap[cur.num])
        {
            ans+=v[neighbor];
            adjmap[neighbor].erase(cur.num);
        }
    }
    cout<<ans<<endl;
    return 0;
}
```

