#include<iostream>
#include<stack>
#define MaxVexSize 1000
using namespace std;

/**
 * 哈密顿回路
*/
typedef struct{
    bool st[MaxVexSize]; //记录某点是否访问过
    int edge[MaxVexSize][MaxVexSize];
    int vexnum, arcnum;
}MGraph;
/**
 * 表示回路的最新点为v，回路已含边数k，起点v0用于判断
*/
void DFS(MGraph &G, int A[], int &k, int v0, int v){
    int n = G.vexnum;
    if(k == n){ //如果走完所有点
        if(v0 == v){ //如果最后这个点就是起点，则满足哈密顿回路
            for(int i = 0; i < n; i++)cout<<A[i]<<'\t';
            cout<<v<<endl;
        }
        return ;
    }
    A[k] = v; //将这个点记到哈密顿回路中
    for(int i = 0; i < n; i++){
        if(!G.st[i] && G.edge[v][i]){
            k++, G.st[i] = true;
            DFS(G, A, k, v0, i);
            k--, G.st[i] = false;//状态回复
        }
    }
}

/**
 * 非递归判断二叉树相等
 * 中序遍历
*/
typedef struct BinaryTree{
    int data;
    struct BinaryTree *lchild, *rchild;
}TNode, *Tree;
bool InOrder(Tree T1, Tree T2){
    stack<Tree> S1, S2;
    Tree t1 = T1, t2 = T2;
    //两棵树只要有一棵遍历完就结束循环  遍历完的标志：当前结点为空且栈空
    while((t1 || !S1.empty()) && (t2 || !S2.empty())){
        if(t1 && t2){
            S1.push(t1);
            t1 = t1->lchild;
            S2.push(t2);
            t2 = t2->lchild;
        }
        else if(!t1 && !t2){
            t1 = S1.top();S1.pop();
            t2 = S2.top();S2.pop();
            if(t1->data != t2->data)return false;
            t1 = t1->rchild;
            t2 = t2->rchild;
        }
        else return false; //结点结构不一致
    }
    //根据是否还有一棵树未遍历完来判断结构是否一致
    return !(t1 || !S1.empty()) && !(t2 || !S2.empty());
} 

int main(){
    MGraph G;
    int A[MaxVexSize];
    G.vexnum = 5;
    G.arcnum = 10;
    for(int i = 0; i < G.vexnum; i++)
        for(int j = 0; j < G.vexnum; j++)
            G.edge[i][j] = i == j ? 0 : 1;
    int k = 0;
    DFS(G, A, k, 0, 0);
    return 0;
}