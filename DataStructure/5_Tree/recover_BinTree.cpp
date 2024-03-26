#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>
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
 * https://www.acwing.com/activity/content/problem/content/8775/  AcWing 5070  哈希表优化
*/
BinTree CreateTree(int post, int il, int ir){
    if(post<0)return NULL;
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
 * 先序+中序 分割成[il, ir)且哈希表优化   哈希表前提：树中无重复元素
 * 预处理：要先将inorder数组存入哈希表，键值对{inorder[i], i}
*/
unordered_map<int, int> order_hash;
BinTree CreateTree2(int pre = 0, int il = 0, int ir = preorder.size()){
    if(pre >= preorder.size())return NULL;
    int i = order_hash.at(preorder[pre]);
    if(i >= il && i < ir){
        BinTree p = new BinNode;
        p->data = preorder[pre];
        p->lchild = CreateTree2(pre + 1, il, i);
        p->rchild = CreateTree2(pre + i - il + 1, i + 1, ir);
        return p;
    }
    return NULL;
}


/**
 * 层序+中序
 * 哈希表优化 时间复杂度O(n)
*/
unordered_map<int, int> hash1;
BinTree CreateTree3(vector<int> levorder, vector<int> inorder){
    queue<pair<pair<int,int>,pair<int, BinNode*>>> Q;
    int il=0, ir=inorder.size()-1;
    BinTree T;
    for(int i = 0; i < levorder.size(); i++){
        BinTree p=new BinNode;
        p->data=levorder[i];
        p->lchild=NULL;
        p->rchild=NULL;
        int j = hash1.at(p->data);
        if(!i)T=p,Q.push({{il, ir},{j, p}});//暂存以p为根的树的中序左边界、右边界、p的中序下标以及p
        else if(!Q.empty()){
            il=Q.front().first.first, ir=Q.front().first.second;
            int iroot = Q.front().second.first;
            BinTree root=Q.front().second.second;
            if(j < iroot){//p是root的左孩子
                root->lchild = p;
                if(j>il || j<iroot-1)Q.push({{il, iroot-1},{j, p}});//如果j的中序序列左右依然有结点，说明p还有孩子
            }
            else {
                root->rchild = p;
                if(ir>j || j>iroot+1)Q.push({{iroot+1, ir},{j, p}});
            }  
            if(iroot==il||iroot==ir||(root->rchild&&root->lchild))Q.pop();//根的孩子全部已更新则将根出队
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
    int n = 5;
    int levo[n] = {3, 9, 20, 15, 7};
    int ino[n] = {9, 3, 15, 20, 7};
    for(int i = 0; i < n; i++)levorder.push_back(levo[i]), inorder.push_back(ino[i]), hash1.emplace(ino[i], i);;
    BinTree T = CreateTree3(levorder, inorder);
    show_Tree(T);
    return 0;
}
