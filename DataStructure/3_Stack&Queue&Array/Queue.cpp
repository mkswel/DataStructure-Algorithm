#include<stdio.h>
typedef int ElemType;

//------------------------------------顺序队列
#define MaxSize 50
typedef struct{
    ElemType data[MaxSize];
    int front, rear;
}SqQueue;

//初始化
void InitQueue(SqQueue &Q){
    Q.rear = 0;
    Q.front = Q.rear;
}

//判队空
bool QueueEmpty(SqQueue &Q){
    return Q.rear == Q.front;
}

//入队
bool EnQueue(SqQueue &Q, ElemType x){
    if((Q.rear + 1) % MaxSize == Q.front)return false;  //队头和队尾只差一格时认为队满
    Q.data[Q.rear] = x;   //先入队再指针后移取决于初始化
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

//出队
bool DeQueue(SqQueue &Q, ElemType &x){
    if(QueueEmpty(Q))return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

//取队头并存到x
bool GetHead(SqQueue &Q, ElemType &x){
    if(QueueEmpty(Q))return false;
    x = Q.data[Q.front];
    return true;
}

//其他判队满/空条件：1)另设size存当前队长;2)设tag标记当前操作为插入/删除，再结合rear==front来判断空满

//-----------------------------------------------链队列
#include<stdlib.h>
typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode;
typedef struct{
    LinkNode *front, *rear;
}LinkQueue;

//初始化（带头结点）
void InitQueue(LinkQueue &Q){    //队头和队尾都指向头结点
    Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
    Q.front->next = NULL;
}

//初始化（不带头结点）
void InitQueue_(LinkQueue &Q){
    Q.front = NULL;
    Q.rear = NULL;
}

//判队空（带头结点）
bool QueueEmpty(LinkQueue Q){
    return Q.front == Q.rear;
}

//判队空（不带头结点）
bool QueueEmpty_(LinkQueue Q){
    return Q.front == NULL;
}

//入队（带头结点）链表尾插法
void EnQueue(LinkQueue &Q, ElemType x){
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;   //队尾的下一节点为新节点
    Q.rear = s;         //更新队尾
}

//入队（不带头结点）
void EnQueue_(LinkQueue &Q, ElemType x){
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x;
    s->next = NULL;
    if(Q.front == NULL){       //如果队空，将队头和队尾都指向新节点
        Q.front = s;
        Q.rear = s;
    }
    else {
        Q.rear->next = s;      //队不空则同理
        Q.rear = s;
    }
}

//出队（带头结点）链表头删法
bool DeQueue(LinkQueue &Q, ElemType &x){
    if(QueueEmpty(Q))return false;
    LinkNode *p = Q.front->next;   //p指向头结点的后一个节点（第一个元素）
    x = p->data;
    Q.front->next = p->next;       //头结点直接指向第二个元素（把第一个元素剔除）
    if(Q.rear == p)                //如果整队只有一个元素，删完就队空（更新队头指针）
        Q.rear = Q.front;
    free(p);
    return true;   
}

//出队（不带头结点）
bool DeQueue_(LinkQueue &Q, ElemType &x){
    if(QueueEmpty_(Q))return false;
    LinkNode *p = Q.front;      //没有头结点故直接指向第一个元素
    x = p->data;
    Q.front = p->next;          //更新第一个节点，即剔除第一个元素
    if(Q.rear == p){            //原理同前
        Q.rear = NULL;
        Q.front = NULL;
    }
    free(p);
    return true;
}

//链队列除非内存满否则不会队满

//---------------------------------------------------------双端队列
