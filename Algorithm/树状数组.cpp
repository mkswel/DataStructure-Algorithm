int tree[MAXN];
//lowbit(x) = x & (-x)
//单点修改
void update(int i, int x)
{
    for (int pos = i; pos < MAXN; pos += lowbit(pos))
        tree[pos] += x;
}

//区间求和
int query(int n)
{
    int ans = 0;
    for (int pos = n; pos; pos -= lowbit(pos))
        ans += tree[pos];
    return ans;
}

//区间查询
int query(int a, int b)
{
    return query(b) - query(a - 1);
}