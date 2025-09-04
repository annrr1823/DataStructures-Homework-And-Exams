# Week12 test

[TOC]

## Phone List

略



## 米奇妙妙树 II

> # Description
>
> Y 非常喜欢米奇妙妙屋，于是他在自己家里种了一棵有 n*n* 个节点的米奇妙妙树。
>
> Y 还养了一条名为布鲁托的狗，这条狗总是叼着一把刷子给树染上不同的颜色。
>
> 已知树上每个节点最初的颜色是 0，节点 1 为树的根，布鲁托会进行 q*q* 次染色操作，每次操作把节点 x*x* 到根节点 1 的路径上的所有节点（包括 x*x* 和 1 本身）都染成颜色 y*y*。
>
> 请问最后每个节点的颜色是什么。
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
> 3 3 2 1 0
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n,q≤1061≤*n*,*q*≤106，1≤x,y≤n1≤*x*,*y*≤*n*，1≤c≤1091≤*c*≤109。

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000010;
vector<int> par[MAXN];
vector<int> nodes(MAXN,0);
int n;
int q;

void color_node(int tar,int chan_col)
{
    if(nodes[tar]!=0)return;
    nodes[tar]=chan_col;
    for(auto father:par[tar])
    {
        color_node(father,chan_col);
    }
    return;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>q;
    for(int i=2;i<=n;i++)
    {
        int f;
        cin>>f;
        par[i].push_back(f);
    }
    
    vector<pair<int,int>> ops;
    for(int i=0;i<q;i++)
    {
        int x,y;
        cin>>x>>y;
        ops.push_back({x,y});
    }
    for(int i=q-1;i>=0;i--)
    {
        int tar=ops[i].first;
        int chan_col=ops[i].second;
        color_node(tar,chan_col);
    }
    for(int i=1;i<=n;i++)cout<<nodes[i]<<" ";
    return 0;
}
```



## 树的遍历

> ## 题目背景
>
> 小思在研究怎样用二叉树的两种遍历来还原这棵树的结构。
>
> 现在有一棵具有 n*n* 个结点的有根二叉树。第一次遍历从根节点出发，按照先序遍历的方式去遍历这棵二叉树（即对于每个结点，先访问自己，然后访问左子树，最后访问右子树），然后记录了访问每个结点的先后顺序；第二次遍历从根节点出发，按照反先序遍历的方式去遍历这棵二叉树（即对于每个结点，先访问自己，然后访问右子树，最后访问左子树），然后记录了访问每个结点的先后顺序。
>
> 现在已知这两个遍历序列，你能否根据已知信息求解出每个结点的父亲结点编号呢？请帮帮小思吧！
>
> ## 输入格式
>
> 第一行输入一个正整数 n*n* ，表示二叉树的结点个数。
>
> 第二行输入 n*n* 个整数，表示这棵二叉树的先序遍历。
>
> 第三行输入 n*n* 个整数，表示这棵二叉树的反先序遍历。
>
> ## 输出格式
>
> 输出 11 行，n*n* 个整数，用空格隔开。第 i*i* 个整数表示编号为 i*i* 的结点的父亲结点。特殊的，如果编号为 i*i* 的结点是根节点，则第 i*i* 个整数输出 00 。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 5
> 3 2 5 1 4
> 3 4 2 1 5
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 2 3 0 3 2
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> 5
> 5 4 3 2 1
> 5 4 3 1 2
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 3 3 4 5 0
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 【样例解释】
>
> 样例中的树形状如图所示：
>
> ![img](http://10.20.8.133/file/8/g2.png)
>
> 【数据范围】
>
> 对于 30% 的数据满足 n≤10*n*≤10
>
> 对于 60% 的数据满足 n≤5000*n*≤5000
>
> 对于 100% 的数据满足 n≤100000*n*≤100000
>
> 保证树的结点编号由 1,2,⋯n1,2,⋯*n* 组成且每个号码恰好出现一次。

```c++
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100010;
vector<int> front_seq;
vector<int> reverse_front_seq;
unordered_map<int,int> reverse_idx;
unordered_map<int,int> front_idx;
int ans[MAXN];
int n;
void mark_father(int front_begin,int front_end,int reverse_begin,int reverse_end)
{
    //cout<<front_begin<<" "<<front_end<<" "<<reverse_begin<<" "<<reverse_end<<endl;
    if(front_begin>=front_end && reverse_begin>=reverse_end)
    {
        return;
    }
    if(front_seq[front_begin+1] == reverse_front_seq[reverse_begin+1])
    {
        ans[front_seq[front_begin+1]]=front_seq[front_begin];
        mark_father(front_begin+1,front_end,reverse_begin+1,reverse_end);
        return;
    }
    int root=front_seq[front_begin];
    ans[front_seq[front_begin+1]]=root;
    ans[reverse_front_seq[reverse_begin+1]]=root;
    int front_left_end=front_idx[reverse_front_seq[reverse_begin+1]]-1;
    int reverse_left_begin=reverse_idx[front_seq[front_begin+1]];
    //left_subtree
    if(front_begin+1<front_end)
    {
        //cout<<"reverse:left "<<front_begin+1<<" "<<front_left_end<<" "<<reverse_left_begin<<" "<<reverse_end<<endl;
        mark_father(front_begin+1,front_left_end,reverse_left_begin,reverse_end);
    }
   
    //righ_bubtree
    if(front_end<=n-1)
    {
        //cout<<"reverse:right "<<front_left_end+1<<" "<<front_end<<" "<<reverse_begin+1<<" "<<reverse_left_begin-1<<endl;
        mark_father(front_left_end+1,front_end,reverse_begin+1,reverse_left_begin-1);
    }
    
    return;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        front_seq.push_back(x);
        front_idx[x]=i;
    }
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        reverse_front_seq.push_back(x);
        reverse_idx[x]=i;
    }
    ans[front_seq[0]]=0;
    mark_father(0,n-1,0,n-1);
    for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
    return 0;
}
```

