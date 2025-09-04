# Week 6 test

[TOC]

## 本质不同子串计数

同作业，略



## 刷墙

> # 题目描述：
>
> George 是一个粉刷匠。粉刷本领强。
>
> 现在有一面墙，可以把墙从左到右分成 n*n* 块。我们用一个数列 a1,a2⋯an*a*1,*a*2⋯*a**n* 来表示每一块墙的颜色。也就是说，ai*a**i* 表示第 i*i* 块墙的颜色。
>
> 最开始的时候，∀1≤i≤n∀1≤*i*≤*n* 有 ai=0*a**i*=0 ，也就是说所有 n*n* 块墙的颜色都是 00 。
>
> 接下来， George 会有 m*m* 次操作，每次操作是下面的两种之一：
>
> 1. George 把最后面的 x*x* 块墙的颜色全部刷成 y*y* 。也就是说，∀n−x+1≤i≤n∀*n*−*x*+1≤*i*≤*n* ，令 ai=y*a**i*=*y* 。
> 2. George 想问问你，现在这 n*n* 块墙上一共出现了多少种不同的颜色？
>
> # 输入输出格式
>
> ## 输入格式：
>
> 第一行，两个正整数 n,m*n*,*m* ，分别代表墙的块数和操作次数。
>
> 接下来 m*m* 行，每行有下面两种可能：
>
> - 输入三个整数 1,x,y1,*x*,*y* ，表示把最后面的 x*x* 块墙的颜色全部刷成 y*y* 。
> - 输入一个整数 22 ，表示询问现在 n*n* 块墙上一共出现了多少种不同的颜色。
>
> ## 输出格式：
>
> 对于每个询问操作，输出一行，一个整数，表示答案。
>
> # 样例
>
> ## 输入数据 1
>
> ```input1
> 5 3
> 2
> 1 2 1
> 2
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 1
> 2
> ```
>
> [Copy](javascript:;)
>
> ## 输入数据 2
>
> ```input2
> 5 6
> 1 2 1
> 2
> 1 4 2
> 2
> 1 1 3
> 2
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 2
>
> ```output2
> 2
> 2
> 3
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围：
>
> 1≤n,m≤5×1051≤*n*,*m*≤5×105
>
> 1≤x≤n1≤*x*≤*n*
>
> 0≤y≤1060≤*y*≤106

```c++
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    int n,m;
    cin>>n>>m;

    vector<pair<long long,int>> walls;
    walls.clear();
    unordered_map<long long,int> cols;
    walls.push_back({0,n});
    cols.insert({0,n});
    int ans=1;

    while(m--)
    {
        int op;
        cin>>op;
        if(op==1)
        {
            int x;
            long long y;
            cin>>x>>y;
            int sub = x;
            while(sub>0 && !walls.empty())
            {
                if(walls.back().second>sub)
                {
                    //cout<<"1:"<<walls.back().first<<" "<<walls.back().second<<" "<<sub<<" ";
                    walls.back().second -= sub;
                    cols[walls.back().first]-=sub;
                    if(!cols.count(walls.back().first) || cols[walls.back().first]==0)ans--;
                    sub=0;
                    //cout<<sub<<endl;
                    
                }
                else
                {
                    //cout<<"2:"<<walls.back().first<<" "<<walls.back().second<<" "<<sub<<" ";
                    sub -= walls.back().second;
                    cols[walls.back().first]-=walls.back().second;
                    if(!cols.count(walls.back().first)||cols[walls.back().first]==0 )ans--;
                    walls.pop_back();
                    //cout<<sub<<endl;
                    
                } 
                
            }
            walls.push_back({y,x});
            if(!cols.count(y))
            {
                cols.insert({y,x});
                ans++;
            }
            else if(cols[y]==0)
            {
                cols[y]+=x;
                ans++;
            }
            else cols[y]+=x;
        }
        else
        {
            
            cout<<ans<<endl;
        }
    }
	return 0;
}
```



## 争夺土地

> ## 题目描述
>
> YGG和NSH在SDZX争夺土地。
>
> SDZX的土地是一个大矩形，进而被划分成了n×m*n*×*m*块小格子土地，即一共 n*n* 行，m*m* 列的矩阵。
>
> NSH答应给YGG划一部分的土地。但是YGG比较妖艳，想要一块正方形的区域作为自己的土地（即，想要一个长宽相同的子矩阵），而且他希望这个正方形区域的土地都是肥沃的。然而SDZX里并不是所有土地都是肥沃的。
>
> 但是YGG可以使用任意次魔法，每次可将任意一行土地的状态取反：即选择一行，把这行中肥沃的土地变得贫瘠，贫瘠土地变得肥沃。
>
> YGG想知道，在上述条件下，他能获得最大的全肥沃的方形区域面积是多大。
>
> ## 输入格式
>
> 第一行，输入正整数 n*n*，m*m*。
>
> 接下来 n*n* 行，每行一个长为 m*m* 的字符串，字符串由`B` 或 `G` 组成。
>
> 上述输入构成了 n×m*n*×*m* 的矩阵，表示每一块小正方形土地（面积为1）是否肥沃，`G` 表示肥沃，`B` 表示贫瘠。
>
> ## 输出格式
>
> 一行，一个整数代表YGG能获得土地的最大面积。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 2 2 
> BB
> BB
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 4
> ```
>
> [Copy](javascript:;)
>
> ### 解释
>
> 他可以把这两行贫瘠的土地都用魔法转换，变成肥沃土地，然后存在 2×22×2 的正方形肥沃土地。
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> 5 6 
> GBBBBB
> BBBBBB
> BGGGGG
> GGGGGG
> GBBBBB
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> 25
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 对30%的数据满足：n,m≤10*n*,*m*≤10
>
> 对60%的数据满足：n,m≤100*n*,*m*≤100
>
> 对100%的数据满足：n,m≤1000*n*,*m*≤1000

```c++
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

bool check(int k,const vector<vector<int>>& next,int n,int m)
{
    int num;
    for(int j=0;j<m;j++)
    {
        num=0;
        for(int i=0;i<n;i++)
        {
            if(next[i][j]>=k)num++;
            else num=0;
            if(num>=k)return true;
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    vector<vector<char>> a(n,vector<char>(m));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            cin>>a[i][j];
        }
    }
    vector<vector<int>> next(n,vector<int>(m,0));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(j==0)
            {
                next[i][j]=1;
            }
            else
            {
                if(a[i][j]==a[i][j-1])next[i][j]=next[i][j-1]+1;
                else next[i][j]=1;
            }
        }
    }
    int left=1,right=min(n,m);
    int mid;
    int ans=1;
    while(left<=right)
    {
        mid=left+(right-left)/2;
        if(check(mid,next,n,m))
        {
            ans=mid;
            left=mid+1;
        }
        else
        {
            right=mid-1;
        }
    }
    cout<<ans*ans<<endl;
    return 0;
}
```

