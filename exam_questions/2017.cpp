#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
typedef struct LList{
    int data;
    struct LList *next;
}LNode, *LinkList;
/**
 * 带有头结点的两个长整数链表相加
 * 表头到表尾为长整数的低位到高位
 * 结果加到L1里
 * 
 * 力扣415、2
*/
LinkList ADD(LinkList L1, LinkList L2){
    LNode *t1 = L1->next, *t2 = L2->next, *pre = L1/*指向t1的前驱*/;
    int c = 0;//进位
    while(t1 && t2){
        int t = t1->data;
        t1->data = (t + t2->data + c)%10;
        c = (t + t2->data + c)/10;
        pre = t1, t1 = t1->next, t2 = t2->next;
    }
    if(t2)//如果L2更长，将t2接到t1后
        pre->next = t2, t1 = pre->next;
    while(t1 && c){//如果进位是0，不会影响后续结果
        int t = t1->data;
        t1->data = (t + c)%10;
        c = (t + c)/10;
        pre = t1, t1 = t1->next;
    }
    if(c){//如果到最高位依然有进位，就新增最高位
        LNode *t = (LNode *)malloc(sizeof(LNode));
        t->data = 1, t->next = NULL;
        pre->next = t;
    }
    LNode *tt;
    while (L2 != t2){//释放L2
        tt = L2->next;
        free(L2);
        L2 = tt;
    }
    return L1;
}
int main(){
    LinkList L1 = (LNode *)malloc(sizeof(LNode));
    LinkList L2 = (LNode *)malloc(sizeof(LNode));
    L1->next = NULL, L2->next = NULL;
    string a, b;
    cin>>a>>b;
    for(int i = 0; i < a.length(); i++){
        LinkList t1 = (LNode *)malloc(sizeof(LNode));
        t1->data = a[i]-'0';
        t1->next = L1->next;
        L1->next = t1;
    }
    for(int i = 0; i < b.length(); i++){
        LinkList t2 = (LNode *)malloc(sizeof(LNode));
        t2->data = b[i]-'0';
        t2->next = L2->next;
        L2->next = t2;
    }
    LinkList L = ADD(L1, L2);
    L = L->next;
    LNode *t;
    string ans = "";
    while(L){
        t = L->next;
        ans += to_string(L->data);
        L = t;
    }
    reverse(ans.begin(), ans.end());
    cout<<ans<<endl;
    return 0;
}