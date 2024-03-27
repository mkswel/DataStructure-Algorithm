/*DFS
  问题1：输出从1到n组成的n位数字的全排列
  问题2：n-皇后（剪枝）
*/

//问题1

#include<iostream>
using namespace std;
const int N=10;
int n;
int path[N];//存储n位数字的各个位上的数
bool st[N];  //存储数字i是否被用过

void dfs(int u)  //表示n位上已经有了u个数
{
    if(u==n)  //此时所有位上都已经填好数，只需输出
    {
        for(int i=0;i<n;i++)printf("%d",path[i]);
        puts("");
        return;
    }
    for(int i=1;i<=n;i++)  //下标和数据保持一致，遍历每一位上的情况
    {
        if(!st[i])   //如果i没有被占用，可以继续
        {
            path[u]=i;   //将i填入当前空位上
            st[i]=true;  //表示数字i已占用
            dfs(u+1);    //递归到下一层
            st[i]=false;  
            /*递归结束后返回上一层，为了保持原状，释放数字i，
            由于外面一层for循环会接着从i+1开始循环因此不必担心出现重复的问题*/
        }
    }
}

int main()
{
    cin>>n;
    dfs(0);   //从已填0个数字开始深搜
    return 0;
}


//***************************************



//问题2


/*法一：回溯深搜   时间n*n!
*/
#include<iostream>
using namespace std;
const int N=20;
int n;
char g[N][N];//存储n*n棋盘上的情况
bool col[N],dj[N],udj[N];  //存储列，主对角线，副对角线上是否出现

void dfs(int u) //表示搜索到第u行
{
    if(u==n)  //此时棋盘已经填满，只需输出
    {
        for(int i=0;i<n;i++)puts(g[i]);
        puts("");
        return;
    }
    for(int i=0;i<n;i++)  //遍历每列的情况
    {
        if(!col[i]&&!dj[u+i]&&!udj[n-u+i])   //如果列和两条对角线都没有被占用，可以继续（剪枝）
        {
            g[u][i]='Q';   //将皇后填入当前空位上
            col[i]=dj[u+i]=udj[n-u+i]=true;  //表示列，主对角线，副对角线已占用
            dfs(u+1);    //递归到下一层
            col[i]=dj[u+i]=udj[n-u+i]=false;  //递归结束返回上层，释放最后一层的列，主副对角线
            g[u][i]='.';
           
        }
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        g[i][j]='.';
    }
    dfs(0);   //从第0行开始深搜
    return 0;
}



/*法二：原始搜索（一格一格判断放不放皇后） 时间2^(n^2)
*/
#include<iostream>
using namespace std;
const int N=20;
int n;
char g[N][N];//存储n*n棋盘上的情况
bool row[N],col[N],dj[N],udj[N];  //存储行，列，主对角线，副对角线上是否出现

void dfs(int x,int y,int s) //表示搜索到坐标(x,y)，累计已放s个皇后
{
    if(y==n)y=0,x++;  //超出范围，回车
    if(x==n&&s==n)    //皇后已到n个，输出
    {
        for(int i=0;i<n;i++)puts(g[i]);
        puts("");
        return;
    }

    //不放皇后
    dfs(x,y+1,s);

    //放皇后
    if(!row[x]&&!col[y]&&!dj[x+y]&&!udj[n-y+x])   //如果列和两条对角线都没有被占用，可以继续（剪枝）
        {
            g[x][y]='Q';   //将皇后填入当前空位上
            row[x]=col[y]=dj[x+y]=udj[n-y+x]=true;  //表示行，列，主对角线，副对角线已占用
            dfs(x,y+1,s+1);    //递归到下一层
            row[x]=col[y]=dj[x+y]=udj[n-y+x]=false;  //递归结束返回上层，释放最后一层的行，列，主副对角线
            g[x][y]='.';
        }

}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        g[i][j]='.';
    }
    dfs(0,0,0);   
    return 0;
}


