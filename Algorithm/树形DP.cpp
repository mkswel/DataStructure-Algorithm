/*
学校里的每个职员之间的关系用树结构来表示：父节点为子节点的直接上司。校长是根节点。
每个职员都有快乐指数H(i)，现要邀请若干位职员参加舞会，但职员不会和他的直接上司一起参加舞会。
现求一种方法邀请若干位职员，使得参加舞会的职员的快乐指数和为最大值。
*/

/*
思路：如果只尝试用一种状态，就无法描述职员和直接上司无法共存的条件：
假设状态为f[i],表示以i为根节点的树的理想方案，则f[i]理应分为两部分：包含根节点i的一类和不包含根节点i的一类。
记s(i)表示i的子节点，则不包含i的一类可以轻易表示为：sum(f[s(i)]);
但包含i的一类根据要求不能再含有其子节点s(i)，这就又需要将f[s(i)]划分为有无根节点的两类，导致问题复杂。

考虑用f[i,0],f[i,1]分别表示以i为根节点但不包含与包含点i的两种状态。
则f[i,0]=sum(max(f[s(i),1],f[s(i),0]));
  f[i,1]=sum(f[s(i),0])+H(i);
*/


#include<iostream>
#include<algorithm>
#include<cstring>


using namespace std;


const int N=6010;
int n;
int happy[N];
int e[N],ne[N],h[N],idx;     //邻接表存树中数据
int f[N][2];   //两类状态
bool have_father[N];   //判断是否有父节点（用于找校长）


void add(int a,int b)
{
    e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void dfs(int u)     //从根为u的树开始递归
{
    f[u][1]=happy[u];           //每次包含根节点的一类都要算上根的快乐指数
    for(int i=h[u];i!=-1;i=ne[i])  //从根本身开始遍历所有子节点
    {
        int j=e[i];
        dfs(j);                   //递归子节点，直到叶子节点
        f[u][0]+=max(f[j][0],f[j][1]);   //累加所有子节点的情况
        f[u][1]+=f[j][0];
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&happy[i]);
    memset(h,-1,sizeof h);
    for(int i=0;i<n-1;i++)  //由于校长没有父节点，故只要n-1次
    {
        int a,b;
        scanf("%d%d",&a,&b);
        have_father[a]=true;
        add(b,a);                  //邻接表存储树中数据
    }

    int root=1;
    while(have_father[root])root++;   //找到校长
    dfs(root);                //从校长开始递归


    printf("%d\n",max(f[root][0],f[root][1]));   //输出整棵树的情况
    return 0;
}