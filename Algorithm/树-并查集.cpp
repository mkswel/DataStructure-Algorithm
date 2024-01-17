/*并查集
  1、将两个集合合并
  2、询问两个元素是否在一个集合中

**原理：集合用树表示，树根编号为集合编号；每个节点存储它的父节点
  1）判断树根：if(p[x]==x)
  2）求x所在的集合编号：while(p[x]!=x)x=p[x];  （优化：路径压缩）
  3）合并两个集合：p[x]=y  （让x树成为y的子树）

*/

#include<iostream>
using namespace std;

const int N=100010;
int n,m; //最初有n个集合，每个集合中有1个元素，分别为1-n；进行m次操作
int p[N];   //父节点

int find(int x)          //**求x所在集合编号（即根节点）,并实现路径压缩（将从x到根节点上所有节点全部改成直接指向根节点）
{
    if(p[x]!=x)p[x]=find(p[x]);//若不为根节点，则将前节点的父节点更新为父节点的父节点
    return p[x];           //每次返回当前节点的父节点
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)p[i]=i;
    while(m--)
    {
        char op[2];
        int a,b;
        scanf("%s%d%d",op,&a,&b);
        if(op[0]=='M')p[find(a)]=find(b); //如果输入M，将a所在集合与b所在集合结合
        else
        {
            if(find(a)==find(b))puts("Yes");  //查询，如果a,b在同一集合，返回yes，否则no
            else puts("No");
        }
    }
    return 0;
}