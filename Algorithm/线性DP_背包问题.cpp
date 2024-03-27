/*背包问题(在容积为m的背包中装n种物品，要求能装下的物品总价值最大)
  
  状态表示：f[i][j]表示从前i种物品中选且总体积不超过j的所有选法中的价值的最大值

  状态计算：如下
*/

//*******************************************************************************
/*0-1背包问题（每种物品只有一个）*/
/*朴素算法
  状态计算：f[i][j]可以表示成1)不装第i种物品2)装第i种物品，然后取这两者的最大值
          1)不装i：f[i-1][j];
          2)装i：f[i-1][j-v[i]]+w[i]（先装i，然后在剩余空间内可以装1~i-1）;
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N=1010;
int n,m;
int v[N],w[N];
int f[N][N];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i]>>w[i];
    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)
        {
            f[i][j]=f[i-1][j];
            if(j>=v[i])f[i][j]=max(f[i][j],f[i-1][j-v[i]]+w[i]);  //装i的情况可能不存在，因为i的体积可能大于背包容积
        }
        cout<<f[n][m]<<endl;
        return 0;
}

/*一维优化
  原理：滚动数组
        https://blog.csdn.net/weixin_40295575/article/details/80181756
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N=1010;
int n,m;
int v[N],w[N];
int f[N];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i]>>w[i];
    for(int i=1;i<=n;i++)
        for(int j=m;j>=v[i];j--)     
        /**
         * 根据式子得知j需要拿上一层的j-v[i]来更新。但由于j-v[i]始终小于j，因此倘若j从小到大遍历，f[j-v[i]]必比f[j]更早被更新，
         * 这就意味着当更新到第i层时，被用来更新j的已经不是第i-1层的j-v[i]了，而是第i层的
         * 而将j从大到小遍历，先更新到的是j，j-v[i]依然是i-1层的值
         * 
         * 为什么可以省略：f[i][j]=f[i-1][j]; 因为这句话的含义可以理解为将上一层的值逐个赋给下一层，
         * 这本身就和滚动数组的含义一致
         */  
        {
            f[j]=max(f[j],f[j-v[i]]+w[i]);  
        }
        cout<<f[m]<<endl;
        return 0;
}


//*******************************************************************************
/*完全背包问题（每种物品有无限个）*/
/*朴素算法
  状态计算：f[i][j]可以表示成1)装0个第i种物品2)装1个第i种物3)装2个第i种物品……n+1)装n个第i种物品，然后取这些情况的最大值
          装k个i：f[i-1][j-k*v[i]]+k*w[i]   k=0,1,2,3,...
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N=1010;
int n,m;
int v[N],w[N];
int f[N][N];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i]>>w[i];
    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)
            for(int k=0;k*v[i]<=j;k++)             //保证放k个第i种物品要能装下
                f[i][j]=max(f[i][j],f[i-1][j-k*v[i]]+k*w[i]);
    cout<<f[n][m]<<endl;
    return 0;


}

/*降维优化
  原理：由于f[i][j]=max(f[i-1][j-0*v[i]]+0*w[i],f[i-1][j-1*v[i]]+1*w[i],f[i-1][j-2*v[i]]+2*w[i],f[i-1][j-3*v[i]]+3*w[i],...,f[i-1][j-k*v[i]]+k*w[i])
      f[i][j-v[i]]=max(                        f[i-1][j-1*v[i]]+0*w[i],f[i-1][j-2*v[i]]+1*w[i],f[i-1][j-3*v[i]]+2*w[i],...,f[i-1][j-k*v[i]]+(k-1)*w[i])

        因此f[i][j]=max(f[i-1][j],f[i][j-v[i]]+w[i])
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N=1010;
int n,m;
int v[N],w[N];
int f[N][N];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i]>>w[i];
    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)
        {
            f[i][j]=f[i-1][j];
            if(j>=v[i])f[i][j]=max(f[i][j],f[i][j-v[i]]+w[i]);
        }
        cout<<f[n][m]<<endl;
        return 0;
}

//再套用一维优化

#include<iostream>
#include<algorithm>

using namespace std;

const int N=1010;
int n,m;
int v[N],w[N];
int f[N];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i]>>w[i];
    for(int i=1;i<=n;i++)
        for(int j=v[i];j<=m;j++)     
        //此处由于f[j],f[j-v[i]]处于同一层，故不用颠倒，其余和0-1问题一维优化完全相同
        {
            f[j]=max(f[j],f[j-v[i]]+w[i]);  
        }
        cout<<f[m]<<endl;
        return 0;
}


//*******************************************************************************
/*多重背包问题（每种物品有指定个）*/
/*朴素算法
  状态计算：f[i][j]可以表示成1)装0个第i种物品2)装1个第i种物3)装2个第i种物品……n+1)装n个第i种物品，然后取这些情况的最大值
          装k个i：f[i-1][j-k*v[i]]+k*w[i]   k=0,1,2,3...,s[i]，s[i]表示第i种物品有s[i]个
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N=1010;
int n,m;
int v[N],w[N],s[N];
int f[N][N];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i]>>w[i]>>s[i];
    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)
            for(int k=0;k<=s[i]&&k*v[i]<=j;k++)             //保证放k个第i种物品要能装下
                f[i][j]=max(f[i][j],f[i-1][j-k*v[i]]+k*w[i]);

        cout<<f[n][m]<<endl;
        return 0;
}

/*二进制优化
  首先不能用完全背包的降维优化
  原因：由于f[i][j]=max(f[i-1][j-0*v[i]]+0*w[i],f[i-1][j-1*v[i]]+1*w[i],f[i-1][j-2*v[i]]+2*w[i],f[i-1][j-3*v[i]]+3*w[i],...,f[i-1][j-s*v[i]]+s*w[i])
      f[i][j-v[i]]=max(                        f[i-1][j-1*v[i]]+0*w[i],f[i-1][j-2*v[i]]+1*w[i],f[i-1][j-3*v[i]]+2*w[i],...,f[i-1][j-s*v[i]]+(s-1)*w[i],f[i-1][j-(s+1)*v[i]]+s*w[i])
     这里多出来一项f[i-1][j-(s+1)*v[i]]+s*w[i]，因此无法用f[i][j-v[i]]来表示f[i][j]
  而背包问题里的降维优化中f[i][j-v[i]]=max(                        f[i-1][j-1*v[i]]+0*w[i],f[i-1][j-2*v[i]]+1*w[i],f[i-1][j-3*v[i]]+2*w[i],...,f[i-1][j-k*v[i]]+(k-1)*w[i])
  没有多出来的这一项，因为前者s的取值限制还包括题目所给要求，可能会出现s*v[i]和j之间仍有距离的情况；而后者k的限制只要保证j>=k*v[i]就行，因此如果多出f[i-1][j-(k+1)*v[i]]+k*w[i]，会因为j<(k+1)*v[i]而出错


  二进制优化原理：1,2,4,8,16,...2^k可以表示1~2^(k+1)-1内任一个数，因此对于任一给定自然数s[i]，可以用该法分解
  举例：原有物品1：3个，物品2：2个，物品3：5个，
  分解后得：1个物品1组成的新物品1，2个物品1组成的新物品2，1个物品2组成的新物品3，1个物品2组成的新物品4，1个物品3组成的新物品5，2个物品3组成的新物品6，2个物品3组成的新物品7
  分解后的所有种类的新物品个数都为1
*/

#include<iostream>
#include<algorithm>

using namespace std;

const int N=25000;
int n,m;
int v[N],w[N];
int f[N];


int main()
{
    cin>>n>>m;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        int a,b,s;  //第i个物品的价值,体积,数量
        int k=1;    //从1开始分解
        while(k<=s) //将s个i分解成若干个新物品，这些新物品可以表示1~s个i
        {
            cnt++;
            v[cnt]=a*k;
            w[cnt]=b*k;
            s-=k;
            k*=2;
        }
        if(s>0)
        {
            cnt++;
            v[cnt]=a*s;
            w[cnt]=b*s;
        }
    }
    n=cnt;        //将新物品种数也加到总物品种数中
    for(int i=1;i<=n;i++)   //对于更新后的物品种数，每种都只有1个，就能转化为0-1问题
        for(int j=m;j>=v[i];j--)     
        {
            f[j]=max(f[j],f[j-v[i]]+w[i]);  
        }
        cout<<f[m]<<endl;
        return 0;

}
//*******************************************************************************
/*分组背包问题（每组物品有若干个，同组物品最多只能选一个）*/
/*朴素算法
  状态计算：0-1问题
           装第i组中的k：f[j-v[i][k]]+w[i][k]   
*/


#include<iostream>
#include<algorithm>

using namespace std;

const int N=110;
int n,m;
int v[N][N],w[N][N],s[N];
int f[N];

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>s[i];                //第i组中物品的个数
        for(int j=0;j<s[i];j++)
        {
            cin>>v[i][j]>>w[i][j];
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=m;j>=0;j--)
            for(int k=0;k<s[i];k++)             
                if(v[i][k]<=j)f[j]=max(f[j],f[j-v[i][k]]+w[i][k]);

        cout<<f[m]<<endl;
        return 0;
}