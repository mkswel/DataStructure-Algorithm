/*单源最短路（可以有负权边）
  SPFA   时间一般O(m)，最坏O(nm)
*/




/*求n的最短路

*/
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int N=100010;
int n,m;
int h[N],n[N],w[N],ne[N],idx, e[N];
int dist[N];
bool st[N];     //某点是否在队列当中，防止入队重复的点

void add(int a,int b,int c)
{
    e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}

int spfa()
{
    memset(dist,0x3f,sizeof dist);
    dist[1]=0;

    queue<int>q;
    q.push(1);               //初始化，先让起点入队
    st[1]=true;              
    while(q.size())          //队不空时循环，在循环到后期，由于所有点的最短路都会被更新到无法更新，所有点会逐渐出队，直至队空
    {
        int t=q.front();
        q.pop();
        st[t]=false;
        for(int i=h[t];i!=-1;i=ne[i])   //遍历该点所有后继
        {
            int j=e[i];
            if(dist[j]>dist[t]+w[i])  //如果该点的一个后继的最短路大于该点最短路加上此边的权值，更新最短路
            {
                dist[j]=dist[t]+w[i];      //松弛该边，更新后继最短路
                if(!st[j])                //如果该后继不在队列中，将其入队
                {
                    q.push(j);
                    st[j]=true;
                }
            }
        }
    }
    if(dist[n]==0x3f3f3f3f)return -1;
    return dist[n];
    
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int a,b,c;                  //每条边的始端，终端，权值
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }
    int t=spfa();
    if(t==-1)puts("impossible");
    else printf("%d\n",t);
    return 0;
}


//*****************************************************

/*判断图中是否有负环
  原理：定义数组cnt[]表示某点当前最短路经过的边数，
       如果存在cnt[k]大于等于总点数n，说明最短路中必定有环，
       而环会出现在最短路中必说明此环为负环
       （其实若最短路中出现负环，由于目标是“最短”则必导致该负环会被无限次经过，最终得到最短路为负无穷，即不存在）
*/

#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int N=100010;
int n,m;
int h[N],n[N],w[N],ne[N],idx;
int dist[N],cnt[N];
bool st[N];     //某点是否在队列当中，防止入队重复的点

void add(int a,int b,int c)
{
    e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}

bool spfa_()
{
    memset(dist,0x3f3f3f,sizeof dist);
    dist[1]=0;

    queue<int>q;
    for(int i=1;i<=n;i++)    //由于可能会有某些负环不出现在以1为起点的最短路中，因此需要将图中所有点入队
    {
        st[i]=true;
        q.push(i);
    }              
    while(q.size())          //队不空时循环，在循环到后期，由于所有点的最短路都会被更新到无法更新，所有点会逐渐出队，直至队空
    {
        int t=q.front();
        q.pop();
        st[t]=false;
        for(int i=h[t];i!=-1;i=ne[i])   //遍历该点所有后继
        {
            int j=e[i];
            if(dist[j]>dist[t]+w[i])  //如果该点的一个后继的最短路大于该点最短路加上此边的权值，更新最短路
            {
                dist[j]=dist[t]+w[i];      //松弛该边，更新后继最短路
                cnt[j]=cnt[t]+1;           //每次松弛边数加1

                if(cnt[j]>=n)return true;  //如果存在某最短路上的边数大于等于点数，说明有负环
                if(!st[j])                //如果该后继不在队列中，将其入队
                {
                    q.push(j);
                    st[j]=true;
                }
            }
        }
    }
    return false;
    
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int a,b,c;                  //每条边的始端，终端，权值
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }

    if(spfa())puts("Yes");
    else puts("No");
    return 0;
}