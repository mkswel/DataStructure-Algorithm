/*离散化-区间和
  先进行n次操作，每次在数轴某一处x上加c（最初数轴上所有数据为0）
  再进行m次询问，询问包含整数l和r，要求区间[l,r]之间所有数的和
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int N=100010;

int n,m; //n次插入，m次询问
int a[N],s[N];  //a[]表示数轴上的数据，s[]表示a[]前缀和
typedef pair<int,int> PII;      //更名

vector<int>alls;         //存储离散化的下标（只需存储所有出现过的下标，所有计算都在这些下标处进行）
vector<PII>add,query;    //add表示插入操作，query表示询问操作

int find(int x)         //二分查找离散化后的下标的位置
{
    int l=0,r=alls.size()-1;
    while(l<r)
    {
        int mid=l+r>>1;
        if(alls[mid]>=x)r=mid;
        else l=mid+1;
    }
    return r;

}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        int x,c;
        scanf("%d%d",&x,&c);
        add.push_back({x,c});  //将插入位置x与插入值c存储到add中
        alls.push_back(x);     //将插入位置x（也即下标）存储到alls中（离散化）
    }
    for(int i=0;i<m;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        query.push_back({l,r});  //将m次的区间端点l,r存储到query中
        alls.push_back(l);       //由于l,r也是下标，所以与x一样存储与alls中（离散化）
        alls.push_back(r);
    }

    sort(alls.begin(),alls.end());    //***将alls中的下标排序
    alls.erase(unique(alls.begin(),alls.end()),alls.end());  //***将排序后的下标去重，此时alls为经过排序、去重的一组下标

    for(auto item:add)        //实现插入操作
    {
        int x=find(item.first);  //在alls中找到要插入数据的位置（下标）
        a[x]+=item.second;       //在找到的位置上加上数据
    }

    for(int i=1;i<alls.size();i++)   //预处理前缀和，为后面输出区间内数的和做准备
    s[i]=s[i-1]+a[i];

    for(auto item:query)    //实现查询操作
    {
        int l=find(item.first),r=find(item.second);  //在alls中找到各区间端点
        int p=s[r]-s[l-1];
        printf("%d\n",p);       //输出区间[l,r]内数的和
        
    }
    return 0;




}