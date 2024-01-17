/*单源最短路（可以有负权边）
  问题：求1到n的有限边的最短路，图中可能有负权回路
  Bellman-Ford    时间O(nm)
*/

#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=510,M=10010;
int n,m,k;       //n个点，m条边，n到1的不超过k条边的最短路
int dist[N],backup[N];    //dist[]当前最短路，backup[]每次松弛前的一次最短路
struct Edge
{
    int a,b,w;
}edges[M];            //结构体存边

int bellman_ford()
{  
    memset(dist,0x3f,sizeof dist);
    dist[1]=0;

    for(int i=0;i<k;i++)         //循环k次，含义：循环到第x次时表示某点的最短路不超过x条边
    {
        memcpy(backup,dist,sizeof dist);     //在每次松弛之前备份一次最短路
        for(int j=0;j<m;j++)        //松弛所有边
        {
            int a=edges[j].a,b=edges[j].b,w=edges[j].w;
            dist[b]=min(dist[b],backup[a]+w);              
            /*对每条边都进行一次更新，
              用备份比较以防止：1）边数角度讲：由于每次松弛可能会增加一条边，故可能导致最短路有k+1条边，用松弛前的边顶替可以避免
                             2）权值角度讲：每次松弛后的权值可能会覆盖掉原来的权值，即可能导致k条边的最短路结果被顶替为k+1条边的最短路结果
            */
        }
    }
    if(dist[n]>0x3f3f3f3f/2)return -1;         //如果最短路不存在，返回-1
    return dist[n];
}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<m;i++)
    {
        int a,b,w;                  //每条边的始端，终端，权值
        scanf("%d%d%d",&a,&b,&w);
        edges[i]={a,b,w};
    }
    int t=bellman_ford();
    if(t==-1)puts("impossible");
    else printf("%d\n",t);
    return 0;
}