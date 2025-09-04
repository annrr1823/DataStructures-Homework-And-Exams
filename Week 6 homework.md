# Week 6 homework

[TOC]

## 抱大腿

> # Description
>
> 有 n*n* 名能力等级(level)分别为 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n* 的同学，他们依次进入机房参加期末上机考试。
>
> 对于第 i*i* 名进入机房的同学，他/她希望找到一个已经进到教室了的（即编号比自己小的），且能力等级严格比自己高的同学，并抱其大腿，如果有多个这样的同学，则取编号最大的那个。特别地，如果找不到这样的同学，那么规定当前同学的大腿为 0 号同学（可以认为是 TA 之类的绝对能力者）。
>
> 你想知道每个同学找到的大腿是编号为多少的同学。
>
> # Format
>
> ## Input
>
> 输入第一行一个正整数 n*n*，表示同学个数。
>
> 第二行 n*n* 个正整数 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*，表示每位同学的能力等级(level)。
>
> ## Output
>
> 输入仅一行 n*n* 个非负整数，表示每位同学找到的大腿同学（或者 TA 之类的绝对能力者）的编号。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 9
> 5 9 3 1 1 9 6 8 1
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 0 0 2 3 3 0 6 6 8
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤105,1≤ai≤1091≤*n*≤105,1≤*a**i*≤109。

```c++
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    vector<long long> a(n);
    vector<pair<long long,int>> big_lag(n+1);
    int top = 0;
    vector<int> ans(n);
    for(int i=0;i<n;i++)
        cin>>a[i];

    for(int i=0;i<n;i++)
    {
        long long cur = a[i];
        if(top ==0)
        {
            ans[i]=0;
        }
        else
        {
            bool found = false;
            for(int j=top;j>0;j--)
            {
                if(big_lag[j].first > cur)
                {
                    ans[i]=big_lag[j].second+1;
                    found= true;
                    break;
                }
            }
            if(!found)ans[i]=0;
        }

        if(top==0 || cur < big_lag[top].first)
        {
            big_lag[++top]={cur,i};
        }
        else{
            while(top>0 && cur >= big_lag[top].first)
            {
                top--;
            }
            big_lag[++top]={cur,i};
        }

    }
    for(int i=0;i<n;i++)cout<<ans[i]<<" ";
    return 0;
}
```



## 快速幂

> # Description
>
> 给定 n,m*n*,*m*，求 nm mod (109+7)*n**m* mod (109+7)。
>
> 如有不理解可查阅资料。
>
> # Format
>
> ## Input
>
> 一行两个整数 n,m*n*,*m*。
>
> ## Output
>
> 一行输出 nm mod (109+7)*n**m* mod (109+7)。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 3 2
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 9
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n,m≤1091≤*n*,*m*≤109。

```c++
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const long long mod = 1e9+7;
unsigned long long fast_power(long long a,long long b)
{
    if(b==0)return 1;
    unsigned long long res = 1;
    unsigned long long base = a%mod;
    while(b>0)
    {
        if(b&1)res=(res * base)%mod;
        base = (base * base)%mod;
        b>>=1;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long a,b;
    cin>>a>>b;
    unsigned long long power = fast_power(a,b);
    cout<<power<<endl;
    return 0;
}
```



## 接雨水

> # 题目描述
>
> 给定 n*n* 个非负整数表示每个宽度为 11 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
>
> ![img](http://10.20.8.133/d/DS2023/file/226/rainwatertrap.png)
>
> 上面是由数组 `[0,1,0,2,1,0,1,3,2,1,2,1]` 表示的高度图（黑色部分表示柱子），在这种情况下，可以接 66 个单位的雨水（蓝色部分表示雨水）。
>
> # 输入输出格式
>
> ## 输入格式
>
> 第一行一个整数 n*n*。
>
> 第二行 n*n* 个整数表示柱子的高度 a1,a2,...,an*a*1,*a*2,...,*a**n*。
>
> ## 输出格式
>
> 一个数表示答案。
>
> ## 样例
>
> ## 输入数据 1
>
> ```input1
> 12
> 0 1 0 2 1 0 1 3 2 1 2 1
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
> # 约束条件
>
> 1≤n≤105,0≤ai≤1041≤*n*≤105,0≤*a**i*≤104。

```c++
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    vector<int> a(n);
    stack<pair<int,int>> higher;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    long long ans = 0;
    for(int i=0;i<n;i++)
    {
        int cur = a[i];
        //cout<<i<<": "<<cur<<":"<<endl;
        if(higher.empty() || higher.top().first >= cur)
        {
            higher.push({cur,i});
            //cout<<"push"<<endl;
        }
        else
        {
            while(higher.top().first < cur )
            {
                int pop_a = higher.top().first;
                //int pop_i = higher.top().second;
                higher.pop();
                if(higher.empty())
                {
                    break;
                }
                if(higher.top().first < cur)
                {
                    ans += (i-higher.top().second-1)*(higher.top().first-pop_a);
                    //cout<<"ans1:"<<higher.top().second<<" "<<ans<<endl;
                }
                else
                {
                    ans += (i-higher.top().second-1)*(cur-pop_a);
                    //cout<<"ans2:"<<ans<<endl;
                }


            }
            higher.push({cur,i});
            //cout<<"push"<<endl;
        }
    }
    cout<<ans<<endl;
    return 0;
}
```



## 滑动窗口问题

> ## 题目背景
>
> 这是一个经典的题目！小思想用它来考考你。
>
> 给出一个长度为 n*n* 的整数序列，a1,a2,⋯an*a*1,*a*2,⋯*a**n*。
>
> 接下来有 Q*Q* 次询问，每次询问会给出一个窗口大小 K*K* ，你需要求解出序列的所有长度为 K*K* 的子区间中的最大值是多少。而为了减少输出文件的大小，你只需要输出这些最大值的和即可。
>
> 形式化来讲，我们定义 Fmax(l,r)=max⁡{al,al+1,⋯ar}*F*max(*l*,*r*)=max{*a**l*,*a**l*+1,⋯*a**r*} ，那么对于第 i*i* 个询问，其窗口大小为 Ki*K**i* ，那么对于该询问，你需要输出 ∑j=1n−Ki+1Fmax(j,j+Ki−1)∑*j*=1*n*−*K**i*+1*F*max(*j*,*j*+*K**i*−1) 的值。
>
> ## 输入格式
>
> 第一行，包含两个整数 n,Q*n*,*Q* ，分别表示序列长度和询问次数。
>
> 接下来一行，n*n* 个整数，用空格隔开，即 a1,a2,⋯an*a*1,*a*2,⋯*a**n* 。
>
> 接下来 Q*Q* 行，每行一个整数 Ki*K**i* ，表示询问的窗口的大小。
>
> ## 输出格式
>
> 输出 Q*Q* 行，对于每个询问，输出对应的答案。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 5 3
> 1 3 2 4 5
> 1
> 2
> 3
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 15
> 15
> 12
> ```
>
> [Copy](javascript:;)
>
> ## 数据范围与提示
>
> 对于 30% 的测试数据，n≤2000*n*≤2000
>
> 对于 70% 的测试数据，Q≤5*Q*≤5
>
> 对于 100% 的测试数据满足 1≤K≤n≤105, 1≤Q≤100,0≤ai≤1091≤*K*≤*n*≤105, 1≤*Q*≤100,0≤*a**i*≤109

```c++
#include<iostream>
#include<deque>
#include<vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    while (q--) {
        int k;
        cin >> k;

        long long ans = 0;
        deque<pair<long long, int>> max_que;

        for (int i = 0; i < k; i++) {
            while (!max_que.empty() && max_que.back().first < a[i])
            {
                max_que.pop_back();
            }
            max_que.push_back({a[i], i});
        }


        ans += max_que.front().first;
        for (int i = k; i < n; i++) {
            if (!max_que.empty() && max_que.front().second <= i - k)
            {
                max_que.pop_front();
            }

            while (!max_que.empty() && max_que.back().first < a[i])
            {
                max_que.pop_back();
            }
            max_que.push_back({a[i], i});
            ans += max_que.front().first;
        }

        cout << ans << endl;
    }

    return 0;
}

```



## 木桶效应

> # 题目描述
>
> ZZR 准备做木桶。
>
> 现在 ZZR 有 n*n* 块木板，这 n*n* 块木板排成一排，每块木板长度为 ai*a**i*。当使用连续的一段木板作木桶时，木桶的容量为这些木板长度的最小值。
>
> 现在 ZZR 想知道，对于任意一个 x*x*(1≤x≤n1≤*x*≤*n*)，ZZR 如果使用 n*n* 块木板中的连续 x*x* 块木板做木桶，木桶的最大容量分别为多少？
>
> # 输入输出格式
>
> ## 输入格式
>
> 第一行为一个数 n*n*，表示木板数量。
>
> 第二行有 n*n* 个整数 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*，表示每块木板长度。
>
> ## 输出格式
>
> 一行 n*n* 个数，第 i*i* 个数表示 ZZR 使用连续 i*i* 块木板做木桶，木桶的最大容量大小。
>
> # 样例
>
> ## 输入数据 1
>
> ```input1
> 10
> 9 2 7 3 5 6 4 8 7 1
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 9 7 4 4 4 3 3 2 2 1
> ```
>
> [Copy](javascript:;)
>
> # 约束条件
>
> 1≤n≤1061≤*n*≤106，1≤ai≤1091≤*a**i*≤109。

```c++
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> count_left(const vector<long long>& a, const int& n) {
    stack<int> increase;
    vector<int> left(n);
    for (int i = 0; i < n; i++) {
        while (!increase.empty() && a[increase.top()] >= a[i]) {
            increase.pop();
        }
        left[i] = increase.empty() ? -1 : increase.top();
        increase.push(i);
    }
    return left;
}

vector<int> count_right(const vector<long long>& a, const int& n) {
    stack<int> increase;
    vector<int> right(n);
    for (int i = n - 1; i >= 0; i--) {
        while (!increase.empty() && a[increase.top()] >= a[i]) {
            increase.pop();
        }
        right[i] = increase.empty() ? n : increase.top();
        increase.push(i);
    }
    return right;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> left = count_left(a, n);
    // for(int i=0;i<n;i++)cout<<left[i]<<" ";
    // cout<<endl;
    vector<int> right = count_right(a, n);
    // for(int i=0;i<n;i++)cout<<right[i]<<" ";
    // cout<<endl;

    vector<long long> max_co(n + 1, -1);
    for (int i = 0; i < n; i++) {
        int cover = right[i] - left[i] - 1;
        max_co[cover] = max(max_co[cover], a[i]);
    }

    for (int i = n - 1; i >= 1; i--) {
        max_co[i] = max(max_co[i], max_co[i + 1]);
    }

    for (int i = 1; i <= n; i++) {
        cout << max_co[i] << " ";
    }

    return 0;
}

```

