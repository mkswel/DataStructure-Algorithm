/*二分图 （不含有奇数环）
  染色法（每点一个隔一个染色，最后没有冲突就是二分图，有就不是）
*/

#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N=100010,M=200010;

int n,m;
int h[N],e[M],ne[M],idx;
int color[N];

void add(int a,int b)    //邻接表存图
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;  
}

bool dfs(int u,int c)        //某个点u被染成某种颜色c
{
    color[u]=c;
    for(int i=h[u];i!=-1;i=ne[i])  //遍历全图
    {
        int j=ne[i];
        if(!color[j])             //如果没被染色
        {
            if(!dfs(j,3-c))return false;  //将其染成第二种颜色（总共1，2两种颜色）并判断是否有冲突
        }
        else if(color[j]==c)return false;  //如果有冲突返回false
    }
    return true;
}

int main()
{
    scanf("%d%d",&n,&m);
    memset(h,-1,sizeof h);
    while(m--)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b),add(b,a);      //无向图
    }
    bool flag=true;             //判断是否有冲突，有返回false
    for(int i=1;i<=n;i++)       //遍历每个点
    {
        if(!color[i])           //如果没有染色
        {
            if(!dfs(i,1))       //从其开始逐一染色并判断是否有冲突
            {
                flag=false;     
                break;
            }
        }
    }
    if(flag)puts("Yes");
    else puts("No");
    return 0;
}