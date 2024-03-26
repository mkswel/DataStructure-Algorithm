#include<iostream>
#include<cstring>
#define MaxSize 20
using namespace std;
const int N = 7;
typedef struct{
    int vexnum , arcnum;
    int edge[MaxSize][MaxSize];//0表示没有边
}VGraph;

/**
 * 返回无向图总边长
*/
int arcsum(VGraph &G){
    int ans = 0;
    for(int i = 0; i < G.vexnum; i++)
        for(int j = i; j < G.vexnum; j++)
            if(G.edge[i][j])ans+=G.edge[i][j], G.arcnum++;
    return ans;       
}
bool st[MaxSize];
/**
 * 判断是否有环并找到要删的边
 * v：当前递归到的结点
 * r：上一个递归的结点
 * a, b：当前环内最长的边
 * t：记录遍历到哪个结点出现了重复
 * p：判断当前递归到的结点是否在环内
 * 复杂度最坏O(|V|^4)或O((|E|+|V|)(|E|-|V|+1))适合稀疏图
 * 
 * 力扣1584
*/
void dfs(VGraph &G, int v, int r, int &a, int &b, int &t, bool &p, int &MST){
    if(G.arcnum == G.vexnum - 1)return;
    for(int i = 0; i < G.vexnum; i++){
        if(G.edge[v][i]){
            if(!st[i]){
                st[i] = true;
                dfs(G, i, v, a, b, t, p, MST);
                st[i] = false;//状态恢复：不能让之前的线路影响现在的线路
                if(p){//当前点在环内
                    if(G.edge[v][i]>G.edge[a][b])a=v, b=i;
                    if(v == t){//已经退到刚进入环的位置
                        MST -= G.edge[a][b];
                        G.edge[a][b]=0, G.edge[b][a]=0, G.arcnum--;
                        p = false;
                        i--;//下一步从原来点开始继续递归
                    }
                    else return;//还没有退到环外就继续退
                }
            }
            else if(i != r){//出现重复点，找到环
                a=v, b=i, t=i, p=true;
                return ;
            }
        }
    }
}

/**
 * 法二（待验证）：dfs过程不需要同法一一般重走
 * 从v1开始递归，递归过程中维护每条走过的边，假设走到vn出现环（v1=vn），
 * 然后从维护的边集中找到路径v1->v2->v3...->vn中最长的边，假设为<vi,vj>（此处可用线段树优化）
 * 将<vi,vj>删去，然后将st[v2],st[v3]...st[vi]设为false(v1不用改因为vn就是v1，后面还要继续走)
 * 从vn开始继续递归下去，当边数=点数-1，终止
*/


//测试方法一
int main(){
    VGraph G;
    G.arcnum = 0, G.vexnum=N;
    int k[N][N]={
    {0, 8, 5, 0, 0, 0, 0},
    {8, 0, 3, 7, 0, 0, 0},
    {5, 3, 0, 0,15, 0, 7},
    {0, 7, 0, 0, 0, 6, 2},
    {0, 0,15, 0, 0, 0,12},
    {0, 0, 0, 6, 0, 0, 9},
    {0, 0, 7, 2,12, 9, 0}
    };
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            G.edge[i][j]=k[i][j];
    int a = 0, b = 0, t = 0, MST = arcsum(G);
    bool p = false;
    memset(st, 0, sizeof(st));
    st[0]=true;
    dfs(G, 0, 0, a, b, t, p, MST);
    cout<<MST<<endl;
}

