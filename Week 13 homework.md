# Week 13 homework

[TOC]

## 约克镇之战

> # Description
>
> “都把子弹退出枪！”
>
> Hamilton 叮嘱所有的士兵，切勿擦枪走火暴露目标，因为他们要潜伏到目标地点。
>
> 战场的地形，从俯视图上可以看作二维平面上的一个N×M*N*×*M* 的矩形，战场的**入口**在左下角，坐标为 (0,0)(0,0) ，而**目标地点**在右上角 (N,M)(*N*,*M*) 。战场上敌人安放了 p*p* 个哨塔，每个哨塔都有自己的探测范围 r*r* ，要想不被发现，Hamilton 的军队必须待在每个探测器的探测范围之外。即他们与任一哨塔的距离必须**严格大于**该哨塔的探测范围，否则就会被发现。
>
> Hamilton 军队在行军的过程中，可以被看作一个没有面积的点，并且军队可以在矩形范围 —— (x,y)∈R×R,0≤x≤N,0≤y≤M(*x*,*y*)∈R×R,0≤*x*≤*N*,0≤*y*≤*M* 中自由移动（注意到可以移动到实数坐标位置）。现在你需要判断他们能否在不被敌方哨塔发现的前提下潜伏到达目标地点。注意，他们必须从入口出发，到达目标地点，且不能离开矩形区域。
>
> 如果他们可以到达，输出 `S` ，否则输出 `N` 。
>
> # Format
>
> ## Input
>
> 第一行，正整数 N*N* ，和正整数 M*M*.
>
> 接下来一行，正整数 p*p* ，代表哨塔的数量。
>
> 接下来 p*p* 行，每行三个整数，x*x*，y*y*，r*r*，表示这个哨塔位于坐标 (x,y)(*x*,*y*) ，探测半径为 r*r*。
>
> ## Output
>
> 如果 Hamilton 的军队能不被发现，到达目标地点，输出 `S`，否则输出 `N`。
>
> # Samples
>
> #### input 1
>
> ```none
> 10 22
> 2
> 4 6 5
> 6 16 5
> ```
>
> [Copy](javascript:;)
>
> #### output 1
>
> ```none
> S
> ```
>
> [Copy](javascript:;)
>
> #### input 2
>
> ```none
> 10 10
> 2
> 3 7 4
> 5 4 4
> ```
>
> [Copy](javascript:;)
>
> #### output 2
>
> ```none
> N
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤N≤100001≤*N*≤10000，1≤M≤100001≤*M*≤10000，1≤p≤10001≤*p*≤1000，0<x<N0<*x*<*N*，0<y<M0<*y*<*M*，0<r≤100000<*r*≤10000

```c++
#include <bits/stdc++.h>
using namespace std;

int N, M, p;

double dist_p(int x1, int y1, int x2, int y2) {
    return sqrt((double)(x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

struct Tower {
    double x, y, r;
    bool is_end;
    Tower() : x(0), y(0), r(0), is_end(0) {}
    Tower(double a, double b, double c, bool i) : x(a), y(b), r(c), is_end(i) {}
    
    bool operator<(Tower other) const {
        return dist_p(x, y, 0, M) - r < dist_p(other.x, other.y, 0, M) - other.r;
    }
};

bool is_cover(Tower a, Tower b) {
    return dist_p(a.x, a.y, b.x, b.y) <= (double)a.r + b.r;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> N >> M >> p;
    vector<Tower> towers;
    vector<Tower> from;

    for (int i = 0; i < p; ++i) {
        double a, b, c;
        cin >> a >> b >> c;
        
        //cout << "Tower " << i + 1 << ": (" << a << ", " << b << ", " << c << ")" << endl;

        if(((b - c <= 0) && (a - c <= 0 ))|| ((b + c >= M) && (a + c >= N))) {
            cout << "N" << endl;
            return 0;
        }
        
        if (b + c >= M || a - c <= 0) {
            Tower t(a, b, c, 0);
            from.push_back(t);
            continue;
        }
        if (b - c <= 0 || a + c >= N) {
            Tower t(a, b, c, 1);
            towers.push_back(t);
            continue;
        }
        
        Tower t(a, b, c, 0);
        towers.push_back(t);
    }

    sort(towers.begin(), towers.end());

    for (auto& token : towers) {
        for (auto& f_token : from) {
            if (is_cover(token, f_token)) {
                if (token.is_end) {
                    cout << "N" << endl;
                    return 0;
                }
                from.push_back(token);
                break;
            }
        }
    }

    cout << "S" << endl;
    return 0;
}
```



## XRJ的钢琴键

> ## 题目背景
>
> XRJ，人称钢琴小王子，乃是 1-213 寝室四大成员之一。
>
> ## 题目描述
>
> XRJ 的魔法钢琴有 n*n* 个钢琴键，每个钢琴键有一个音乐值 ci*c**i*，这些值可正可负可为 00。
>
> XRJ 手很长，一次可以按下区间 [L,R][*L*,*R*] 里面的所有钢琴键，区间 [L,R][*L*,*R*] 的音乐值为区间内钢琴键的音乐值的总和。
>
> 他想知道，音乐值大于零的区间到底有多少个？
>
> 合法区间 [L,R][*L*,*R*] 应当满足 1≤L≤R≤n1≤*L*≤*R*≤*n*
>
> ## 输入格式
>
> 一行，一个整数 n*n*
>
> 接下来 n*n* 行，每行一个整数 ci*c**i*，代表第 i*i*个钢琴键的音乐值。
>
> ## 输出格式
>
> 一行，一个整数，代表音乐值大于零的区间的个数。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 4
> 10
> -10
> 7
> -5
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 5
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 100%的数据，n≤5×105*n*≤5×105，∣ci∣≤107∣*c**i*∣≤107。

```c++
#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
using namespace std;

long long fenwick_search_point(vector<long long>& fenwick, int idx) {
    long long sum = 0;
    for(int i=idx;i>0;i-=lowbit(i)) {
        sum += fenwick[i];
    }
    return sum;
}

void fenwick_point_add_one(vector<long long>& fenwick, int idx) {
    for(int i=idx;i<(int)fenwick.size();i+=lowbit(i)) {
        fenwick[i] += 1;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;
    vector<long long> prefix(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        long long x;
        cin >> x;
        prefix[i] = prefix[i - 1] + x;
    }

    vector<long long> sortedPrefix = prefix;
    sort(sortedPrefix.begin(), sortedPrefix.end());

    // 树状数组
    vector<long long> fenwick(sortedPrefix.size() + 1, 0);
    long long ans = 0;

    for (int i = 0; i <= n; ++i) {
        int idx = lower_bound(sortedPrefix.begin(), sortedPrefix.end(), prefix[i]) - sortedPrefix.begin() + 1;
        ans += fenwick_search_point(fenwick, idx - 1);
        fenwick_point_add_one(fenwick, idx);
    }

    cout << ans << endl;
    return 0;
}
```



## 破坏数组

> # Description
>
> 给定一个数组 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*，再给定一个长度为 n*n* 的排列，要求按照排列顺序破坏指定位置的元素。
>
> 在每次破坏一个元素之后，你要找到一个连续的没被破坏过的区间，使得区间元素之和最大，并输出最大值。
>
> # Format
>
> ## Input
>
> 第一行一个整数 n*n*，表示数组长度。
>
> 第二行包括 n*n* 个整数，表示 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*。
>
> 第三行包括 n*n* 个整数，为一个长度为 n*n* 排列，表示按照破坏元素的位置顺序。
>
> ## Output
>
> 一共 n*n* 行，每行一个数，第 i*i* 行表示第 i*i* 次破坏元素之后的连续未被破坏区间的最大值。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 4
> 1 3 2 5
> 3 4 1 2
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 5
> 4
> 3
> 0
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 8
> 5 5 4 4 6 6 5 5
> 5 2 8 7 1 3 4 6
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> 18
> 16
> 11
> 8
> 8
> 6
> 6
> 0
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤1061≤*n*≤106，1≤ai≤1091≤*a**i*≤109。

```c++
//只要把所有的cin\cout改成printf\scanf就过了.......
#include <bits/stdc++.h>
using namespace std;

vector<long long> sum;
vector<int> parent, un_size; 
int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    
    // 直接按秩合并，减少判断
    if (un_size[x] < un_size[y]) swap(x, y);
    parent[y] = x;
    sum[x] += sum[y];
    un_size[x] += un_size[y];
}

int main() {
    int n;
    scanf("%d", &n); // 使用scanf读取n

    vector<long long> a(n + 1);
    vector<int> op(n);
    sum.resize(n + 1);
    parent.resize(n + 1);
    un_size.resize(n + 1, 1);  // 初始化size为1，表示每个节点初始是一个单独的集合
    
    fill(parent.begin() + 1, parent.end(), -1);
    fill(sum.begin() + 1, sum.end(), 0);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]); // 使用scanf读取a[i]
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &op[i]); // 使用scanf读取op[i]
    }

    vector<long long> result;
    result.push_back(0);
    long long maxSum = 0;

    // 从最后一个恢复开始
    for (int i = n - 1; i >= 0; i--) {
        int pos = op[i];
        parent[pos] = pos;  // 恢复pos的位置为根节点
        sum[pos] = a[pos];  // 恢复sum

        // 合并相邻节点，只在当前恢复点的相邻节点已经恢复并且是有效的
        if (pos > 1 && parent[pos - 1] != -1) unite(pos, pos - 1);
        if (pos < n && parent[pos + 1] != -1) unite(pos, pos + 1);

        maxSum = max(maxSum, sum[find(pos)]);  // 查找并更新最大值
        result.push_back(maxSum);
    }

    // 逆序输出结果
    for (int i = n - 1; i >= 0; i--) {
        printf("%lld\n", result[i]); // 使用printf输出结果
    }

    return 0;
}
```



## k 子串

> # Description
>
> 给定一个长度为 n*n*，且全部为小写字母的字符串 s*s*。
>
> 定义 k*k* 子串为字符串 subsk=sksk+1...sn+1−k*s**u**b**s**k*=*s**k**s**k*+1...*s**n*+1−*k*，显然 subs1=s*s**u**b**s*1=*s*，且有⌈n2⌉⌈2*n*⌉个 k*k* 子串。
>
> 当满足以下条件时，我们称字符串 t*t* 为 T*T* 的奇前后缀。
>
> - ∣T∣>∣t∣∣*T*∣>∣*t*∣
> - ∣t∣∣*t*∣ 是一个奇数
> - t*t* 同时是 T*T* 的前缀和后缀
>
> 现在对于每一个 k*k* 子串 ( k∈[1,⌈n2⌉]*k*∈[1,⌈2*n*⌉] )，求它的最大奇前后缀的长度。
>
> # Format
>
> ## Input
>
> 第一行一个整数 n*n*，表示字符串 s*s* 的长度
>
> 第二行为字符串 s*s*，包含 n*n* 个小写字母
>
> ## Output
>
> 输出 ⌈n2⌉⌈2*n*⌉ 个数，第 i*i* 个数表示 i*i* 子串的最大奇前后缀的长度。如果没有最大奇前后缀，则输出 −1−1 。
>
> # Samples
>
> 输入样例1
>
> ```none
> 15
> bcabcabcabcabca
> ```
>
> [Copy](javascript:;)
>
> 输出样例1
>
> ```none
> 9 7 5 3 1 -1 -1 -1
> ```
>
> [Copy](javascript:;)
>
> 输入样例2
>
> ```none
> 24
> abaaabaaaabaaabaaaabaaab
> ```
>
> [Copy](javascript:;)
>
> 输出样例2
>
> ```none
> 15 13 11 9 7 5 3 1 1 -1 -1 1
> ```
>
> [Copy](javascript:;)
>
> 输入样例3
>
> ```none
> 19
> cabcabbcabcabbcabca
> ```
>
> [Copy](javascript:;)
>
> 输出样例3
>
> ```none
> 5 3 1 -1 -1 1 1 -1 -1 -1
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤1061≤*n*≤106
>
> 第一个样例：
>
> 1子串：**bcabcabca**bcabca
>
> 2子串：**cabcabc**abcabc

```c++
#include<bits/stdc++.h>
using namespace std;
const int base = 131;
const int mod = 1000000007;
const int MAX=10000010;
long long my_hash[MAX], power_base[MAX];
int n;

long long gethash(int x, int y) {
    return (my_hash[y] - my_hash[x-1] * power_base[y-x+1] % mod + mod) % mod;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    string s;
    cin >> s;
    power_base[0] = 1;
    for (int i = 1; i <= n; i++) 
        power_base[i] = power_base[i-1] * base % mod;

    my_hash[0] = 0;
    for (int i = 1; i <= n; i++) 
        my_hash[i] = (my_hash[i-1] * base + s[i-1] - 'a') % mod;

    int start_p = (n - 1) / 2;
    vector<int> result(start_p + 2);
    result[start_p + 1] = -1;

    for (int i = start_p; i >= 0; i--) {
        result[i] = result[i + 1] + 2;
        while (result[i] > 0 && i * 2 + result[i] >= n) 
            result[i] -= 2;
        while (result[i] > 0 && gethash(i + 1, i + result[i]) != gethash(n - i - result[i] + 1, n - i)) 
            result[i] -= 2;
    }

    for (int i = 0; i <= start_p; i++) 
        cout << result[i] <<" ";

    return 0;
}
```



## 跑步

> ## 题目背景
>
> 因为题目太难，同学们集体罢工不在考试，于是统统到操场跑步去了。
>
> ## 题目描述
>
> 俯视操场，把操场看成一个平面，建立平面直角坐标系。
>
> - 同学们分成了两组。
> - 第一组的同学刚开始站在 x*x* 轴上，位置在 (pi,0)(*p**i*,0)，他们的跑动速度**都是** (0,v1)(0,*v*1)`（即：向y轴方向以v1速度跑动）`。每个人有一个视野范围 wi*w**i*，也就是说，当他位于坐标(x,y)(*x*,*y*)时，能够看见点 (x,y)(*x*,*y*) 到点(x+wi,y)(*x*+*w**i*,*y*) 这条线段上的人（包含端点）。
> - 第二组的同学刚开始站在 y*y* 轴上，位置在(0,pi)(0,*p**i*)，他们的跑动速度**都是** (v2,0)(*v*2,0)`（即：向x轴方向以v2速度跑动）`。每个人有一个视野范围 wi*w**i* ，也就是说，当他位于坐标 (x,y)(*x*,*y*) 时，能够看见点 (x,y)(*x*,*y*) 到点 (x,y+wi)(*x*,*y*+*w**i*) 这条线段上的人（包含端点）。
> - 同学们都有一个自己的出现时间 ti*t**i*，可以理解为，在ti*t**i*时间，这个同学会**出现**在自己的位置上，然后按照自己的速度开始奔跑。
> - 每位同学在自己**奔跑的时候**，会记录自己视野范围内出现的人，现在你需要求出每位同学在自己奔跑的过程中，能记录到多少个不同的人（不包括自己）。（假设时间无限，一直跑下去）
>
> ## 输入格式
>
> 一行，三个整数，n,v1,v2*n*,*v*1,*v*2。
>
> 接下来 n*n* 行，每行四个整数 ai,ti,pi,wi*a**i*,*t**i*,*p**i*,*w**i*，分别表示这个同学时第 ai*a**i* 组的同学，他的出现时间是 ti*t**i*，位置参数是 pi*p**i*，视野范围是 wi*w**i*。
>
> ## 输出格式
>
> n*n* 行，第 i*i* 行表示第 i*i* 个人在跑步过程中一共看见的不同的人数。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 2 1 1
> 1 1 1 1
> 2 2 2 1
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 1
> 1
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> 5 1 1
> 1 1 1 1
> 2 2 2 1
> 1 2 2 3
> 2 3 3 3
> 2 6 6 6
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> 3
> 2
> 3
> 2
> 2
> ```
>
> [Copy](javascript:;)
>
> ## 提示
>
> 【数据范围】：
>
> 对30%的数据满足，n≤1000*n*≤1000
>
> 对50%的数据满足，v1=v2=1*v*1=*v*2=1
>
> 对100%的数据满足，1≤n,v1,v2,ti,pi,wi≤105，ai∈{1,2}1≤*n*,*v*1,*v*2,*t**i*,*p**i*,*w**i*≤105，*a**i*∈{1,2}。 保证同组的同学中，任意两个同学的 ti,pi*t**i*,*p**i* 不相同。

```c++
#include<bits/stdc++.h>
using namespace std;
const double EXP=1e-9;
struct people{
    double a,t,p,w;
    people(double x,double y,double z,double q):a(x),t(y),p(z),w(q){}

};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    double v1,v2;
    cin>>v1>>v2;
    vector<people> ps;
    vector<double> fi,fj;
    for(int i=0;i<n;i++)
    {
        double ai,ti,pi,wi;
        cin>>ai>>ti>>pi>>wi;
        people p=people(ai,ti,pi,wi);
        ps.push_back(p);
        if(ai==1)
        {
            double x=pi/v2-ti;
            fi.push_back(x);
        }
        else
        {
            double x=pi/v1-ti;
            fj.push_back(x);
        }
    }
    sort(fi.begin(),fi.end());
    sort(fj.begin(),fj.end());
    for(int i=0;i<n;i++)
    {
        people cur=ps[i];
        if(cur.a==1)
        {
            double lo_x=cur.p/v2-cur.t;
            double up_x=lo_x+cur.w/v2;
            auto lower=lower_bound(fj.begin(),fj.end(),lo_x-EXP);
            auto upper=lower_bound(fj.begin(),fj.end(),up_x+EXP);
            cout<<(int)(upper-lower)<<endl;
        }
        else
        {
            double lo_x=cur.p/v1-cur.t;
            double up_x=lo_x+cur.w/v1;
            auto lower=lower_bound(fi.begin(),fi.end(),lo_x-EXP);
            auto upper=lower_bound(fi.begin(),fi.end(),up_x+EXP);
            cout<<(int)(upper-lower)<<endl;
        }
    }
    return 0;
}
```

