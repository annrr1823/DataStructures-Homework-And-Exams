# Week 3 homework

[TOC]

### A. 你的数太多了

> ### 题目描述
>
> 给定一个大小为 n*n* 的有序可重数列，要求把其中出现了超过 1 次的数字都去掉，求操作之后的数列。
>
> ### 输入格式
>
> 第一行一个正整数 n*n*，表示数列的大小。第二行 n*n* 个正整数 ai*a**i*，表示数列的元素，保证数列有序。
>
> ### 输出格式
>
> 仅一行若干个正整数，表示操作之后的序列。
>
> ### 样例
>
> #### 输入样例
>
> ```none
> 5
> 2 3 3 3 4
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 2 4
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> 1≤n≤105,1≤ai≤1091≤*n*≤105,1≤*a**i*≤109。

```c++
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int prev=-1;
    int count =0;
    int tmp;
    for(int i=0;i<n;i++)
    {
        
        cin>>tmp;
        if(tmp != prev)
        {
            if(count == 1)cout<<prev<<" ";
            prev = tmp;
            count = 1;
        }
        else
        {
            count++;
        }
    }
    if(count ==1)cout<<tmp;
    return 0;
}
```



### B. Permutation Transformer

> ### 题目描述
>
> （[附加文件](http://10.20.8.133/d/DS2023/file/8/PermutationTransformer.zip)）
>
> 给出 1∼n1∼*n* 的排列，最开始是 1,2,⋯n1,2,⋯*n* 的顺序序列。
>
> 接下来有 m*m* 个操作，对于每个操作 [l,r][*l*,*r*]，需将排列下标 l∼r*l*∼*r* 的元素翻转后放到整个序列的末尾。
>
> 输入整数 n,m*n*,*m*，接下来 m*m* 行包括每个操作对应的区间。
>
> 输出最终得到的序列。
>
> ### 输入格式
>
> 第一行两个整数 n,m*n*,*m* 。
>
> 接下来 m*m* 行，每行两个整数 l,r*l*,*r* ，表示把当前序列的下标 [l,r][*l*,*r*] 区间的元素翻转后放到整个序列的末尾。
>
> ## 输出格式
>
> 输出一行，n*n* 个整数，表示最后的序列。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 10 2
> 2 5
> 4 8
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 1 6 7 3 2 4 5 10 9 8
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围
>
> 1≤n,m≤1051≤*n*,*m*≤105。

```c++
//参考洛谷tangyigeng题解
#include<cstdio>
#include<iostream>
#include<random>
using namespace std;

const int N=1e6,inf= 2e9;
int n,m;
int Root,cnt;

random_device R;
mt19937 G(R());

struct newnode{
    int val,size,lson,rson,laze,pri;

}treap[N+10];

int rd(int l,int r)
{
    return uniform_int_distribution<int>(l,r)(G);
}

void newnode(int & u ,int val)
{
    u = ++cnt;
    treap[u].pri = rd(1,N);
    treap[u].size = 1;
    treap[u].val = val;
}

void push_down(int u)
{
    if(treap[u].laze)
    {
        treap[treap[u].lson].laze ^= 1;
        treap[treap[u].rson].laze ^= 1;
        swap(treap[treap[u].lson].lson,treap[treap[u].lson].rson);
        swap(treap[treap[u].rson].lson,treap[treap[u].rson].rson);
        treap[u].laze = 0;
    }
}

void push_up(int u)
{
    treap[u].size = treap[treap[u].lson].size + treap[treap[u].rson].size +1;
}

void merge(int &u,int root_l,int root_r)
{
    if(!root_l || !root_r)return (void(u= root_l | root_r));
    if(treap[root_l].pri >= treap[root_r].pri)
    {
        u = root_l;
        push_down(root_l);
        merge(treap[u].rson,treap[root_l].rson,root_r);
    }
    else
    {
        u = root_r;
        push_down(root_r);
        merge(treap[u].lson,root_l,treap[root_r].lson);
    }
    push_up(u);
}

void split_size(int u,int & root_l,int & root_r,int cri)
{
    if(!u)return void(root_l=root_r=0);
    push_down(u);
    if(treap[treap[u].lson].size +1 <= cri)
    {
        root_l = u;
        split_size(treap[u].rson,treap[root_l].rson,root_r,cri-treap[treap[u].lson].size-1);

    }
    else
    {
        root_r = u;
        split_size(treap[u].lson,root_l,treap[root_r].lson,cri);

    }
    push_up(u);
}
void reverse(int l,int r)
{
    int root_l,root_r,root_l_l,root_l_r;
    split_size(Root,root_l,root_r,r);
    split_size(root_l,root_l_l,root_l_r,l-1);
    treap[root_l_r].laze ^= 1;
    swap(treap[root_l_r].lson,treap[root_l_r].rson);
    merge(root_l,root_l_l,root_r);
    merge(Root,root_l,root_l_r);
}

void dfs(int u)
{
    if(!u)return ;
    push_down(u);
    dfs(treap[u].lson);
    printf("%d ",treap[u].val);
    dfs(treap[u].rson);
}

void ins(int val,int id)
{
    int root_l,root_r,son;
    split_size(Root,root_l,root_r,id-1);
    newnode(son,val);
    merge(root_r,son,root_r);
    merge(Root,root_l,root_r);
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        ins(i,i);
    }
    while(m--)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        reverse(l,r);
    }
    dfs(Root);
    return 0;
}
```



### C. 合并链表

> ### 题目描述
>
> 一个链表共有 n*n* 个 “块”，编号依次为 1, 2, ..., n1, 2, ..., *n* ，每块中放置了一个长度为 k*k* 的数组，第 i*i* 块中的数组的前 ai*a**i* 位储存了有效信息。
>
> 这样，第 i*i* 块中的数组就有 k−ai*k*−*a**i* 的单位空间没有使用，造成了时间和空间的浪费，所以需要合并一部分块来提高运行效率。
>
> 两个块 i, j*i*, *j* ( i<j*i*<*j* )能够合并，当且仅当它们相邻即 j−i=1*j*−*i*=1 ，且 ai+aj≤k*a**i*+*a**j*≤*k*。
>
> 合并操作为：将 j*j* 的有效信息紧接到 i*i* 的有效信息后面，在 i*i* 的数组中形成长度为 ai+aj*a**i*+*a**j* 的有效信息，并删除 j*j*。
>
> 求这个链表可以合并到最少多少块。
>
> ### 输入格式
>
> 第一行两个正整数 n,k*n*,*k*。
>
> 第二行 n*n* 个非负整数 a1, a2, ..., an*a*1, *a*2, ..., *a**n*。
>
> ### 输出格式
>
> 一个整数，表示答案。
>
> ### 样例
>
> #### 输入样例
>
> ```none
> 3 2
> 1 1 1
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 2
> ```
>
> [Copy](javascript:;)
>
> ### 数据范围与提示
>
> 1≤n≤106, 1≤k≤1091≤*n*≤106, 1≤*k*≤109。
>
> 所有 ai≤k (1≤i≤n)*a**i*≤*k* (1≤*i*≤*n*)。
>
> 样例解释：可以将前两个 11 合并形成一个块，第三个 11 形成第二个块。

```c++
#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int n,k;
    cin>>n>>k;
    int store = 0;
    int ans =0;
    for(int i=0;i<n;i++)
    {
        int tmp;
        cin>>tmp;
        if(tmp + store <=k)
        {
            store += tmp;
        }
        else
        {
            ans ++;
            store = tmp;
        }
    }
    if(store != 0)ans++;
    if(ans==0)ans = 1;
    cout<<ans;
    return 0;
}
```



### D. 重复字符串 I

> # Description
>
> 给定一个长度为 n*n*，全部由小写英文字母组成字符串 s*s*，找出最长的子串，使得该子串在字符串 s*s* 中至少出现两次且不重叠。
>
> 具体来说，不妨令子串长度为 l*l*，则：
>
> - ∃1≤l1,l2≤n−l+1∃1≤*l*1,*l*2≤*n*−*l*+1，l1+l≤l2*l*1+*l*≤*l*2；
> - sl1+i=sl2+i  (∀i∈{0,1,...,l−1})*s**l*1+*i*=*s**l*2+*i*  (∀*i*∈{0,1,...,*l*−1})。
>
> 如果子串不存在，则输出 0。
>
> # Format
>
> ## Input
>
> 第一行一个整数 n*n* 表示字符串长度。
>
> 第二行为长度为 n*n* 的字符串 s*s*。
>
> ## Output
>
> 一个整数，表示在字符串 s*s* 中出现两次且不重叠的最长子串的长度。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 13
> strangeorange
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
> # Limitation
>
> 2≤n≤5×1032≤*n*≤5×103。

```c++
#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

bool check_hash(string s,pair<int,int> x,pair<int,int> y)
{
    if((x.first<y.first && x.second>y.first)||(x.first>y.first && y.second>x.first))
        return false;
    for(int i=x.first,j=y.first;i<=x.second;i++,j++)
    {
        if(s[i]!=s[j])return false;
    }
    return true;
}

bool check(string s,int len)
{
    int base = 26;
    int mod = 1000007;
    int ai=1;
    int num = 0;
    unordered_map<int,pair<int,int>> seen;
    for(int i=0;i<len;i++)
    {
        ai=(ai*base)%mod;
        num = (num*base+s[i]-'a')%mod;
    }
    seen.insert({num,{0,len-1}});
    for(int i=1;i<=(int)s.size()-len;i++)
    {
        num = (num*base - ((s[i-1]-'a')*ai)%mod + (s[i+len-1]-'a') +mod)%mod;
        if(seen.count(num) && check_hash(s,{i,i+len-1},seen[num]))
            return true;
        seen.insert({num,{i,i+len-1}});
    }
    return false;
}

int main()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    int low=0,high = n/2;
    int ans = 0;
    while(low<=high)
    {
        int mid = low + (high-low)/2;
        if(check(s,mid))
        {
            low = mid+1;
            ans = mid;
        }
        else
        {
            high = mid -1;
        }
    }
    cout<<ans;
    return 0;
}
```



### E. 同构匹配

> ## 题目背景
>
> 动态匹配不够刺激，同构匹配，刺激。
>
> ## 题目描述
>
>  Plover最近学得了一种魔法，每次操作可以把字符串中**已有的**两种**不同**的字母互换，形式化的来讲，可以选择字符 ci*c**i* 和字符 cj*c**j*，然后把字符串中所有的 ci*c**i* 字符替换成 cj*c**j* ，同时把所有的 cj*c**j* 替换成 ci*c**i*。比如，对于字符串 `abbac`，他可以交换字母 `b` 和 `c` ，从而把字符串变成 `accab` ；如果他继续交换字母 `b` 和字母 `a` ，那么字符串就会变成 `bccba`。
>
>  考虑两个字符串 S*S* 和 T*T* ，我们称 S*S* 和 T*T* 是同构的，当且仅当 Plover 在施展有限次魔法的前提下，能够将 S*S* 变成 T*T* 。比如，`abbac` 和 `bccba` 就是同构的；而 `abaac` ，`abbac` ，`addae` ，`abb` 这些串两两之间都不同构。
>
>  现在有一个字符串 S*S* 。然后有 m*m* 次询问，每次询问给出两组下标 l1,r1*l*1,*r*1 和 l2,r2*l*2,*r*2 ，表示 S*S* 的两个子串。问子串 S[l1,r1]*S*[*l*1,*r*1] 和 S[l2,r2]*S*[*l*2,*r*2] 是否是同构的，是则输出 `Yes` ，否则输出 `No` 。
>
> > S[l,r]*S*[*l*,*r*] 表示的是从 S*S* 串的第 l*l* 个字符开始，连续取到第 r*r* 个字符形成的子串。
>
> ## 输入格式
>
> 第一行字符串 S*S* 。
>
> 第二行整数 m*m* 。
>
> 接下来 m*m* 行每行四个整数，l1,r1,l2,r2*l*1,*r*1,*l*2,*r*2 。表示一组询问。
>
> ## 输出格式
>
> 一共 m*m* 行，每行表示询问的答案。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> abbacaacb
> 4
> 1 5 5 9
> 1 2 5 6
> 3 5 7 9
> 1 1 2 2
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> Yes
> No
> Yes
> No
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> georgeinthegorge
> 6
> 1 5 2 6
> 1 2 5 6
> 1 4 1 5
> 2 9 2 9
> 1 1 5 5
> 3 6 13 16
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> Yes
> Yes
> No
> Yes
> Yes
> Yes
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 【数据范围】：
>
>  对于20%的数据，保证 r1−l1≤9,r2−l2≤9,*r*1−*l*1≤9,*r*2−*l*2≤9,。
>
>  对于50%的数据，保证 m=1*m*=1
>
>  对于100％的数据，保证 ∣S∣≤2×105∣*S*∣≤2×105 ， m≤105*m*≤105 ，1≤l1≤r1≤∣S∣,1≤l2≤r2≤∣S∣1≤*l*1≤*r*1≤∣*S*∣,1≤*l*2≤*r*2≤∣*S*∣ ，所有字符串由小写字母组成。
>
> 【时间限制】 1000ms 【空间限制】 256MB

没AC，无代码