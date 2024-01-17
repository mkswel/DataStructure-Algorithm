#include<stdio.h>
#include<stdlib.h>  //malloc free函数头文件
//---------------------------静态分配
#define MaxSize 10
typedef struct{
    int data[MaxSize];  //静态数组存放元素
    int length;     //表长
}SqList;

//初始化
void InitList(SqList &L){
    for(int i = 0; i < MaxSize; i++)
        L.data[i] = 0;      //所有元素设置为初始值
    L.length = 0;           //表长设为0
}

//插入
/**
 * 在位序i处（不是数组下标）插入元素e
 * 平均时间复杂度O（n）
 */
bool ListInsert(SqList &L, int i, int e){
    if(i < 1 || i > L.length + 1)   //输入i是否有效
        return false;
    if(L.length >= MaxSize)     //空间已满
        return false;
    for(int j = L.length; j >= i; j--)  //第i个元素及后续元素后移
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    L.length++;
    return true;
}

//删除
/**
 * 删除位序i的元素
 * 平均时间复杂度O(n)
 */
bool ListDelete(SqList &L, int i, int &e){
    if(i < 1 || i > L.length)
        return false;
    e = L.data[i - 1];
    for(int j = i; j < L.length; j++)
        L.data[j - 1] = L.data[j];
    L.length--;
    return true;
}

//按位查找
/**
 * 查找位序第i个元素
 * 时间复杂度O(1)
 */
int GetElem(SqList &L, int i){
    return L.data[i - 1];
}

//按值查找
/**
 * 查找第一个值为e的元素的位序
 * 平均时间复杂度O(n)
 */
int LocateElem(SqList &L, int e){
    for(int i = 0; i < L.length; i++)
        if(L.data[i] == e)
            return i + 1;
    return 0;
}

//---------------------------动态分配
#define InitSize 10
typedef struct{
    int *data;      //动态分配数组的指针
    int Maxsize;    //顺序表最大容量
    int length;     //表长
}SeqList;

//初始化
void InitList(SeqList &L){
    L.data = (int *)malloc(InitSize*sizeof(int));
    L.length = 0;
    L.Maxsize = InitSize;
}

//增加动态数组长度
void IncreaseSize(SeqList &L, int len){
    int *p = L.data;
    L.data = (int *)malloc((L.Maxsize + len)*sizeof(int));
    for(int i = 0; i < L.length; i++){
        L.data[i] = p[i];               //复制数据到新区域
    }
    L.Maxsize = L.Maxsize + len;
    free(p);                            //释放原内存空间
}