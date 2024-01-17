/*二分图
  问题：在二分图中分两个点集n1,n2（任意一条边的两端点不会在同一个点集内），求其最大匹配数
        将任意一个点仅可接触一条边时全图的边数为匹配数
  匈牙利算法
  原理：每次从n1开始看，如果能在n2中找到对应点从而连成边，则继续；如果找到的对应点已经和n1的某个x点匹配，则追溯到x，找x的其它可与其对应的点

*/

#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=510,M=100010;
int n1,n2,m;               //两个点集和边
int h[N],e[M],ne[M],idx;
int match[N];              //n2中某点在n1中的对应点
bool st[N];                //某点是否匹配成功
void add(int a,int b)      //邻接表存图
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

bool find(int x)              //是否找到x在n2中的对应点
{
    for(int i=h[x];i!=-1;i=ne[i])  //遍历x的若干后继结点（即n2中的对应点）
    {
        int j=e[i];
        if(!st[j])            //如果x的对应点尚且没有被匹配
        {
            st[j]=true;       //直接让这两个点匹配
            if(match[j]==0||find(match[j]))   //如果这个对应点没有在n1中的其它对应点或者这个对应点在n1中的对应点找到了其它可以匹配的点
            {
                match[j]=x;            //就直接让这个对应点在n1中的对应点为x
                return true;           //返回匹配成功
            }
        }
    }
    return false;  //否则匹配失败
}

int main()
{
    scanf("%d%d%d",&n1,&n2,&m);
    memset(h,-1,sizeof h);
    while(m--)
    {
        int a,b;
        scanf("%d%d",&a,&b);   //表示n1中点a与n2中点b之间有一条边
        add(a,b);
    }
        int res=0;              //已匹配数
        for(int i=1;i<=n1;i++)
        {
            memset(st,false,sizeof st);   //初始化所有点的匹配情况
            if(find(i))res++;             //如果找到了对应点，则匹配成功
        }
    printf("%d\n",res);
    return 0;
}