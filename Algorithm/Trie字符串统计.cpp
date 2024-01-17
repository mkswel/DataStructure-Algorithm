
/*树的字符串统计
  可将字符串插入树中，可查询某字符串出现次数
*/
#include<iostream>
using namespace std;


const int N=100010;

int n;  //进行n次操作
int son[N][26],qu[N],idex;//son[i][26]表示i节点应有26个子节点，qn[i]记录该字符串出现次数，idex表示当前用到结点
char str[N];
void insert(char str[])   //在树中插入一个字符串，如果重复则该字符串出现次数加一
{
    int p=0;      //默认从根节点开始
    for(int i=0;str[i];i++) //对字符串遍历
    {
        int u=str[i]-'a';  //将各小写字母映射为0-25的数字
        if(!son[p][u])son[p][u]=++idex;  //如果p节点的第u个子节点不存在，则创造一个
        p=son[p][u]; //更新为子节点

    }
    qu[p]++;//字符串出现次数加一
    
}

int query(char str[])  //查询字符串出现次数
{
    int p=0;    //默认从根节点开始
    for(int i=0;str[i];i++)
    {
        int u=str[i]-'a';
        if(!son[p][u])return 0;  //如果子节点不存在，返回0，表示并未出现（字符串的最后一个字符也会有子节点，只不过用不到）
        p=son[p][u];       //指向子节点
    }

    return qu[p];  //返回字符串出现次数
}

int main()
{
    scanf("%d",&n);
    while(n--)
    {
        char op[2];   //指定操作类型，输入insert执行插入操作，输入query执行查询操作
        scanf("%s%s",op,str);
        if(op[0]=='insert')insert(str);
        else if(op[0]=='query')printf("%d\n",query(str));
        return 0;
    }
}