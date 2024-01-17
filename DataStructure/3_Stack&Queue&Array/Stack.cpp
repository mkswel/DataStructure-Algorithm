#include<stdio.h>
typedef int ElemType;

//-----------------------------------------------顺序栈
#define MaxSize 10
typedef struct{
    ElemType  data[MaxSize];
    int top;
}SqStack;

//初始化
void InitStack(SqStack &S){
    S.top = -1;
}

//判栈空
bool StackEmpty(SqStack &S){
    return S.top == -1;
}

//进栈
/**
 * 元素x入栈
 */
bool Push(SqStack &S, ElemType x){
    if(S.top == MaxSize - 1)return false;
    S.data[++S.top] = x;  //初始化栈顶是-1，因此指针先加1
    return true;
} 

//出栈
/**
 * 元素出栈并存到x
 */ 
bool Pop(SqStack &S, ElemType &x){
    if(StackEmpty(S))return false;
    x = S.data[S.top--];  //由于栈顶始终有元素故先出再退，否则因先退再出
    return true;
}

//共享栈
typedef struct{
    ElemType data[MaxSize];
    int top0;
    int top1;
}ShStack;

//初始化共享栈
void InitStack(ShStack &S){
    S.top0 = -1;  //-1为0号栈栈底
    S.top1 = MaxSize;  //MaxSize为1号栈栈底
}
//判栈满：top1 - top0 = 1

//-----------------------------------------------------链式栈
typedef struct Linknode{
    ElemType data;
    struct Linknode *next;
}*LiStack;
//链式栈的入栈相当于单链表头插操作；出栈相当于单链表“头删”操作（单链表头相当于栈顶）