#include <iostream>
#include <cmath>
using namespace std;
typedef struct BiTreeNode{
    char data;
    struct BiTreeNode *lchild, *rchild;
}BTreeNode;
/**
 * 返回运算符a的优先级，不合法运算符(包括数字)优先级为正无穷
 */
int pri(char a){
    int n = 5;
    pair<char, int> pr[n] = {{'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'^', 2}};
    for (int i = 0; i < n; i++)
        if (pr[i].first == a)
            return pr[i].second;
    return 0x3f3f3f3f;
}
/**
 * 将只含一位数运算的四则运算式表示成二叉树形式
 * 思路：找到算式[s,e)中最后使用的运算符，将该运算符作为根节点，再左右递归子树
 * 如何寻找一个[s,e)中最后一个使用的运算符：
 * 1、该运算符不会在[s,e)中的任何一对括号内；
 * 2、该运算符必须满足1、条件下的最低优先级运算符中的最右侧
 * 式子包含 + - * / ^
 */
BTreeNode *transform(string &str, int s, int e){
    if (e - s == 1){
        BTreeNode *p = (BTreeNode *)malloc(sizeof(BTreeNode));
        p->data = str[s];
        p->lchild = p->rchild = NULL;
        return p;
    }
    int bracket = 0, root = -1; // bracket:统计括号以确定哪些位置不在任何括号内 root:初始化root
    for (int i = s; i < e; i++){
        if (str[i] == '(')bracket++;
        else if (str[i] == ')')bracket--;
        else if (!bracket && (root == -1 || pri(str[i]) <= pri(str[root])))
            root = i;
    }
    if (root == -1)return transform(str, s + 1, e - 1); // 如果root没变，说明最外层有一对括号
    BTreeNode *p = (BTreeNode *)malloc(sizeof(BTreeNode));
    p->data = str[root];
    p->lchild = transform(str, s, root);
    p->rchild = transform(str, root + 1, e);
    return p;
}

/**
 * 利用二叉树计算结果
*/
double cal(BTreeNode* T){
    switch(T->data){
        case '+':
            return cal(T->lchild)+cal(T->rchild);
        case '-':
            return cal(T->lchild)-cal(T->rchild);
        case '*':
            return cal(T->lchild)*cal(T->rchild);
        case '/':
            return cal(T->lchild)/cal(T->rchild);
        case '^':
            return pow(cal(T->lchild),cal(T->rchild));//指数
    }
    return T->data - '0';
}

// int main(){
//     string str = "(5-4*(3+7/8)^(3-9)/4*(5+3)-2)";//答案 2.997637
//     BTreeNode *T = transform(str, 0, str.length());
//     cout<<cal(T)<<endl;
//     return 0;
// }