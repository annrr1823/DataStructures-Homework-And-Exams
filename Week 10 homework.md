# Week 10 homework

[TOC]

## 后序遍历

> # Description
>
> 给定一棵 n*n* 个节点的二叉树的前序遍历（根、左、右）和中序（左、根、右）遍历，求其后序遍历（左、右、根）。
>
> # Format
>
> ## Input
>
> 第一行一个数 n*n*，表示树的节点个数。
>
> 接下来一行 n*n* 个整数，表示前序遍历的节点编号。
>
> 接下来一行 n*n* 个整数，表示中序遍历的节点编号。
>
> ## Output
>
> 一行 n*n* 个整数，表示后序遍历的节点编号。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 9
> 1 2 4 7 3 5 8 9 6
> 4 7 2 1 8 5 9 3 6
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 7 4 2 8 9 5 6 3 1
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤10001≤*n*≤1000。
>
> 样例：
>
> ![image.png](https://i.loli.net/2021/11/05/rsA9gTh2ODUuyCv.png)

```c++
#include<bits/stdc++.h>
using namespace std;

void buil_post_order(const vector<long long>& preorder,int pre_start,int pre_end,
                     const vector<long long>& inorder,int in_start,int in_end,
                     unordered_map<long long,int>& index_map,vector<long long>& postorder)
{
    if(pre_start>pre_end || in_start>in_end)return;
    int root_val=preorder[pre_start];
    int root_idx=index_map[root_val];
    int left_size=root_idx-in_start;
    //left
    buil_post_order(preorder,pre_start+1,pre_start+left_size,inorder,in_start,root_idx-1,index_map,postorder);
    //right
    buil_post_order(preorder,pre_start+left_size+1,pre_end,inorder,root_idx+1,in_end,index_map,postorder);
    postorder.push_back(root_val);
    return ;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    vector<long long> preorder(n);
    vector<long long> inorder(n);
    for(int i=0;i<n;i++)cin>>preorder[i];
    for(int i=0;i<n;i++)cin>>inorder[i];

    unordered_map<long long,int> index_map;
    for(int i=0;i<n;i++)index_map[inorder[i]]=i;
    vector<long long> postorder;
    buil_post_order(preorder,0,n-1,inorder,0,n-1,index_map,postorder);
    for(int i=0;i<n;i++)cout<<postorder[i]<<" ";
    return 0;
}
```



## 石子合并

> # Description
>
> ZZR 有 n*n* 堆石子，每堆石子的石子数量为 ai*a**i*。
>
> 现在他想要将这 n*n* 堆石子合并为一堆石子。他每次可以选择其中任意两堆🪨进行合并，合并产生的新堆石子数量为这两堆之和。
>
> ZZR 年老体弱，而每次合并两堆石子要花费两堆石子数量之和的体力值。现在 ZZR 想要以最少的体力合并这些石子，请问最少需要花费多少体力？
>
> # Format
>
> ## Input
>
> 第一行包含一个整数 n*n*，表示🪨堆数。
>
> 接下来一行包含 n*n* 个整数 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*，表示每堆🪨中🪨数量。
>
> ## Output
>
> 一个整数，表示 ZZR 需要花费的最少体力。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 3
> 8 5 8
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 34
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤1051≤*n*≤105，1≤ai≤1091≤*a**i*≤109。
>
> 对于样例，ZZR 首先合并第一堆石子和第二堆石子为一堆，合并后🪨数共 13 个，花费 13 体力；接下来还有两堆🪨数量分别为 13 和 8，合并这两堆🪨为一堆🪨，共 21 🪨数，花费 21 体力。总共花费 13+21=34 体力。

```c++
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    priority_queue<long long, vector<long long>, greater<long long>> minHeap; 

    for (int i = 0; i < n; ++i) {
        long long ai;
        cin >> ai;
        minHeap.push(ai);
    }

    long long totalCost = 0; 
    while (minHeap.size() > 1) {
        long long first = minHeap.top();
        minHeap.pop();
        long long second = minHeap.top(); 
        minHeap.pop();

        long long mergeCost = first + second;
        totalCost += mergeCost;

        minHeap.push(mergeCost);
    }

    cout << totalCost << endl; 
    return 0;
}

```



## 成为一棵树

> # Description
>
> 
>
> *如果有来生，我要做一棵树，*
>
> *站成永恒，没有悲欢的姿势，**一半在尘土里安详，一半在风里飞扬；**一半洒落荫凉，一半沐浴阳光，**非常沉默、非常骄傲。**从不依靠、从不寻找。*
>
> 
>
> Y 觉得树很好，他希望军训的同学也能像树一样。
>
> 为此，他将 n*n* 名同学排成树的形状，每个同学站在树的一个节点上，1 号同学站在根的位置。
>
> 这 n*n* 名同学的美丽值为 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*。而 Y 又定义了一个名为“树值”的玩意，他认为，每个同学的树值为该同学对应节点子树中所有同学的美丽值之和加上子树中同学的数量。注意，节点 v*v* 的子树包括节点 v*v* 自己。
>
> Y 想知道，所有同学的树值之和是多少。
>
> # Format
>
> ## Input
>
> 第一个一个整数 n*n* 表示同学数量。
>
> 第二行 n−1*n*−1 个整数分别表示第 2,3,⋯ ,n2,3,⋯,*n* 号同学的“父亲”。
>
> 第三行 n*n* 个整数表示 a1,a2,⋯ ,an*a*1,*a*2,⋯,*a**n*。
>
> ## Output
>
> 一行一个整数表示所有同学的树值之和。
>
> # Samples
>
> #### 输入样例
>
> ```none
> 10
> 1 1 3 4 2 4 3 3 9 
> 9 4 7 9 7 4 6 10 6 6
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例
>
> ```none
> 223
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 1≤n≤1061≤*n*≤106，1≤ai≤1051≤*a**i*≤105。
>
> 节点编号从 1 开始。

```c++
#include <iostream>
#include <vector>
using namespace std;

#define MAX_NODES 1000011 
int n;             
int beauty[MAX_NODES]; 
int subtree_size[MAX_NODES]; 
vector<int> tree[MAX_NODES]; 

long long total_tree_value = 0;

long long dfs(int node) {
    subtree_size[node] = 1;
    long long current_tree_value = beauty[node];

    for (int child : tree[node]) {
        long long child_tree_value = dfs(child); 
        current_tree_value += child_tree_value;
        subtree_size[node] += subtree_size[child];
    }

    total_tree_value += current_tree_value + subtree_size[node];
    return current_tree_value; 
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;

    for (int i = 2; i <= n; i++) {
        int parent;
        cin >> parent;
        tree[parent].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        cin >> beauty[i];
    }

    dfs(1);

    cout << total_tree_value << endl;

    return 0;
}

```



## 翻转二叉树

> # Description
>
> 给定一颗二叉树，翻转这棵二叉树（每个结点都交换左右子树），按照先序遍历输出。
>
> # Format
>
> ## Input
>
> 第一行两个整数 n,m*n*,*m* ，表示这颗二叉树的节点数量和第二行输入的数量。
>
> 第二行总共 m*m*个数据（整数 / `null`）表示这个树。
>
> 假设输入了 m*m* 个数据为 a1,a2,...,am*a*1,*a*2,...,*a**m*，数据保证 a1*a*1 不是 `null`。
>
> 对于数据 ai*a**i*，若 i*i* 是奇数，则代表 a⌊i2⌋*a*⌊2*i*⌋ 右儿子信息；若 i*i* 是偶数，则代表 a⌊i2⌋*a*⌊2*i*⌋ 左儿子信息。
>
> 数据中 `null` 表示该节点为空节点，数据保证树是合法的，且为了节省输入数据的数量，省略这颗树最后的连续的 `null`。
>
> ## Output
>
> 一行 n*n* 个数，表示翻转之后的二叉树的前序遍历结果。
>
> # Samples
>
> #### 输入样例 1
>
> ```none
> 7 7
> 4 2 7 1 3 6 9
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 1
>
> ```none
> 4 7 9 6 2 3 1
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 2
>
> ```none
> 3 3
> 2 1 3
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 2
>
> ```none
> 2 3 1
> ```
>
> [Copy](javascript:;)
>
> #### 输入样例 3
>
> ```none
> 5 7
> 3 9 20 null null 15 7
> ```
>
> [Copy](javascript:;)
>
> #### 输出样例 3
>
> ```none
> 3 20 7 15 9
> ```
>
> [Copy](javascript:;)
>
> # Limitation
>
> 3≤n≤5×1053≤*n*≤5×105。
>
> 1≤m≤1061≤*m*≤106。
>
> 树中所有的数 <109<109，且各不相同。
>
> 将 `string` 转成 `int`：
>
> ```cpp
> #include <cstdlib>
> 
> int toint(string x) {
>     return atoi(x.c_str());
> }
> ```

```c++
#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;
long long toint(string x) {
    return atoll(x.c_str());
}

struct TreeNode {
    long long val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(long long x) : val(x), left(nullptr), right(nullptr) {}
};


TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) {
            return nullptr;
        }
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        root->left = right;
        root->right = left;
        return root;
}

void preorder(TreeNode* root) {
    if (root == nullptr) return ;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

TreeNode* buildTree(const vector<string>& nodes) {
    TreeNode* root = new TreeNode(toint(nodes[0]));
    vector<TreeNode*> treeNodes = { root };
    for (int i = 1; i < (int)nodes.size(); ++i) {
        if (nodes[i] != "null") {
            TreeNode* newNode = new TreeNode(toint(nodes[i]));
            treeNodes.push_back(newNode);

            TreeNode* parent = treeNodes[(i - 1) / 2];
            
            if (i % 2 == 0) {
                parent->right = newNode;
            } else {
                parent->left = newNode; 
            }
        } else {
            treeNodes.push_back(nullptr);
        }
    }

    return root;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<string> nodes(m);
    for (int i = 0; i < m; ++i) {
        cin >> nodes[i];
    }
    
    TreeNode* root = buildTree(nodes);
    
    root = invertTree(root);
    
    preorder(root);
    cout << endl;
    
    return 0;
}
```



## 二叉树上的询问

> #### 【题目描述】
>
> 给出一棵具有 n*n* 个结点的树。
>
> 我们规定，11 是这棵树的树根。
>
> 并且，我们规定，对于所有的 2≤i≤n2≤*i*≤*n* ，编号为 i*i* 的结点的父结点是 ⌊i2⌋⌊2*i*⌋ 。
>
> 显然，这是一棵二叉树，对于节点 i*i* ，其左子结点是 2i2*i* ，其右子结点是 2i+12*i*+1 （如果它有对应子节点的话）。
>
> 现在，有 m*m* 个询问。每个询问，问编号为 x*x* 的结点在这棵二叉树的前序遍历中排名第几。你需要对每组询问输出对应的答案。
>
> 前序遍历：对每棵子树，先访问其根结点，再访问其左子树，最后访问其右子树。
>
> 例如，当 n=5*n*=5 的时候，前序遍历为 {1,2,4,5,3}{1,2,4,5,3}
>
> #### 【输入格式】
>
> 第一行，输入两个整数 n,m (1≤n≤1018, 1≤m≤105)*n*,*m* (1≤*n*≤1018, 1≤*m*≤105)，分别表示这棵树的结点总数，以及询问个数。
>
> 接下来 m*m* 行，第 i*i* 行输入一个整数 xi (1≤xi≤n)*x**i* (1≤*x**i*≤*n*) ，表示询问结点 xi*x**i* 在这棵树前序遍历中的排名。
>
> #### 【输出格式】
>
> 对每个询问，输出一行，一个整数，表示对应询问的答案。
>
> #### 【样例】
>
> 【输入】
>
> ```none
> 10 5
> 1
> 3
> 5
> 7
> 9
> ```
>
> [Copy](javascript:;)
>
> 【输出】
>
> ```none
> 1
> 8
> 6
> 10
> 5
> ```
>
> [Copy](javascript:;)
>
> #### 【时空限制】
>
> 1000ms 256MB

```c++
//思路参考zcy同学
#include <bits/stdc++.h>
using namespace std;

long long calculate_subtree_nodes(long long root, long long n) {
    long long count = 0;
    long long level_nodes = 1;
    while (root <= n) {
        count += min(level_nodes, n - root + 1);
        root *= 2;
        level_nodes *= 2;
    }
    return count;
}

long long find_position(long long x, long long n) {
    long long position = 1; 
    while (x > 1) {
        long long parent = x / 2;
        if (x == parent * 2 + 1) { 
            long long left_sibling = parent * 2;
            //cout<<parent<<" "<<left_sibling<<" "<<calculate_subtree_nodes(left_sibling, n)<<endl;
            position += calculate_subtree_nodes(left_sibling, n);
        }
        position++;
        x = parent;
    }
    return position;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int m;
    cin >> n >> m;
    while (m--) {
        long long x;
        cin >> x;
        cout << find_position(x, n) << '\n';
    }

    return 0;
}
```

