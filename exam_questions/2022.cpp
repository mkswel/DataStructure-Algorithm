#include<iostream>
using namespace std;
typedef struct{
    int g[7][7]={
    {0, 1, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 1, 1},
    {0, 1, 0, 0, 0, 0, 1},
    {0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 1, 1, 1, 0},
    };
    int value[7]={10, 12, 18, 19, 20, 17, 23};
    int vexnum, arcnum;
}Graph;
bool st[7]; //判断是否走过
void dfs(Graph &G, int v, int &maxnum){
    for(int i = 0; i < G.vexnum; i++){
        if(!st[i] && G.g[v][i]){
            st[i] = true;
            maxnum = max(maxnum, G.value[i]);
            dfs(G, i, maxnum);
            /*
            st[i]=false;
            某点被访问后无需再被访问，故不需要状态恢复
            状态恢复是在当前状态可能影响未来状态的情况下使用。对于该题而言（有向图亦是如此）当一条
            支线被访问完后哪怕不恢复状态，以后走其他支线也不会受到影响，除非其他支线将跟当前支线在
            中间交叉，但这是不可能的，因为如果产生交叉情况，根据深搜的原则，当前支线一定会走到底
            为止，未来的支线就算会跟当前支线相交，也只会交于它的终点，而这也不影响对每个点的访问。
            由此，删去状态恢复后每个结点只会被访问一次，时间复杂度降到O（|V|）
            */
        }
    }
}
int main(){
    Graph G;
    G.vexnum = 7, G.arcnum = 10;
    int ans = -1;
    dfs(G, 0, ans);
    cout<<ans<<endl;
    return 0;
}