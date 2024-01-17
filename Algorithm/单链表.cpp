#include<iostream>
using namespace std;
const int N=100010;
//头插法实现
int head,e[N],ne[N],idx;  //head头节点,e[]存储数据，ne[]存储下一个节点位置，idx当前节点

void init ()//初始化
{
    head=-1;  //头节点指向空
    idx=0;    //当前节点为0
}

void add_to_head(int x)
{
    e[idx]=x,ne[x]=head,head=idx++;  
    /* x存到idx节点，idx节点指向头节点指向的节点，
    头节点指向当前节点，将当前节点移至下一个位置 */
}
void add(int k,int x) //在下标是k的点后插入x
{
    e[idx]=x;
    ne[idx]=ne[k];
    ne[k]=idx;
    idx++;
}
void remove(int k)//移除下标是k的点后的一个点
{
    ne[k]=ne[ne[k]];
}

int main()
{
    init();

    
    return 0;
}