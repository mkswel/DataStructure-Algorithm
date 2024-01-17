#include<iostream>
#include<queue>
#include<stack>
using namespace std;

typedef struct BinaryTree{
    int data;
    struct BinaryTree *lchild, *rchild;
}TNode, *Tree;

typedef struct BiTreeNode{
    char data;
    struct BiTreeNode *lchild, *rchild;
}BTreeNode;
/**
 * 将数组下标1-n-1的元素按照从上到下，从左到右的顺序排成一棵完全二叉树
*/
Tree createTree(int A[], int n){
    queue<TNode *> Q;
    Tree T = (TNode *)malloc(sizeof(TNode));;
    int i = 1;
    Q.push(T);
    while(i < n){
        Tree t = Q.front(); Q.pop();
        if(A[i] == -1){i++; continue;}
        if((i<<1) < n && A[i<<1] != -1)t->lchild = (TNode *)malloc(sizeof(TNode));
        if((i<<1|1) < n && A[i<<1|1] != -1)t->rchild = (TNode *)malloc(sizeof(TNode));
        t->data = A[i++];
        Q.push(t->lchild), Q.push(t->rchild);
    }
    return T;
}
/**
 * 递归
 * 将数组下标1-n-1的元素按照从上到下，从左到右的顺序排成一棵完全二叉树
 * T为空指针
 * 数组A[]格式：根从下标1开始，下标0不参与计算
 *            数组长度n=2^树高
 *            空结点用-1表示
*/
void createTree2(int A[], int n, Tree &T, int k = 1){
    if(!T){
        if(k >= n || A[k] == -1)return;
        else {
            T = (Tree)malloc(sizeof(TNode));
            T->data = A[k];
        }
    }
    createTree2(A, n, T->lchild, k<<1);
    createTree2(A, n, T->rchild, k<<1|1);
}

/**
 * 验证是否为完全二叉树
*/
bool JudgeTree(Tree T){
    queue<TNode *> Q;
    Q.push(T);
    bool judge = false; //判断是否走过了空指针
    while(!Q.empty()){
        TNode* t = Q.front();Q.pop();
        if(!t)judge = true;
        else {
            if(judge)return false;
            Q.push(t->lchild), Q.push(t->rchild);
        }
    }
    return true;
}

int get_height(Tree T){
    if(!T)return 0;
    return max(get_height(T->lchild), get_height(T->rchild)) + 1;
}
int get_width(Tree T){
    int h = get_height(T);
    int ans = 1;
    while(--h)ans *= 2;
    return ans;
}
/**
 * 打印二叉树
*/
void printTree(Tree T){
    queue<Tree> Q;
    Q.push(T);
    int width = get_width(T) * 2, cntt = 0;
    while(!Q.empty()){
        cntt++;
        int size = Q.size(), cnt = 0;
        int cntl = 1;
        for(int j = 0; j < cntt; j++)cntl*=2;
        for(int j = 0; j < width; j+=cntl)cout<<"    ";
        for(int i = 0; i < size; i++){
            Tree t = Q.front();Q.pop();
            if(t){
                cout<<t->data;
                Q.push(t->lchild), Q.push(t->rchild);
            }
            else {
                cout<<"_";
                Q.push(NULL), Q.push(NULL);
                cnt++;
            }
            for(int j = 0; j < 2*width; j+=cntl)cout<<"    ";
        }
        cout<<'\n'<<'\n';
        if(cnt == size)return;
    }
}

void printTree2(Tree T){
    queue<Tree> Q;
    Q.push(T);
    while(!Q.empty()){
        int size = Q.size(), cnt = 0;
        for(int i = 0; i < size; i++){
            Tree t = Q.front(); Q.pop();
            if(t){
                cout<<t->data<<"  ";
                Q.push(t->lchild),Q.push(t->rchild); 
            }
            else cout<<"_  ";
            Q.push(NULL), Q.push(NULL);
            cnt++;
        }
        cout<<endl;
        if(cnt == size)return ;
    }
}

void InOrder(Tree T){
    if(!T)return;
    InOrder(T->lchild);
    cout<<T->data<<" ";
    InOrder(T->rchild);
}
// int main(){
//     int n = 16;
//     int A[16] = {-1,7,3,11,2,5,9,13,1,-1,4,6,8,10,12,14};
//     Tree T = NULL;
//     createTree2(A, n, T);
//     InOrder(T);
//     cout<<endl;
//     cout<<JudgeTree(T)<<endl;
//     cout<<endl;
//     printTree(T);
//     return 0;
// }

//以下是例子
//n=16 {-1,1,2,3,4,5,-1,7,8,-1,10,11,-1,-1,14,15}
//n=16 {-1,7,3,11,2,5,9,13,1,-1,4,6,8,10,12,14}