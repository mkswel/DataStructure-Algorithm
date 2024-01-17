#include"1998.cpp"
using namespace std;

/**
 * 将二叉树转换成四则运算符
 * 思路：中序遍历，从第二层开始除了叶子结点每个结点递归前先套一层括号
*/
string InTransform(BTreeNode* T, int deep = 1){
    string ans = "";
    if(!T)return ans;
    else if(!T->lchild && !T->rchild)return ans+T->data;
    else{
        if(deep > 1)ans += '(';
        ans += InTransform(T->lchild, deep + 1);
        ans += T->data;
        ans += InTransform(T->rchild, deep + 1);
        if(deep > 1)ans += ')';
    }
    return ans;
}

int main(){
    string str = "(5-4*(3+7/8)^(3-9)/4*(5+3)-2)";//答案 2.997637
    BTreeNode *T = transform(str, 0, str.length());
    int k = 2;
    while(k--){
        cout<<cal(T)<<endl;
        str = InTransform(T);
        cout<<str<<endl;
        T = transform(str, 0, str.length());
    }
    return 0;
}