/*拓扑序列
  宽搜实现拓扑序列
*/

#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=100010;
int n,m;
int h[N],e[N],ne[N],idx;   //邻接表存储
int d[N],q[N];    //d[]入度；q[]队列

void add(int a,int b)    //建立结点a到b的有向边
{
    e[idx]=b;ne[idx]=h[a],h[a]=idx++;
}


bool topsort()       
{
    int hh=0,tt=0;   //数组实现队列
    for(int i=1;i<=n;i++)
    {
        if(!d[i])         //如果入度为0，入队
        q[++tt]=i;
    }
    while(hh<=tt)
    {
        int t=q[hh++];
        for(int i=h[t];i!=-1;i=ne[i])
        {
            int j=e[i];       
            d[j]--;      //对于当前点的后继结点，入度减一
            if(d[j]==0)
            {
                q[++tt]=j;
            }
        }
    }
    return tt==n-1;
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
   
    if(topsort())
    {
        for(int i=0;i<n;i++)printf("%d",q[i]);   //输出拓扑序
    }
    else puts("-1");
    return 0;
}