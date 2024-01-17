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
    AdjList *vertices;
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
    AGraph ans;
    ans.vexnum = G.vexnum;
    ans.vertices = new AdjList[MaxSize];
    for(int i = 0; i < ans.vexnum; i++){
        VNode *tmp = ans.vertices[i];
        tmp->node = i;
        tmp->first = NULL;
        for(int j = 0; j < G.vexnum; j++){
            if(G.edge[i][j]){
                ANode *t = new ANode;
                t->nextnode = j;
                t->next = tmp->first;
                tmp->first = t;
            }
        }
    }
    return ans;
}