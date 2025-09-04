# Week 5 test

[TOC]



## 最大子矩阵

> ### 题目描述
>
> 给定一个仅包含整数的二维方阵 AN×N*A**N*×*N*，求其所有子矩阵中矩阵和最大的一个。
>
> 一个子矩阵被定义为二维矩阵中大小为 1×11×1 或者更大的连续矩阵，矩阵和为其中所有元素的和。
>
> 例如，一个二维矩阵 A4×4*A*4×4 如下：
>
> ```none
> 0 -2 -7  0 
>  9  2 -6  2 
> -4  1 -4  1 
> -1  8  0 -2
> ```
>
> [Copy](javascript:;)
>
> 其中左下角的子矩阵为：
>
> ```none
> 9 2 
> -4 1 
> -1 8
> ```
>
> [Copy](javascript:;)
>
> 其矩阵和为 15。
>
> ### 输入格式
>
> 第一行包含一个整数 N*N*，表示二维方阵每一维的大小。
>
> 从二行开始每行 N*N* 个整数，表示方阵的每一行。共 N*N* 行。
>
> ### 输出格式
>
> 输出一行表示最大的子矩阵和。
>
> ### 样例
>
> #### 输入样例
>
> ```none
> 4
> 0 -2 -7 0 
> 9 2 -6 2
> -4 1 -4 1
> -1 8 0 -2
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 15
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> N≤100*N*≤100；
>
> ai,j∈[−127,127]*a**i*,*j*∈[−127,127]，ai,j*a**i*,*j* 为 AN×N*A**N*×*N* 中的元素。

```c++
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin>>n;
    vector<vector<int>> a(n,vector<int>(n,0));
    vector<vector<int>> pre(n,vector<int>(n,0));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];
    
    long long ans = -130;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            long long tmp = a[i][j];
            if(i>0)
            {
               tmp+=a[i-1][j];
            }
            if(j>0)
            {
                tmp +=a[i][j-1];
            }
            if(i>0 && j>0)
            {
                tmp -=a[i-1][j-1];
            }
            pre[i][j]=tmp;
            a[i][j]=tmp;
            //cout<<"fin: "<<fin<<endl;
            //cout<<endl;
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int p=0;p+i<n;p++)
            {
                for(int q=0;q+j<n;q++)
                {
                    long long sum = pre[i+p][j+q];
                    if(i>0)sum -= pre[i-1][j+q];
                    if(j>0)sum -= pre[i+p][j-1];
                    if(i>0 && j>0)sum += pre[i-1][j-1];
                    ans = max(ans,sum);
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```



## 周期循环

同作业



## 括号字符串转置

> ## 题目背景
>
> ### 问题描述
>
> 给定一个字符串 S=S1S2S3…S∣S∣*S*=*S*1*S*2*S*3…*S*∣*S*∣，由大写和小写的英文字母、`(` 、`)` 、`[` 和`]`组成。字符串 S*S* 中的括号是匹配的。
>
> 重复执行以下操作，直到无法再执行为止：
>
> - 首先，选择一对整数
>
>    
>
>   (l,r)(*l*,*r*)
>
>   ，满足以下所有条件：
>
>   - l<r*l*<*r*
>   - 字符串 Sl+1,Sl+2,…,Sr−1*S**l*+1,*S**l*+2,…,*S**r*−1 中的每个字符都是大写或小写的英文字母。
>   - Sl=*S**l*= `(`，Sr=*S**r*= `)`或Sl=*S**l*= `[`，Sr=*S**r*= `]`
>
> - 令
>
>    
>
>   T1=Sl+1Sl+2…Sr−1‾*T*1=*S**l*+1*S**l*+2…*S**r*−1
>
>    
>
>   ,
>
>    
>
>   T2=Sr−1Sr−2…Sl+1*T*2=*S**r*−1*S**r*−2…*S**l*+1
>
>   。
>
>   - 这里，x‾*x* 表示通过切换 x*x* 中每个字符的大小写（大写变小写，反之亦然）而得到的字符串。
>
> - 然后，删除 S*S* 中第 l*l* 到 r*r* 的字符，如果Sl=*S**l*= `(`，Sr=*S**r*= `)`则在删除位置插入字符串 T1*T*1，否则在删除位置插入字符串 T2*T*2。
>
> 可以证明，使用上述操作可以去除字符串中的所有 `(` 、`)` 、`[` 和`]`，并且最终字符串与操作的顺序无关。请确定最终的字符串。
>
> 字符串 S*S* 中的括号匹配是什么意思？首先，一个正确的括号序列定义如下：
>
> - 正确的括号序列是满足以下条件之一的字符串：
> - 它是一个空字符串
> - 他是一个仅包含大写或小写的英文字母的字符串。
> - 存在一个正确的括号序列 A*A*，该字符串由 `(`、A*A*、`)` 或 `[`、A*A*、`]` 依次连接而成。
> - 存在非空的正确括号序列 A*A* 和 B*B*，该字符串由 A*A* 和 B*B* 依次连接而成。
>
> 当且仅当从字符串 S*S* 中提取出的 `(` 和 `)`（保持顺序不变）形成一个正确的括号序列时，字符串 S*S* 中的括号才是匹配的。
>
> ## 输入格式
>
> 第一行输入一个字符串S*S*，保证S*S*由大写和小写的英文字母、`(` 、`)` 、`[` 和`]`组成且S*S* 中的括号是匹配的。
>
> ## 输出格式
>
> 输出一行，表示按照上述规则去除S*S*中的所有 `(` 、`)` 、`[` 和`]`后最终的字符串。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> [(A)y]x()
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> yax
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> S([VPX[w[t]PcV]PBG])
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> SgbpWTpCvxpv
> ```
>
> [Copy](javascript:;)
>
> ## 数据范围与提示
>
> 1≤∣S∣≤5×1051≤∣*S*∣≤5×105 。

```c++
//参考http://10.20.8.133/d/DS2023/record/66fa637fc7e3c70a968d222f

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

const int N = 1e6 + 10;

int n, pos;

char s[N], ans[N];
int sta[N], lst[N], nxt[N];

char change(char a) {
    if (a >= 'A' && a <= 'Z') return a - 'A' + 'a';
    if (a >= 'a' && a <= 'z') return a - 'a' + 'A';
    return a;
}

bool isalpha(char a) {
    return (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z');
}

void write_to_answer(int l, int r, bool reverse, bool convert_case) {
    if (reverse) {
        for (int i = r; i >= l; --i) {
            ans[++pos] = convert_case ? change(s[i]) : s[i];
        }
    } else {
        for (int i = l; i <= r; ++i) {
            ans[++pos] = convert_case ? change(s[i]) : s[i];
        }
    }
}

void process(int l, int r, bool reverse, bool convert_case) {
    if (l > r) return;
    
    if (reverse) {
        for (int i = r; i >= l; --i) {
            if (!isalpha(s[i])) {
                if (s[i] == ']') process(nxt[i] + 1, i - 1, !reverse, convert_case);
                else process(nxt[i] + 1, i - 1, reverse, !convert_case);
                i = nxt[i];
            } else {
                int j = i;
                while (j >= l && isalpha(s[j])) --j;
                write_to_answer(j + 1, i, reverse, convert_case);
                i = j+1;
            }
        }
    } else {
        for (int i = l; i <= r; ++i) {
            if (!isalpha(s[i])) {
                if (s[i] == '[') process(i + 1, lst[i] - 1, !reverse, convert_case);
                else process(i + 1, lst[i] - 1, reverse, !convert_case);
                i = lst[i];
            } else {
                int j = i;
                while (j <= r && isalpha(s[j])) ++j;
                write_to_answer(i, j - 1, reverse, convert_case);
                i = j-1;
            }
        }
    }
}

int main() {
    scanf("%s", s + 1);
    int len = strlen(s + 1), top = 0;
    for (int i = 1; i <= len; ++i) {
        if (s[i] == '[' || s[i] == '(') {
            sta[++top] = i;
        }
        if (s[i] == ']' || s[i] == ')') {
            lst[sta[top]] = i;
            nxt[i] = sta[top--];
        }
    }
    process(1, len, false, false);
    for (int i = 1; i <= pos; ++i) {
        printf("%c", ans[i]);
    }
    return 0;
}

```

