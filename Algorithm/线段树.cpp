/**
题目描述
如题，已知一个数列，你需要进行下面两种操作：
1.将某区间每一个数加上x
2.求出某区间每一个数的和
输入格式
第一行包含两个整数N、M，分别表示该数列数字的个数和操作的总个数。
第二行包含N个用空格分隔的整数，其中第i个数字表示数列第i项的初始值。
接下来M行每行包含3或4个整数，表示一个操作，具体如下：
操作1： 格式：1 x y k 含义：将区间[x,y]内每个数加上k
操作2： 格式：2 x y 含义：输出区间[x,y]内每个数的和
输出格式
输出包含若干行整数，即为所有操作2的结果。
 * 
*/

//参考文章
//https://zhuanlan.zhihu.com/p/106118909?utm_id=0
//https://blog.csdn.net/huangzihaoal/article/details/81813454

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 1e5 + 5;
ll tree[MAXN << 2], mark[MAXN << 2]/*开4倍空间*/, n/*元素个数*/, m/*操作个数*/, A[MAXN];
void push_down(int p, int len)  //下沉
{
    if (len <= 1) return;  //叶子节点不必加标记
    tree[p << 1] += mark[p] * (len - len / 2);
    mark[p << 1] += mark[p];
    tree[p << 1 | 1] += mark[p] * (len / 2);
    mark[p << 1 | 1] += mark[p];
    mark[p] = 0;
}
void build(int p = 1, int cl = 1, int cr = n)  //建树
{
    if (cl == cr) return void(tree[p] = A[cl]);
    int mid = (cl + cr) >> 1;
    build(p << 1, cl, mid);  //左子树
    build(p << 1 | 1, mid + 1, cr);  //右子树
    tree[p] = tree[p << 1] + tree[p << 1 | 1];  //保存区间和
}
ll query(int l, int r, int p = 1, int cl = 1, int cr = n)  //区间查询
{
    if (cl >= l && cr <= r) return tree[p];
    push_down(p, cr - cl + 1);  //需要先下沉
    ll mid = (cl + cr) >> 1, ans = 0;
    if (mid >= l) ans += query(l, r, p << 1, cl, mid);
    if (mid < r) ans += query(l, r, p << 1 | 1, mid + 1, cr);
    return ans;
}
void update(int l, int r, int d, int p = 1, int cl = 1, int cr = n)  //区间修改
{
    if (cl >= l && cr <= r){//实际上不会出现区间[cl, cr] < [l, r]的情况,因为在递归时区间[cl, cr]总是被撑满的,保证了[cl, cr]总是 >= [l, r]
        tree[p] += (cr - cl + 1) * d;
        if (cr > cl)mark[p] += d;
        return;
    }
    push_down(p, cr - cl + 1);  //需要先下沉
    int mid = (cl + cr) >> 1;
    if (mid >= l) update(l, r, d, p << 1, cl, mid); //递归左子树
    if (mid < r) update(l, r, d, p << 1 | 1, mid + 1, cr); //递归右子树
    tree[p] = tree[p << 1] + tree[p << 1 | 1];
}
int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> A[i];
    build();
    while (m--)
    {
        int o, l, r, d;
        cin >> o >> l >> r;
        if (o == 1)
            cin >> d, update(l, r, d);
        else
            cout << query(l, r) << '\n';
    }
    return 0;
}