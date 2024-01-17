#include<stdio.h>
typedef int ElemType; 
//邻接矩阵E[i][j]表示边(vi, vj)   空间消耗O(n^2)
//点i到点j的长度为n的路径条数等于E^n[i][j]
//可以快速获得某点的度、入度、出度：无向图中度为某行(列)和，有向图中入度为某列和，出度为某行和
#define MaxVertexNum 100
typedef char VertexType;
typedef int EdgeType;
typedef struct{
    VertexType Vex[MaxVertexNum];//顶点表,存放每个点的权值
    EdgeType Edge[MaxVertexNum][MaxVertexNum];//邻接矩阵
    int vexnum, arcnum;
}MGraph; 

//邻接表   空间消耗：无向图O(|V|+2|E|)  有向图O(|V|+|E|)
typedef struct ArcNode{  //定义链表结点（存边）
    int adjvex;         //这条边指向的顶点
    struct ArcNode *next;
    //InfoType info;//网的边权值
}ArcNode;
typedef struct VNode{    //定义数组元素（存点）
    VertexType data;
    ArcNode *first;
}VNode, AdjList[MaxVertexNum];
typedef struct{          //定义数组
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;

//十字链表法
typedef struct ArcNoe{
    struct ArcNode *tailvex, *headvex;  //尾域和头域， 表示弧尾是某点，弧头是某点，对应关系firstout->tailvex，firstin->headvex
    struct ArcNode *hlink, *tlink;   //hlink指向下一个有相同弧头的弧，tlink指向下一个有相同弧尾的弧                                                             
    ElemType info;  //存边权等  
}ArcNode;
typedef struct VNode{
    ElemType data;  //顶点值
    struct ArcNode *firstin/*头*/, *firstout/*尾*/;  //指向某弧弧头（尾），表示这个点是这条弧的弧头（尾）
}VNode, VList[MaxVertexNum] ;
typedef struct{ 
    VList vertices;
    int vexnum, arcnum;  
}ALGraph2;
