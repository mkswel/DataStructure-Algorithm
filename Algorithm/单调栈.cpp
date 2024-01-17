/*单调栈
  求一段整数数列中，每一个数左边第一个比它小的数，若没有则返回-1
*/

#include<iostream>
using namespace std;
const int N=100010;

int n;   //数列元素个数
int stk[N],tt;  //stk[]为数组形式的栈，tt为栈顶下标

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)   //每输入一个数就能导出其对应的“左边第一个比它小的数”的结果
    {
        int x;
        scanf("%d",&x);
        while(tt&&stk[tt]>=x)tt--;  //如果栈不空且当前栈顶的数不小于新输入的数时，就删掉当前栈顶的数
        if(tt)printf("%d",stk[tt]);  //如果经过若干次删除后栈不空，说明此时栈顶的数就是“左边第一个比它小的数”
        else printf("-1");       //若栈空，说明左边没有比它小的数，返回-1
        stk[++tt]=x;          //将输入的数作为新的栈顶
        /*原理：对于两个数al,ar（l<r）如果al>ar，
        则al必不会成为ar后面的数的答案，将其直接删除不会影响总体结果
        **因此创造出的栈是单调增的
        */

    }
    return 0;
}