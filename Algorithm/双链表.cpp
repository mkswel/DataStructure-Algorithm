#include<iostream>
using namespace std;

const int N=100010;
int m;
int e[N],l[N],r[N],idx;  
/* e[]存储数据，l[]存储左侧下一个节点的位置，
r[]存储右侧下一节点位置，idx当前节点 */

void init()  //初始化
{
    r[0]=1,l[1]=0;  //令下标是0的节点为链表右端点，下标1的节点为左端点
    idx=2;
}

void add(int k,int x)   //在下标是k的节点后插入节点
{
    e[idx]=x;
    r[idx]=r[k];  //当前节点右指针指向k节点右指针指向的位置
    l[idx]=k;   //当前节点左指针指向k节点
    l[r[k]]=idx; //k的右指针指向的节点的左指针指向idx
    r[k]=idx;      //k的右指针指向idx
}

void remove(int k)  //移除下标是k的节点
{
    r[l[k]]=r[k]; //k的左指针指向的节点的右指针指向k的右指针指向的节点
    l[r[k]]=l[k]; //k的右指针指向的节点的左指针指向k的左指针指向的节点
}

int main()
{
    init();


    return 0;

}