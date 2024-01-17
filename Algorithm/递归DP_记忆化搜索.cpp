/*
滑雪：一个矩阵中每个格子上的数表示这个格子的高度，
运动员从某一个格子开始从高到低往下滑，一直滑到最低的格子。求能滑的最长距离
*/

/*
思路：对于某个格子[i,j]，用f[i][j]表示在该点起能滑的最远距离
用f[i+1][j],f[i-1][j],f[i][j+1],f[i][j-1]表示滑的四个方向
*/


#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;
const int N=310;
int n,m;
int h[N][N];     //格子高度
int f[N][N];     //格子状态
int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
int dp(int x,int y)
{
    int &v=f[x][y];        //引用状态
    if(v!=-1)return v;     //如果状态已经被更新，就返回
    v=1;                   //默认最短的最长距离是1（即起点本身，也就是不滑）
    for(int i=0;i<4;i++)   //遍历四个方向
    {
        int a=x+dx[i],b=y+dy[i];
        if(a>=1&&a<=n&&b>=1&&b<=m&&h[a][b]<h[x][y])    //如果下一个格子合法（未出界且低于当前格子）
            v=max(v,dp(a,b)+1);             //当前格子的最远距离即四个方向下的下一个格子最远距离加1的最大值
    }
    return v;
} 



int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&h[i][j]);
    memset(f,-1,sizeof f);       //初始化所有状态为-1
    int res=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            res=max(res,dp(i,j));   //找到能滑最远距离的格子
    printf("%d\n",res);              //最远距离
    return 0;
}