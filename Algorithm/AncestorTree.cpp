#include<iostream> 
#include"BuildTreeandJudge.cpp"
using namespace std;

//typedef struct BinaryTree{
//    int data;
//    struct BinaryTree *lchild, *rchild;
//}TNode, *Tree;

/**
 * 输出结点x的所有祖先 xanc表示结点T是否是x祖先（或是否已经找到x），初始为false
 * 思路：后序遍历中，如果遍历到x，那说明x的所有祖先必然已被全部调用，
 * 且x的非祖先要么已经释放，要么尚未调用
 * 思路参考王道P243第6题解答
*/
void Ancestor(Tree T, int x, bool &xanc){
    if(!T)return;
    Ancestor(T->lchild, x, xanc);
    if(!xanc)Ancestor(T->rchild, x, xanc);
    if(T->data == x)xanc = true;
    else if(xanc)cout<<T->data<<" ";
}

/**
 * 输出结点x和y的最近公共祖先（非三叉链表）
 * 法一：先找到x、y中一个结点，然后从它的最小祖先开始找另一个结点，没找到就继续第二小的祖先
 * 时间复杂度：共n个结点，找第一个最坏耗时O（n），找第二个最坏耗时O(nlogn)，故为O(nlogn)
 * 法二：先找到x，y中一个，将它的祖先全部存入哈希表；再找另外一个，从其最小祖先开始比对哈希表。
 * 时间复杂度：找第一个最坏耗时O(n)，找第二个最坏耗时O(n)，比对祖先耗时O（1），故为O(n)
 * 法三：后序遍历子树内含有x或y的个数，第一个为2的就是
*/
void CommonAncestor(Tree T, int x, int y, int &tmpanc, int &num){
    // if(!T)return;
    // CommonAncestor(T->lchild, x, y, tmpanc, num);
    // if(num != 2)CommonAncestor(T->rchild, x, y, tmpanc, num);
    // if(T->data == x || T->data == y)
    //     num++;
    // else if(num){
    //     if(num == 1)tmpanc = T->data;
    //     else cout<<tmpanc;
    // }

}
/**
 * 二叉链表存储结构
 * 寻找x和y的最小公共祖先（假设x是y的祖先，那最小公共祖先就是x的父结点）
 * 力扣236
 * 
 * 函数返回树T内结点x或y的个数
 * find=0：没有找到公共祖先
 *      1：找到了x或y中的第二个结点，此时公共祖先就是它的父结点
 *      2：找到最小公共祖先
 * 复杂度分析：对T进行一次后序遍历，最坏O(n)
*/
int CommonAncestor(Tree T, int x, int y, int &find){
    if(!T)return 0;
    int left=0, right=0, root=0, sum=0;
    left=CommonAncestor(T->lchild, x, y, find);
    if(find<1)right=CommonAncestor(T->rchild, x, y, find);
    if(find<2){
        root = (T->data==x||T->data==y?1:0);
        sum = root+left+right;
        if(sum==2){
            find++;
            if(!root){//如果不是x和y，直接找到结果
                cout<<T->data;
                find++;
            }
            else if(find==2)cout<<T->data;//找到x或y，要再找它的父结点
        }
    }
    return sum;
}


int main(){
    int n = 16;
    int A[16] = {-1,7,3,11,2,5,9,13,1,-1,4,6,8,10,12,14};
    Tree T = NULL;
    createTree2(A, n, T);
    printTree(T);
    cout<<endl;
    // for(int i = 1; i < n; i++){
    //     bool anc = false;
    //     if(A[i] != -1)Ancestor(T, A[i], anc);
    //     cout<<"这是"<<A[i]<<"的祖先\n"<<endl;
    // }
    for(int i = 2; i < n; i++)
        for(int j = i; j < n; j++){
            if(i != j && A[i] != -1 && A[j] != -1){
                int find = 0;
                CommonAncestor(T, A[i], A[j], find);
                cout<<"是"<<A[i]<<"和"<<A[j]<<"的最小公共祖先\n";
            }
        }
    cout<<endl;
    return 0;
}
