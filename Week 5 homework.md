# Week 5 homework

[TOC]

## 汉诺塔

> ### 题目背景
>
> by Gym
>
> ### 题目描述
>
> 汉诺塔是一个非常经典的问题。给你三个柱盘，编号为A*A*，B*B*，C*C*，现在 A*A* 柱盘上面套有三个圆饼，下面的圆饼半径大于上面的。B*B*，C*C* 柱为空。
>
> 通常，我们的任务是利用 B*B* 柱，把A柱的所有圆饼移到 C*C* 柱上，并且过程中要保证大圆饼不能放在小圆饼上面。这个问题过于简单，引发出了进阶版，即有 n*n* 个圆饼时该怎么操作？这个问题肯定也难不倒你，因为这个问题已经被证明了有唯一最优解，需要 2n−12*n*−1 个步骤。
>
> 现在，问题变得更加细致一点。输入三个盘柱上面圆饼的状态，请你判断这个状态是否处于最优步骤中的某个状态，如果是，请输出这个状态还需要多少个步骤才能把所有圆饼移到 C*C* 柱上。
>
> ### 输入格式
>
> 共三行：
>
> 第一行：整数 a*a* ，代表 A*A* 柱此时有 a*a* 个圆饼，接下来输入 a*a* 个整数，表示圆饼的半径。
>
> 第二行：整数 b*b* ，代表 B*B* 柱此时有 b*b* 个圆饼，接下来输入 b*b* 个整数，表示圆饼的半径。
>
> 第三行：整数 c*c* ，代表 C*C* 柱此时有 c*c* 个圆饼，接下来输入 c*c* 个整数，表示圆饼的半径。
>
> 保证当前给出的所有圆饼的半径是一系列从 1 开始的连续的整数，且不重复，且大半径的圆饼一定在小半径圆饼的下方。
>
> ### 输出格式
>
> 如果当前的状态不在最优步骤中，输出 No ，否则输出还需要多少个步骤完成任务。
>
> ### 样例 #1
>
> #### 样例输入 #1
>
> ```none
> 1 3 
> 2 2 1 
> 0
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #1
>
> ```none
> 4
> ```
>
> [Copy](javascript:;)
>
> ### 样例 #2
>
> #### 样例输入 #2
>
> ```none
> 1 3 
> 0 
> 2 2 1
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #2
>
> ```none
> No
> ```
>
> [Copy](javascript:;)
>
> ### 提示
>
> 对100%的数据满足：a+b+c≤50*a*+*b*+*c*≤50

```c++
#include<iostream>
#include<vector>
using namespace std;
int A_tag=1,B_tag=2,C_tag=3;
long long count_step(int n,int from ,int aux,int to,const vector<int> &pos)
{
    if(n==0)
    {
        return 0;
    }
    if(pos[n]==from)
    {
        return count_step(n-1,from,to,aux,pos);
    }
    if(pos[n]==to)
    {
        long long pre_step = (1LL<<(n-1));
        long long after_step = count_step(n-1,aux,from,to,pos);
        if(after_step==-1)return -1;
        return pre_step + after_step;
    }
    return -1;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a,b,c;
    cin>>a;
    vector<int> A(a);
    for(int i=0;i<a;i++)cin>>A[i];
    cin>>b;
    vector<int> B(b);
    for(int i=0;i<b;i++)cin>>B[i];
    cin>>c;
    vector<int> C(c);
    for(int i=0;i<c;i++)cin>>C[i];
    int sum = A.size()+B.size()+C.size();
    vector<int> pos(sum+1,0);
    for(int i=0;i<a;i++)pos[A[i]]=A_tag;
    for(int i=0;i<b;i++)pos[B[i]]=B_tag;
    for(int i=0;i<c;i++)pos[C[i]]=C_tag;
    long long  ans = count_step(sum,A_tag,B_tag,C_tag,pos);
    if(ans==-1)cout<<"No"<<endl;
    else
    {
        long long all_step = (1LL<<sum)-1;
        long long remain = all_step-ans;
        cout<<remain<<endl;
    }
    return 0;
}
```



## 括号算式

> ## 题目背景
>
> 小光正在学习如何写一个编译器，但是他的代码能力还不够。
>
> 他希望，编译器能够正确识别出带有括号的常数加、减、乘、幂算式，并且直接计算出算式的结果，以此达到编译优化的目的。
>
> 现在，他把识别出的算式交给了你，你需要帮助他完成计算的任务。
>
> #### 算式的定义
>
> 为了严谨，我们将使用类似于上下文无关文法的规则来定义算式 S*S* ：
>
> - 任意非负整数 n(n≥0)*n*(*n*≥0)，是一个算式。例如：`0`, `123`, `1905`, `1145141918210` 等。
> - 如果 A*A* 是一个算式，B*B* 是一个算式，op*o**p* 是 `-` 、`+`、`*` 和 `^` 中的一种，那么 A op B*A* *o**p* *B* 拼接在一起，也是一个算式。例如：`1+1`, `5*3+1`, `2^2^2` 等。
> - 如果 A*A* 是一个算式，那么 (A)(*A*) 也是一个算式。例如，`(12)`, `((13*7)-(4+12))`, `(((1+1)))` 等。
>
> #### 运算符说明
>
> 请注意，因为小光的机器只提供 32 位二进制寄存器，任何一个运算符的运算结果，超出二进制32位的进位和借位统统忽略，因此你需要输出运算结果在 32 位无符号整形中的值。
>
> - `+` 运算符表示加法，例如 `3+2` 的结果是 `5` ；`4294967295+1` 的结果是 `0` （因为溢出）。加法满足结合律。
> - `-` 运算符表示减法，例如 `3-2` 的结果是 `1` ；`0-1` 的结果是 `4294967295` （因为溢出）。减法不满足结合律，应当左结合优先运算，即 `3-2-1` 的结果是 `((3-2)-1)=0` 而不是 `(3-(2-1))=2` 。
> - `*` 运算符表示乘法，例如 `3*2` 的结果是 `6` 。乘法溢出相当于将结果 mod  232mod232 。乘法满足结合律。
> - `^` 运算法表示幂次运算，如果发生溢出相当于 mod  232mod232 ，即 `a^b` 的结果为 ab(mod232)*a**b*(mod232) 。在这里，幂次运算不满足结合律，且是一个右结合的运算符。即 `2^3^4 = (2^(3^4))` 。特殊的，此题目中规定 00 的 00 次幂等于 11 。
>
> 算式的优先级中，幂次运算优先级最高，乘法次之，加法和减法的优先级相同且最低。而括号，则是最高优先级，最里层的括号运算应该最先计算。
>
> 现在给出一个满足上述规则描述的算式，请你计算出算式的运算结果。
>
> ## 输入格式
>
> 第一行一个算式 S*S* 。
>
> ## 输出格式
>
> 输出一行，一个整数 ans*an**s* 表示答案，0≤ans<2320≤*an**s*<232 。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> (((((1+1)^2)-4)*8)+16)
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 16
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> (20-0)*(12-10)-(20-2)
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> 22
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #3
>
> ### 样例输入 #3
>
> ```none
> 2147483647
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #3
>
> ```none
> 2147483647
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #4
>
> ### 样例输入 #4
>
> ```none
> 0-1*1
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #4
>
> ```none
> 4294967295
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #5
>
> ### 样例输入 #5
>
> ```none
> 2^2^32
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #5
>
> ```none
> 1
> ```
>
> [Copy](javascript:;)
>
> ## 数据范围与提示
>
> 对于前 10% 的测试数据满足算式 S*S* 的长度不超过 103103 。
>
> 对于前 30% 的测试数据满足算式中不含有括号。
>
> 对于前 60% 的测试数据满足算式中不包含幂次和乘法运算。
>
> 对于 100% 的测试数据满足算式符合题目描述的规则，算式中每个字符紧密相连而没有额外的空格，算式 S*S* 的长度不超过 3×1053×105 。算式中出现的任何一个整数 n*n* ，满足 0≤n<2320≤*n*<232 。

```c++
#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

struct OperatorInfo {
    int precedence;
    bool right_associative;
};

OperatorInfo get_operator_info(char op) {
    switch(op) {
        case '^':
            return {3, true};
        case '*':
            return {2, false};
        case '+':
        case '-':
            return {1, false};
        default:
            return {0, false};
    }
}


unsigned int pow_mod(unsigned int a, unsigned int b) {
    if (a == 0 && b == 0) return 1; 
    unsigned int res = 1;
    unsigned int base = a;
    while(b > 0){
        if (b & 1){
            res = static_cast<unsigned int>((static_cast<unsigned long long>(res) * base) & 0xFFFFFFFF);
        }
        base = static_cast<unsigned int>((static_cast<unsigned long long>(base) * base) & 0xFFFFFFFF);
        b >>=1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    string expr;
    cin >> expr;
    
    vector<string> output_queue; 
    stack<char> operator_stack;
    
    int n = expr.length();
    int i = 0;
    while(i < n){
        char c = expr[i];
        if(c>='0'&&c<='9'){
            string num = "";
            while(i < n && expr[i]<='9' && expr[i]>='0'){
                num += expr[i];
                i++;
            }
            output_queue.push_back(num);
        }
        else if(c == '+' || c == '-' || c == '*' || c == '^'){
            OperatorInfo current_op = get_operator_info(c);
            while(!operator_stack.empty()){
                char top_op = operator_stack.top();
                if(top_op == '(') break;
                OperatorInfo top_info = get_operator_info(top_op);
                if((current_op.right_associative && current_op.precedence < top_info.precedence) ||
                   (!current_op.right_associative && current_op.precedence <= top_info.precedence)){
                    string op_str = "";
                    op_str += top_op;
                    output_queue.push_back(op_str);
                    operator_stack.pop();
                }
                else{
                    break;
                }
            }
            operator_stack.push(c);
            i++;
        }
        else if(c == '('){
            operator_stack.push(c);
            i++;
        }
        else if(c == ')'){
            while(!operator_stack.empty() && operator_stack.top() != '('){
                string op_str = "";
                op_str += operator_stack.top();
                output_queue.push_back(op_str);
                operator_stack.pop();
            }
            if(!operator_stack.empty() && operator_stack.top() == '('){
                operator_stack.pop(); 
            }
            i++;
        }

    }
    

    while(!operator_stack.empty()){
        char top_op = operator_stack.top();
        operator_stack.pop();
        string op_str = "";
        op_str += top_op;
        output_queue.push_back(op_str);
    }
    
    stack<unsigned int> eval_stack;
    for(auto &token : output_queue){
        if(token[0] >= '0' && token[0] <= '9'){
            unsigned int num = stoul(token);
            eval_stack.push(num);
        }
        else{

            char op = token[0];
            if(op == '+' || op == '-' || op == '*' || op == '^'){
                if(op == '^'){

                    unsigned int b = eval_stack.top(); eval_stack.pop();
                    unsigned int a = eval_stack.top(); eval_stack.pop();
                    unsigned int res = pow_mod(a,b);
                    eval_stack.push(res);
                }
                else{
                    unsigned int b = eval_stack.top(); eval_stack.pop();
                    unsigned int a = eval_stack.top(); eval_stack.pop();
                    unsigned int res = 0;
                    if(op == '+'){
                        res = a + b; 
                    }
                    else if(op == '-'){
                        res = a - b; 
                    }
                    else if(op == '*'){
                        res = static_cast<unsigned int>((static_cast<unsigned long long>(a) * b) & 0xFFFFFFFF);
                    }
                    eval_stack.push(res);
                }
            }
            
        }
    }
    
    unsigned int result = eval_stack.top();
    cout << result << "\n";

    
    return 0;
    
}

```



## 本质不同子串计数

> ### 题目背景
>
> 给出一个字符串 S*S*，请你统计其中本质不同的子串个数。
>
> 例如：如果 S=aba*S*=aba ，那么它有 66 个子串，a,b,a,ab,ba,abaa,b,a,ab,ba,aba 。但是，本质不同的子串只有 a,b,ab,ba,abaa,b,ab,ba,aba 这 55 种。
>
> ### 输入格式
>
> 第一行，一个字符串 S*S* 。
>
> ### 输出格式
>
> 输出一行，一个整数表示 S*S* 的本质不同的子串个数 。
>
> ### 样例 #1
>
> #### 样例输入 #1
>
> ```none
> aba
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #1
>
> ```none
> 5
> ```
>
> [Copy](javascript:;)
>
> ### 样例 #2
>
> #### 样例输入 #2
>
> ```none
> george
> ```
>
> [Copy](javascript:;)
>
> #### 样例输出 #2
>
> ```none
> 18
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> ∣S∣≤2000∣*S*∣≤2000 ，输入字符串均由小写字母组成。

```c++
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;


int ans = 0;

const int base = 26;
const int mod = 1000000007;

bool same_check(const string& s, int a, int b, int len)
{
    for(int a_b = a - len + 1, b_b = b - len + 1; a_b <= a; a_b++, b_b++)
    {
        if(s[a_b] != s[b_b])
        {
            return false;
        }
    }
    return true;
}

void check_hash(int len, const vector<long long>& hash, const string& s, const vector<long long>& power_base)
{
    unordered_map<long long, vector<int>> checked;

    for(int i = 0; i <= (int)s.size() - len; i++)
    {

        long long cur_hash;
        if(i == 0)
        {
            cur_hash = hash[len-1];
        }
        else
        {
            cur_hash = (hash[i+len-1] - (hash[i-1] * power_base[len]) % mod + mod) % mod;
        }

        bool unique = true;
        if(checked.count(cur_hash) )
        {
            for(auto pos : checked[cur_hash])
            {
                if(same_check(s, i+len-1, pos, len))
                {
                    unique = false;
                    break;
                }
            }
        }

        if(unique)
        {
            ans++;
            checked[cur_hash].push_back(i+len-1);
        }
    }
    return;
}

vector<long long> count_hash(const string& s)
{
    int len = s.size();
    vector<long long> hash(len, 0);

    hash[0] = s[0] - 'a';
    for(int i = 1; i < len; i++)
    {
        hash[i] = (hash[i-1] * base + (s[i] - 'a')) % mod;
    }
    return hash;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    int len = s.size();

    vector<long long> hash = count_hash(s);

    vector<long long> power_base(len + 1, 1);
    for(int i = 1; i <= len; i++) {
        power_base[i] = (power_base[i-1] * base) % mod;
    }

    for(int i = 1; i <= len; i++)
    {
        check_hash(i, hash, s, power_base);
    }

    cout << ans;
    return 0;
}

```



## 构造字符串

> ## 题目描述
>
> 给出一个长度为 n*n* 的 next 数组，你需要构造一个长度为 n*n* 的字符串 S*S*，使得它的 next 数组与给出的一致，
>
> nexti(1≤i≤n)*n**e**x**t**i*(1≤*i*≤*n*) 定义为字符串的前 i*i* 个字符构成的子串（ S[1,i]*S*[1,*i*] ）的“最长公共前后缀”的长度。例如：`ababcababd` 的 next 数组是 0,0,1,2,0,1,2,3,4,00,0,1,2,0,1,2,3,4,0
>
> 为了防止这道题目的思维负担过大，我们不使用小写英文字母作为字符集，取而代之，你可以使用任何整数视为一种字符。
>
> ## 输入格式
>
> 第一行输入 n*n* ，表示数组长度。
>
> 第二行 n*n* 个整数，用空格隔开，表示 next 数组。
>
> ## 输出格式
>
> 输出一行，一个字符串，长度为 n*n* ，字符集为整数，因此你需要输出 n*n* 个整数。而为了防止混淆，整数之间请用一个空格隔开。数据保证答案存在。如果有多种合法答案，输出任何一个皆可。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 10
> 0 0 1 2 0 1 2 3 4 0
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 1 2 1 2 3 1 2 1 2 4
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> n≤105*n*≤105

```c++
#include<iostream>
#include<vector>
#include<string>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    vector<int> next(n);
    vector<int> ans(n);
    for(int i=0;i<n;i++)cin>>next[i];
    int now =0;
    for(int i=0;i<n;i++)
    {
        int tmp = next[i];
        if(tmp == 0)
        {
            now ++ ;
            ans[i]=now;
        }
        else
        {
            ans[i]=ans[tmp-1];
        }
        cout<<ans[i]<<" ";
    }
    return 0;
}
```

