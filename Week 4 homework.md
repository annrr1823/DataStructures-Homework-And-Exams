# Week 4 homework

[TOC]



## 求解next数组

> # Background
>
> KMP匹配的精髓在于next数组的使用。 对于字符串 S=s1s2⋯sn*S*=*s*1*s*2⋯*s**n* ，其next数组的定义为：next[i]*n**e**x**t*[*i*] 表示的是子串 s1s2⋯si*s*1*s*2⋯*s**i* 的 ”最长公共前后缀的长度“。如果对该定义不是很了解，可以参考书本或者资料。
>
> 例如字符串 S=abcabcd*S*=*ab**c**ab**c**d* 的next数组为 {0,0,0,1,2,3,0}{0,0,0,1,2,3,0}
>
> 特殊地，我们在这道题目中规定 next[1]=0*n**e**x**t*[1]=0 。
>
> # Description
>
> 给出一个字符串，输出其next数组。
>
> # Format
>
> ## Input
>
> 字符串 S*S* 。仅由小写字母组成。
>
> ## Output
>
> 输出 ∣S∣∣*S*∣ 个数字，表示next数组。
>
> # Samples
>
> ## 输入数据 1
>
> ```input1
> abcabcd
> ```
>
> [Copy](javascript:;)
>
> ## 输出数据 1
>
> ```output1
> 0 0 0 1 2 3 0
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> ∣S∣≤106∣*S*∣≤106.

```c++
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int len = s.size();
    vector<int> next(len, 0);
    for (int i = 1, j = 0; i < len; ++i) {
        while (j > 0 && s[i] != s[j]) {
            j = next[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        next[i] = j;
    }

    for (int j = 0; j < len; j++) {
        cout << next[j] << ' ';
    }
    return 0;
}

```



## 后缀表达式

> # Description
>
> 所谓后缀表达式是指这样的一个表达式：式中不再引用括号，运算符号放在两个运算对象之后，所有计算按运算符号出现的顺序，严格地由左而右新进行（不用考虑运算符的优先级）。
>
> 如：`34*(5–2)+7`对应的后缀表达式为：`34．5．2．-*7．+@`。`@`为表达式的结束符号。`.`为操作数的结束符号，防止操作数连在一起分不清。
>
> # Format
>
> ## Input
>
> 输入：后缀表达式，以`@`结尾
>
> ## Output
>
> 输出：表达式的值，运算结果
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 3.5.2.-*7.+@
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 16
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 字符串长度，1000内。
>
> 运算符只有加减乘除四种(+-*/),保证所有的中间结果都是int范围

```c++
#include<iostream>
#include<string>
#include<vector>
#include<stack>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin>>s;
    int num=0;
    int len = s.size();
    stack<int> nums;
    int ans=0;
    for(int i=0;i<len;i++)
    {
        char tmp=s[i];
        //cout<<tmp<<endl;
        if(tmp<='9' && tmp>='0')
        {
            num=(num*10+tmp-'0');
            //cout<<"add:"<<tmp-'0'<<endl;
        }
        else if(tmp=='.')
        {
            nums.push(num);
            //cout<<num<<endl;
            num=0;
        }
        else if(tmp=='+')
        {
            int op1=nums.top();
            nums.pop();
            int op2=nums.top();
            nums.pop();
            nums.push(op1+op2);
            //cout<<op1<<" "<<tmp<<" "<<op2<<endl;
        }
        else if(tmp=='-')
        {
            int op1=nums.top();
            nums.pop();
            int op2=nums.top();
            nums.pop();
            nums.push(op2-op1);
            //cout<<op1<<" "<<tmp<<" "<<op2<<endl;
        }
        else if(tmp=='*')
        {
            int op1=nums.top();
            nums.pop();
            int op2=nums.top();
            nums.pop();
            nums.push(op1*op2);
            //cout<<op1<<" "<<tmp<<" "<<op2<<endl;
        }
        else if(tmp=='/')
        {
            int op1=nums.top();
            nums.pop();
            int op2=nums.top();
            nums.pop();
            nums.push(op2/op1);
            //cout<<op1<<" "<<tmp<<" "<<op2<<endl;
        }
        else if(tmp=='@')
        {
            ans=nums.top();
            break;
        }
    }
    cout<<ans;
    return 0;
}
```



## 括号序列 III

> # Description
>
> 给定的字符串 s*s* 由四种类型的左括号和右括号组成`<>`，`{}`，`[]`，`()`。括号有两种类型:左括号和右括号。你可以用相同类型（同为左或同为右）的另一个括号代替任何一个括号。例如，您可以替换`<`为括号`{`，但不能用`)`或`>`代替。
>
> 下面的“正则括号序列”定义是众所周知的，因此您可以熟悉它。
>
> 让我们定义一个“正则括号序列”(RBS)。空字符串是RBS。设 s1*s*1 和 s2*s*2 是一个RBS，那么字符串<s1>s2<*s*1>*s*2，{s1}s2{*s*1}*s*2，[s1]s2[*s*1]*s*2，(s1)s2(*s*1)*s*2 也是RBS。
>
> 例如,字符串 `[[(){}]<>]` 是RBS,但`[)()`， `][()()` 不是。
>
> 在这个问题中，你需要确定使字符串 s*s* 变成 RBS 的最少替换次数，或者判断这是不可能的。
>
> # Format
>
> ## Input
>
> 唯一的一行包含一个非空字符串s，只包含四种类型的左括号和右括号。
>
> ## Output
>
> 如果不能从s得到正则括号序列，则输出`Impossible`
>
> 否则输出把s变成正则括号序列的最小替换次数
>
> # Samples
>
> #### 输入样例1
>
> ```none
> [<}){}
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例1
>
> ```none
> 2
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例2
>
> ```none
> {()}[]
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例2
>
> ```none
> 0
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例3
>
> ```none
> ]]
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例3
>
> ```none
> Impossible
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> s的长度不超过106106。

```c++
#include<iostream>
#include<string>
#include<stack>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    stack<char> store;
    string s;
    cin>>s;
    int ans = 0;
    int len = s.size();
    for(int i=0;i<len;i++)
    {
        char tmp=s[i];

        if(tmp=='<' || tmp =='{' || tmp == '[' || tmp == '(')
        {
            store.push(tmp);
        }
        else
        {
            if(store.empty())
            {
                cout<<"Impossible";
                return 0;
            }
            char match = store.top();
            store.pop();
            if((tmp=='>'&& match=='<') ||( tmp =='}'&& match=='{') || (tmp == ']'&& match=='[') ||( tmp == ')'&& match=='('))
            {
                //cout<<"delet: "<<tmp<<match<<endl;
            }
            else{
                //cout<<"change: "<<tmp<<match<<endl;
                ans ++;
            }
        }
    }
    if(store.empty())
    {
        cout<<ans;
    }
    else{
        cout<<"Impossible";
    }
    return 0;
}
```



## 栈与询问

> ### 题目背景
>
> 现在有一个空的栈，接下来会进行 m*m* 次操作，每次操作后你需要输出栈中最大的元素。
>
> 每次操作是下面的一种：
>
> 1. push x*x* 向栈中插入一个元素 x*x*
> 2. pop 弹出栈顶元素
>
> ### 输入格式
>
> 第一行，一个整数 m*m* 。
>
> 接下来一行，每行表示一个操作，格式是下面的一种：
>
> - push xpush *x*
> - poppop
>
> ### 输出格式
>
> 输出 m*m* 行，每次输出栈中最大的元素。特别的，如果栈此时为空，输出一行 emptyempty 。
>
> ### 样例 #1
>
> #### 样例输入 #1
>
> ```none
> 5
> push 2
> push 3
> pop
> pop
> push 5
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #1
>
> ```none
> 2
> 3
> 2
> empty
> 5
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> m≤105, 0≤x≤109*m*≤105, 0≤*x*≤109 .

```c++
#include<iostream>
#include<string>
#include<stack>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    cin>>m;
    stack<long long > store;
    stack<long long > max_s;
    for(int i=0;i<m;i++)
    {
        string op;
        cin>>op;
        
        if(op=="push")
        {
            
            long long num;
            cin>>num;
            store.push(num);
            if(max_s.empty())
            {
                max_s.push(num);
            }
            else
            {
                long long cur_top = max_s.top();
                if(num>cur_top)max_s.push(num);
                else max_s.push(cur_top);
            }

            //cout<<"push"<<max_s.top()<<endl;
        }
        else
        {
            //cout<<"pop"<<max_s.top()<<endl;
            max_s.pop();
            store.pop();
        }
        if(store.empty())
        {
            cout<<"empty"<<endl;
            continue;
        }
        cout<<max_s.top()<<endl;
    }

    return 0;
}
```



## 周期循环

> # Description
>
> ZZR 喜欢周期循环，看到不是周期循环的字符串就很不爽。
>
> 现在 ZZR 得到一个字符串，可以在字符串末尾添加若干任意字符。
>
> 请你帮 ZZR 想想，最少添加多少个字符，才能使得字符串变得周期循环（即存在一个循环节至少循环两次）。
>
> # Format
>
> ## Input
>
> 第一行一个整数 T*T* 代表测试数据的组数。
>
> 接下来 T*T* 行每行一个字符串，由小写字母组成，字符串的长度为 L*L*。
>
> ## Output
>
> 每组数据输出一行表示最少添加的字符数量。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 3
> ppp
> pip
> machinelearning
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 0
> 1
> 15
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤T≤1001≤*T*≤100，3≤L≤1053≤*L*≤105。
>
> 样例解释：ppp 为周期循环，循环节为 p，循环 3 次。

```c++
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> computeLPS(const string &s) {
    int len = s.size();
    vector<int> lps(len, 0);
    int length = 0;
    int i = 1;

    while (i < len) {
        if (s[i] == s[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        vector<int> lps = computeLPS(s);
        int L = s.size();
        int lenOfLastLPS = lps[L - 1];
        int smallestPeriod = L - lenOfLastLPS;
        
        // If L is already a multiple of the smallest period
        if (L % smallestPeriod == 0 ) {
            if(L / smallestPeriod >=2)
            cout << 0 << endl;
            else cout<<L<<endl;
        } else {
            int neededLength = smallestPeriod - (L % smallestPeriod);
            cout << neededLength << endl;
        }
    }
    return 0;
}
```

