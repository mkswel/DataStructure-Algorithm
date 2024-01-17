/*离散化-区间和并
  将n个区间合并（区间之间有交集或边界重合则可以合并，否则跳过）输出合并完后区间的个数
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int,int> PII;

const int N=100010;

int n;   //有n个区间
vector<PII>segs;    //区间的两端点


void merge(vector<PII>&segs)  //区间和并
{
    vector<PII>res;                 //存放合并后的区间
    sort(segs.begin(),segs.end());  //将所有区间端点下标递增排序（先按l大小排，再按r大小排）
    int st=-2e9,ed=-2e9;            //默认区间端点初值为负无穷
    for(auto seg:segs)              //遍历segs
    {
        if(ed<seg.first)            //如果当前区间右端点小于下一个区间左端点
        {
            if(st!=-2e9)res.push_back({st,ed});  //就将当前区间存入res
            st=seg.first,ed=seg.second;          //更新到下一个区间
        }
        else ed=max(ed,seg.second);     //否则将当前区间的右端点更新
        
    }
    if(st!=-2e9)res.push_back({st,ed});  //将最后一个区间存入res（上述遍历还差最后一个区间）
    segs=res;       //将segs更新为合并完成的结果

}

/*原理：当前区间与下一个区间的关系只有三种情况：
（1）两区间无交集（直接前进到下一个区间）；
（2）下一个区间右端点大于当前区间右端点（更新后区间长度增加）；
（3）下一个区间右端点小于当前区间右端点（更新后区间长度不变）；
*/

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        segs.push_back({l,r}); //将每次输入的端点存入segs
    }
    merge(segs);    //进行区间和并操作

    printf("%d\n",segs.size());   //输出最终区间个数




    return 0;
}