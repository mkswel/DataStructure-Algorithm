/*图-bfs遍历
  问题：在有向图中，输出点1到n的最短距离
*/


#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=100010;
int n,m;
int h[N],e[N],ne[N],idx;   //邻接表存储
int d[N],q[N];    //d[]某点到1的距离；q[]队列

void add(int a,int b)    //建立结点a到b的有向边
{
    e[idx]=b;ne[idx]=h[a],h[a]=idx++;
}

int bfs()       //宽搜框架
{
    int hh=0,tt=0;   //数组实现队列
    q[0]=1;
    memset(d,-1,sizeof d);
    d[1]=0;
    while(hh<=tt)
    {
        int t=q[hh++];
        for(int i=h[t];i!=-1;i=ne[i])
        {
            int j=e[i];
            if(d[j]==-1)
            {
                d[j]=d[t]+1;
                q[++tt]=j;
            }
        }
    }
    return d[n];
}

int main()
{
    cin>>n;
    memset(h,-1,sizeof h);
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a,b);   
    }
   
    cout<<bfs()<<endl;
    return 0;
}