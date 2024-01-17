#include<stdio.h>
#include<stdlib.h>
typedef struct LNode{
    int/*ElemType*/ data;
    struct LNode *next;
}LNode, *LinkList;

//-------------------------------------带头结点
//初始化
bool InitList(LinkList &L){
    L = (LNode *)malloc(sizeof(LNode));
    if(L == NULL)
        return false;
    L->next = NULL;
    return true;
}

//头插法建立单链表（用于逆向建表，先加入的在表尾，后加入的在表头）
LinkList List_HeadInsert(LinkList &L){
    LNode *s;
    int x;
    L = (LinkList)malloc(sizeof(LNode));    //创建头结点
    L->next = NULL;                         //初始化表空
    scanf("%d", &x);
    while(x != 9999){
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;                        //新节点赋值
        s->next = L->next;                  //新节点后继变为头结点后继
        L->next = s;                        //新节点前驱为头结点
        scanf("%d", &x);
    }
    return L;
}

//尾插法建立单链表
LinkList List_TailInsert(LinkList &L){
    int x;
    L = (LinkList)malloc(sizeof(LNode));    //建立头结点
    LNode *s, *r = L;                       //r为表尾指针
    scanf("%d", &x);
    while(x != 9999){                       //输入9999表示停止
        s = (LNode *)malloc(sizeof(LNode)); //新建节点
        s->data = x;                        //新节点赋值
        r->next = s;                        //将新节点加到表尾
        r = s;                              //更新表尾
        scanf("%d", &x);
    }
    r->next = NULL;
    return L;
}

//插入
/**
 * 在位序i处插入e
 */
bool ListInsert(LinkList &L, int i, int e){
    if(i < 1)return false;
    LNode *p;
    int j = 0;  //从头结点开始
    p = L;      //p指向头结点
    while(p != NULL && j < i - 1){  //循环用于找到位序i-1的节点
        p = p->next;
        j++;
    }
    if(p == NULL)return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));  //新节点
    //三步
    s->data = e;        //新节点赋值
    s->next = p->next;  //新节点后继 成为 原节点后继
    p->next = s;        //原节点后继 成为 新节点
    return true;
}
/**
 * 后插操作：p节点之后插入e
 */
bool InsertNextNode(LNode *p, int e){
    if(p == NULL)return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(s == NULL)return false;   //分配空间失败
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}
/**
 * 前插操作：p节点之前插入e
 * 方法1：循环查找p的前驱，然后插入
 * 时间复杂度O(n)
 */ 
bool InsertPriorNode(LinkList &L, LNode *p, int e){

}
/**
 * 前插操作2：先在p节点之后插入e，再将p和e交换
 * 时间复杂度O(1)
 */
bool InsertPriorNode(LNode *p, int e){
    if(p == NULL)return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(s == NULL)return false;
    s->next = p->next;
    p->next = s;        //将新节点插到p后
    s->data = p->data;  //将p的值赋给新节点
    p->data = e;        //将e覆盖掉p的值
    return true;
}

//删除
/**
 * 按位序删除
 * 删掉第i个节点，并将值保存到e
 */
bool ListDelete(LinkList &L, int i, int &e){
    if(i < 1)return false;
    LNode *p;
    int j = 0;
    p = L;
    while(p != NULL && j < i - 1){
        p = p->next;
        j++;
    }
    if(p == NULL || p->next == NULL)return false;
    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return true;
}
/**
 * 删除指定节点p
 * 将p的后继赋给p，然后删掉p的后继
 * 时间复杂度O(1)
 */ 
bool DeleteNode(LNode *p){
    if(p == NULL)return false;
    LNode *q = p->next;  //令q是p的后继
    p->data = p->next->data;  //把q的值赋给p
    p->next = q->next;      //把q的后继变为p的后继
    free(q);
    return true;
}

//查找
/**
 * 按位查找
 * 平均时间复杂度O(n)
 */ 
LNode * GetElem(LinkList &L, int i){
    if(i < 0)return NULL;
    LNode *p;
    int j = 0;
    p = L;
    while(p != NULL && j < i){
        p = p->next;
        j++;
    }
    return p;
}
/**
 * 按值查找
 * 从头开始找第一个值为e的节点
 * 平均时间复杂度O(n)
 */ 
LNode * LocateElem(LinkList &L, int e){
    LNode *p = L->next;
    while(p != NULL && p->data != e)
        p = p->next;
    return p;
}

//求表长
int Length(LinkList &L){
    int len = 0;
    LNode *p = L;
    while(p->next != NULL){
        p = p->next;
        len++;
    }
    return len;
}

//-------------------------------------不带头结点
//初始化
bool InitList_(LinkList &L){
    L = NULL;
    return true;
}

//插入
/**
 * 在位序i处插入e
 */
bool ListInsert(LinkList &L, int i, int e){
    if(i < 1)return false;
    if(i == 1){         //插入第1个节点操作与其他不同
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;      //头指针指向新节点
        return true;
    }
    LNode *p;
    int j = 1; //从第1个节点开始
    p = L;     //p指向第1个节点（非头结点）
    while(p != NULL && j < i - 1){
        p = p->next;
        j++;
    }
    if(p == NULL)return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));  //新节点
    //三步
    s->data = e;        //新节点赋值
    s->next = p->next;  //新节点后继 成为 原节点后继
    p->next = s;        //原节点后继 成为 新节点
    return true;
}
