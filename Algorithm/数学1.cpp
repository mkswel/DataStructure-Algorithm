#include<iostream>
#include<algorithm>
#include<vector> 
#include<unordered_map>

using namespace std;
const int N=1000010;



//试除法判断质数 O(sqrt(n))
bool is_prime(int n)  
{
    if(n<2)return false;
    for(int i=2;i<=n/i;i++)  //i*i<n有溢出风险；sqrt(n)太慢
    {
        if(n%i==0)
        return false;
    }
    return true;
}

//试除法求质因数及其出现次数 O(sqrt(n))
void divide(int n)   
{
    for(int i=2;i<=n/i;i++)
    {
        if(n%i==0)   //i必为质数
        {
            int s=0;   //某质因数出现次数
            while(n%i==0)
            {
                n/=i;
                s++;
            }
            printf("%d %d\n",i,s);
        }
    }
    if(n>1)printf("%d %d\n",n,1);
}
/**
 * 筛法核心：在2~N中从头开始依次筛掉当前所指的数的所有倍数，余下的数就是质数
 * 若N没被筛掉，说明它不是2~N-1中任一数的倍数，否则它会被筛掉。因此它是质数
*/

//埃氏筛法求1~n中质数个数 O(nloglogn)
bool st[N];//判断数i是否被筛掉，默认初值0
int cnt;//统计质数个数
void get_prime(int n)   
{
    cnt=0;
    for(int i=2;i<=n;i++)
    {
        if(!st[i])  //i没被筛掉，说明它是质数
        {
            cnt++;
            for(int j=i+i;j<=n;j+=i)st[j]=true;  //把i的倍数全筛掉
        }
    }
    cout<<cnt;
}

//线性筛法求1~n中质数个数 O(n)
//保证每个合数都是被它的最小质因数筛掉，因此每个合数都只会被筛一次
bool st[N];
int primes[N]/*质数表*/,cnt/*质数个数*/;
void get_prime2(int n)   
{
    for(int i=2;i<=n;i++)  //不用n/i，因为不是用i来筛
    {
        if(!st[i])primes[cnt++]=i;  //i没被筛掉,将该质数加入质数表

        /**
         * 以下这个循环的作用是通过从小到大枚举质数来筛掉以当前所枚举到的质数为最小质因子的合数
         * 
         * 说明为什么它可以保证某个合数会被其最小质因子筛掉：由于该循环是从小到大枚举的所有质数，那么当枚举到的质数还不能被i整除时，说明它甚至比i的最小质因数还小，
         * 这时就可以用它来筛掉primes[j]*i这个合数，因为它小于i的最小质因子，因此它一定是primes[j]*i的最小质因子，满足线性筛要求；
         * 当枚举到的质数能被i整除时，由于从小到大枚举，这时它一定是i的最小质因子，那么它也一定是primes[j]*i的最小质因子，满足线性筛要求；
         * 当枚举到的质数能被i整除但依然不跳出循环，那当它枚举到下一个质数时，就不能用它来筛掉primes[j]*i,因为此时primes[j]*i的最小质因子是i的最小质因子
         * 
         * 说明为什么它可以保证筛掉每个合数：因为每个合数都必定存在一个最小质因子，那么当循环枚举到某个合数x的最小质因子p，且i刚好枚举到x/p时，x就会被筛掉。
        */
        for(int j=0;primes[j]<=n/i;j++)   //希望筛掉的合数不能超过n，也可以理解为从小到大枚举所有质数直到sqrt(n)
        {
            st[primes[j]*i]=true;       //primes[j]*i的最小质因数是primes[j]，将primes[j]*i筛掉
            if(i%primes[j]==0)break;    //如果i%primes[j]!=0，说明primes[j]比i的最小质因子还小，就继续筛，当primes[j]等于i的最小质因子时，就跳出
        }
    }
    cout<<cnt;
}

//试除法求约数 O(sqrt(n))
vector<int> get_divisors(int n)
{
    vector<int> res;
    for(int i=1;i<=n/i;i++)  //遍历1~sqrt(n)中所有数
        if(n%i==0)           //找到约数
        {
            res.push_back(i);
            if(i!=n/i)res.push_back(n/i);  //找到另一个约数（不包括sqrt(n)）
        }
    sort(res.begin(),res.end()); //排序
    return res;
    
}

//求约数个数
/**
 * N=p1^a1*p2^a2*p3^a3...pn^an，pn表示质因数，
 * 则N的因数个数为这n个质数的所有取法组合的种数，为(a1+1)(a2+1)...(an+1)，即每个指数有0~ai这(ai+1)种取法
 * 
*/
void get(int x)
{
    unordered_map<int,int> primes;   //哈希表存质因数以及它的指数
    for(int i=2;i<=x/i;i++)
    {
        while(x%i==0)   //除掉所有是i的倍数的因数
        {
            x/=i;
            primes[i]++;  //每次让i这个质因数的指数++
        }
    }
    if(x>1)primes[x]++; //可能会漏一个，
    long long res=1;
    for(auto prime:primes)res=res*(prime.second+1);        //最终求(a1+1)(a2+1)(a3+1)...(an+1)
    cout<<res<<endl;
}

//求约数和
//原理如上，约数和为(p1^0+p1^1+p1^2+...+p1^a1)...(pn^0+pn^1+pn^2+...+pn^an)
void get(int x)
{
    unordered_map<int,int> primes;   //哈希表存质因数到它的指数
    for(int i=2;i<=x/i;i++)
    {
        while(x%i==0)   //找到质因数
        {
            x/=i;
            primes[i]++;
        }
        if(x>1)primes[x]++;
    }
    
    long long res=1;
    for(auto prime:primes)
    {
        int p=prime.first,a=prime.second;
        long long t=1;
        while(a--)t=(t*p+1);
        res=res*t;      
    }  
    cout<<res<<endl;
}

//欧几里得法求最大公约数 O(logn)
//a,b的最大公约数等于b,a%b的最大公约数
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}


