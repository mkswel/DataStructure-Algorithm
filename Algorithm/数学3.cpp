#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
/*
高斯消元
枚举每一列
1 找到绝对值最大的一行
2 将该行换到最顶端
3 将当前行首位变为1
4 用当前行将下面所有列消成0
*/
// a[N][N]是增广矩阵 n个方程n个未知数
int gauss()
{
    int c, r;
    for (c = 0, r = 0; c < n; c ++ )
    {
        int t = r;
        for (int i = r; i < n; i ++ )   // 找到绝对值最大的行
            if (fabs(a[i][c]) > fabs(a[t][c]))   
                t = i;

        if (fabs(a[t][c]) < eps) continue;   //该列所有数的绝对值为0（eps=1e-6）

        for (int i = c; i <= n; i ++ ) swap(a[t][i], a[r][i]);      // 将绝对值最大的行换到最顶端
        for (int i = n; i >= c; i -- ) a[r][i] /= a[r][c];      // 将当前行的首位变成1
        for (int i = r + 1; i < n; i ++ )       // 用当前行将下面所有的列消成0
            if (fabs(a[i][c]) > eps)   //如果是0就不用消了
                for (int j = n; j >= c; j -- )
                    a[i][j] -= a[r][j] * a[i][c];

        r ++ ;//遍历下一行
    }

    if (r < n)
    {
        for (int i = r; i < n; i ++ )
            if (fabs(a[i][n]) > eps)//0等于非0
                return 2; // 无解
        return 1; // 有无穷多组解
    }

    for (int i = n - 1; i >= 0; i -- )//从最后一行开始
        for (int j = i + 1; j < n; j ++ )
            a[i][n] -= a[i][j] * a[j][n];

    return 0; // 有唯一解
}


//组合数
/*
求多组组合数
情况一：10万组询问，范围1<b<a<2000，求C(a,b)模1e9+7，               可以用递推式C(a,b)=C(a-1,b)+C(a-1,b-1)解决
情况二：1万组询问，范围1<b<a<100000，求C(a,b)模1e9+7，              可以用阶乘公式预处理（考虑取模情况，a!/((b-a)!b!)要取模，则要对(b-a)!b!取逆元处理）
情况三：20组询问，范围1<b<a<1e18，2<p<1e5，p是质数。求C(a,b)模p，    用卢卡斯定理 C(a,b)同余C(a mod p,b mod p)*C(a/p,b/p)(mod p)
情况四：求C(a,b)，要求得到高精度结果                                质因数分解,将转化成C(a,b)=p1^x1*p2^x2*...*pn^xn的乘法形式，然后实现高精度乘法
                                                                  求a!中质因数p的个数：为a/p+a/p^2+a/p^3+...
                                                                    证明：在数1*2*3*...*a中可能存在p,2p,...,kp，用a/p可得即1次p的个数k；
                                                                    再看1p^2,2p^2,...,hp^2，用a/p^2可得2次p的个数h，这里p的次数本应为2h，
                                                                    但在算1次p时已经重复算过一次了，所以要减一个h，所以只需算一次a/p^2，后续以此类推。
*/

//情况二
//fact[n]表示n!，infact[n]表示模1e9+7的逆元(n!)^-1
int qmi(int a, int k, int p)    // 快速幂模板(模1e9+7是质数，可以用快速幂模板)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

// 预处理阶乘的余数和阶乘逆元的余数
fact[0] = infact[0] = 1;
for (int i = 1; i < N; i ++ )
{
    fact[i] = (LL)fact[i - 1] * i % mod;
    infact[i] = (LL)infact[i - 1] * qmi(i, mod - 2, mod) % mod;
}

//情况三
    // 若p是质数，则对于任意整数 1 <= m <= n，有：
    // C(n, m) = C(n % p, m % p) * C(n / p, m / p) (mod p)

int qmi(int a, int k, int p)  // 快速幂模板
{
    int res = 1 % p;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

int C(int a, int b, int p)  // 通过定理求组合数C(a, b)
{
    if (a < b) return 0;

    LL x = 1, y = 1;  // x是分子，y是分母
    for (int i = a, j = 1; j <= b; i --, j ++ )   //组合数公式
    {
        x = (LL)x * i % p;
        y = (LL) y * j % p;
    }

    return x * (LL)qmi(y, p - 2, p) % p;  //取模所以除法换成乘逆元
}

int lucas(LL a, LL b, int p)
{
    if (a < p && b < p) return C(a, b, p);
    return (LL)C(a % p, b % p, p) * lucas(a / p, b / p, p) % p;
}



//情况四

int primes[N], cnt;     // 存储所有质数
int sum[N];     // 存储每个质数的次数
bool st[N];     // 存储每个数是否已被筛掉


void get_primes(int n)      // 线性筛法求素数
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}


int get(int n, int p)       // 求n！中的次数
{
    int res = 0;
    while (n)
    {
        res += n / p;
        n /= p;
    }
    return res;
}


vector<int> mul(vector<int> a, int b)       // 高精度乘低精度模板
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i ++ )
    {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }

    while (t)
    {
        c.push_back(t % 10);
        t /= 10;
    }

    return c;
}

get_primes(a);  // 预处理范围内的所有质数

for (int i = 0; i < cnt; i ++ )     // 求每个质因数的次数
{
    int p = primes[i];
    sum[i] = get(a, p) - get(b, p) - get(a - b, p);
}

vector<int> res;
res.push_back(1);

for (int i = 0; i < cnt; i ++ )     // 用高精度乘法将所有质因子相乘
    for (int j = 0; j < sum[i]; j ++ )
        res = mul(res, primes[i]);




//卡特兰数
/*
设序列1,2,3,4,...,n依次入栈，求出栈序列种数
记f(i)表示长度为i的序列出栈种数。设最后出栈的数为k，则比它小的数要出栈，即f(k-1)，比它大的数也要出栈，即f(n-k)两者相乘f(k-1)f(n-k)
数列满足递推式a(n+1)=a(0)a(n)+a(1)a(n-1)+...+a(n)a(0)
卡特兰数 C(2n,n)-C(2n,n-1)或C(2n,n)/(n+1)
*/