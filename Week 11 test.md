# Week 11 test

[TOC]

## A. 成为一棵树

> # Description
>
> 
>
> *如果有来生，我要做一棵树，*
>
> *站成永恒，没有悲欢的姿势，**一半在尘土里安详，一半在风里飞扬；**一半洒落荫凉，一半沐浴阳光，**非常沉默、非常骄傲。**从不依靠、从不寻找。*
>
> 
>
> Y 觉得树很好，他希望军训的同学也能像树一样。
>
> 为此，他将 n*n* 名同学排成树的形状，每个同学站在树的一个节点上，1 号同学站在根的位置。
>
> 这 n*n* 名同学的美丽值为 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*。而 Y 又定义了一个名为“树值”的玩意，他认为，每个同学的树值为该同学对应节点子树中所有同学的美丽值之和加上子树中同学的数量。注意，节点 v*v* 的子树包括节点 v*v* 自己。
>
> Y 想知道，所有同学的树值之和是多少。
>
> # Format
>
> ## Input
>
> 第一个一个整数 n*n* 表示同学数量。
>
> 第二行 n−1*n*−1 个整数分别表示第 2,3,⋯ ,n2,3,⋯,*n* 号同学的“父亲”。
>
> 第三行 n*n* 个整数表示 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*。
>
> ## Output
>
> 一行一个整数表示所有同学的树值之和。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 10
> 1 1 3 4 2 4 3 3 9 
> 9 4 7 9 7 4 6 10 6 6
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 223
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤1061≤*n*≤106，1≤ai≤1051≤*a**i*≤105。
>
> 节点编号从 1 开始。

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAX=1000010;
vector<long long > beauty;
vector<long long > subtree;
vector<long long> tree[MAX];
long long total_ans=0;
long long dfs(int x)
{
    subtree[x]=1;
    long long cur_beauty=beauty[x];
    for(auto token: tree[x])
    {
        cur_beauty += dfs(token);
        subtree[x]+=subtree[token];
    }
    total_ans += cur_beauty + subtree[x];
    return cur_beauty;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    beauty.resize(n+1);
    subtree.resize(n+1);
    for(int i=2;i<=n;i++)
    {
        int fa;
        cin>>fa;
        tree[fa].push_back(i);
    }
    for(int i=1;i<=n;i++)cin>>beauty[i];
    dfs(1);
    cout<<total_ans<<endl;
    return 0;
}
```



## 米奇妙妙树

> # Description
>
> Y 非常喜欢米奇妙妙屋，于是他在自己家里种了一棵有 n*n* 个节点的米奇妙妙树。
>
> Y 还养了一条名为布鲁托的狗，这条狗总是叼着一把刷子给树染上不同的颜色。
>
> 已知树上每个节点最初的颜色是 00。节点 11 为树的根，布鲁托会进行 q*q* 次染色操作，每次操作把以节点 x*x* 为根的子树（即 x*x* 和其所有子孙后代结点）染成颜色 y*y*。
>
> 请问 q*q* 次操作后，最后每个节点的颜色是什么。
>
> # Format
>
> ## Input
>
> 第一行一个整数 n,q*n*,*q* 分别表示节点数量和操作数量。
>
> 第二行 n−1*n*−1 个整数依次表示第 2,3,⋯ ,n2,3,⋯,*n* 号节点的父亲。
>
> 接下来 q*q* 行每行两个数 x,y*x*,*y* 表示这 q*q* 个操作。
>
> ## Output
>
> 一行 n*n* 个数用空格隔开表示每个节点的颜色。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 5 4
> 1 1 2 3
> 3 1
> 3 2
> 4 1
> 2 3
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 0 3 2 3 2
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n,q≤1061≤*n*,*q*≤106，1≤x≤n1≤*x*≤*n*，1≤y≤1091≤*y*≤109。

```c++
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000011;
vector<int> tree[MAX];
int color[MAX];
int latest_operation[MAX];

void dfs(int node, int current_color) {
    if (color[node] != -1) return;
    color[node] = current_color;
    for (int child : tree[node]) {
        dfs(child, current_color);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    for (int i = 2; i <= n; i++) {
        int parent;
        cin >> parent;
        tree[parent].push_back(i);
    }

    fill(color, color + n + 1, -1);
    vector<pair<int, int>> operations;
    
    for (int i = 0; i < q; i++) {
        int x;
        int y;
        cin >> x >> y;
        operations.push_back({x, y});
    }

    for (int i = q - 1; i >= 0; i--) {
        int node = operations[i].first;
        int col = operations[i].second;
        if (color[node] == -1) {
            dfs(node, col); 
        }
    }
 
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) color[i] = 0;
        cout << color[i] << " ";
    }
    
    return 0;
}

```



## 出成绩

> ### 题目背景
>
> 3202年，FDU-DS课出成绩了。可惜啊，到了 3202 年，FDU 课程的 A 类还是只给到 30%。
>
> 现在，按顺序给出 n*n* 个同学的成绩 pi(1≤pi≤n)*p**i*(1≤*p**i*≤*n*)，每当第 i*i* 个同学的成绩出来时，你需要输出前 i*i* 个同学中，排名位于当前的前 30% 的同学的最低分数，也就是当前的 A 类分数线。保证所有同学的成绩互不相同。
>
> **特殊的**，如果当前人数少于 1010 人，则没有 A 类限制，此时输出前 i*i* 个同学中的最低成绩即可。
>
> ### 输入格式
>
> 第一行，一个整数 n*n* ，表示班级人数。
>
> 第二行，n*n* 个整数 p1,p2,⋯pn*p*1,*p*2,⋯*p**n*，表示同学的成绩。保证所有同学的成绩互不相同。
>
> ### 输出格式
>
> 输出 n*n* 行，每行一个整数，表示只考虑前 i*i* 个同学时，A类的分数线。如果 i<10*i*<10 ，则输出前 i*i* 个同学中的最低成绩。
>
> ### 样例 #1
>
> #### 样例输入 #1
>
> ```none
> 15
> 13 9 14 11 8 3 12 6 1 10 4 7 2 5 15
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #1
>
> ```none
> 13
> 9
> 9
> 9
> 8
> 3
> 3
> 3
> 1
> 12
> 12
> 12
> 12
> 11
> 12
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> 对于 100% 的测试数据满足 1≤n≤3×1051≤*n*≤3×105 。
>
> 请注意读入效率。

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    priority_queue<int> pq_g;
    priority_queue<int,vector<int>,greater<int>> pq;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int p;
        cin>>p;
        
        if(i<10)
        {
            pq.push(p);
            cout<<pq.top()<<endl;
        }
        else
        {
            if(pq.empty()|| p>pq.top() )pq.push(p);
            else pq_g.push(p);
            
            while((int)pq.size()>(int)(i*0.3) && !pq.empty())
            {
                //cout<<"POP: "<<pq.top();
                pq_g.push(pq.top());
                pq.pop();
            }
            while((int)pq.size()<(int)(i*0.3)&& !pq_g.empty())
            {
                //cout<<"POP: "<<pq.top();
                pq.push(pq_g.top());
                pq_g.pop();
            }
            cout<<pq.top()<<endl;
            
        }
    }
    return 0;
}
```

