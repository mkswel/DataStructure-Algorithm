#include<stdio.h>
#include<stdlib.h>
/**
 * 归并排序：将两个或两个以上有序表合成一个新的有序表
 * 二路归并：把两个已经有序的序列合并成一个，每一次比较就能确定一个元素的位置
 * 空间复杂度O(n)
 * 时间复杂度O(nlog2(n))，每趟归并O(n)
 * 复杂度与初始状态无关
 * 
 * 稳定性：稳定
 */ 
typedef int ElemType;
const int M = 100;
ElemType *B = (ElemType *)malloc((M + 1)*sizeof(ElemType));
void Merge(ElemType A[], int low, int mid, int high){  //把[low, mid],[mid+1, high]两个有序表合并
    int i, j, k;  //i是B中起点为low的指针，j是B中起点为mid+1的指针，k是A的起点为low指针
    for(k = low; k <= high; k++)   //先全复制到空数组B中
        B[k] = A[k];
    for(i = low, j = mid + 1,k = i; i <= mid && j <= high; k++){
        if(B[i] <= B[j])A[k] = B[i++];
        else A[k] = B[j++];
    }
    while(i <= mid)A[k++] = B[i++];  //两个while循环只会执行一个，用于把剩下的元素全部复制到A里
    while(j <= high)A[k++] = B[j++];
}
void MergeSort(ElemType A[], int low, int high){
    if(low < high){
        int mid = low + high >> 1;
        MergeSort(A, low, mid);
        MergeSort(A, mid + 1, high);
        Merge(A, low, mid, high);
    }
}



//-------------------基数排序 Radix Sort
/**
 * 基于关键字各位大小来排序
 * 假设一个r进制元素有d位，则建立r个辅助队列，
 * MSD：从高到低的执行每趟排序 LSD：从低到高
 * LSD为例：先将所有元素按最低位依次入每个队列，然后从最高位的队列依次出队完成一趟排序。
 *         如此执行完r位就得到递减序列
 * 空间复杂度：一趟需要辅助空间r(r个队列：r个队头和队尾指针),后续重复使用故O(r)
 * 时间复杂度：总共d趟分配收集，一趟分配O(n)，一趟收集O(r)，基数排序时间复杂度O(d(n+r))
 * 
 * 稳定性：稳定 
 * 
 * 适用范围：1、元素关键字可以方便拆分成d组，d较小
          2、每组关键字取值范围不大，r较小
          3、元素个数n较大
*/
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
typedef int ElemType;
const int N = 1000;
/**
 * 输入r,d,n分别是进制数，元素位数，元素个数，输入n个10进制元素,
 * 输出他们的有序序列
 * 局限：两两不同
*/
int h[N], e[N], ne[N], idx;
void radixsort(queue<ElemType> &data, int r, int d){
    queue<ElemType> qu[r];
    for(int ii = 1; ii <= d; ii++){  //进行d趟排序
        while(!data.empty()){       //把元素放到各队列
            ElemType t = data.front();data.pop();
            int i = h[t], j = d - ii;//低位优先
            while(i != -1 && j--)i = ne[i]; 
            if(i != -1)qu[e[i]].push(t);
        }
        for(int i = r-1; i >= 0; i--){  //把元素从各队列取出，因为是从最低位开始取，所以最终得到升序
            while(!qu[i].empty()){
                data.push(qu[i].front());
                qu[i].pop();
            }
        }
    }
    while(!data.empty()){
        cout<<data.front()<<'\t';
        data.pop();
    }
}

inline void convert(ElemType t, int r, int d){
    int tmp = 0;
    int p = t;
    while(d--){
        tmp = p % r;
        p /= r;
        e[idx] = tmp, ne[idx] = h[t], h[t] = idx++;
    } 
}

int main(){
    int r, d, n;
    cin>>r>>d>>n;
    memset(h, -1, sizeof(h));
    queue<ElemType> data;
    for(int i = 0; i < n; i++){
        ElemType a;
        cin>>a;
        convert(a, r, d);
        data.push(a);
    }
    if(r == 0)cout<<"no way"<<endl;
    else radixsort(data, r, d);
    return 0;
}

// 10 3 10 278 109 63 930 589 184 505 269 8 83