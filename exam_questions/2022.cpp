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