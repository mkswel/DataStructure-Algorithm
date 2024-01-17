/*BFS
  迷宫0表示能走，1表示墙壁
*/



#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

typedef pair<int,int>PII;
const int N=110;
int n,m;   //定义迷宫的宽和长
int g[N][N];  //迷宫
int d[N][N];  //定义某个点第几次被搜到（即到起点距离为几）
PII q[N*N];   //定义队列

int bfs()
{
    int hh=0,tt=0;   //定义队头队尾
    q[0]={0,0};      //队头从迷宫左上角开始
    memset(d,-1,sizeof d);   //初始化所有点，表示都没被搜索到
    d[0][0]=0;               //从左上角开始搜索
    int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};  //上下左右
    while(hh<=tt)      //当队列不空
    {
        auto t=q[hh++];    //取出队头
        for(int i=0;i<4;i++)     
        {
            int x=t.first+dx[i],y=t.second+dy[i];  //遍历上下左右四个操作
            if(x>=0&&x<n&&y>=0&&y<m&&g[x][y]==0&&d[x][y]==-1)  //如果不出界且可以走且没走到过
            {
                d[x][y]=d[t.first][t.second]+1; //就让这个点到起点的距离比队头到起点的距离多1
                q[++tt]={x,y};  //将这个点入队
            }
        }
    }
    return d[n-1][m-1];
}


int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        scanf("%d",&g[i][j]);
    }
    cout<<bfs()<<endl;
    return 0;
}





/*用stl队列实现
*/
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

typedef pair<int,int>PII;
const int N=110;
int n,m;   //定义迷宫的宽和长
int g[N][N];  //迷宫
int d[N][N];  //定义某个点第几次被搜到（即到起点距离为几）
queue<PII> qu;

int bfs()
{
    qu.push({0,0});      //队头从迷宫左上角开始
    memset(d,-1,sizeof d);   //初始化所有点，表示都没被搜索到
    d[0][0]=0;               //从左上角开始搜索
    int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};  //上下左右
    while(!qu.empty())      //当队列不空
    {
        auto t=qu.front();
        qu.pop();
        for(int i=0;i<4;i++)     
        {
            int x=t.first+dx[i],y=t.second+dy[i];  //遍历上下左右四个操作
            if(x>=0&&x<n&&y>=0&&y<m&&g[x][y]==0&&d[x][y]==-1)  //如果不出界且可以走且没走到过
            {
                d[x][y]=d[t.first][t.second]+1; //就让这个点到起点的距离比队头到起点的距离多1
                qu.push({x,y});  //将这个点入队
            }
        }
    }
    return d[n-1][m-1];
}


int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        scanf("%d",&g[i][j]);
    }
    cout<<bfs()<<endl;
    return 0;
}


