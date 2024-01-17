/*最短路-多源汇
  Floyd 时间O(n^3)
*/

#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
const int N=210,INF=1e9;
int n,m,Q;
int d[N][N];    //表示从某点到某点的当前最短路

void floyd()
{
    for(int k=1;k<=n;k++)
       for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);   //通过遍历任意三个点组成的三角形，对每个当前最短路更新
            }
}

int main()
{
    scanf("%d%d%d",&n,&m,&Q);   //n个点，m条边,执行Q次操作
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i==j)d[i][j]=0;
            else d[i][j]=INF;   //初始化无穷大
    while(m--)
    {
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);
        d[a][b]=min(d[a][b],w);    //处理重复边
    }
    floyd();
    while(Q--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        if(d[a][b]>INF/2)puts("impossible");   //最短路不存在
        else printf("%d\n",d[a][b]);
    }
    return 0;
}