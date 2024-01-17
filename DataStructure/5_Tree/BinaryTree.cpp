#include<stdio.h>
typedef int ElemType;

//----------------------------------------------------顺序存储
#define MaxSize 100;
struct TreeNode{
    ElemType value; //结点中的数组元素
    bool isEmpty;   //结点是否为空
};
//    TreeNode t[MaxSize];

//----------------------------------------------------链式存储
typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
    struct BiTNode *parent;
}BiTNode, *BiTree;
//n个结点的二叉链表共有n+1个空链域(仅有左孩子右孩子两个指针的情况)

//初始化根结点
#include<stdlib.h>
void InitRoot(){
    BiTree root = NULL;
    root = (BiTree) malloc (sizeof(BiTNode));
    root->data = 1;
    root->lchild = NULL;
    root->rchild = NULL;
    root->parent = NULL;
}

//插入新结点
/**
 * 结点p插入新的左孩子\右孩子
 * l为0为左孩子，1为右孩子
 */ 
bool InsertTNode(BiTNode *p, int l, ElemType x){
    BiTNode *node = (BiTNode *)malloc(sizeof(BiTNode));
    if(node == NULL || p == NULL)return false;
    node->data = x;
    node->lchild = NULL;
    node->rchild = NULL;
    switch(l){
        case 0:
        if(p->lchild == NULL){
            p->lchild = node;
            node->parent = p;
        }
        else return false;
        return true;
        case 1:
        if(p->rchild == NULL){
            p->rchild = node;
            node->parent = p;
        }
        else return false;
        return true;
    }
    return false;
}

//--------------------------------------------二叉树遍历
//访问某结点
void visit(BiTNode *p){
    printf("%d", p->data);
}

//先序遍历（前缀表达式）
void PreOrder(BiTree T){
    if(T != NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
//中序遍历（中缀表达式）
void InOrder(BiTree T){
    if(T != NULL){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}
//后序遍历（后缀表达式）
void PostOrder(BiTree T){
    if(T != NULL){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}

//求树的深度
int treeDepth(BiTree T){
    if(T == NULL)return 0;
    int l = treeDepth(T->lchild);
    int r = treeDepth(T->rchild);
    return l > r ? l + 1 : r + 1;
}

//非递归实现中序遍历
#include<stack>
void InOrder2(BiTree T){
    std::stack<BiTree>S;
    BiTree p = T;
    while(p || !S.empty()){
        if(p){
            //visit(p)//先序遍历
            S.push(p);     //一路向左走
            p = p->lchild;
        }
        else{
            p = S.top();//当前访问的结点为空，说明左走走过头，此时栈顶就是当前的父节点
            S.pop();
            visit(p);//先序遍历仅需将vist(p)移到Push(S, p)前面即可
            p = p->rchild;
        }
    }
}
//非递归的后序遍历见王道P151
void PostOrder2(BiTree T){
    BiTNode *p = T, *r = NULL;//r指向p的前驱，用来标记最近是否访问过
    std::stack<BiTree>S;//**栈中保存p的所有祖先**
    while(p||!S.empty()){
        if(p){
            S.push(p);
            p = p->lchild;
        }
        else {
            p = S.top();
            if(p->rchild && p->rchild != r)//如果树有右孩子并且未访问过
                p = p->rchild;
            else{
                S.pop();
                visit(p);
                r = p;
                p = NULL;   //将p赋空，否则将重走左子树
            }
        }
    }
}

//层次遍历(bfs)
#include<queue>
void LevelOrder(BiTree T){
    std::queue<BiTree>Q;
    Q.push(T);
    BiTree p;
    while(!Q.empty()){
        p = Q.front();
        Q.pop();
        visit(p);
        if(p->lchild != NULL)
            Q.push(p->lchild);
        if(p->rchild != NULL)
            Q.push(p->rchild);
    }
}