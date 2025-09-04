# Week 12 Homework

[TOC]

## 嘉然今天分什么

> # Description
>
> Y 给嘉然带了一根拉面，他希望嘉然能够喜欢。
>
> 但是嘉然根本不喜欢吃拉面，于是嘉然希望将这根拉面切成 k*k* 段分给她的粉丝们，每段都必须连续。
>
> 由于 Y 的拉面水平很差，他拉出来的面的每个单位长度的重量都不一定一样。具体地，这条长度为 n*n* 的拉面的每个单位长度的重量分别为 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*。同时，嘉然只能切出整数长度的拉面。
>
> 当然，不能给一个粉丝分太多的拉面，嘉然希望分出的这 k*k* 段拉面重量的最大值最小。请输出这个最小的最大值。
>
> 注意，每段拉面的重量被定义为这段所对应的每个单位长度拉面的重量**之和**。
>
> # Format
>
> ## Input
>
> 第一行两个整数 n,k*n*,*k* 表示拉面长度和粉丝数量。
>
> 第二行 n*n* 个整数表示每单位长度的拉面重量 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*。
>
> ## Output
>
> 输出一行表示这 k*k* 段拉面重量的最大值的最小值。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 5 3
> 2 3 4 1 3
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
> 1≤k<n≤5×1051≤*k*<*n*≤5×105，1≤ai≤1091≤*a**i*≤109。
>
> 样例解释：切割方式为 2 3 ∣∣ 5 ∣∣ 1 3，第一段的重量为 2 + 3 = 5，第二段的重量为 5，第三段的重量为 1 + 3 = 4。

```c++
#include<bits/stdc++.h>
using namespace std;

bool canDivide(const vector<long long>& a, int k, long long maxWeight) {
    long long currentSum = 0;
    int count = 1;
    for (int i = 0; i < (int) a.size(); ++i) {
        if (currentSum + a[i] > maxWeight) {
            count++;
            currentSum = a[i];
        } else {
            currentSum += a[i];
        }
    }  
    return count<=k;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,k;
    cin>>n>>k;
    vector<long long> a(n);
    for(int i=0;i<n;i++)cin>>a[i];

    long long left = *max_element(a.begin(), a.end());
    long long right = accumulate(a.begin(),a.end(),0LL);
    long long mid;
    
    while (left <= right) {
        mid = left + (right-left) / 2;   
        if (canDivide(a, k, mid)) {
            right = mid-1;
        } else {
            left = mid + 1;
        }
    } 
    cout << left << endl;
    return 0;
}
```



## 嘉然今天切什么

> # Description
>
> 嘉然家的玻璃被熊孩子打坏了！
>
> 在这寒冷的天气中，没有玻璃怎么行？Y 很着急，他不想让嘉然着凉！
>
> 于是，Y 从玻璃制造厂拉了一大块玻璃来，大小恰好为 H×W*H*×*W*。当然，他还需要自己动手切割，才能恰好切割出嘉然窗户的形状。
>
> Y 有两种切割玻璃的方式：
>
> - `H a`，表示沿着 a*a* 刻度的位置水平切一刀；
> - `W a`，表示沿着 a*a* 刻度的位置垂直切一刀。
>
> Y 想知道，每次切割以后，最大块的玻璃的面积是多少。
>
> # Format
>
> ## Input
>
> 第一行三个整数 W*W*，H*H* 和 n*n* 分别表示宽、高和切割次数。
>
> 接下来 n*n* 行，每行一个字符（`H` 或 `W`）表示水平切割还是垂直切割，和一个整数 a*a* 表示切割的刻度位置。
>
> ## Output
>
> 对于每次切割，输出当前最大的玻璃的面积。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 4 3 4
> H 2
> W 2
> W 3
> W 1
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 8
> 4
> 4
> 2
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤2×1051≤*n*≤2×105，2≤W,H≤1092≤*W*,*H*≤109。
>
> 保证切割的刻度必定存在，保证不会在同一个地方切割两次。

```c++
#include <iostream>
#include <set>

using namespace std;

int main() {
    int W, H, n;
    cin >> W >> H >> n;

    set<int> horizontalCuts, verticalCuts;
    multiset<int> horizontalGaps, verticalGaps;

    horizontalCuts.insert(0);
    horizontalCuts.insert(H);
    horizontalGaps.insert(H);

    verticalCuts.insert(0);
    verticalCuts.insert(W);
    verticalGaps.insert(W); 

    for (int i = 0; i < n; ++i) {
        char direction;
        int a;
        cin >> direction >> a;

        if (direction == 'H') {
            auto it = horizontalCuts.lower_bound(a);
            int upper = *it;      
            int lower = *prev(it); 

            horizontalGaps.erase(horizontalGaps.find(upper - lower));
            horizontalGaps.insert(a - lower);
            horizontalGaps.insert(upper - a);

            horizontalCuts.insert(a);
        } else if (direction == 'W') {
            auto it = verticalCuts.lower_bound(a);
            int upper = *it;       
            int lower = *prev(it); 

            verticalGaps.erase(verticalGaps.find(upper - lower));
            verticalGaps.insert(a - lower);
            verticalGaps.insert(upper - a);

            verticalCuts.insert(a);
        }

        int maxHeight = *horizontalGaps.rbegin();
        int maxWidth = *verticalGaps.rbegin();
        cout << 1LL * maxHeight * maxWidth << endl;
    }

    return 0;
}
```



## 郁闷的出纳员

> # Description
>
> OIER 公司是一家大型专业化软件公司，有着数以万计的员工。作为一名出纳员，我的任务之一便是统计每位员工的工资。这本来是一份不错的工作，但是令人郁闷的是，我们的老板反复无常，经常调整员工的工资。如果他心情好，就可能把每位员工的工资加上一个相同的量。反之，如果心情不好，就可能把当前在公司的所有员工的工资扣除一个相同的量。我真不知道除了调工资他还做什么其它事情。
>
> 工资的频繁调整很让员工反感，尤其是集体扣除工资的时候，一旦某位员工发现自己的工资已经低于了合同规定的工资下界，他就会立刻气愤地离开公司，并且再也不会回来了。每位员工的工资下界都是统一规定的。每当一个人离开公司，我就要从电脑中把他的工资档案删去，同样，每当公司招聘了一位新员工，我就得为他新建一个工资档案。
>
> 老板经常到我这边来询问工资情况，他并不问具体某位员工的工资情况，而是问现在工资第 k*k* 多的员工拿多少工资。每当这时，我就不得不对数万个员工进行一次漫长的排序，然后告诉他答案。
>
> 好了，现在你已经对我的工作了解不少了。正如你猜的那样，我想请你编一个工资统计程序。怎么样，不是很困难吧？
>
> 如果某个员工的初始工资低于最低工资标准，那么将不计入最后的答案内。
>
> # Format
>
> ## Input
>
> 第一行有两个整数 n*n* 和 min*min*。n*n* 表示下面有多少条命令，min*min* 表示工资下界。
>
> 接下来的 n*n* 行，每行一个字符 x*x* 和一个整数 k*k*，表示一条命令。命令可以是以下四种之一：
>
> - `I k`：新建一个工资档案，初始工资为 k*k*。如果某员工的初始工资低于工资下界，他将立刻离开公司。
> - `A k`：把每位员工的工资加上 k*k*。
> - `S k`：把每位员工的工资扣除 k*k*。
> - `F k`：查询第 k*k* 多的工资。
>
> 在初始时，可以认为公司里一个员工也没有。
>
> ## Output
>
> 对于每条 `F` 命令，你的程序要输出一行，仅包含一个整数，为当前工资第 k*k* 多的员工所拿的工资数，如果 k*k* 大于目前员工的数目，则输出 −1−1。
>
> 输出的最后一行包含一个整数，为离开公司的员工的总数。
>
> 请注意，初始工资低于工资下界的员工不算做离开公司的员工。
>
> # Samples
>
> 输入样例
>
> ```none
> 9 10
> I 60
> I 70
> S 50
> F 2
> I 30
> S 15
> A 5
> F 1
> F 2
> ```
>
> [Copy](javascript:;)
>
> 输出样例
>
> ```none
> 10
> 20
> -1
> 2
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 0≤n≤3×105,0≤min≤1090≤*n*≤3×105,0≤*min*≤109
>
> 每次工资调整不超过 103103，新员工工资不超过 105105

```c++
//参考洛谷题解  
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;  
using namespace std;  
struct node{  
   int v,id;  
   node(int a,int b){v=a;id=b;}  
   bool operator >(node b) const  
   {return v==b.v?id>b.id:v>b.v;}  
};  
tree<node,null_type,greater<node>,rb_tree_tag,tree_order_statistics_node_update> T,TE;  
int main(){  
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
   int n,m,k,s=0,ans=0;  
   char c; 
   cin>>n>>m;  
   while(n--){  
       cin>>c;
       cin>>k;  
       if(c=='I')
       {
            k+=s;
            if(k>=m) T.insert(node(k,n));
        }  
       else if(c=='A')
       {
            m-=k,s-=k; 
       }  
       else if(c=='S'){  
           m+=k,s+=k;  
           T.split(node(m,-1),TE);  
           ans+=TE.size();  
       }  
       else if(c=='F')  
       {
            if(k>(int)T.size())
            {
                cout<<-1<<endl;
            }
            else
            {
                cout<<T.find_by_order(k-1)->v -s<<endl;
            } 
       }  
             
           
   }  
   cout<<ans<<endl;
   return 0;  
}
```



## 少林寺

> # Description
>
> 少林寺以武僧闻名。每年都有很多年轻人去少林寺出家。少林大师对一个年轻人的评价主要是看他在理解佛经方面的天赋，但也要考虑到他的武功。
>
> 当一个年轻人通过了所有的测试并被宣布为少林寺的新和尚时，作为欢迎会的一部分，将会有一场战斗。每个和尚都有一个唯一的 id 和一个唯一的战斗分，且均为整数。新和尚必须与一位战斗分与其战斗分最接近的老和尚战斗。如果有两个老和尚满足这个条件，新和尚将选择战斗分低于他的和尚。
>
> 师傅是少林寺的第一和尚，id 是 1，战斗分是 108108。他刚刚丢失了格斗记录。但他仍然记得谁先加入少林，谁后加入。请帮他找回战斗记录。
>
> # Format
>
> ## Input
>
> 第一行是一个整数 n*n*，表示少林大师之后加入少林的僧侣人数（不包括少林大师）。
>
> 接下来 n*n* 行，每行有两个整数 k*k* 和 g*g*，表示僧侣的 id 和战斗分。
>
> 和尚按加入时间的升序排列，也就是说，较早加入少林的和尚排在前面。
>
> ## Output
>
> 按发生时间的升序输出所有战斗。一场战斗用两个僧侣的 id 表示，每次战斗，先输出新和尚的 id，然后输出老和尚的 id。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 3
> 2 1
> 3 3
> 4 2
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 2 1
> 3 2
> 4 2
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤1051≤*n*≤105，1≤k,g≤5×1061≤*k*,*g*≤5×106。

```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, x, y;
    cin>>n;
    map<int, int> a;
    a[1e8] = 1;
        
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        
        a[y] = x;

        auto it = a.find(y);
        if (it == a.begin()) {
            cout<<x<<" "<<(++it)->second;
        } else if (it == a.end()) {
            cout<<x<<" "<<(--it)->second;
        } else {
            auto prev_it = prev(it);
            auto next_it = next(it);
            
            if (abs((next_it)->first - y) < abs((prev_it)->first - y)) {
                cout<<x<<" "<<next_it->second;
            } else {
                cout<<x<<" "<<prev_it->second;
            }
        }
        cout<<endl;
    }

    return 0;
}
```



## 有天你飞起来去摘那云彩

> # Description
>
> 天上有 n*n* 朵云彩，他们从左到右排成一排，每朵云彩都有一个洁白值，分别是 p1,p2,⋯pn*p*1,*p*2,⋯*p**n* ，并且每朵云彩的洁白值都不同。
>
> 现在，你想要飞起来去摘下一些云彩，为此你需要计算一个奇特的任务。
>
> 具体的，你需要从每个长度为 m*m* 的区间中，选出 k*k* 朵云彩，使得它们的洁白值之和尽可能小。
>
> # Format
>
> ## Input
>
> 第一行，三个整数，n,m,k*n*,*m*,*k* 。
>
> 第二行，n*n* 个整数，p1,p2,⋯pn*p*1,*p*2,⋯*p**n* 表示云彩的洁白值。
>
> 保证云彩的洁白值互不相同。
>
> ## Output
>
> 输出一行，包含 n−m+1*n*−*m*+1 个整数，其中第 i*i* 个整数表示从 pi,pi+1,⋯pi+m−1*p**i*,*p**i*+1,⋯*p**i*+*m*−1 中选出恰好 k*k* 个云彩能得到的最小洁白值总和。
>
> # Samples
>
> #### input 1
>
> ```none
> 6 4 3
> 1 3 4 2 5 6
> ```
>
> [Copy](javascript:;)
>
> #### output 1
>
> ```none
> 6 9 11
> ```
>
> [Copy](javascript:;)
>
> #### input 2
>
> ```none
> 10 6 3
> 1 2 10 9 7 8 4 3 6 5
> ```
>
> [Copy](javascript:;)
>
> #### output 2
>
> ```none
> 10 13 14 13 12
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤k≤m≤n≤1061≤*k*≤*m*≤*n*≤106
>
> 1≤pi≤n1≤*p**i*≤*n* ，对于 i≠j*i*\\=*j* 有 pi≠pj*p**i*\\=*p**j*

```c++
#include <bits/stdc++.h>
using namespace std;
int n, m, k;
long long sum_k = 0;
multiset<int> low, high; // low存前k小，high存其余的
void adjust()
{
    while ((int)low.size() > k) 
    {
        auto it = prev(low.end());
        sum_k -= *it;
        high.insert(*it);
        low.erase(it);
    }
    while ((int)low.size() < k && !high.empty()) 
    {
        auto it = high.begin();
        sum_k += *it;
        low.insert(*it);
        high.erase(it);
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;

    vector<int> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }


    for (int i = 0; i < m; i++) {
        low.insert(p[i]);
        sum_k += p[i];
    }
    adjust();

    vector<long long> result;
    result.push_back(sum_k);

    for (int i = 1; i <= n - m; i++) {
        int to_remove = p[i - 1];
        int to_add = p[i + m - 1];

        if (low.find(to_remove) != low.end()) {
            sum_k -= to_remove;
            low.erase(low.find(to_remove));
        } else {
            high.erase(high.find(to_remove));
        }

        if (!low.empty() && to_add <= *prev(low.end())) {
            sum_k += to_add;
            low.insert(to_add);
        } else {
            high.insert(to_add);
        }

        // 调整low和high，使low中正好有k个最小值
        adjust();

        result.push_back(sum_k);
    }

    for (long long res : result) {
        cout << res << " ";
    }
    cout << endl;

    return 0;
}
```

