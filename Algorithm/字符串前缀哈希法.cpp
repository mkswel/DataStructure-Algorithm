/*字符串哈希方法
  **判断字符串相同

  原理：将字符串的每段前缀映射成各自对应的哈希值（十进制范围0-2^64-1）；

  注意点：1)字符串不能映射成0；
         2)进制P取131或13331，模Q取2^64，可以视为不发生冲突

*/

#include<iostream>
using namespace std;

typedef unsigned long long ULL;  //等价于mod Q（溢出即为取模）
const int N=100010;
const int P=131;
int n,m;     //字符串长度n，进行m次操作
char str[N];
ULL h[N],p[N];    //h[n]存储前n个字符组成的字符串的哈希值，该哈希值为一个用十进制表示的P进制的数,p[n]表示n个字符表示的P进制位数 

ULL get(int l,int r)        //返回[l,r]位置的字符串的哈希值
{
    return h[r]-h[l-1]*p[r-l+1];  //在'l-1'字符串后补0，补到位数和'r'字符串一致，再将两字符串相减，所得结果就是[l,r]处字符串的哈希值
}

int main()
{
    scanf("%d%d%s",&n,&m,str+1);  //输入字符串长度n，进行m次操作，读入字符串（从下标1开始）
    p[0]=1;
    for(int i=1;i<=n;i++)    //预处理每段前缀的哈希值
    {
        p[i]=p[i-1]*P;     //i个字符的字符串显然比i-1个字符的字符串多一位
        h[i]=h[i-1]*P+str[i];  //将上一个哈希值进上一位，在空出的“个”位上加上当前字符的ASCLL码值
    }
    while(m--)
    {
        int l1,l2,r1,r2;
        scanf("%d%d%d%d",&l1,&r1,&l2,&r2);

        if(get(l1,r1)==get(l2,r2))puts("Yes");   //如果两端字符串的哈希值相等，则说明两端字符串相同
        else puts("No");
    }
    return 0;
}