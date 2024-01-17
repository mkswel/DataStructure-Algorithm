/*最小生成树MST-普利姆
*/

/*朴素普利姆O(n^2 + m)*/

#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=510,INF=0x3f3f3f3f;
int n,m;
int g[N][N];    //定义边权
int dist[N];    //某个点到MST里所有点的距离的最小值
bool st[N];     //是否已经加入MST

int prim()
{
    memset(dist,0x3f,sizeof dist);
    int res=0;                     //最小生成树的边权总和
    for(int i=0;i<n;i++) //每次循环都会让一个点加入MST，经过n次循环遍历完所有点
    {
        int t=-1;
        for(int j=1;j<=n;j++)    //遍历MST以外的每个点，用于找距离MST最近的点
            if(!st[j]&&(t==-1||dist[t]>dist[j]))t=j;
        if(i&&dist[t]==INF)return INF; //从寻找第二点起如果存在得到的最短距为无穷大，说明图不连通
        if(i)res+=dist[t];             //从寻找第二个点起将边权总和累加
        st[t]=true;                    //将这个点加入MST
        for(int j=1;j<=n;j++)dist[j]=min(dist[j],g[t][j]);   //更新其余点的距离：这个点到最新加入MST的点的距离 与 它到MST里其他点的距离的最小值 的最小值
    }
    return res;
}

int main()
{
    scanf("%d%d",&n,&m);
    memset(g,0x3f,sizeof g);
    while(m--)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        g[a][b]=g[b][a]=min(g[a][b],c);   //无向图且避免有重边
    }
    int t=prim();
    if(t==INF)puts("impossible");
    else printf("%d\n",t);
    return 0;
}