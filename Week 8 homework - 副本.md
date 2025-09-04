# Week 8 homework

[TOC]

## 五折券

> # Description
>
> ZZR 打算买 n*n* 个商品，其中第 i*i* 个商品的价格为 ai*a**i* 元，现在 ZZR 有 m*m* 张五折券。
>
> 若他买第 i*i* 个商品使用了 Y*Y* 张打折券，则他购买这个商品只需要花费 ⌊ai2Y⌋⌊2*Y**a**i*⌋ 元。
>
> ZZR 想请你帮他计算一下，他购买这些商品至少要花费多少元？
>
> # Format
>
> ## Input
>
> 第一行包含两个整数 n,m*n*,*m* 表示商品数量和五折券数量。
>
> 第二行 n*n* 个正整数，表示每个商品的价格 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*。
>
> ## Output
>
> 一个整数，表示 ZZR 购买这些商品最少需要花费多少元。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 3 3
> 2 13 8
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 9
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 4 4
> 1 9 3 5
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
> 1 100000
> 1000000000
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 3
>
> ```none
> 0
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤105，1≤m≤2×1051≤*n*≤105，1≤*m*≤2×105，1≤ai≤1091≤*a**i*≤109。
>
> 对于第一个样例，ZZR 购买第一个商品不使用打折券，花费 2 元，购买第二个商品使用两张打折券，花费 3 元，购买第三个商品使用一张打折券，花费 4 元，一共花费 9 元。

```c
#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin>>n>>m;
    vector<long long> a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    priority_queue<long long> price(a.begin(),a.end());
    while(m--)
    {
        long long cur = price.top()/2;
        price.pop();
        price.push(cur);

    }
    long long sum = 0;
    while(!price.empty())
    {
        sum += price.top();
        price.pop();
    }
    cout<<sum;
    return 0;
}
```



## 前缀的TopK

> # Description
>
> 给定一个长度为 n*n* 的数组 a*a*，输出所有前缀子数组的前 k*k* 大的数之和。
>
> # Format
>
> ## Input
>
> 第一行两个整数 n,k*n*,*k*。
>
> 第二行 n*n*个整数表示这个数组中的数。
>
> ## Output
>
> 总共 n−k+1*n*−*k*+1 个数，假设数组表示为 a1,a2,...,an*a*1,*a*2,...,*a**n*，则第 i*i* 个输出 fi=Sum-Topk(a1,a2,...,ak+i−1)*f**i*=Sum-Topk(*a*1,*a*2,...,*a**k*+*i*−1) ，其中 Sum-TopkSum-Topk 返回一个数组中前 k*k* 大的元素的和。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 6 3
> 2 6 3 4 5 1
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 11 13 15 15
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 8 3
> 1 3 -1 -3 5 3 6 7
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> 3 3 9 11 14 18
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤k≤n≤105,−109≤ai≤1091≤*k*≤*n*≤105,−109≤*a**i*≤109 。
>
> 对于第2个样例的解释：
>
> | 前缀数组            | Top-k    | 和   |
> | :------------------ | :------- | :--- |
> | [1 3 -1] -3 5 3 6 7 | [1 3 -1] | 3    |
> | [1 3 -1 -3] 5 3 6 7 |          |      |
> | [1 3 -1 -3 5] 3 6 7 | [1 3 5]  | 9    |
> | [1 3 -1 -3 5 3] 6 7 | [3 3 5]  | 11   |
> | [1 3 -1 -3 5 3 6] 7 | [3 5 6]  | 14   |
> | [1 3 -1 -3 5 3 6 7] | [5 6 7]  | 18   |
>
> **额外提示：n×k\*n\*×\*k\* 可能很大，答案可能超过int范围。**

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
    vector<long long> a(k);
    long long sum = 0;
    for(int i=0;i<k;i++)
    {
        cin>>a[i];
        sum += a[i];
    }
    cout<<sum<<" ";
    priority_queue<long long,vector<long long>,greater<long long>> top_k(a.begin(),a.end()); //small on the top
    for(int i=0;i<n-k;i++)
    {
        long long cur;
        cin>>cur;
        long long small_top=top_k.top();
        if(small_top < cur)
        {
            top_k.pop();
            top_k.push(cur);
            sum -= small_top;
            sum += cur;
        }
        cout<<sum<<" ";

    }
    return 0;
}
```



## 血魔训练 II

> # Description
>
> ZZR 经常玩 DOTA2，尤其喜欢玩血魔。现在 ZZR 正在练习玩血魔。
>
> 血魔的技能之一为，每当他击杀一个英雄单位后，他能够回复该英雄生命值上限百分比的血量。在此题中：
>
> 假设 ZZR 有 x*x* 滴血，现在有 n*n* 个敌方英雄。ZZR 杀死每个敌方英雄需要损失 ai*a**i* 滴血，但是当他杀死该英雄之后能够恢复 bi*b**i* 滴血。
>
> 当 ZZR 血量小于或等于 0 时 ZZR 就阵亡，训练结束。
>
> ZZR 想要击杀尽可能多的敌方英雄，请问他在保证自己不阵亡的情况下，能否击杀所有英雄。
>
> # Format
>
> ## Input
>
> 第一行包括两个数 n,x*n*,*x*，分别表示 n*n* 个英雄和 x*x* 滴血。
>
> 第二行包括 n*n* 个数 a1,⋯ ,an*a*1,⋯,*a**n*，表示 ZZR 击杀每个英雄所需要消耗的血量。
>
> 第三行包括 n*n* 个数 b1,⋯ ,bn*b*1,⋯,*b**n*，表示 ZZR 击杀每个英雄恢复的血量。
>
> ## Output
>
> “YES” 或 “NO”，表示能否击杀所有英雄。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 4 10
> 12 11 2 3
> 10 2 5 4
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> YES
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 3 10
> 6 8 7
> 2 6 4
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> NO
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤1051≤*n*≤105，1≤x,ai,bi≤1091≤*x*,*a**i*,*b**i*≤109。
>
> 样例 1 解释：ZZR 首先击杀第 3 个英雄，还剩 13 滴血，再击杀第 4 个英雄，还剩 14 滴血，再击杀第 1 个英雄，还剩 12 滴血，最后击杀第 2 个英雄，还剩 3 滴血。如果 ZZR 在击杀第 3、4 个英雄后先击杀第 2 个英雄后剩 3 滴血，剩余血量就无法击杀第 1 个英雄。

```c
#include<bits/stdc++.h>
using namespace std;
struct hero{
    long long a,b,d;
};
bool cmp_a(const hero& x,const hero& y)
{
    return x.d>y.d;
}
bool cmp_b(const hero& x,const hero& y)
{
    return x.a<y.a;
}
bool cmp_c(const hero& x,const hero& y)
{
    return x.b>y.b;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    long long x;
    cin>>n>>x;
    vector<hero> heros(n);
    for(int i=0;i<n;i++)cin>>heros[i].a;
    for(int i=0;i<n;i++)cin>>heros[i].b;
    for(int i=0;i<n;i++)heros[i].d = heros[i].b - heros[i].a;
    vector<hero> beni_small,beni_big,harm;
    for(int i=0;i<n;i++)
    {
        if(heros[i].d >= 0 && heros[i].a < x)
        {
            beni_small.push_back(heros[i]);
        }
        else if(heros[i].d >= 0)
        {
            beni_big.push_back(heros[i]);
        }
        else{
            harm.push_back(heros[i]);
        }
    }
    sort(beni_small.begin(),beni_small.end(),cmp_a);
    sort(beni_big.begin(),beni_big.end(),cmp_b);
    sort(harm.begin(),harm.end(),cmp_c);
    for(auto token:beni_small)
    {
        if(x>token.a)
        {
            x-=token.a;
            x+=token.b;
        }
        else
        {
            cout<<"NO"<<endl;
            return 0;
        }
    }
    for(auto token:beni_big)
    {
        if(x>token.a)
        {
            x-=token.a;
            x+=token.b;
        }
        else
        {
            cout<<"NO"<<endl;
            return 0;
        }
    }
    for(auto token:harm)
    {
        if(x>=token.a)
        {
            x-=token.a;
            x+=token.b;
        }
        else
        {
            cout<<"NO"<<endl;
            return 0;
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
```



## 区间乘积的分类

> ## 题目背景
>
> from Gym
>
> ## 题目描述
>
> 这是一道送分题。
>
> 有一个长度为n*n*的整数序列a1*a*1，a2*a*2，…an*a**n*
>
> 接下来你需要求三个值：
>
> 1.有多少个点对(l,r)(*l*,*r*)，满足l≤r*l*≤*r*且al⋅al+1⋅⋅⋅ar−1⋅ar<0*a**l*⋅*a**l*+1⋅⋅⋅*a**r*−1⋅*a**r*<0
>
> 2.有多少个点对(l,r)(*l*,*r*)，满足l≤r*l*≤*r*且al⋅al+1⋅⋅⋅ar−1⋅ar=0*a**l*⋅*a**l*+1⋅⋅⋅*a**r*−1⋅*a**r*=0
>
> 3.有多少个点对(l,r)(*l*,*r*)，满足l≤r*l*≤*r*且al⋅al+1⋅⋅⋅ar−1⋅ar>0*a**l*⋅*a**l*+1⋅⋅⋅*a**r*−1⋅*a**r*>0
>
> ## 输入格式
>
> 第一行，正整数n*n*.
>
> 接下来一行，n*n*个整数。
>
> ## 输出格式
>
> 一行三个整数，用空格隔开，分别对应题目描述中的三个问题的答案。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 5 
> 5 -3 3 -1 0
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 6 5 4
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> 10 
> 4 0 -4 3 1 2 -4 3 0 3
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> 12 32 11
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #3
>
> ### 样例输入 #3
>
> ```none
> 5 
> -1 -2 -3 -4 -5
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #3
>
> ```none
> 9 0 6
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 对30%的数据满足：n≤1000*n*≤1000
>
> 对100%的数据满足：1≤n≤2000001≤*n*≤200000，−109≤ai≤109−109≤*a**i*≤109

```c
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)cin >> a[i];

    long long negative_pairs = 0; 
    long long zero_pairs = 0; 
    long long positive_pairs = 0;

    int negative_count = 0;
    int total_pairs = 0;
    unordered_map<int, int> neg_map;
    neg_map[0] = 1; 

    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            total_pairs = 0; 
            negative_count = 0;
            neg_map.clear(); 
            neg_map[0] = 1;
        } else {
            if (a[i] < 0) {
                negative_count++;
            }
            if (negative_count % 2 == 0) {
                positive_pairs += neg_map[0]; 
                negative_pairs += neg_map[1];
                neg_map[0]++; 
            } else {
                positive_pairs += neg_map[1];
                negative_pairs += neg_map[0]; 
                neg_map[1]++;
            }
            total_pairs++; 
        }
    }

    zero_pairs =n*(n+1)/2-negative_pairs-positive_pairs;

    cout << negative_pairs << " " << zero_pairs << " " << positive_pairs << endl;
    return 0;
}

```



## 数字管理

> ## 题目背景
>
> 在数字化背景下，数字实在是太多了，我们要删除掉一些。
>
> ## 题目描述
>
>  有一个很长的数字序列，它由数字集{1,2,3,4,5,6,7,8,9}{1,2,3,4,5,6,7,8,9}组成。
>
>  现在，我们要从这个数字序列中删除a1*a*1个11，再删除a2*a*2个22，……，删除a9*a*9个9。
>
>  删除掉这些数字之后，剩下的数字序列按照原来的相对顺序合拢，可以看成一个整数。问这个整数最大是多少。（保证问题有解）
>
> ## 输入格式
>
>  第一行，字符串S*S*，表示数字序列。
>
>  第二行99个数字表示a1,a2,…a9*a*1,*a*2,…*a*9。
>
> ## 输出格式
>
> 输出一行，删掉指定数量的数字之后剩下的序列最大是多少。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 12345
> 1 0 0 1 1 0 0 0 0
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 23
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> 112345
> 2 1 1 0 0 0 0 0 0
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> 45
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #3
>
> ### 样例输入 #3
>
> ```none
> 8898443445
> 0 0 0 2 0 0 0 1 0
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #3
>
> ```none
> 8984435
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
>  【数据范围】：
>
>  对30%的数据满足，∣S∣≤10∣*S*∣≤10
>
>  另有30%的数据满足，S*S*仅由数字{1,2}{1,2}组成
>
>  对100%的数据满足，∣S∣≤1000∣*S*∣≤1000，S*S*由{1,2,3,4,5,6,7,8,9}{1,2,3,4,5,6,7,8,9}组成，问题保证有解。

```c
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<stack>
using namespace std;
string s, res;
int del[10], cnt[10];

int main(){
	cin >> s;
	res = "";

	stack<int> st;
	for (int i = 1; i <= 9; i ++){
		cin >> del[i];
	}
    for (char c: s){
    	cnt[c-'0'] ++;
	}

	for (char c: s){
		int dig = c-'0';
		if(del[dig]>=cnt[dig])
		{
			del[dig]--;
		}
		else
		{
			while(!st.empty() && (st.top()<dig && del[st.top()]))
			{
				del[st.top()]--;
				st.pop();
			}
			st.push(dig);
		}
		cnt[dig]--;
	}
	while (!st.empty()){
		res += st.top()+'0';
		st.pop();
	}
	reverse(res.begin(), res.end());
	cout << res;
	return 0;
}
```

