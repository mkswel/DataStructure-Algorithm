#include<iostream>
#include<algorithm>

using namespace std;
const int N=1000010;

//欧拉函数 在N以内与N互质的数的个数o(N)=N*(1-1/p1)(1-1/p2)(1-1/p3)...(1-1/pm)   pi表示N的质因子
//原理：容斥原理
int get_eulers(int n)
{
    int res=n;
    for(int i=2;i<=n/i;i++)
    {
        if(n%i==0)    //找所有质因数  
        {
            res=res/i*(i-1);
            while(n%i==0)n/=i;  //除掉这个质因数及所有是该质数的倍数的因子
        }
    }
    if(n>1)res=res/n*(n-1);
    return res;
}

//线性筛优化欧拉函数
bool st[N];  //是否是质数
int primes[N]/*质数表*/,cnt/*质数个数*/;
int phi[N];  //某数的欧拉函数
long long get_eulers2(int n)
{
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(!st[i])primes[cnt++]=i,phi[i]=i-1;  //没被筛说明是质数，而质数的欧拉函数是它本身减一
        for(int j=0;primes[j]<=n/i;j++)
        {
            st[primes[j]*i]=true;
            if(i%primes[j]==0)  //如果该质数是i的最小质因数
            {
                phi[primes[j]*i]=primes[j]*phi[i];//primes[j]*i和i有相同的质因数集，结合欧拉函数公式可推得
                break;
            }
            phi[primes[j]*i]=(primes[j]-1)*phi[i];//如果该质数小于i的最小质因数，primes[j]*i的最小质因数是primes[j]，其余的质因数则是i的质因数集
        }
    }
    return phi[n];
}


/*
欧拉定理：
a和n互质，a^(euler(n))同余1(mod n)
当n为质数时，euler(n)=n-1，即a^(n-1)同余1(mod n)   （费马小定理）
*/




/**
 * 快速幂
 * 用O(log2 n)复杂度求(a^k)mod(p)
 * 思路：将k用二进制表示
*/

typedef long long LL;
int qmi(int a,int k,int p)
{
    int res = 1;
    while(k)
    {
        if(k & 1)res  = (LL)res *a%p;
        k = k>>1;
        a = (LL)a*a%p;//二进制每进一位都要乘二，在幂上则为平方
    }
    return res;
}



/**
 * 快速幂求逆元
 * 若b和m互质且b|a且有a/b同余a*x(mod m)则称x为b模m的逆元
 * 记x为b^-1 有结论b*b^-1同余1(mod m)
 * 即问题转化为找到x使得b*x同余1(mod m)
 * 
 * 当m是一个质数时利用费马小定理，b的逆元就是b^(m-2)，用快速幂求解
*/




/**
 * 裴蜀定理：对于任一对正整数a,b,存在整数x,y使得ax+by等于a,b最大公约数(a,b)
 * 扩展欧几里得算法寻找系数x,y
 * 
 * 由于(a,b)也是b,a%b的最大公约数，因此也存在b*x1+a%b*y1=(a,b)
*/
//返回系数x,y
int exgcd(int a,int b,int  &x,int &y)
{
    if(!b)
    {
        x = 1,y = 0;
        return a;
    }
    int d = exgcd(b,a%b,y,x);//d表示(a,b)
    /*
    说明为什么递归(b,a%b,y,x)
    由于exgcd(a,b,x,y)等于ax+by，等于(a,b)，利用欧几里得算法知其等于(b,a%b)，即等于bx1+a%by1
    则只需寻找x1,y1使得bx1+a%by1=(a,b)即可
    下面说明可以找到x1=y,y1=x满足上式
    记a=kb+r，其中r=a%b，若将x1替换为y，y1替换为x，则有bx1+a%by1=by+rx，
    因为ax+by-(by+rx)=kbx=kxb，故by+rx同余ax+by(mod d)，d表示(a,b)
    因此可以递归成(b,a%b,y,x)
    
    说明为什么有y-=a/b*x，而且出现在递归后面
    当利用递归求出(a,b)结果后，此时的x和y只能代表a%b和b的系数，而不能代表a和b的系数（而实际需要的是a和b的系数）。
    因此需要将等式变形以更新x和y
    d=by+(a%b)x=ax+b(y-a/b*x)
    */
    y -= a/b*x;  
    return d;
}

/*
扩展欧几里得算法求线性同余方程 ax同余b(mod m) 的解
线性同余方程转化为ax=km+b，k为商。令y=-k，再将其转化为ax+my=b
当b可以整除(a,m)时，该方程有解，解为x1*b/(a,m)，其中x1用扩展欧几里得求
*/

/*
中国剩余定理：对于两两互质的n个数m1,m2,m3...,mn和任意整数a1,a2,a3...,an
线性同余方程组 x同余a1(mod m1)
              x同余a2(mod m2)
              x同余a3(mod m3)
              .
              .
              .
              x同余an(mod mn)
记M=m1m2m3...mn
则方程有解x=a1*M1*M1^-1+a2*M2*M2^-1+...+an*Mn*Mn^-1
其中M1=M/m1,M2=M/m2,...,Mn=M/mn
M1^-1,M2^-1,...,Mn^-1分别表示M1,M2,...,Mn的逆元
*/