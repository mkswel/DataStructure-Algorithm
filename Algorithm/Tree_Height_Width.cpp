#include<iostream>
#include<queue>
using namespace std;
typedef struct BinaryTree{
    int data;
    struct BinaryTree *lchild, *rchild;
}TNode, *Tree;

/**
 * 返回二叉树高度
*/
int TreeHeight(Tree T){
    if(!T)return 0;
    return 1 + max(TreeHeight(T->lchild), TreeHeight(T->rchild));
}

/**
 * 返回二叉树宽度，即结点树最多的那层的结点数
*/
int TreeWidth(Tree T){
    queue<TNode *> Q; //在每层末尾加一个标记表示该层结束，此时队列长度即为当前层宽
    if(!T)return 0;
    int maxwidth = 1;
    TNode *sign = (TNode *)malloc(sizeof(TNode));
    Q.push(T);
    Q.push(sign);
    while(!Q.empty()){
        TNode *t = Q.front();Q.pop();
        if(t == sign){
            maxwidth = max((int)Q.size(), maxwidth);
            if(!Q.empty())Q.push(sign); //避免死循环
        }
        else {
            if(t->lchild)Q.push(t->lchild);
            if(t->rchild)Q.push(t->rchild);
        }
    }
    free(sign);
    return maxwidth;
}

/**
 * 力扣662
 * 返回二叉树实际宽度，中间的空指针也算
*/