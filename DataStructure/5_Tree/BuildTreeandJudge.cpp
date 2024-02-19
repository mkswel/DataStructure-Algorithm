#include<iostream>
#include<queue>
#include<stack>
using namespace std;

typedef struct BinaryTree{
    int data;
    struct BinaryTree *lchild, *rchild;
    int count;
}TNode, *Tree;
/**
 * 将数组下标1-n-1的元素按照从上到下，从左到右的顺序排成一棵完全二叉树
 * 方法一：队列
*/
Tree createTree(int A[], int n){
    queue<TNode *> Q;
    Tree T = (TNode *)malloc(sizeof(TNode));
    int i = 1;
    Q.push(T);
    while(i < n){
        Tree t = Q.front(); Q.pop();
        if(A[i] == -1){i++; continue;}
        t->data = A[i];
        t->lchild = NULL;
        t->rchild = NULL;
        if((i<<1) < n && A[i<<1] != -1)t->lchild = (TNode *)malloc(sizeof(TNode));
        if((i<<1|1) < n && A[i<<1|1] != -1)t->rchild = (TNode *)malloc(sizeof(TNode));
        i++;
        Q.push(t->lchild), Q.push(t->rchild);
    }
    return T;
}
/**
 * 方法二：递归
 * 将数组下标1-n-1的元素按照从上到下，从左到右的顺序排成一棵完全二叉树
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
            T->lchild = NULL;
            T->rchild = NULL;
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
                if(t->data < 10)cout<<"0";
                cout<<t->data;
                Q.push(t->lchild), Q.push(t->rchild);
            }
            else {
                cout<<"__";
                Q.push(NULL), Q.push(NULL);
                cnt++;
            }
            for(int j = 0; j < 2*width; j+=cntl)cout<<"    ";
        }
        cout<<"\n\n";
        if(cnt == size)return;
    }
}
void InOrder(Tree T){
    if(!T)return;
    InOrder(T->lchild);
    cout<<T->data<<" ";
    InOrder(T->rchild);
}
int main(){
    int n = 32;
    int A[n] = {-1, 31 ,9 ,12 ,5 ,1 ,17 ,29 ,4 ,15 ,2 ,11 ,8 ,30 ,22 ,16 ,25 ,26 ,10 ,6 ,28 ,19 ,27 ,20 ,18 ,14 ,21 ,3 ,24 ,13 ,23 ,7};
    Tree T = NULL;
    T = createTree(A, n);
    InOrder(T);
    cout<<endl;
    cout<<JudgeTree(T)<<endl;
    cout<<endl;
    printTree(T);
    return 0;
}

//以下是例子
//n=16 {-1,1,2,3,4,5,-1,7,8,-1,10,11,-1,-1,14,15}


/*
     11   21   31   41
    11 21 31 41 51 61 71 81


*/
