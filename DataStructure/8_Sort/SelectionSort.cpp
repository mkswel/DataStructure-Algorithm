#include<stdio.h>
#include<iostream>
typedef int ElemType;
/** 简单选择排序
 * 每次找到最小的元素
 * 
 * 稳定性：不稳定
 * 
 * 空间复杂度：O(1)
 * 时间复杂度：O(n^2)
 * 复杂度与初始状态无关
 */ 
void SimpleSectionSort(int A[], int n){
    for(int i = 0; i < n - 1; i++){
        int min = i;
        for(int j = i + 1; j < n; j++)
            if(A[j] < A[min])min = j;
        if(min != i)std::swap(A[i], A[min]);
    }
}

/**
 * 堆排序
 * 大根堆：所有元素满足L(i)>=L(2i)且L(i)>=L(2i+1)
 * 小根堆：所有元素满足L(i)<=L(2i)且L(i)<=L(2i+1)
 * 
 * 空间复杂度：O(1)
 * 时间T复杂度：建堆O(n),n-1次向下调整，每次调整不超过O(h)，故堆排序O(nlog2(n))
 * 复杂度与初始状态无关
 * 
 * 稳定性：不稳定
 */ 
//将k为根的子树调整为大根堆  下沉操作
void HeapAdjust(ElemType A[], int k, int len){
    A[0] = A[k];  //A[0]暂存根结点
    for(int i = 2 * k; i <= len; i *= 2){
        if(i < len && A[i] < A[i + 1])i++; //比较k的两个孩子的大小
        if(A[0] >= A[i])break;//如果根已经比更大的孩子大，直接退出
        else {
            A[k] = A[i];   //根结点替换为i，同时继续调整它的子树
            k = i;
        }
    }
    A[k] = A[0];
}
//建立大根堆
void BuildMaxHeap(ElemType A[], int len){
    for(int i = len / 2;i > 0; i--)//自底向上，保证了对于下一个要调整的树而言，左右子树的最大值就是其左右孩子
        HeapAdjust(A, i, len);
}

//堆排序 每次把堆顶和堆底进行交换，得到的就是最大值
void HeapSort(ElemType A[], int len){
    BuildMaxHeap(A, len);
    for(int i = len; i > 1; i--){
        std::swap(A[i], A[1]);
        HeapAdjust(A, 1, i - 1);
    }
}

//大根堆的插入和删除
//插入：插到堆底，然后不断上升，每次上升只需跟自己的双亲对比一次
void HeapInsert(ElemType A[], int &len, int k){
    A[++len] = k;
    int t = len;
    A[0] = A[t];
    for(int i = t / 2; t > 0; t /= 2){
        if(A[0] <= A[i])break;
        else {
            A[t] = A[i];
            t = i;
        }
    }
    A[t] = A[0];
}
void HeapInsert2(ElemType A[], int &len, int k){
    A[++len] = k;
    int t = len;
    while(t>1 && A[t]>A[t/2])
        std::swap(A[t], A[t/2]), t /= 2;
}
//删除，将堆顶和堆底交换，然后删掉堆底，然后不断下坠，每次下坠比较1或2次

int main(){
    ElemType A[] = {-1, 53, 17, 78, 9,45, 65, 87, 32};
    HeapSort(A, 8);
    for(int i = 1; i <= 8; i++){
        std::cout<<A[i]<<'\t';
    }
    return 0;
}