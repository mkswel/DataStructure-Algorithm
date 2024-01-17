/*图-dfs遍历
  问题：返回删掉一棵树的重心后其余无向连通子图的最大结点个数
      重心：将其删掉后的其余最大连通块的最大结点个数最小

  原理：通过深搜找到每个结点删掉后其子图的结点个数
*/



#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int N=100010;   
const int M=N*2;      
int n,m;     //n为树的结点数；m为边数（无向边相当于两个方向相反的有向边）
int h[N],e[M],ne[M],idx;   //邻接表存储无向图
bool st[N];     //存储是否遍历过某点

int ans=N;

void add(int a,int b)    //建立结点a到b的有向边
{
    e[idx]=b;ne[idx]=h[a],h[a]=idx++;
}

int dfs(int u)   //返回数u的子图的结点个数和
{
    st[u]=true;    //数u已被遍历
    int sum=1,res=0;   //sum：点数和包括u本身   res：删除u后的最大连通块结点个数
    for(int i=h[u];i!=-1;i=ne[i])   //遍历u的子图中的每个结点
    {
        int j=e[i];
        if(!st[j])       //对于未被遍历过的点，找到这个点的最大子图结点个数
        {
            int s=dfs(j);
            res=max(res,s);  //找到这个点的最大子图结点个数
            sum+=s;       //u的子图结点个数包括u的子图结点的子图结点个数
        }
    }

    res=max(res,n-sum);  //删除u后的最大连通块结点个数是比较u的子图结点个数与u的父节点个数
    ans=min(ans,res);    //最终结果为所有点的res中的最小值
    return sum;
}

int main()
{
    cin>>n;
    memset(h,-1,sizeof h);
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        cin>>a>>b;
        add(a,b),add(b,a);   //将树存储至邻接表中
    }
    dfs(1);             //由于无向图中每条边都是双向的，因此可以遍历到所有点
    cout<<ans<<endl;
    return 0;
}