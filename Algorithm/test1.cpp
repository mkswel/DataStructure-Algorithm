#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;
typedef struct TreeNode{
    int data;
    struct TreeNode *lchild, *rchild;
}TreeNode;
vector<int> postorder, inorder;
unordered_map<int, int> hash1;
TreeNode* CreateTree(int post = postorder.size()-1, int il = 0, int ir = inorder.size()){
    int i = hash1.at(postorder[post]);
    if(i>=il && i < ir){
        TreeNode* p = new TreeNode;
        p->data = postorder[post];
        p->lchild = CreateTree(post-(ir-i), il, i);
        p->rchild = CreateTree(post-1, i+1, ir);
        return p;
    }
    return NULL;
}

void preorder(TreeNode* T, int &ans){
    if(!T)return;
    ans = T->data;
    preorder(T->lchild, ans);
    preorder(T->rchild, ans);
}
int main(){
    int n;
    cin>>n;
    for(int i = 0; i < n; i++){
        int a;
        scanf("%d", &a);
        postorder.push_back(a);
    }
    for(int i = 0; i < n; i++){
        int a;
        scanf("%d", &a);
        inorder.push_back(a);
        hash1.emplace(a, inorder.size()-1);
    }
    TreeNode* T = CreateTree();
    int ans = 0;
    preorder(T, ans);
    cout<<ans;
    return 0;
}