# Week 13 test

[TOC]

## A. 少林寺

略



## B. 新·合并果子

> ## 题目描述
>
> 乔治家后面有 n*n* 堆果子，第 i*i* 堆中有 ai*a**i* 个果子。
>
> 乔治想把这些果子合并成一堆。他仅可以执行以下操作：
>
> 选中两堆果子，不妨设其中一堆有 x*x* 个果子，另一堆有 y*y* 个果子，将这两堆果子合并成含有 x+y*x*+*y* 个果子的一堆。此次操作消耗的体力值是原来两堆果子数目的平均值，也就是 x+y22*x*+*y*。
>
> 现在，乔治已经帮你把果子堆按照果子数目排好了顺序，希望你为他找到一种策略，使得把所有果子合并成一堆，并且消耗尽可能少的体力值。请输出这个最少的体力消耗值，保留一位小数。
>
> ## 输入格式
>
> 第一行输入一个整数 T*T* 表示数据组数。
>
> 对于第一组数据，先输入一个整数 n*n* ，表示果子堆数。
>
> 接下来一行， n*n* 个整数，表示数列 ai*a**i* （ 保证 ∀i<j, ai≤aj∀*i*<*j*, *a**i*≤*a**j* ）。
>
> 对于剩下的 T−1*T*−1 组数据，将通过对上一组数据的数列 {ai}{*a**i*} 略作修改生成，规则如下：
>
> 对于每组数据，先输入一个整数 m*m* ，表示要修改的操作数。
>
> 接下来 m*m* 行，每行两个整数 u,v*u*,*v* ，表示把上一组数据中的第 u*u* 个数 au*a**u* 改为 v*v* （数据保证任何时刻都有 ∀i<j, ai≤aj∀*i*<*j*, *a**i*≤*a**j* ）.
>
> 当 m*m* 次修改完成后，你就得到了当前这组测试数据的数列 {ai}{*a**i*} ，你需要对这组数据求解出问题的答案。
>
> ## 输出格式
>
> 共 T*T* 行，每一行代表对应测试数据下，把 n*n* 个果子堆合并成一堆所消耗的体力值，输出保留一位小数。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 2
> 5
> 1 1 1 1 1
> 2
> 5 4
> 4 2
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 6.0
> 9.5
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 解释：对于样例1，有两组测试数据，第一组是 `1 1 1 1 1`， 第二组是 `1 1 1 2 4`。
>
> 对于 100% 的数据满足 1≤u≤n≤5×1051≤*u*≤*n*≤5×105 ， ∑m≤105∑*m*≤105 ， 1≤T≤201≤*T*≤20 ，1≤ai,v≤1091≤*a**i*,*v*≤109 。
>
> 注意每组数据（无论是否是经过修改而产生的）都保证 ∀i<j, ai≤aj∀*i*<*j*, *a**i*≤*a**j* 。
>
> 注意数据范围
>
> #### 注意到本题的提交语言禁用了O2优化，因此请尽量使用线性做法，并尽量避免使用STL库**注意到本题的提交语言禁用了****O2****优化，因此请尽量使用线性做法，并尽量避免使用****STL****库**

```c++
#include<bits/stdc++.h>
using namespace std;
vector<long long> a;
long long t,m,n;
void calculate()
{
    double ans=0.0;
    vector<long long> merd(2*n);
    long long front=0,end=0,cur_a=0;
    while(cur_a<n || front<end-1)
    {
        long long first,second;
        if((front < end && cur_a>=n) || (front<end && a[cur_a]>=merd[front]))
        {
            first = merd[front++];
        }
        else
        {
            first = a[cur_a++];
        }
        if((front < end && cur_a>=n) || (front<end && a[cur_a]>=merd[front]))
        {
            second = merd[front++];
        }
        else if(cur_a<n)
        {
            second = a[cur_a++];
        }
        else
        {
            break;
        }
        long long sum=first+second;
        ans+=sum/2.0;
        merd[end++]=sum;
    }
    printf("%.1f\n",ans);
    return;
}
int main()
{
    scanf("%lld",&t);
    scanf("%lld",&n);
    a.resize(n);
    for(int i=0;i<n;i++)scanf("%lld",&a[i]);
    calculate();
    while(--t)
    {
        scanf("%lld",&m);
        while(m--)
        {
            long long u,v;
            scanf("%lld %lld",&u,&v);
            a[u-1]=v;
        }
        calculate();
    }
    return 0;
}
```



## C. 田忌赛马

> # Description
>
> 齐王和田忌都很喜欢赛马，他们都会去市场上买马，然后在赛马场上一决高下。他们有一个君子约定，他们保证每匹马只会在一场比赛中登场，换而言之，比赛过的马就可以退休了。
>
> 为了赢得更多的比赛奖金，田忌希望尽量多地赢下比赛，于是他来找你，他最信任的谋士，商量赛马事宜。田忌告诉你，每次比赛齐王总会派出他当前能上的最好的马，让你来帮他安排田忌的马的出场顺序，使田忌的胜场最多。
>
> 由于方案可能不唯一，请你告诉田忌，他最多能赢多少场。
>
> # Format
>
> ## Input
>
> 第一行包含一个正整数 n*n* ，表示事件数。
>
> 接下 n*n* 行按时间顺序给出了 n*n* 个事件。每行有一个正整数 op*o**p* ,表示事件类型。若 op*o**p* 为 00 ,表示有一场比赛；否则代表齐王或田忌买了一匹马，接下来是一个正整数 grade*g**r**a**d**e* ,代表马的级别。若 op*o**p* 为 11 ,表示齐王买了一匹级别为 grade*g**r**a**d**e* 的马；若 op*o**p* 为 22 ,表示田忌买了一匹级别为 grade*g**r**a**d**e* 的马。
>
> **比赛时，若两匹马 grade\*g\**r\**a\**d\**e\* 相等，则算齐王获胜；若不等， grade\*g\**r\**a\**d\**e\* 较大的马胜**。
>
> **数据保证比赛时，齐王和田忌都有没参加过比赛的马。**
>
> ## Output
>
> 输出一行一个正整数，代表田忌最多能赢多少场。
>
> # Samples
>
> #### 样例输入
>
> ```none
> 9
> 1 1
> 1 2
> 1 3
> 2 1
> 2 2
> 2 3
> 0
> 0
> 0
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出
>
> ```none
> 2
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤1061≤*n*≤106
>
> op∈{0,1,2}*o**p*∈{0,1,2}
>
> 0≤grade≤1090≤*g**r**a**d**e*≤109

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    priority_queue<long long> qiwang;
    multiset<long long> tianji;
    long long ans=0;
    while(n--)
    {
        int op;
        cin>>op;
        if(op==1)
        {
            int grade;
            cin>>grade;
            qiwang.push(grade);
        }
        else if(op==2)
        {
            int grade;
            cin>>grade;
            tianji.insert(grade);
        }
        else
        {
            long long best=qiwang.top();
            qiwang.pop();
            auto it = tianji.upper_bound(best);
            if(it != tianji.end())
            {
                tianji.erase(it);
                ans ++;
            }
            else
            {
                tianji.erase(tianji.begin());
            }
        }
    }
    cout<<ans;
    return 0;
}
```

