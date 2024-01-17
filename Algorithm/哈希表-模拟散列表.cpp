/*哈希表  O(1)
  1）拉链法
  2）开放寻址法
*/

/*
  *************拉链法实现
  对于每一个存储单元，下拉一个单链表来存储有冲突的元素
*/

#include<iostream>
#include<cstring>
using namespace std;

const int N=100003;    //尽量取成质数，这样冲突最少
int h[N],ne[N],e[N],idex;//拉链部分的单链表

void insert(int x)
{
    int k=(x%N+N)%N;   //保证x的取模操作结果为正
    e[idex]=x;         //将x插入该内存单元下的“拉链”链表中
    ne[idex]=h[k];
    h[k]=idex++;
}

bool find(int x)    //查询x是否在内存中
{
    int k=(x%N+N)%N;   //找到x取模映射到的内存单元
    for(int i=h[k];i!=-1;i=ne[i])    //遍历这个内存单元上的“拉链”
    if(e[i]==x)return true;        //找到返回真，否则返回假
    return false;
}

int main()
{
    int n;
    scanf("%d",&n);
    memset(h,-1,sizeof(h));   //初始化链表元素为-1
    while(n--)
    {
        char op[2];
        int x;
        scanf("%s%d",op,&x);
        if(*op=='I')insert(x);  //通过取模映射将x存入相应内存单元
        else
        {
            if(find(x))puts("Yes");
            else puts("No");
        }
    }
    return 0;
}



/*
***********开放寻址法实现
开两到三倍的存储空间，元素遇到冲突则向后进一格，直至没有冲突
*/


#include<iostream>
#include<cstring>
using namespace std;

const int N=200003;    //开两倍空间，尽量取成质数，这样冲突最少
const int null=0x3f3f3f3f;   //视为空
int h[N];

int find_(int x)    //搜索x所在位置或可以存放的位置
{
    int k=(x%N+N)%N;   //找到x取模映射到的内存单元
    while(h[k]!=null&&h[k]!=x)   //如果该单元不空且不是x就继续查找，到底回归
    {
        k++;
        if(k==N)k=0;
    }
    return k;   //返回x所在位置或可以存放的位置
}

int main()
{
    int n;
    scanf("%d",&n);
    memset(h,0x3f,sizeof(h));   //初始化链表元素为无穷大
    while(n--)
    {
        char op[2];
        int x;
        scanf("%s%d",op,&x);
        int k=find(x);
        if(*op=='I')h[k]=x;    //找到位置直接插入
        else
        {
            if(h[k]!=null)puts("Yes");   //如果该位置不空，说明x已在
            else puts("No");
        }
    }
    return 0;
}
