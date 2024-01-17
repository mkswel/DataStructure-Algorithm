#include<stdio.h>
#define MAX_TREE_SIZE 100
typedef int ElemType;


//双亲表示法（结点定义）
typedef struct{
    ElemType data;
    int parent;     //存双亲
}PTNode;
typedef struct{//（类型定义）
    PTNode nodes[MAX_TREE_SIZE];
    int n;          //结点数
}PTree;

//-------------------------孩子表示法（每个结点用顺序存储，每个结点的孩子用链式存储）
struct CTNode{//链式存储结点的所有孩子
    int child;  //孩子结点在数组中的位置
    struct CTNode *next;  //指向下一个孩子的指针
};
typedef struct{//定义顺序存储中的每个单元
    ElemType data;
    struct CTNode *firstChild;  //第一个孩子（一般为最左边的）
}CTBox;
typedef struct{//顺序存储每个结点
    CTBox nodes[MAX_TREE_SIZE];
    int n, r;   //结点数和根的位置
}CTree;

//-------------------------孩子兄弟表示法(树和二叉树转化)
typedef struct CSNode{
    ElemType data;
    struct CSNode *firstchild, *nextsibling;//第一个孩子和指向右兄弟的指针
}CSNode, *CSTree;
