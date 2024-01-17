#include<stdio.h>
typedef int ElemType;

typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode *lchild, *rchild;
    int ltag, rtag;  //ltag为0表示指向左孩子，为1表示指向前驱；rtag同理
}ThreadNode, *ThreadTree;

//中序线索化二叉树
ThreadNode *pre = NULL; //设置全局变量pre
/**
 * 用于将当前结点的两个孩子线索化
 * p指向当前结点，pre指向p的前驱
 */ 
void visit(ThreadNode *p){
    if(p->lchild == NULL){//左孩子为空，建立前驱线索
        p->lchild = pre;
        p->ltag = 1;
    }
    if(pre != NULL && pre->rchild == NULL){     //前驱的右孩子为空，将本身建为前驱的后继线索
        pre->rchild = p;
        pre->rtag = 1;
    }
    pre = p;//更新pre
}
/**
 * 中序过程，将整个二叉树线索化
 */ 
void InThread(ThreadTree T){
    if(T != NULL){
        InThread(T->lchild);//递归左子树
        visit(T);
        InThread(T->rchild);//递归右子树
    }
}
/**
 * 线索化主过程
 * T：根结点
 */
void CreateInThread(ThreadTree T){
    pre = NULL;  //第一个结点没有前驱
    if(T != NULL){
        InThread(T);
        pre->rchild = NULL;  //递归结束后处理最后一个结点
        pre->rtag = 1;
    }
} 

//先序建立线索树
void PreThread(ThreadTree T){
    if(T != NULL){
        visit(T);
        if(T->ltag == 0)    //只有左孩子存在时才会递归下去，否则陷入死循环。因为visit中已经更新了lchild
            PreThread(T->lchild);
        PreThread(T->rchild);
    }
}

//后序线索树
void PostThread(ThreadTree T){
    if(T != NULL){
        PostThread(T->lchild);
        PostThread(T->rchild);//由于visit被放在最后，因此不会陷入循环
        visit(T);
    }
}


//-----------------------------------------------中序线索二叉树的遍历
/**
 * 寻找以T为根的树的第一个结点（最左下结点）
 */ 
ThreadNode *FirstNode(ThreadTree T){
    while(T->ltag == 0)T = T->lchild;   //有左子树就递归访问左子树
    return T;
}

/**
 * 寻找p的后继
 */ 
ThreadNode *NextNode(ThreadNode *p){
    if(p->rtag == 0)return FirstNode(p->rchild);   //p有右子树，其后继即为右子树最左下角
    else return p->rchild;
}
/**
 * 寻找以T为根的最后一个结点（最右下角）
 */ 
ThreadNode *LastNode(ThreadTree T){
    while(T->rtag == 0)T = T->rchild;
    return T;
}
/**
 * 寻找p的前驱
 */ 
ThreadNode *PreNode(ThreadNode *p){
    if(p->ltag == 0)return LastNode(p->lchild);
    else return p->lchild;
}
/**
 * 对以T为根的中序线索二叉树进行中序遍历（非递归）
 */
void Inorder(ThreadNode *T){
    for(ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p))
        visit(p);
} 
//同理利用寻找最后结点和寻找前驱可以实现逆向中序遍历

//先序线索树
/**
 * 根为T的先序线索树的第一个结点：就是T
 * 
 * 找p的先序后继：
 * 1）若p有左孩子，则后继为p的左孩子
 * 2）若p无左孩子有右孩子，则后继为p的右孩子
 * 
 * 根为T的先序线索树的最后一个结点：在有右子树的情况下递归右子树，否则递归左子树
 * 
 * 找p的先序前驱：
 * 1）若p是左孩子，则前驱为p的父结点
 * 2）若p是右孩子且无左兄弟，则前驱为p的父结点
 * 3）若p是右孩子且有左兄弟，则前驱为p的左兄弟子树里的最后一个结点
 */ 

//后序线索树
/**
 * 根为T的后序线索树的最后一个结点：就是T
 * 
 * 找p的后序前驱：
 * 1）若p有右孩子，则前驱为p的右孩子
 * 2）若p无右孩子有左孩子，则前驱为p的左孩子
 * 
 * 根为T的后序线索二叉树的第一个结点：有左子树的情况下递归左子树，否则递归右子树
 * 
 * 找p的后续后继：
 * 1）若p是右孩子，则后继为p的父结点
 * 2）若p是左孩子且无右兄弟，则后继为p的父结点
 * 3）若p是左孩子且有右兄弟，则后继为p的右兄弟子树中的第一个结点
 * 
 */ 