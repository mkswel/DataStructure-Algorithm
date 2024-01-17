#include<iostream>
#include"BuildTreeandJudge.cpp"
using namespace std;
// typedef struct BinaryTree{
//     int data;
//     struct BinaryTree *lchild, *rchild;
// }TNode, *Tree;

bool Identical(Tree T1, Tree T2){
    if(T1 && T2)return T1->data == T2->data;
    else if(!T1 && !T2)return true;
    else return false;
}

int main(){
    int n=16, A[]={-1,1,2,3,4,5,-1,7,8,-1,10,11,-1,-1,14,15};
    Tree T1=NULL, T2=NULL;
    createTree2(A, n, T1);
    createTree2(A, n, T2);
    cout<<Identical(T1, T2)<<endl;
}