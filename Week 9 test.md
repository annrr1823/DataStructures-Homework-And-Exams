# Week 9 test

[TOC]

## C. 前缀的TopK

略



## B. 最小的n个和

> # Description
>
> 给定 A*A* 、 B*B* 两个数列，各包含 n*n* 个数，分别从 A*A* 和 B*B* 中任意取一个数相加得到和，这样会有 n2*n*2 种结果(包括重复的)，求 n2*n*2 个结果中前 n*n* 个最小的和。
>
> # Format
>
> ## Input
>
> 第一行为 n*n* ，第二行为数列 A*A* ，第三行为数列 B*B* 。
>
> ## Output
>
> 输出一行，包含前 n*n* 个最小的和，按照升序输出，两数之间用一个空格隔开。
>
> # Samples
>
> ## 输入数据 1
>
> ```input1
> 5
> 1 3 4 2 0
> 7 3 5 2 11
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 2 3 3 4 4
> ```
>
> [Copy](javascript:;)
>
> ## 输入数据 2
>
> ```input2
> 20
> 33 84 93 14 89 61 55 54 63 24 81 36 58 42 1 100 21 39 42 58 
> 22 35 78 63 13 2 72 3 39 15 85 2 60 72 98 15 53 61 95 30 
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 2
>
> ```output2
> 3 3 4 14 16 16 16 16 17 23 23 23 24 26 26 27 27 29 29 31 
> ```
>
> [Copy](javascript:;)
>
> ## 输入数据 3
>
> ```input3
> 20
> 91 78 44 65 66 40 32 69 38 87 66 79 10 93 56 31 29 48 49 66 
> 14 78 69 74 18 22 6 62 77 61 63 69 8 48 4 88 58 49 78 93 
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 3
>
> ```output3
> 14 16 18 24 28 32 33 35 35 36 37 37 38 39 40 42 43 44 44 45 
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤100000,0≤Ai,Bi≤1091≤*n*≤100000,0≤*A**i*,*B**i*≤109。

```c++
#include<bits/stdc++.h>
using namespace std;
struct node{
    int aa,bb;
    long long sum;
    node():aa(0),bb(0),sum(0){}
    node(int x,int y,long long z):aa(x),bb(y),sum(z){}
    bool operator<(node other)const
    {
        return sum < other.sum;
    }
    bool operator>(node other)const
    {
        return sum>other.sum;
    }
};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    vector<long long> a(n),b(n);
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)cin>>b[i];
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    priority_queue<node,vector<node>,greater<node>> pq;
    for(int i=0;i<n;i++)
    {
        node cur = node(i,0,a[i]+b[0]);
        pq.push(cur);
    }
    vector<long long> ans;
    for(int i=0;i<n;i++)
    {
        node cur = pq.top();
        pq.pop();
        ans.push_back(cur.sum);
        node take_out = node(cur.aa,cur.bb+1,a[cur.aa]+b[cur.bb+1]);
        pq.push(take_out);
    }
    for(int i=0;i<n;i++)cout<<ans[i]<<" ";
    return 0;
}
```



## A. 四角不同色

> ## 题目描述
>
> 你需要构造一个 n*n* 行 m*m* 列的01矩阵。
>
> 其中第 i*i* 行第 j*j* 列的元素记作 ai,j*a**i*,*j*，满足 ai,j∈{1,0}*a**i*,*j*∈{1,0} (1≤i≤n,1≤j≤m)(1≤*i*≤*n*,1≤*j*≤*m*) 。
>
> 此外你构造的这个矩阵还需要满足一个条件：对于每个长宽均大于 11 的子矩阵，它的四个角上的元素不能完全相同。
>
> 形式化的说，对于任意的 1≤i1<i2≤n, 1≤j1<j2≤m1≤*i*1<*i*2≤*n*, 1≤*j*1<*j*2≤*m*，不允许 ai1,j1=ai1,j2=ai2,j1=ai2,j2*a**i*1,*j*1=*a**i*1,*j*2=*a**i*2,*j*1=*a**i*2,*j*2 的情况出现。
>
> 如果说不存在合法的构造方案，请输出 “No solution”（不包含引号）。
>
> 如果存在合法的构造方案，请输出字典序最小的构造方案。
>
> 对于矩阵的字典序，在这道题中我们这样规定：
>
> - 对比两个 n×m*n*×*m* 的01矩阵的字典序，我们先将两者分别看作 n*n* 行的长度为 m*m* 的01字符串，然后将这些字符串按照行号从小到大的顺序从左往右拼接得到单个字符串。将两者得到的字符串的字典序作为矩阵的字典序比较即可。
>
> 形式化的说，比较矩阵的字典序时，实际上是在比较序列：
>
> a1,1,a1,2,⋯a1,m,a2,1,a2,2,⋯a2,m,⋯⋯an,1,an,2,⋯an,m*a*1,1,*a*1,2,⋯*a*1,*m*,*a*2,1,*a*2,2,⋯*a*2,*m*,⋯⋯*a**n*,1,*a**n*,2,⋯*a**n*,*m*
>
> 的字典序。
>
> ## 输入格式
>
> 第一行，一个正整数 T*T* 表示询问组数。
>
> 对每组询问，输入一行两个整数，n,m*n*,*m*，表示矩阵的行数和列数。
>
> ## 输出格式
>
> 对于每组询问：
>
> - 如果无解，则输出一行 “No solution”（不包含引号）.
> - 如果有解，请直接输出矩阵，用 n*n* 行的长度为 m*m* 的01字符串表示你的答案，不要有额外的空格。注意要求是输出字典序最小的解。
>
> ## 样例
>
> ## 输入数据 1
>
> ```input1
> 4
> 2 2
> 3 4
> 8 2
> 400 400
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 00
> 01
> 0001
> 0110
> 1010
> 00
> 01
> 01
> 01
> 01
> 01
> 01
> 01
> No solution
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 【数据范围】
>
> 对于 2020% 的数据，满足 n,m,T≤4*n*,*m*,*T*≤4
>
> 对于 5050% 的数据，满足 n,m,T≤10*n*,*m*,*T*≤10
>
> 对于 7070% 的数据，满足 n,m,T≤50*n*,*m*,*T*≤50
>
> 对于 100100% 的数据，满足 T≤8000*T*≤8000，2≤n,m≤105,∑n⋅m≤2×1052≤*n*,*m*≤105,∑*n*⋅*m*≤2×105
>
> 【时空限制】
>
> 时间限制：1000 ms
>
> 空间限制：256 MB

```c++
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, m;
int a[10][10]; 
bool dfs(int x, int y) {
    if (x == n + 1) return true;

    int tx = x, ty = y + 1;
    if (ty > m) {
        ++tx;
        ty = 1;
    }

    a[x][y] = 0;
    bool flag = false;

    for (int i = 1; i < x; i++) {
        for (int j = 1; j < y; j++) {
            if (a[i][j] == a[x][y] && a[i][j] == a[i][y] && a[i][j] == a[x][j]) {
                flag = true; 
                break;
            }
        }
        if (flag) break;
    }

    if (!flag) {
        if (dfs(tx, ty)) return true; 
    }

    a[x][y] = 1;
    flag = false; 
    for (int i = 1; i < x; i++) {
        for (int j = 1; j < y; j++) {
            if (a[i][j] == a[x][y] && a[i][j] == a[i][y] && a[i][j] == a[x][j]) {
                flag = true;
                break;
            }
        }
        if (flag) break;
    }

    if (!flag) return dfs(tx, ty);
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T; 

    while (T--) {
        memset(a, 0, sizeof(a)); 
        cin >> n >> m;

        if (n == 2) {
            for (int i = 1; i <= m; i++) cout << '0';
            cout << endl;
            cout << '0';
            for (int i = 1; i < m; i++) cout << '1';
            cout << endl;
        }
        else if (m == 2) {
            cout << "00" << endl;
            for (int i = 1; i < n; i++) cout << "01" << endl;
        }
        else if (n >= 7 || m >= 7 || (n >= 5 && m >= 5)) {
            cout << "No solution" << endl;
        }
        else {
            if (dfs(1, 1)) {
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= m; j++) {
                        cout << a[i][j];
                    }
                    cout << endl;
                }
            } else {
                cout << "No solution" << endl;
            }
        }
    }

    return 0;
}
```

