#include<iostream>
#include<stack>
#include"BuildTreeandJudge.cpp"
using namespace std;
//typedef struct BinaryTree{
//    int data;
//    struct BinaryTree *lchild, *rchild;
//}TNode, *Tree;
int Num(Tree T, int n){
    int ans = 0;
    stack<TNode*> S;
    Tree t = T;
    while(t || !S.empty()){
        if(t){
            S.push(t);
            t = t->lchild;
        }
        else {
            t = S.top(), S.pop();
            if(t->data <= n)ans++;
            else return ans;
            t = t->rchild;
        }
    }
    return ans;
}
int main(){
    int n = 16;
    int A[16] = {-1,7,3,11,2,5,9,13,1,-1,4,6,8,10,12,14};
    Tree T = NULL;
    createTree2(A, n, T);
    cout<<Num(T, 9)<<endl;
    return 0;
}