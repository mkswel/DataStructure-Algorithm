#include<iostream>
#define MaxSize 100
using namespace std;

typedef struct ArcNode{
    int nextnode;
    struct ArcNode *next;
}ANode;
typedef struct VNode{
    int node;
    ANode *first;
    //VNode() : node(0), first(nullptr) {} // 构造函数
}VNode, AdjList[MaxSize];
typedef struct Graph{
    AdjList vertices;
    int vexnum, arcnum;
}AGraph;

typedef struct {
    int edge[5][5]= {//该样例见王道P223
        {0, 1, 0, 1, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
    };
    int vexnum = 5;
}VGraph;

/**
 * 将邻接矩阵转成邻接表
*/
AGraph transform(VGraph G){
    AGraph Graph;
    Graph.vexnum = G.vexnum;
    for(int i = 0; i < Graph.vexnum; i++){
        VNode &tmp = Graph.vertices[i];
        tmp.node = i;
        tmp.first = NULL;
        for(int j = 0; j < G.vexnum; j++){
            if(G.edge[i][j]){
                ANode *t = new ANode;
                t->nextnode = j;
                t->next = tmp.first;
                tmp.first = t;
            }
        }
    }
    return Graph;
}


/**
 * 返回从点v到终点b的所有路径，路径中的结点数为k
*/
bool visited[MaxSize];
void dfs(AGraph &G, int v, int b, int path[], int &k){
    if(v == b){
        for(int i = 0; i < k; i++)cout<<path[i]/* +1 因为样例的点是从1开始的*/<<" ";
        cout<<endl;
        return;
    }
    for(ANode *i = G.vertices[v].first; i != NULL; i = i->next){
        int t = i->nextnode;
        if(!visited[t]){
            visited[t] = true, path[k++] = t;
            dfs(G, t, b, path, k);
            visited[t] = false, k--;
        }
    }
}
int main(){
    int path[MaxSize], k = 1;
    path[0] = 0;
    VGraph VG;
    AGraph G = transform(VG);
    dfs(G, 0, 4, path, k);//从0到4的所有路径
    return 0;
}