# Week 3 test

[TOC]



## A. 学习时间

> ## 题目背景
>
>  在研究生阶段中，很多时候来实验室学习的时间是比较自由的。但是为了保证自己的学习质量，小问还是给自己制定了一个学习计划。他希望以星期为单位安排自己的学习计划，即在学期中的每一个周一的安排一样，每一个周二的安排一样，以此类推。小问会给出周一到周日他到达实验室的时间和离开实验室回寝室休息的时间。特别的，实验室规定每一天的12:00∼13:0012:00∼13:00是午饭时间，17:00∼18:0017:00∼18:00是晚饭时间。小问在午饭时间和晚饭时间即使在实验室也不会学习，除此之外小问只要在实验室就可以学习。现在小问会给出一个学期的天数和这个学期的第一天是星期几。请你告诉小问这一个学期他的学习时间是多少**分钟**。
>
> ## 输入格式
>
> 第一行是一个正整数T*T*，表示测试数据的组数
>
> 对于每一个测试数据：
>
> 第一行有两个正整数n*n*和m*m*，分别表示一个学期的天数和这个学期的第一天是星期几。特别的，m=7*m*=7表示学期第一天是周日。
>
> 第二到八行分别表示周一到周日小问的安排，每一行包含两个24小时制的时间代表计划到实验室的时间和离开实验室的时间。
>
> **24小时制**:时间的格式是 HH:MM其中HH是代表小时数，从小到大是00,01,02,...,23。MM代表分钟，从小到大是00,01,...,59.
>
> ## 输出格式
>
> 文件包含T*T*行，每一行一个正整数。第i*i*行的正整数表示第i*i*个测试用例的答案。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 1
> 8 1
> 13:00 22:36
> 09:45 21:24
> 12:46 22:59
> 08:17 09:53
> 10:48 16:19
> 13:26 20:38
> 08:00 22:04
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 3613
> ```
>
> [Copy](javascript:;)
>
> ## 样例 #2
>
> ### 样例输入 #2
>
> ```none
> 5
> 441344068 7
> 12:53 15:27
> 09:15 10:45
> 05:31 06:24
> 08:17 20:41
> 08:14 19:31
> 09:26 20:34
> 08:33 18:12
> 840937714 5
> 01:29 22:11
> 06:38 07:30
> 04:52 08:46
> 09:28 15:19
> 09:16 15:19
> 11:01 13:37
> 19:30 23:05
> 9269945 3
> 12:24 15:58
> 15:31 17:55
> 10:04 22:22
> 00:04 04:28
> 03:28 07:23
> 01:03 21:40
> 15:56 22:18
> 35754769 2
> 15:35 23:47
> 06:25 18:38
> 01:58 18:19
> 01:28 21:45
> 09:14 15:09
> 10:39 12:29
> 08:19 17:42
> 711324604 1
> 06:19 09:40
> 08:02 12:30
> 10:26 16:23
> 12:31 19:51
> 13:34 17:49
> 07:38 17:31
> 01:37 09:44
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #2
>
> ```none
> 156235799405
> 277869847470
> 3738436705
> 19614044773
> 231891820687
> ```
>
> [Copy](javascript:;)
>
> ## 数据范围与提示
>
> - 对于测试点 1∼21∼2：1≤n≤10001≤*n*≤1000。
> - 对于测试点 3∼43∼4：保证n*n*是77的倍数。
> - 对于测试点 5∼105∼10：无特殊限制。
> - 对于所有数据：1≤T≤1001≤*T*≤100，1≤n≤1091≤*n*≤109，1≤m≤71≤*m*≤7。
>
> ## 样例提示
>
> 以下是测试用例1中，周一到周四学习情况说明：
>
> - 周一的学习时间是13:00∼17:0013:00∼17:00和18:00∼22:3618:00∼22:36，所以周一的工作时间是240+276=516240+276=516分钟。
> - 周二的学习时间是09:45∼12:0009:45∼12:00和13:00∼17:0013:00∼17:00和18:00∼21:2418:00∼21:24，所以周二的工作时间是135+240+204=579135+240+204=579分钟。
> - 周三的学习时间是13:00∼17:0013:00∼17:00和18:00∼22:5918:00∼22:59，所以周三的工作时间是240+299=539240+299=539分钟。
> - 周四的学习时间是08:17∼09:5308:17∼09:53，所以周四的工作时间是9696分钟.。

```c++
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
void num_time(long long & t1,long long &t2)
{
    string s1,s2;
    cin>>s1>>s2;
    //cout<<s1<<s2<<endl;
    //long long t1=0,t2=0;
    t1 =((s1[0]-'0')*600+(s1[1]-'0')*60+(s1[3]-'0')*10+s1[4]-'0');
    t2 =((s2[0]-'0')*600+(s2[1]-'0')*60+(s2[3]-'0')*10+s2[4]-'0');
    return ;
}
long long count_time() {
    
    long long t1;
    long long t2;
    num_time(t1,t2);
    long long total_study_time = 0;
    long long lunch_start = 12 * 60; // 12:00
    long long lunch_end = 13 * 60;   // 13:00
    long long dinner_start = 17 * 60; // 17:00
    long long dinner_end = 18 * 60;   // 18:00

    if (t1 < lunch_start) {
        if (t2 <= lunch_start) {
            total_study_time = t2 - t1;
        } else if(t2 <= lunch_end){
            total_study_time = lunch_start-t1;
        } else if (t2 <= dinner_start) {
            total_study_time = t2 - 60 - t1;
        } else if (t2 <= dinner_end){
            total_study_time = dinner_start - 60 -t1;
        }else {
            total_study_time = t2-t1 -120;
        }
    } else if (t1 <= lunch_end) {
        if (t2<=lunch_end){
            total_study_time=0;
        } else if(t2 < dinner_start) {
            total_study_time = t2 - lunch_end; 
        } else if(t2< dinner_end){
            total_study_time = dinner_start-lunch_end;
        }else {
            total_study_time = t2-60-lunch_end;
        }
    } else if (t1 <= dinner_start) { 
        if(t2<dinner_start)total_study_time = t2-t1;
        else if(t2 < dinner_end)total_study_time = dinner_start - t1;
        else total_study_time = t2-t1-60;
    } else if(t1 <= dinner_end){
        if(t2 < dinner_end)total_study_time=0;
        else total_study_time= t2-dinner_end;
    }else {
        total_study_time = t2 - t1;
    }

    return max((long long)0,total_study_time);
}

int main()
{
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        long long n,m;
        cin>>n>>m;
        if(n<=0)
        {
            cout<<0<<endl;
            continue;
        }
        unsigned long long ans = 0;
        long long time[7];
        long long sum_7 =0;
        for(int j=0;j<7;j++)
        {
            time[j]=count_time();
            //cout<<j+1<<" : "<<time[j]<<endl;
            sum_7 += time[j];
        }
        ans += (n/7)*sum_7;
        long long left = n%7;
        for(int j=m-1;j<m+left-1;j++)
        {
            ans += time[j%7];
        }
        cout<<ans<<endl;
         
    }
    return 0;
}
```



## B. 螺旋矩阵

> ## 题目背景
>
> 输出一个 n*n* 行 m*m* 列的顺时针螺旋矩阵。
>
> 顺时针螺旋矩阵的定义是这样的：
>
> - 该矩阵由 [1,nm][1,*nm*] 中的这 n⋅m*n*⋅*m* 个整数组成，且每个整数恰好出现一次。
> - 矩阵的构造方式要求如下：
>   - 我们一个一个从小到大的顺序去放置整数。
>   - 左上角放置整数 11 ，然后开始向右放置整数，直到触及边界或者已经有数字的位置；然后向下放置；然后向左；然后向上……循环这个过程直到所有数字都放置完毕。
>
> 例如，3×33×3 的顺时针螺旋矩阵是：
>
> [123894765]187296345
>
> 例如，3×43×4 的顺时针螺旋矩阵是：
>
> [123410111259876]110921183127456
>
> 例如，4×44×4 的顺时针螺旋矩阵是：
>
> [12341213145111615610987]11211102131693141584567
>
> ## 输入格式
>
> 输入一行两个整数 n,m*n*,*m* ，意义如题目描述所示。
>
> ## 输出格式
>
> 输出 n*n* 行，每行 m*m* 个整数，整数之间用空格隔开，表示一个顺时针螺旋矩阵。
>
> ## 样例 #1
>
> ### 样例输入 #1
>
> ```none
> 5 5
> ```
>
> [Copy](javascript:;)
>
> ### 样例输出 #1
>
> ```none
> 1 2 3 4 5
> 16 17 18 19 6
> 15 24 25 20 7
> 14 23 22 21 8
> 13 12 11 10 9
> ```
>
> [Copy](javascript:;)
>
> ## 数据范围与提示
>
> 对于 70% 的测试数据满足 n=m≤10*n*=*m*≤10
>
> 对于 100% 的测试数据满足 1≤n≤100, 1≤m≤1001≤*n*≤100, 1≤*m*≤100

```c++
#include<iostream>
#include<vector>
using namespace std;
int n,m;
int main()
{
    //int n,m;
    cin>>n>>m;
    pair<int,int> de[4]={{0,1},{1,0},{0,-1},{-1,0}};
    int ** ans= (int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
    {
        ans[i]=(int*)malloc(m*sizeof(int));
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            ans[i][j]=0;
            //cout<<ans[i][j]<<" ";
        }
    }
    int sum = n*m;
    int i=0,j=0;
    int cnt = 1;
    int de_i=0;
    while(sum>0)
    {
        sum--;
        if( i<n && j<m &&i>=0 &&j>=0 && ans[i][j]==0 )
        {
            ans[i][j]=cnt;
            
            //out<<i<<" "<<j<<" "<<ans[i][j]<<endl;
            i=i+de[de_i].first;
            j=j+de[de_i].second;
            
        }
        else 
        {
            i=i-de[de_i].first;
            j=j-de[de_i].second;
            //cout<<i<<" "<<j<<endl;
            if(de_i==3)de_i=0;
            else de_i++;
            //cout<<de_i<<endl;
            i=i+de[de_i].first;
            j=j+de[de_i].second;
            //cout<<i<<" "<<j<<endl;
            ans[i][j]=cnt;
            i=i+de[de_i].first;
            j=j+de[de_i].second;
            //cout<<i<<" "<<j<<endl;
            //cout<<endl;
        }
        cnt++;
        
        //cout<<i<<" "<<j<<endl;
    }
    for(int p=0;p<n;p++)
    {
        for(int q=0;q<m;q++)
        {
            cout<<ans[p][q]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
```



## C. 重复字符串 I

同作业