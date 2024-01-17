/*最小生成树
  克鲁斯卡尔算法O(mlogm)
  原理：并查集
*/

#include<iostream>
#include<algorithm>

using namespace std;
const int N=100010;

int n,m;    //点，边
int p[N];  //某点的父节点

struct edge    //结构体存图
{
    int a,b,w;
    bool operator< (const edge &W)const  //重载小于号，为后续排序
    {
        return w<W.w;
    }
}edges[N];

int find(int x)   //并查集模板
{
    if(p[x]!=x)p[x]=find(p[x]);
    return p[x];
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int a,b,w;
        scanf("%d%d%d",&a,&b,&w);
        edges[i]={a,b,w};
    }
    sort(edges,edges+m);             //将边权从小到大排序
    for(int i=1;i<=n;i++)p[i]=i;     //并查集初始化
    int res=0,cnt=0;                 //res表示当前集合内的边权总和，cnt表示集合内的边数
    for(int i=0;i<m;i++)             //遍历所有边
    {
        int a=edges[i].a,b=edges[i].b,w=edges[i].w;
        a=find(a),b=find(b);
        if(a!=b)
        {
            p[a]=b;
            res+=w;
            cnt++;
        }
        if(cnt<n-1)puts("impossible"); //如果边数小于点数，说明集合不连通，没有最小生成树
        else printf("%d\n",res);
        return 0;

    }
}