#include<iostream>
#include"BuildTreeandJudge.cpp"
using namespace std;
// typedef struct BinaryTree{
//     int data;
//     struct BinaryTree *lchild, *rchild;
// }TNode, *Tree;

void dfs(Tree T, int path[], int &h, int &n){
    if(!T)return;//关键字不在树中
    if(T->data == n){
        for(int i = 0; i < h; i++)cout<<path[i]<<"->";
        cout<<T->data<<endl;
        return;
    }
    if(T->data < n){
        path[h++] = T->data;
        dfs(T->rchild, path, h, n);
    }
    else {
        path[h++] = T->data;
        dfs(T->lchild, path, h, n);
    }
}
int main(){
    Tree T=NULL;
    int A[16] = {-1,9,8,15,7,-1,12,20,-1,-1,-1,-1,-1,-1,19,27};
    createTree2(A, 16, T);
    int path[100];
    int n = 19, h = 0;
    dfs(T, path, h, n);
    return 0;
}