#include<iostream>
#include"BuildTreeandJudge.cpp"
using namespace std;
// typedef struct BinaryTree{
// int data, count;
// struct BinaryTree *lchild, *rchild;
// }TNode, *Tree;
/**
 * 返回二叉排序树树T中第k小的结点
 * 思路：先确定当前根是第几小，假设为第t小
 * 如果t=k，那就是根；如果t>k，那只要在T左子树找第k小；如果t<k，只要在T右子树找第k-t小
*/
TNode *dfs(Tree T, int k){
    if(!T || k <= 0)return NULL;
    int cnt;
    if(T->lchild)cnt = T->lchild->count + 2;//当前根节点T是第几小
    else cnt = 1;
    if(cnt == k)return T;
    else if(cnt > k)dfs(T->lchild, k);
    else dfs(T->rchild, k - cnt);
}

/**
 * 返回以T为根的树的结点个数，顺便记录每个count
*/
int createCount(Tree T){
    if(!T)return 0;
    int l = createCount(T->lchild);
    int r = createCount(T->rchild);
    T->count = l + r;
    return T->count + 1;
}

int main(){
    int n = 8;
    int A[] = {-1, 5, 4, 6, 2, -1, -1, 7};//{-1, 5, -1, 7, -1, -1, 6, 8};//{-1, 2, 1, 33, 0, -1, 25, 40};
    Tree T = NULL;
    createTree2(A, n, T);
    createCount(T);
    for(int i = 1; i < n; i++){
        TNode * t = dfs(T, i);
        if(t)cout<<t->data<<endl;
        else cout<<"NULL"<<endl;
    }
    return 0;
}

