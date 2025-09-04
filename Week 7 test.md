# Week7 test

[TOC]

## 木桶效应

同作业



## 子串差距和

> # 题目描述
>
> 给定一个长度为n*n*的数组a1,a2,...,an*a*1,*a*2,...,*a**n*。定义函数f(i,j)=max(ai,ai+1,...aj)−min(ai,ai+1,...aj)*f*(*i*,*j*)=*ma**x*(*a**i*,*a**i*+1,...*a**j*)−*min*(*a**i*,*a**i*+1,...*a**j*)。求∑l=1n∑r=lnf(l,r)∑*l*=1*n*∑*r*=*l**n**f*(*l*,*r*)
>
> # 输入输出格式
>
> ## 输入格式
>
> 第一行一个整数 n*n*。
>
> 第二行 n*n* 个整数，第 i*i* 个整数表示ai*a**i*。
>
> ## 输出格式
>
> 一个整数，表示 ∑l=1n∑r=lnf(l,r)∑*l*=1*n*∑*r*=*l**n**f*(*l*,*r*)的答案
>
> ## 样例
>
> ## 输入数据 1
>
> ```input1
> 10
> 7 6 6 5 6 5 1 9 2 10
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 245
> ```
>
> [Copy](javascript:;)
>
> # 约束条件
>
> 1≤n≤1061≤*n*≤106，1≤ai≤1091≤*a**i*≤109。

```c++
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

vector<int> make_left_max(const vector<long long> & a, int n)
{
    vector<int> next(n);
    stack<int> sta;
    next[0] = -1;
    sta.push(0);
    for(int i = 1; i < n; i++)
    {
        while(!sta.empty() && a[sta.top()] < a[i]) 
            sta.pop();
        if(sta.empty()) next[i] = -1;
        else next[i] = sta.top();
        sta.push(i);
    }
    return next;
}

vector<int> make_right_max(const vector<long long> & a, int n)
{
    vector<int> next(n);
    stack<int> sta;
    next[n-1] = n;
    sta.push(n-1);
    for(int i = n-2; i >= 0; i--)
    {
        while(!sta.empty() && a[sta.top()] <= a[i]) 
            sta.pop();
        if(sta.empty()) next[i] = n;
        else next[i] = sta.top();
        sta.push(i);
    }
    return next;
}

vector<int> make_left_min(const vector<long long> & a, int n)
{
    vector<int> next(n);
    stack<int> sta;
    next[0] = -1;
    sta.push(0);
    for(int i = 1; i < n; i++)
    {
        while(!sta.empty() && a[sta.top()] > a[i]) 
            sta.pop();
        if(sta.empty()) next[i] = -1;
        else next[i] = sta.top();
        sta.push(i);
    }
    return next;
}

vector<int> make_right_min(const vector<long long> & a, int n)
{
    vector<int> next(n);
    stack<int> sta;
    next[n-1] = n;
    sta.push(n-1);
    for(int i = n-2; i >= 0; i--)
    {
        while(!sta.empty() && a[sta.top()] >= a[i]) 
            sta.pop();
        if(sta.empty()) next[i] = n;
        else next[i] = sta.top();
        sta.push(i);
    }
    return next;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vector<int> left_max = make_left_max(a, n);
    vector<int> right_max = make_right_max(a, n);
    vector<int> left_min = make_left_min(a, n);
    vector<int> right_min = make_right_min(a, n);
    long long ans = 0;
    for(int i = 0; i < n; i++)
    {
        long long count_max = (long long)(i - left_max[i]) * (right_max[i] - i);
        long long count_min = (long long)(i - left_min[i]) * (right_min[i] - i); 
        // cout << i << " " << count_max << " " << count_min << endl; // 注释掉调试输出
        ans += (count_max - count_min) * a[i];
    }
    cout << ans;
    return 0;
}
```



## 跑酷

> # 题目描述
>
> ZZR 很喜欢跑酷。
>
> 一天 ZZR 在大楼楼顶上进行跑酷（**危险动作，请勿模仿**），他最开始在 1 号楼，他需要从 1 号楼跳到 n*n* 号楼，其中第 i*i* 号楼高度为 hi*h**i*。
>
> ZZR 认为回头是懦弱的表现，所以他进行的所有跳跃都是从左向右的。
>
> 他跳跃能力很强，当满足以下条件中的任意一个时，他能够从 i*i* 号楼直接跳到 j*j* 号楼：(i<j*i*<*j*)
>
> - i+1=j*i*+1=*j*；
> - max⁡(hi+1,...,hj−1)<min⁡(hi,hj)max(*h**i*+1,...,*h**j*−1)<min(*h**i*,*h**j*)；
> - min⁡(hi+1,...,hj−1)>max⁡(hi,hj)min(*h**i*+1,...,*h**j*−1)>max(*h**i*,*h**j*)。
>
> 请问 ZZR 从 1 号楼跳到 n*n* 号楼最少要跳几次？
>
> # 输入输出格式
>
> ## 输入格式
>
> 第一行一个整数 n*n*。
>
> 第二行 n*n* 个整数，第 i*i* 个整数表示第 i*i* 号楼高度 hi*h**i*。
>
> ## 输出格式
>
> 一个整数，表示 ZZR 从 1 号楼跳到 n*n* 号楼跳的最少次数。
>
> ## 样例
>
> ## 输入数据 1
>
> ```input1
> 7
> 1 4 3 2 6 5 7
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 3
> ```
>
> [Copy](javascript:;)
>
> ## 输入数据 2
>
> ```input2
> 3
> 3 1 2
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 2
>
> ```output2
> 1
> ```
>
> [Copy](javascript:;)
>
> # 约束条件
>
> 1≤n≤1061≤*n*≤106，1≤ai≤1091≤*a**i*≤109。

```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; ++i){
        cin >> a[i];
    }
    

    vector<int> dp(n + 1, INT32_MAX);
    dp[1] = 0;


    vector<int> inc; 
    vector<int> dec; 

    inc.push_back(1);
    dec.push_back(1);

    for(int i = 2; i <= n; ++i){
        dp[i] = dp[i-1] + 1;

        while(!inc.empty() && a[i] > a[inc.back()]){
            dp[i] = min(dp[i], dp[inc.back()] + 1);
            inc.pop_back();
        }
        if(!inc.empty()){
            dp[i] = min(dp[i], dp[inc.back()] + 1);
        }

        if(!inc.empty() && a[i] == a[inc.back()]){
            inc.pop_back();
        }
        inc.push_back(i);


        while(!dec.empty() && a[i] < a[dec.back()]){
            dp[i] = min(dp[i], dp[dec.back()] + 1);
            dec.pop_back();
        }
        if(!dec.empty()){
            dp[i] = min(dp[i], dp[dec.back()] + 1);
        }

        if(!dec.empty() && a[i] == a[dec.back()]){
            dec.pop_back();
        }
        dec.push_back(i);
    }

    cout << dp[n];
    return 0;
}

```

