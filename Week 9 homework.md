# Week 9 homework

[TOC]

## 中庸之道 I

> # Description
>
> Y 在以前都只关注“美丽值”高的同学，他觉得这种同学才是顶呱呱的。
>
> 可是，恰逢 X 来视察军训的同学，而 X 喜欢“中庸”的同学，即美丽值处于中位数的同学。
>
> Y 为了迎合 X 的品味，也开始关注同学们美丽值的中位数。Y 希望你能设计一个数据结构，来实现如下两种操作，
>
> 1. `1 x`，表示加入一名美丽值为 x*x* 的同学。
> 2. `2`，表示查询所有同学美丽值的中位数。
>
> 注意，最开始的时候没有任何同学。中位数的定义为在所有同学按美丽值从小到大排序后的序列 A*A* 中，下标为 ⌈∣A∣2⌉⌈2∣*A*∣⌉ 的同学的美丽值。
>
> # Format
>
> ## Input
>
> Y 在以前都只关注“美丽值”高的同学，他觉得这种同学才是顶呱呱的。
>
> 可是，恰逢 X 来视察军训的同学，而 X 喜欢“中庸”的同学，即美丽值处于中位数的同学。
>
> Y 为了迎合 X 的品味，也开始关注同学们美丽值的中位数。Y 希望你能设计一个数据结构，来实现如下两种操作，
>
> 1. `1 x`，表示加入一名美丽值为 x*x* 的同学。
> 2. `2`，表示查询所有同学美丽值的中位数。
>
> 注意，最开始的时候没有任何同学。中位数的定义为在所有同学按美丽值从小到大排序后的序列 A*A* 中，下标为 ⌈∣A∣2⌉⌈2∣*A*∣⌉ 的同学的美丽值。
>
> ## Output
>
> 依次对于每个操作 `2`，输出美丽值的中位数。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 6
> 1 5
> 2
> 1 6
> 1 3
> 1 2
> 2
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 5
> 3
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤q≤2×1051≤*q*≤2×105，−109≤x≤109−109≤*x*≤109。
>
> 保证输入的第一个操作不为 `2`。

```c
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int q;
    cin>>q;
    priority_queue<long long> small_ones;//big on the top
    priority_queue<long long,vector<long long>,greater<long long>> big_ones;//small on the top
    int n=0;
    while(q--)
    {
        int op;
        cin>>op;
        if(op==1)
        {
            long long x;
            cin>>x;
            n++;
            
            if(small_ones.empty() || x<small_ones.top())small_ones.push(x);
            else big_ones.push(x);
            
            
            while((int)small_ones.size()>(n+1)/2 )
            {
                big_ones.push(small_ones.top());
                small_ones.pop();
            }
            while((int)small_ones.size()<(n+1)/2 )
            {
                small_ones.push(big_ones.top());
                big_ones.pop();
            }
        }
        else
        {
            cout<<small_ones.top()<<endl;
        }
    }
    return 0;
}
```



## 作业狂魔

> ## 题目背景
>
> from Gym
>
> ## 题目描述
>
> PW*P**W*是一个作业狂魔。
>
> 寒假里一共有n*n*份作业，每份作业都有一个难度值，PW*P**W*喜欢享受洗刷作业的快感，于是必定按照作业的布置顺序完成作业。他会把作业分配到寒假每一天来完成，每一天他都必须至少完成一份作业。每天他获得的快乐值是当天所完成的这些作业中的最大难度值。
>
> 由于寒假爆发了疫情，所以假期可能会比较长，一共有k*k*天。
>
> PW整个寒假获得的快乐值就是每天的快乐值之和。
>
> PW按照作业布置的从先到后的顺序告诉你每份作业的难度值。他希望你为他合理分配作业到每一天，并且输出他寒假能获得的最大快乐值。
>
> ## 输入格式
>
> 第一行，正整数n*n*，正整数k*k*.
>
> 接下来n*n*个正整数，ai*a**i*，表示按照布置顺序，给出作业的难度值。
>
> ## 输出格式
>
> 输出PW*P**W*寒假的最大快乐值。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 2 1
> 3 1
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 3
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> 2 2
> 3 100
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> 103
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 对30%的数据满足：n≤100*n*≤100
>
> 对100%的数据满足：1≤k≤n≤20001≤*k*≤*n*≤2000，1≤ai≤10001≤*a**i*≤1000

```c
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,k;
    cin>>n>>k;
    vector<int> a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    priority_queue<int> pq(a.begin(),a.end());
    long long sum = 0;
    while(k--)
    {
        sum += pq.top();
        pq.pop();
    }
    cout<<sum<<endl;
    return 0;
}
```



## 双人旋转赛车 II

> # 题目描述
>
> ZZR 和 LJZ 在玩一个双人旋转赛车的小游戏。
>
> 他们将进行一些比赛。每局比赛必须按顺序进行，胜者会得到该局对应的分数 xi*x**i* 。
>
> 由于 ZZR 技艺不精（**每局都可以由 LJZ 决定胜负**），因此他给自己设置了初始分数 k*k* ，希望自己能够一直领先 ZZR。
>
> 不过 LJZ 识破了 ZZR 的诡计，现在 LJZ 想知道自己至少需要赢几局才可以使得自己能够在**某一时刻的比分不落后**于 ZZR。
>
> 若无法达到则输出 −1−1 。
>
> # 输入输出格式
>
> ## 输入格式
>
> 第一行两个整数 n,k*n*,*k*，表示游戏局数以及 ZZR 初始分数。
>
> 第二行 n*n* 个整数 xi*x**i* ，表示每局游戏的分数。
>
> ## 输出格式
>
> 一个整数，表示答案。
>
> # 样例
>
> #### 输入样例 1
>
> ```none
> 3 3
> 4 1 2
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 1
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 3 7
> 1 2 3
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> -1
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 3
>
> ```none
> 12 40
> 8 6 6 5 3 2 8 2 1 8 8 3
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 3
>
> ```none
> 7
> ```
>
> [Copy](javascript:;)
>
> # 数据范围
>
> 1≤n≤2×105,0≤xi,k≤1091≤*n*≤2×105,0≤*x**i*,*k*≤109。
>
> 样例一：LJZ 只需要赢第一局，即可获得 44 分，这时候就领先于 ZZR 11 分。
>
> 样例二：LJZ 全胜也领先不了。
>
> 样例三：LJZ 选择赢第 1,2,3,4,7,10,111,2,3,4,7,10,11场比赛，获得 8+6+6+5+8+8+8=498+6+6+5+8+8+8=49 分，截止第 1111 场为止，ZZR 得分为 40+3+2+2+1=4840+3+2+2+1=48 分，此时 LJZ 领先 ZZR 11 分。（特别注意，如果 LJZ 采用的策略是开始一直赢，那么需要 88 场才能不落后于 ZZR 的 4040 分，不是最优解。）

```c
#include<bits/stdc++.h>
using namespace std;

bool can_win(int n,long long k,int time,const vector<long long>& x)
{
    long long sum=0;
    priority_queue<long long,vector<long long>,greater<long long>> pq;//small_top
    for(int i=0;i<time;i++)
    {
        pq.push(x[i]);
        sum += x[i];
    }
    if(sum >= k)return 1;
    else
    {
        for(int i=time;i<n;i++)
        {
            sum += x[i];
            sum -= pq.top();
            k += pq.top();
            pq.pop();
            pq.push(x[i]);
            if(sum >= k)return 1;
        }
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    long long k;
    cin>>n>>k;
    vector<long long> x(n);
    for(int i=0;i<n;i++)cin>>x[i];
    int left=1,right=n;
    while(left<=right)
    {
        int mid = left +(right-left)/2;
        if(can_win(n,k,mid,x))right = mid-1;
        else left = mid+1;
    }
    if(left>n)cout<<-1<<endl;
    else cout<<left<<endl;
    return 0;
}
```



## 排序

> **本题只允许使用C语言提交**
>
> ### 题目背景
>
> 我们定义一个随机数生成器 `xorshift()` 函数。
>
> ```c
> unsigned int xorshift(unsigned int x){
>     x ^= x << 13;
>     x ^= x >> 17;
>     x ^= x << 5;
>     return x;
> }
> ```
>
> [Copy](javascript:;)
>
> 现在，告诉你两个整数 n,x0*n*,*x*0 ，需要你用这个随机数生成器生成 x1,x2⋯xn*x*1,*x*2⋯*x**n* 。
>
> 其中，xi=xorshift(xi−1)*x**i*=xorshift(*x**i*−1) ， 1≤i≤n1≤*i*≤*n* 。
>
> 然后，你需要将 x1,x2⋯xn*x*1,*x*2⋯*x**n* 从小到大排序，使得 x1≤x2≤⋯xn*x*1≤*x*2≤⋯*x**n* 。
>
> 对于排序后的序列，并不要求你输出整个数列。为了防止输出量太大，你只需要输出 ∑i=1ni⋅xi∑*i*=1*n**i*⋅*x**i* 对 232232 取模的结果即可。
>
> ### 输入格式
>
> 第一行，两个整数 n,x0*n*,*x*0 。
>
> ### 输出格式
>
> 输出一个整数，表示答案（注意数据范围）。
>
> ### 样例 #1
>
> #### 样例输入 #1
>
> ```none
> 3 1
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #1
>
> ```none
> 3782878834
> ```
>
> [Copy](javascript:;)
>
> #### 样例输入 #2
>
> ```none
> 3 2147483647
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #2
>
> ```none
> 262620378
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> 对于 100% 的测试数据满足 n≤3×107*n*≤3×107 .
>
> 一般来说，Xorshift 算法可以产生较为均匀的分布。
>
> **提示：**
>
> 相同复杂度的算法，使用 STL 实现的时空间常数通常高于自己的手动实现。
>
> 如果你认为复杂度正确，但是超时，可以考虑把基于 STL 容器的实现改为手动实现。
>
> 注意数据范围，此题的数值属于 `unsigned int` 范畴。
>
> **样例解释**
>
> 样例1的三个数排序后为：
>
> ```none
> 270369 67634689 2647435461
> ```
>
> [Copy](javascript:;)
>
> 于是 270369+2×67634689+3×2647435461mod232=3782878834270369+2×67634689+3×2647435461mod232=3782878834
>
> **一些看上去没用且无关的知识**
>
> - [时钟周期](https://baike.baidu.com/item/时钟周期/1545064)是频率的倒数，它是处理器操作的最小时间单位。
> - 本OJ目前使用的CPU为Intel core I3-4130，发售于2013年。查询[官网](https://www.intel.cn/content/www/cn/zh/products/sku/77480/intel-core-i34130-processor-3m-cache-3-40-ghz/compatible.html)可知此CPU为双核四线程，拥有3.4GHz的主频和3MB的高速缓存。其三级缓存分别为 32KB(每核心)、256KB(每核心)、3MB（共享）。
> - CPU中，L1缓存拥有最小的容量和最快的访存速度，具体时钟周期依型号而定，但可认为L1普遍只需1-5个时钟周期，其所用时间是L2的14∼1341∼31，L2是L3的13∼1231∼21，而L3缓存的访存速度远大于内存。
> - CPU在处理各类运算指令时会将其移交对应的运算器进行，不同的运算器具有不同的时钟周期。你可以假定加法只要1-3个时钟周期，乘法一般要大约10个时钟周期，除法约20-50时钟周期。在本机CPU上你可以直接将除法视为>40。取模器与除法器配套。但位运算由于优越的二进制性质，一般可以只用1个时钟周期。
> - 在一般的CPU中，对分支指令(包括`if`, `while` 和 `for`的判断条件)都会产生预测，预测失败一般会带来额外的时间开销。

```c
#include <stdio.h>
#include <stdlib.h>

unsigned int xorshift(unsigned int x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

void radix_sort(int n, unsigned int *a) {
    unsigned int *b = (unsigned int *)malloc(n * sizeof(unsigned int));
    
    unsigned int *cnt = (unsigned int *)malloc(257* sizeof(unsigned int));

    for (int i = 0; i < 32; i += 8) {
        for (int j = 0; j < 256; j++) {
            cnt[j] = 0;
        }

        for (int j = 0; j < n; j++) {
            cnt[(a[j] >> i) & 0xFF]++;
        }

        for (int sum = 0, j = 0; j != (1 << 8); ++j) {
            sum += cnt[j], cnt[j] = sum - cnt[j];
        }

        for (int j = 0; j < n; j++) {
            b[cnt[(a[j] >> i) & 0xFF]++] = a[j];
        }

        for (int j = 0; j < n; j++) {
            a[j] = b[j];
        }
    }

    free(cnt);
    free(b);
}


int main() {
    unsigned int n, x0;
    scanf("%u %u", &n, &x0);

    unsigned int *sequence = (unsigned int *)malloc((n+1) * sizeof(unsigned int));
    sequence[0] = x0;
    for (unsigned int i = 1; i <= n; i++) {
        sequence[i] = xorshift(sequence[i - 1]);
    }

    radix_sort(n, sequence+1);

    unsigned int sum = 0;
    for (unsigned int i = 1; i <= n; i++) {
        sum = (sum + (i) * sequence[i]) & 0xFFFFFFFF;
    }

    printf("%u\n", sum);
    free(sequence);
    return 0;
}

```



## 人齐了？

> # 题目描述
>
> Y 今天没带眼镜，当他检阅军训同学时，只能看到同学们的“美丽值”。这意味着，美丽值相同的同学会被 Y 看成相同的同学。
>
> 对于 n*n* 名同学的序列，每个同学的美丽值为 ai*a**i*。Y 想知道，有多少不同的序列区间，满足其中至少出现 k*k* 种不同的美丽值。
>
> # 输入输出格式
>
> ## 输入格式
>
> 第一行两个整数 n,k*n*,*k* 用空格隔开。
>
> 第二行 n*n* 个整数用空格隔开表示 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*。
>
> ## 输出格式
>
> 一行一个整数表示合法的区间个数。
>
> # 样例
>
> #### 输入样例
>
> ```none
> 5 3
> 7 9 10 7 7
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 5
> ```
>
> [Copy](javascript:;)
>
> # 数据范围
>
> 1≤k≤n≤3×1061≤*k*≤*n*≤3×106，1≤ai≤1091≤*a**i*≤109。

```c++
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

long long countIntervals(int n, int k, const vector<int>& a) {
    unordered_map<int, int> count;
    int unique_count = 0;
    long long result = 0;
    int left = 0;
    
    for (int right = 0; right < n; ++right) {
        if (++count[a[right]] == 1) {
            unique_count++;
        }

        while (unique_count >= k) {
            result += n - right;
            if (--count[a[left]] == 0) {
                unique_count--;
            }
            left++;
        }
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)cin >> a[i];
    cout << countIntervals(n, k, a) << endl;
    return 0;
}

```

