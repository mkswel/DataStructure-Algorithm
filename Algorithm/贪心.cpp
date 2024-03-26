
//*******************************************************************************************
//区间选点
/*对于数轴上若干个闭区间，尝试选出最少数目的点，以保证在每个区间内都至少包含一个点*/

/*
思路：对每个区间按右端点大小进行排序，并规定：
从前往后遍历每个区间，如果当前区间内已经包含点，就直接跳过，否则选出它的右端点作为一个点
证明：记实际的最少点数为ans，按上述规定选出的点数为cnt
由于规定保证了每个区间内至少有一个点，故ans<=cnt；
1)对于区间和区间之间没有交集的一些区间，由于ans要保证每个区间内至少有一个点，而在该情况下，cnt总是会选出区间的右端点，故ans>=cnt
2)对于区间和区间之间有交集的一些区间，由于ans要保证每个区间内至少有一个点，
而在该情况下上一个区间的右端点总是会通过交集传给下一个区间，因此cnt总是跳过已包含上一区间右端点的区间，故ans>=cnt；
综上有ans=cnt;
*/


#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N=100010;
int n;
struct Range        //结构体表示每个区间(便于排序)
{
    int l,r;
    bool operator< (const Range &W)const  //升序
    {
        return r<W.r;
    }

}range[N];

int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        range[i]={l,r};
    }
    sort(range,range+n);
    int res=0,ed=-2e9;
    for(int i=0;i<n;i++)
       if(range[i].l>ed)  //判断下一个区间是否包含上一个点
       {
            res++;
            ed=range[i].r;
       }
    printf("%d\n",res);
    return 0;
}


//*******************************************************************************************
//最大不相交区间数量
/*对于数轴上若干个区间，尝试选出最多数目的区间，以保证选出的每个区间都互不产生交集*/
/*
思路：原理同上题：根据每个区间的右端点对每个区间排序，从前往后遍历每个区间，如果区间内包含点则跳过，否则挑出它的右端点，并选出这个区间。
*/
//代码完全同上。


//*******************************************************************************************
//区间分组
/*对于数轴上若干个区间，尝试将它们分成尽可能少的组，保证任一组内的各个区间之间不产生交集*/

/*
思路：将区间按左端点大小排序，从前往后遍历每个区间，判断能否将其放入现有的某个组中，即判断其左端点是否大于某个组的右端点。
若可以，将其放入，并更新组的右端点；若不行，另开一个新组
*/



#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int N=100010;

int n;
struct Range
{
    int l,r;
    bool operator<(const Range &W)const
    {
        return l<W.l;
    }
 
}range[N];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        range[i]={l,r};
    }
    sort(range,range+n);
    priority_queue<int,vector<int>,greater<int>>heap;     //小根堆表示现有组，每个节点表示一个组的最右端
    for(int i=0;i<n;i++)
    {
        auto r=range[i];
        if(heap.empty()||heap.top()>=r.l)heap.push(r.r); //如果当前区间小于现有所有组中右端点最小值，说明无法将它放入现有的任一组中，就为它开一个新组，并将其入堆
        else{
            int t=heap.top();
            heap.pop();      //否则更新堆顶节点
            heap.push(r.r);
        }

    }
    printf("%d\n",heap.size());
    return 0;
}




//*******************************************************************************************
//区间覆盖
/*对于数轴上若干个区间和一个指定区间，尝试利用尽可能少的区间去完全覆盖住这个指定区间，输出最少区间数，若无法完全覆盖，输出-1*/

/*
思路：将若干区间按左端点大小排序。记指定区间左端点为start,右端点为end;
依次遍历区间,每次选出包含start点且右端点最大的那个区间；
将start更新为选出的那个区间的右端点，判断start是否小于end，若是则继续循环，若否则终止。
*/

#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

const int N=100010;

int n;
struct Range
{
    int l,r;
    bool operator<(const Range &W)const
    {
        return l<W.l;
    }
}range[N];

int main()
{
    int st,ed;
    int res=0;
    scanf("%d%d",&st,&ed);
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        range[i]={l,r};
    }
    sort(range,range+n);
    int res=0;
    for(int i=0;i<n;i++)
    {
        int j=i,r=-2e9;
        while(j<n&&range[j].l<=st)    //找出左端点小于start的所有区间中的最大右端点
        {
            r=max(r,range[j].r);
            j++;
        }
        if(r<st){          //如果最大的右端点都小于start，说明无论怎样都有间隙，无法覆盖
            res=-1;
            break;
        }               
        if(r>=ed)break;//如果完全覆盖，结束
        st=r;          //更新start
        i=j-1;         //直接从当前start所在区间开始往后遍历

    }
    printf("%d\n",res);
}

//*******************************************************************************************
//合并果子
/*对于若干堆果子，每次将他们中的两堆合并成一堆，并消耗相对应的体力（果堆中果子数等于消耗体力数），最终将它们合并成一堆果子。问最少消耗体力数*/

/*
思路：类似于哈夫曼树。每次优先合并最小的两堆果子

*/

#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>

using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    
    priority_queue<int,vector<int>,greater<int>>heap;     //小根堆表示现有组，每个节点表示一个组的最右端
    while(n--)
    {
        int x;
        scanf("%d",&x);
        heap.push(x);

    }
    int res=0;
    while(heap.size()>1)
    {
        int a=heap.top();
        heap.pop();
        int b=heap.top();
        heap.pop();
        res+=a+b;
        heap.push(a+b);
    }
    printf("%d\n",res);
    return 0;

}