# Week 14 test

[TOC]

## A. 约克镇之战

略



## B. 算一算 III

> # Description
>
> Y 老是惦记着同学们的“美丽值”，现在，他又玩出了新花样。
>
> 他想从 n*n* 个同学里选出若干个同学（可以选择 0 个同学），使得他们的美丽值之和恰好为 s*s*。
>
> 请问聪明的你，有多少种不同的选法？
>
> # Format
>
> ## Input
>
> 第一行两个整数 n,s*n*,*s* 表示同学数量和美丽值之和。
>
> 第二行 n*n* 个整数 ai*a**i* 用空格隔开表示每个同学的美丽值。
>
> ## Output
>
> 一行一个整数表示答案。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 3 19260817
> 1 1 1
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 0
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 7 10
> 1 3 4 2 8 1 9
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> 6
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 3
>
> ```none
> 3 0
> 0 0 0
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 3
>
> ```none
> 8
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤451≤*n*≤45，−109≤ai,s≤109−109≤*a**i*,*s*≤109。

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    long long s;
    cin>>n>>s;
    vector<long long> a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    int mid=n/2;
    vector<long long> sum1,sum2;
    for(int i=0;i<(1<<mid);i++)
    {
        long long sum=0;
        for(int j=0;j<mid;j++)
        {
            if(i&(1<<j))sum+=a[j];
        }
        sum1.push_back(sum);
    }
    for(int i=0;i<(1<<(n-mid));i++)
    {
        long long sum=0;
        for(int j=0;j<(n-mid);j++)
        {
            if(i&(1<<j))sum+=a[j+mid];
        }
        sum2.push_back(sum);
    }
    sort(sum1.begin(),sum1.end());
    sort(sum2.begin(),sum2.end());
    int i=0,j=(int)sum2.size()-1;
    while(i<(int)sum1.size() && j>=0)
    {
        long long cur_sum = sum1
    }
    return 0;
}
```



## 公共子串 II

> # Description
>
> 给定两个字符串 s*s* 和 t*t*，计算字符串 s*s* 和 t*t* 公共子串对数量。
>
> 假设第一个字符串 s=(s1,s2,...,sn)*s*=(*s*1,*s*2,...,*s**n*) 和 t=(t1,t2,...,tm)*t*=(*t*1,*t*2,...,*t**m*) ，统计有多少对 (i,j,k)(*i*,*j*,*k*) 使得子串 si,...,si+k−1*s**i*,...,*s**i*+*k*−1 和tj,...,tj+k−1*t**j*,...,*t**j*+*k*−1“相等”。（其中 k>0,1≤i+k−1≤n,1≤j+k−1≤m*k*>0,1≤*i*+*k*−1≤*n*,1≤*j*+*k*−1≤*m* ）。
>
> 这里我们定义两个字符串s*s* 和 t*t*是相等当且仅当将两个字符串按照字典序排序之后，每一个位置都对应相等，例如字符串`abc`和字符串`acb`在这种定义下认为是相等的。
>
> # Format
>
> ## Input
>
> 第一行两个整数 n*n* 和m*m* 表示字符串长度。
>
> 第二行为长度为 n*n* 的字符串 s*s*和长度为 m*m* 的字符串t*t*。
>
> 两个字符串之间用空格隔开。
>
> ## Output
>
> 一个整数，表示字符串 s*s* 和 t*t* 公共子串对数量。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 7 7
> strange egnarts
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 28
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 2≤n,m≤30002≤*n*,*m*≤3000。

```c++
#include<bits/stdc++.h>
using namespace std;
const int base=26;
long long get_hush(const vector<int>& freq)
{
    long long my_h=0;
    for(int i=0;i<26;i++)my_h = my_h*base+freq[i];
    return my_h;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    string s,t;
    cin>>s>>t;
    long long ans=0;
    for(int k=1;k<=min(n,m);k++)
    {
        unordered_map<long long,int> s_sub,t_sub;
        vector<int> s_freq(26,0);
        vector<int> t_freq(26,0);
        for(int i=0;i<k;i++)
        {
            s_freq[s[i]-'a']++;
        }
        s_sub[get_hush(s_freq)]++;
        for(int i=k;i<n;i++)
        {
            s_freq[s[i]-'a']++;
            s_freq[s[i-k]-'a']--;
            s_sub[get_hush(s_freq)]++;
        }
        for(int i=0;i<k;i++)
        {
            t_freq[t[i]-'a']++;
        }
        t_sub[get_hush(t_freq)]++;
        for(int i=k;i<m;i++)
        {
            t_freq[t[i]-'a']++;
            t_freq[t[i-k]-'a']--;
            t_sub[get_hush(t_freq)]++;
        }
        for(auto& token:s_sub)
        {
            long long s_t=token.first;
            if(t_sub.count(s_t))
            {
                ans+=token.second*t_sub[s_t];
            }
        }
    }
    cout<<ans;
    return 0;
}
```

