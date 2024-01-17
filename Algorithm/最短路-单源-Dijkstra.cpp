/*单源最短路（所有边权都为正）
  
*/



/*
稠密图-朴素Dijkstra  时间O(n^2 + m)

  原理：每次从未确定最短路径的点中找到距离起点最近的点，将其作为桥梁刷新其余未确定最短路径的点，然后把这个点加入到已确定最短路径的点中
*/

#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=510;
int n,m;
int g[N][N];   //g[][]表示边(,)——稠密图存储方式
int dist[N];   //某点当前到起点的距离
bool st[N];    //是否找到最短路

int dijkstra()
{
  memset(dist,0x3f,sizeof dist);    //初始化所有点当前最短路为无穷大
  dist[1]=0;                        //初始化起点当前最短路为0
  for(int i=0;i<n;i++)              //处理n个点，每次确定一个点的最短路，同时拿这个点来更新其他点的最短路
  {
    int t=-1;                       
    for(int j=1;j<=n;j++)           //这个循环用于找到未确定最短路的点中距离起点最近的点
    {
      if(!st[j]&&(t==-1||dist[t]>dist[j]))   //如果当前点没确定最短路且该点到起点的当前距离是最小的
      t=j;
    }
    st[t]=true;                   //将该点加入到已确定最短路的点集中
    for(int j=1;j<=n;j++)         //这个循环用于更新每个未确定最短路的点到起点的距离
    dist[j]=min(dist[j],dist[t]+g[t][j]);   //该点的最短路=min{（该点当前距离——因为有一部分点已经确定了最短路了需要排除）,(已确定最短路的点到起点的距离+已确定最短路的点到该点的距离)}————最短路更新（纵向比较）
  }
  if(dist[n]==0x3f3f3f3f)return -1;
  return dist[n];
}

int main()
{
    scanf("%d%d",&n,&m);   //n点数 m边数
    memset(g,0x3f,sizeof g);
    while(m--)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);  //从点a到点b，权值为c
        g[a][b]=min(g[a][b],c);   //对于有重边情况，只取短的一条边
    }
    int t=dijkstra(); 
    printf("%d\n",t);
    return 0;
}

//******************************************************************

/*
稀疏图—堆优化Dijkstra  时间O(mlogn)

  原理：将朴素做法中找最短距离的点的过程用堆实现
*/


#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>

using namespace std;

typedef pair<int,int> PII;

const int N=100010;
int n,m;
int h[N],w[N],e[N],ne[N],idx;   //邻接表存储——稀疏图存储方式
int dist[N];   //某点到起点的当前距离
bool st[N];    //是否找到最短路

void add(int a,int b,int c)
{
  e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}


int dijkstra()          
{
  memset(dist,0x3f,sizeof dist);    //初始化所有点当前最短路为无穷大
  dist[1]=0;                        //初始化起点当前最短路为0
  priority_queue<PII,vector<PII>,greater<PII>>heap;      //小根堆初始化
  heap.push({0,1});         //将某点当前最短路和该点入队
  while(heap.size())        //队列里存放的与即将存放的都是没有确定最短路的点，每次提出堆顶元素得到未确定最短路的点集中距离起点最近的点
  {
    auto t=heap.top();        
    heap.pop();               //直接将该点出队，不再参与之后的循环，即已找到最短路
    int ver=t.second,distance=t.first;  //将该点用来更新其他直接与它相邻的点
    if (st[ver]) continue;
    st[ver] = true;
    for(int i=h[ver];i!=-1;i=ne[i])  //更新所有能更新的点（直接与其相邻）
    {
      int j=e[i];
      if(dist[j]>distance + w[i])            //边的起始端当前最短路小于终端当前最短路
      {
        dist[j]=distance+w[i];       //将终端当前最短路更新
        heap.push({dist[j],j});      //将该点及其当前最短路入队
      }
    }
  }

  if(dist[n]==0x3f3f3f3f)return -1;
  return dist[n];
}

int main()
{
    scanf("%d%d",&n,&m);   //n点数 m边数
    memset(h,-1,sizeof h);
    while(m--)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);  //从点a到点b，权值为c
        add(a,b,c);   
    }
    int t=dijkstra(); 
    printf("%d\n",t);
    return 0;
}

