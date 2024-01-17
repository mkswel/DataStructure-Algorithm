/*堆-堆排序
  满足以下操作：
  1）插入一个元素；      heap[++size]=x;up(size);
  2）求集合当中最小值；  heap[1];
  3）删除最小元素；      heap[1]=heap[size];size--;down(1);
  4）删除任意元素；      heap[k]=heap[size];size--;down(k);up(k);
  5）修改任意元素；      heap[k]=x;down(k);up(k;)

  6）将数列调整为堆：    for(int i=size/2;i;i--)down(i);
*/

#include<iostream>
#include<algorithm>
using namespace std;

const int N=100010;
int n,m;          //n个元素    进行m次操作，输出前m小的数
int heap[N], size;  //堆heap   堆元素个数size

void down(int u)    //将以u为下标的元素为根节点的树调整为小顶堆
{
    int t=u;         //t为父节点、左孩子、右孩子中最小的那个节点的下标，先令其为父节点
    if(u*2<=size&&heap[u*2]<heap[t])t=u*2; //如果左孩子存在且小于当前t，就将t更新为左孩子
    if(u*2+1<=size&&heap[u*2+1]<heap[t])t=u*2+1;//如果右孩子存在且小于当前t，就将t更新为右孩子
    if(u!=t)               //如果t不是父节点，说明该树需要调整
    {
        swap(heap[u],heap[t]);
        down(t);     //递归整个树
    }
}

void up(int u)     //将以u为下标的元素与其父节点比较，并向上递归至根节点
{
    if(heap[u/2]&&heap[u]<heap[u/2])  //如果u节点的父节点存在且大于u节点，则需要调整
    {
        swap(heap[u],heap[u/2]);
        up(u/2);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&heap[i]);
    size=n;
    for(int i=n/2;i;i--)down(i);   //从树的倒数第二层开始将数列调整为小顶堆（叶子节点无需调整，因此从第二层开始调）
    while(m--)
    {
        printf("%d",heap[1]);      //输出最小值
        heap[1]=heap[size];        //执行删除最小值操作，先将堆最后一个数赋到堆顶，再调整整个堆
        size--;
        down(1);
    }
    return 0;
}