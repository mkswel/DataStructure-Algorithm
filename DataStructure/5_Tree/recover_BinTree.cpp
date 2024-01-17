#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
typedef int ElemType;
typedef struct BT{
    ElemType data;
    struct BT *lchild, *rchild;
}BinNode, * BinTree;
vector<ElemType> postorder, inorder, preorder, levorder;

/**
 * 输出中序和后序确定的二叉树
 * 后序序列中的元素postorder[post]为树根，中序遍历序列inorder[]中区间[il, ir]为树的所有结点
*/
BinTree CreateTree(int post, int il, int ir){
    for(int i = il; i <= ir; i++)
        if(inorder[i] == postorder[post]){
            BinTree p = new BinNode;
            p->data = postorder[post];
            p->lchild = CreateTree(post - (ir - i) - 1, il, i - 1);//根据中后序列子树结点数相同
            p->rchild = CreateTree(post - 1, i + 1, ir);
            return p;
        }
    return NULL;
}
/**
 * 先序+中序
*/
BinTree CreateTree2(int pre, int il, int ir){
    for(int i = il; i <= ir; i++)
        if(inorder[i] == preorder[pre]){
            BinTree p = new BinNode;
            p->data = preorder[pre];
            p->lchild = CreateTree2(pre + 1, il, i - 1);
            p->rchild = CreateTree2(pre + (i - il) + 1, i + 1, ir);
            return p;
        }
    return NULL;
}


/**
 * 层序+中序
 * 优化思路：看层序里面的一个结点在中序里面是不是左右都有结点，如果是那后面连续两个结点
 * 分别是它的左右孩子，否则具体判断
 * 
 * Q用于存放中序序列中每次循环后左边界、根、右边界（四种情况：三者都不同；左与根相同；右与根相同；三者相同）
 * 循环遍历层序序列，将遍历到的点与Q的队头进行匹配：如果该点在根左，即为左孩子，在根右即为右孩子，然后视情况判断该点状态是否入队：若三者相同则无需入队
 * 
*/
BinTree CreateTree3(vector<int> levorder, vector<int> inorder){
    queue<pair<pair<int,int>,BinNode*>> Q;
    int il=0, ir=inorder.size()-1;
    BinTree T;
    for(int i = 0; i < levorder.size(); i++){
        BinTree p=new BinNode;
        p->data=levorder[i];
        p->lchild=NULL;
        p->rchild=NULL;
        if(!i)T=p,Q.push({{il, ir},p});
        else if(!Q.empty()){
            il=Q.front().first.first, ir=Q.front().first.second;
            BinTree root=Q.front().second;
            int j;
            for(j=il; j<=ir && root->data!=inorder[j]; j++)//从左边界遍历到右边界（实际上遍历到根即可）
                if(levorder[i]==inorder[j])//找到则说明为左孩子，继续遍历完便于找到根的下标
                    root->lchild=p;
            if(root->lchild == p && j - 1 > il)
                Q.push({{il, j-1},p});
            else if(root->lchild != p){
                root->rchild = p;
                if(ir > j + 1)Q.push({{j+1, ir},p});
            }
            if(root->data==inorder[il]||root->data==inorder[ir]||(root->rchild&&root->lchild))Q.pop();
        }
    }
    return T;
}

void show_Tree(BinTree T){//输出层序遍历
    queue<BinNode *> qu;
    qu.push(T);
    while(!qu.empty()){
        BinTree t = qu.front();
        qu.pop();
        if(t != NULL){
            cout<<t->data<<'\t';
            qu.push(t->lchild);
            qu.push(t->rchild);
        }        
    }
}
/**
 * 利用后序遍历和中序遍历还原二叉树，并输出层序遍历
 * leetcode 106.
 */ 
int main(){
    int n = 7;
    int levo[n] = {1,2,3,4,5,6,7};
    int ino[n] = {4,2,5,1,6,3,7};
    for(int i = 0; i < n; i++)levorder.push_back(levo[i]), inorder.push_back(ino[i]);
    BinTree T = CreateTree3(levorder, inorder);
    show_Tree(T);
    return 0;
}
