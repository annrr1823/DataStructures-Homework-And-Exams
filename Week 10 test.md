# Week 10 test

[TOC]



## A. 双人旋转赛车 II

略



## B. B - A

> # Description
>
> Pareto*P**a**re**t**o* 法则，也就是 80/2080/20 规则，很情形下，20%20% 的因素导致 80%80% 的结果。比如，微软发现，修复 20%20% 被报告的bug，他们消除系统 80%80% 关机时间。在商业界，20%20% 的人拥有 80%80% 的收入。
>
> 你的任务是检查在某家银行，这个规则的靠谱程度。20%20% 的账户真的拥有 80%80% 的钱？或者更夸张的， 10%10% 的账户拥有 85%85% 的钱？
>
> 更清楚地，根据 N*N* 个客户的账户余额，你的任务是确定实数 A*A* ， B*B* ，使得 B−A*B*−*A* 最大化，同时有 A%*A*% 的人拥有 B%*B*% 的钱。
>
> # Format
>
> ## Input
>
> 第一行一个整数 N*N* 。
>
> 第二行 N*N* 个正整数，不超过 105105。
>
> ## Output
>
> 输出一个数，表示 B−A*B*−*A* 的最大值。
>
> 接受的误差在 0.00010.0001 以内。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 2
> 100 200
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 16.666666
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 5
> 5 5 5 5 80
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> 60
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 3
>
> ```none
> 6
> 10 20 30 40 50 60
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 3
>
> ```none
> 21.428571
> ```
>
> # Limitation
>
> 1≤N≤50001≤*N*≤5000，**数据保证第二行的 N\*N\* 个数从小到大排序**。
>
> 对于第一个样例而言， 50%50% 的账户（200200 元）拥有所有钱的 66.666667%66.666667%，66.666667%−50%=16.666667%66.666667%−50%=16.666667%。
>
> 对于第二个样例而言， 20%20% 的账户（8080 元）拥有所有钱的 80%80%，80%−20%=60%80%−20%=60%。
>
> 对于第三个样例而言， 50%50% 的账户（40+50+60=15040+50+60=150 元）拥有所有钱的 71.428571%71.428571%，71.428571%−50%=21.428571%71.428571%−50%=21.428571%

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n;
    cin>>n;
    vector<double> a(n);
    double sum=0;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)sum += a[i];
    // priority_queue<int> pq;//big_top
    double each_peaople=100.0/n;
    double now_people=0;
    double now_sum=0;
    double prev_diff=0;
    double now_diff=0;
    for(int i=n-1;i>=0;i--)
    {
        prev_diff=now_diff;
        now_people+=each_peaople;
        now_sum+=a[i];
        now_diff = (double)(now_sum/sum)*100 - now_people;
        //cout<<a[i]<<" "<<each_peaople<<" "<<now_people<<" "<<(now_sum/sum)*100<<" "<<now_diff<<" "<<prev_diff<<endl;
        if(now_diff<prev_diff)break;
    }
    cout<<prev_diff;
    return 0;
}
```



## C. 模后和

> # Description
>
> HMP_Haoge 编写了一款开放世界游戏。游戏中有一个关于战斗的小游戏，首先玩家拥有 n*n* 个战士，它们的战斗力分别为 a1,a2,⋯an*a*1,*a*2,⋯*a**n* ；接着，玩家拥有 n*n* 个辅助，它们的辅助力分别为 b1,b2,⋯bn*b*1,*b*2,⋯*b**n* 。
>
> 现在，玩家需要将这 2n2*n* 个角色分为 n*n* 组，每组为一个战士和一个辅助，每组的战斗力为组内战士战斗力和辅助的辅助力之和。然而，开发者在开发时不小心写了一个bug，它将每个组的战斗力对 n*n* 进行了取模。形式化来说，对于第 x*x* 组，我们记该组的战斗力为 cx*c**x*，假设该组由第 i*i* 个战士和第 j*j* 个辅助组成，那么 cx=(ai+bj)mod  n*c**x*=(*a**i*+*b**j*)mod*n*。
>
> 你发现了这个bug，但是你却无法改变它，这时你作为玩家，你希望完成分组，并且使得所有组的战斗力之和最大，即最大化 ∑x=1ncx∑*x*=1*n**c**x*。
>
> 你只需要输出这个最大的战斗力之和即可。
>
> # Format
>
> ## Input
>
> 首先输入一个正整数 T*T* ，表示数据组数。
>
> 对于每组数据：
>
> 第一行，一个整数 n*n* 表示战士和辅助的数目；
>
> 第二行， n*n* 个整数，第 i*i* 个数表示 ai*a**i* ；
>
> 第三行， n*n* 个整数，第 i*i* 个数表示bi*b**i* ；
>
> 保证 T*T* 组测试数据的 ∑n∑*n* 不超过 2×1052×105 。
>
> ## Output
>
> 对于每组数据，输出一行，一个整数，表示最大的∑i=1nci∑*i*=1*n**c**i*
>
> # Samples
>
> ### 样例输入 #1
>
> ```none
> 2
> 4
> 31 45 92 65
> 35 89 79 32
> 10
> 1 1 4 5 1 4 1 1 4 5
> 1 9 1 9 8 1 0 1 9 1
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 8
> 37
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 【样例解释】
>
> 用二元组 (i,j)(*i*,*j*) 表示把 ai*a**i* 和 bj*b**j* 分为一组。
>
> 那么对于第一组数据，可以采用的分组方案为：(1,3),(2,4),(3,1),(4,2)(1,3),(2,4),(3,1),(4,2)
>
> 此时得到最大的战斗力和为：
>
> {(31+79)mod4}+{(45+32)mod4}+{(92+35)mod4}+{(65+89)mod4}=2+1+3+2=8{(31+79)mod4}+{(45+32)mod4}+{(92+35)mod4}+{(65+89)mod4}=2+1+3+2=8
>
> 【数据范围】
>
> 1≤T≤2×1051≤*T*≤2×105
>
> 1≤n≤2×105,∑n≤2×1051≤*n*≤2×105,∑*n*≤2×105，0≤ai,bi≤2×1050≤*a**i*,*b**i*≤2×105

```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while (t--)
    {
        int n;
        cin>>n;
        vector<int> a(n),b(n);
        for(int i=0;i<n;i++)cin>>a[i];
        for(int i=0;i<n;i++)cin>>b[i];
        for(int i=0;i<n;i++)a[i]%=n;
        for(int i=0;i<n;i++)b[i]%=n;
        sort(a.begin(),a.end());
        sort(b.begin(),b.end());
        long long sum=0;
        for(int i=0;i<n;i++)sum += (a[i]+b[i]);
        priority_queue<int,vector<int>,greater<int>> b_small_top(b.begin(),b.end());
        for(int i=n-1;i>=0;i--)
        {
            if(a[i]+b_small_top.top() <n)
                b_small_top.pop();
            else sum -=n;
        }
        cout<<sum<<endl;
    }
    return 0;
}
```

