//定义：左子树上所有结点 < 根 < 右子树上所有结点
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct BST{
    ElemType data;
    struct BST *lchild, *rchild;
}BSTNode, *BSTree;

//BST的查找
BSTNode *ST_Search(BSTree T, ElemType key){
    while(T != NULL && key != T->data){
        if(key < T->data)T = T->lchild;
        else T = T->rchild;
    }
    return T;
}

//BST插入（也即构造）
bool BST_Insert(BSTree &T, int k){
/*空指针也需要引用，否则只是拷贝了一个空指针，
函数内部的指针操作都是针对这个复制品进行的，原指针依然指向NULL
除非这里传入的不是空指针，即拥有实际的地址*/
    if(T == NULL){
        T = (BSTree)malloc(sizeof(BSTNode));
        T->data = k;
        T->lchild = NULL;
        T->rchild = NULL;
        return true;
    }
    else if(T->data == k)return false;
    else if(T->data > k)return BST_Insert(T->lchild, k);
    else return BST_Insert(T->rchild, k);
}

//BST删除
/**
 * 1）删叶子结点：直接删
 * 2）删只有一个孩子的结点：将其孩子替换之即可
 * 3）删有两个孩子的结点：用该结点的直接前驱（后继）代替之，然后删掉这个直接前驱（后继）
 *          直接前驱是其左子树的最右边（最后一个）的值，直接后继是右子树的最左边（第一个）的值
 */ 
bool BST_Delete(BSTree &T, int k){

}





//**************************************************测试
//中序遍历（中缀表达式）
void InOrder(BSTree T){
    if(T != NULL){
        InOrder(T->lchild);
        printf("%d\t", T->data);
        InOrder(T->rchild);
    }
}
int main(){
    BSTree T = NULL;
    int str[8] = {50, 66, 60, 26, 21, 30, 70, 68};
    for(int i = 0; i < 8; i++){
        if(!BST_Insert(T, str[i])){
            printf("FAIL\n");
            return 0;
        }
    }
    InOrder(T);
    return 0;

}