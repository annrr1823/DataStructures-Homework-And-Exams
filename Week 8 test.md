# Week 8 test

[TOC]



## 序列延申与后缀查询

> ### 题目描述
>
> 有一个初始为空的序列 A*A*，在题目描述中，我们用 ai*a**i* 表示 A*A* 中的第 i*i* 个数字。
>
> 你需要支持以下两种操作：
>
> 1. 延申：在序列 A*A* 的尾部添加一个数 x*x*（形式化来说，假设当前 A*A* 中有 m*m* 个数，添加之后则有 m+1*m*+1 个数，且 am+1=x*a**m*+1=*x*）。
> 2. 查询：询问当前序列 A*A* 最后的 k*k* 个数中，最大的数是多少（形式化来说，假设当前 A*A* 中有 m*m* 个数，即询问 max{ai∣m−k+1≤i≤m}max{*a**i**m*−*k*+1≤*i*≤*m*} 的值） 。
>
> 为了强制你在线处理询问，输入数据进行了加密，你需要维护一个值叫 lastans*l**a**s**t**an**s* （**初始值为 00**），表示上一次询问操作的答案，并且需要使用 lastans*l**a**s**t**an**s* 来解密出真正的操作内容。具体细节可以查看输入格式。
>
> ### 输入格式
>
> 第一行，一个整数 n*n* ，表示操作的次数。
>
> 接下来 n*n* 行，每行输入两个加密后的整数 a,b*a*,*b* 。
>
> 你需要用 lastans*l**a**s**t**an**s* 解密得到 op,v*o**p*,*v* ，规则为：
>
> - op=lastans⊕a*o**p*=*l**a**s**t**an**s*⊕*a*
> - v=lastans⊕b*v*=*l**a**s**t**an**s*⊕*b*
>
> （其中 ⊕⊕ 表示按位异或运算，即 C++ 的 `^` 运算符）
>
> 如果 op=1*o**p*=1 ，那么执行延申操作，在序列 A*A* 尾部添加一个 v*v* 。
>
> 如果 op=2*o**p*=2 ，那么执行查询操作，询问序列 A*A* 最后的 v*v* 个数中，最大的数是多少。并且你需要在求解出这个答案之后，用此答案更新 lastans*l**a**s**t**an**s* ，以确保之后的操作能够正确解密。
>
> 输入保证第一个操作一定是延申操作，且 op=2*o**p*=2 时，v*v* 不会超过此时序列 A*A* 的长度。
>
> ### 输出格式
>
> 为了减少输出文件的大小，你并不需要按顺序输出所有询问的答案，你只需要输出一个值，表示所有询问的答案的和即可（请注意数据范围大小）。
>
> ### 样例 #1
>
> #### 样例输入 #1
>
> ```none
> 6
> 1 2
> 1 3
> 1 1
> 2 3
> 1 2
> 3 3
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #1
>
> ```none
> 7
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> 【样例解释】
>
> 首先进行了3次延申操作，使得序列 A={2,3,1}*A*={2,3,1} ，然后第四次操作询问了后3个数中的最大值，答案应当为 33 ，于是第五次操作解密后是询问后1个数中的最大值，答案为 11 ，然后第六次操作解密后是询问后2个数中的最大值，答案应当为 33 ，所以最后输出 3+1+3=73+1+3=7 .
>
> 【数据范围】
>
> 对于 100% 的测试数据满足 n≤106,1≤op≤2,1≤v≤109*n*≤106,1≤*o**p*≤2,1≤*v*≤109 .
>
> 输入保证第一个操作一定是延申操作，且 op=2*o**p*=2 时，v*v* 不会超过此时序列 A*A* 的长度。
>
> 请注意读入数据的效率。

```c
#include<bits/stdc++.h>
using namespace std;
bool cmp(const pair<long long,int>& a,const pair<long long,int>& b)
{
    return a.second<b.second;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    long long lastans=0;
    deque<pair<long long,int>> decrease;
    int m=0;
    long long sum = 0;
    while(n--)
    {
        long long a,b;
        cin>>a>>b;
        long long op = lastans^a;
        long long v=lastans^b;
        if(op==1)
        {
            m++;
            while(!decrease.empty() && decrease.back().first < v)
                decrease.pop_back();
            decrease.push_back({v,m});
        }
        else
        {
            int idx=m-v+1;
            auto it = lower_bound(decrease.begin(),decrease.end(),make_pair(0,idx),cmp);
            lastans = it->first;
            sum += lastans;
        }
    }
    cout<<sum;
    return 0;
}
```



## 疯狂插队

> > 规则4原表述有误，应为“不大于”，现已更正。
>
> # 题目描述
>
> 正在军训的 n*n* 名同学排成一排，每个人的武力值为 ai*a**i*。
>
> 由于 Y 不在，同学们不讲武德，开始插队。但是，插队也要满足基本法，规则如下：
>
> 1. 每个同学每次只能插到 **相邻** 同学的前面；
> 2. 如果 A 的武力值不小于 B，则 A 可以插在 B 的前面，否则不行；
> 3. 每个同学可以使用 **一次** “爆气” 技能，插在武力值比他大的人前面；
> 4. 使用 “爆气” 技能后，仍然可以插到武力值不大于其的同学前面。
>
> 请问，在这种规则下，每个同学都尽量往前插队，能插到的最前面的位置是什么（位置从 1 开始编号）。
>
> > 换言之，本题即对每个 i(1≤i≤n)*i*(1≤*i*≤*n*) 求解从第 i*i* 个人往前数第二个武力值大于 ai*a**i* 的人的位置+1，如果不存在则输出1。
>
> # 输入输出格式
>
> ## 输入格式
>
> 第一行一个整数 n*n* 表示同学的数量。
>
> 第二行 n*n* 个整数 a1,⋯ ,an*a*1,⋯,*a**n* 用空格隔开表示每个同学的武力值。
>
> ## 输出格式
>
> 一行 n*n* 个数用空格隔开表示每个同学能插到的最靠前的位置。
>
> # 样例
>
> ## 输入数据 1
>
> ```input1
> 5
> 5 4 2 1 2
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 1 1 2 3 2
> ```
>
> [Copy](javascript:;)
>
> # 数据范围
>
> 1≤n≤5×1061≤*n*≤5×106，1≤ai≤1091≤*a**i*≤109。

```c
#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 10;  

int a[N];      
int ans[N];   
int stk[N];    
bool tag[N];  

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;  
    cin>>n;;  

    // 读入每个同学的武力值
    for (int i = 1; i <= n; i++)
        cin>>a[i];

    // 初始化栈和标记
    int top = 0;  // 栈顶指针
    for (int i = n; i > 0; i--) {  // 从后向前遍历同学
        int tempStack[N];  // 临时存放需要回退的同学
        int nt = 0;  // 计数器，用于临时栈

        // 处理栈中同学
        while (top && a[i] > a[stk[top]]) {
            if (tag[stk[top]]) {
                // 如果同学已经使用过“爆气”，更新答案
                ans[stk[top]] = i + 1;
            } else {
                // 否则将其存入临时栈
                tempStack[++nt] = stk[top];
            }
            top--;  // 弹出栈顶元素
        }
        
        // 当前同学入栈
        stk[++top] = i;

        // 处理临时栈中的同学
        while (nt) {
            stk[++top] = tempStack[nt];  // 将待处理同学入栈
            tag[tempStack[nt]] = 1;      // 标记为使用过“爆气”
            nt--;  // 计数器递减
        }
    }

    // 处理栈中剩余的同学，设置他们的插队位置为1
    while (top) {
        ans[stk[top]] = 1;  // 未能插到前面的同学，答案为1
        top--;  // 弹出栈顶元素
    }

    for (int i = 1; i <= n; i++)
        cout<<ans[i]<<" ";
    
    return 0;
}

```



## 最大伤害值

> ## 题目背景
>
> 小思在玩一种战斗的电脑游戏，他的士兵们站成了一个 n*n* 行 m*m* 列的矩阵。每个士兵都有一个正整数体力值，形式化的来说，第 i*i* 行第 j*j* 列的士兵的体力值为 ci,j*c**i*,*j* 。因为士兵的数量实在是太多了，我们并不会通过输入来获取每个士兵的体力值，而是通过下面的规则表示士兵的体力值。
>
> 在这个问题中，士兵的体力值是由所在行列的体力加成值决定的。具体来说，有一列正整数 a1,a2⋯an*a*1,*a*2⋯*a**n* 分别表示第 1,2⋯n1,2⋯*n* 行的体力加成；同样，有一列正整数 b1,b2,⋯bm*b*1,*b*2,⋯*b**m* 分别表示第 1,2⋯m1,2⋯*m* 列的体力加成。据此，我们规定 ci,j=ai+bj*c**i*,*j*=*a**i*+*b**j* ，即为第 i*i* 行第 j*j* 列的士兵的体力值。
>
> 接下来，有一颗炮弹掉入了士兵矩阵中，如果这颗炮弹的伤害值为 D*D* ，那么所有士兵中只有体力值大于 D*D* 的士兵才能够活下来。
>
> 现在，小思希望至少有 K*K* 个士兵能够活下来。显然，如果要满足这个条件，炮弹的伤害值不能够太大，但是小思想知道，满足这个条件的炮弹伤害值 D*D* 最大是多少？由于士兵实在是太多了，请你来写个程序帮忙找出答案吧！
>
> ## 输入格式
>
> 第一行，输入三个正整数 n,m,K*n*,*m*,*K* ，分别表示士兵矩阵的行数和列数，以及小思希望至少存活的士兵数。
>
> 接下来一行，共 n*n* 个正整数，表示 a1,a2,⋯an*a*1,*a*2,⋯*a**n*，为每行的体力加成，意义见上文的题目描述。
>
> 接下来一行，共 m*m* 个正整数，表示 b1,b2,⋯bm*b*1,*b*2,⋯*b**m* ，为每列的体力加成，意义见上文的题目描述。
>
> ## 输出格式
>
> 输出一个整数，表示满足条件的伤害值 D*D* 的最大整数值。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 2 3 3
> 1 2
> 16 8 4
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 9
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> 2 3 4
> 1 2
> 3 4 5
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> 4
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 【样例解释】
>
> 在第二个样例中，士兵们的体力值为：
>
> [456567][455667]
>
> 要想至少 44 个人存活，那么炸弹的伤害值最大为 44，此时有 55 个人存活。
>
> 当伤害值为 55 的时候只有 33 个人存活因而不满足条件。
>
> 【数据范围】
>
> 对于 10% 的数据满足 n,m≤10*n*,*m*≤10
>
> 对于 25% 的数据满足 n,m≤70*n*,*m*≤70
>
> 对于 45% 的数据满足 n,m≤1000*n*,*m*≤1000
>
> 对于 70% 的数据满足 n,m≤5000*n*,*m*≤5000
>
> 对于 100% 的数据满足 n,m≤100000*n*,*m*≤100000，1≤K≤n⋅m1≤*K*≤*n*⋅*m*，1≤ai,bi≤1091≤*a**i*,*b**i*≤109

```c
#include <bits/stdc++.h>
using namespace std;

bool isValid(long long bomb, const vector<long long>& a, const vector<long long>& b, int n, int m, long long k) {
    long long survivor = 0;
    for(int i = 0; i < n; i++) {
        survivor += m - (upper_bound(b.begin(), b.end(), bomb - a[i]) - b.begin());
    }
    return survivor >= k;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    long long k;
    cin >> n >> m >> k; 
    
    vector<long long> a(n), b(m);
    for(int i = 0; i < n; i++) cin >> a[i]; 
    for(int i = 0; i < m; i++) cin >> b[i]; 
    sort(a.begin(),a.end());
    sort(b.begin(), b.end());

    // 二分查找炸弹的最大伤害值，初始范围为 0 到 a_max + b_max
    long long l = 0, r = *max_element(a.begin(), a.end()) + *max_element(b.begin(), b.end()), mid;
    
    while (l <= r) {
        mid = l + (r - l) / 2;
        
        if (isValid(mid, a, b, n, m, k)) 
            l = mid + 1; 
        else 
            r = mid - 1; 
    }
    
    cout << r << endl; 
    return 0;
}

```

