#include<iostream>
using namespace std;
/**
 * 冒泡排序Bubble Sort
 * 依次比较两个元素
 * 
 * 空间复杂度O(1)
 * 时间复杂度最好O(n)（原本有序）, 最坏O(n^2)（原本逆序）
 * 
 * 稳定性：稳定
 * 
 * 适用性：顺序存储或链式存储
 */ 
void BubbleSort(int A[], int n){
    for(int i = 0; i < n - 1; i++){  //每趟排序确定一个元素的位置
        bool flag = false;
        for(int j = n - 1; j > i; j--)
            if(A[j - 1] > A[j]){
                std::swap(A[j - 1], A[j]);
                flag = true;
            }
        if(flag == false)return;
    }
}

/**
 * 快速排序Quick Sort
 * 确定一个基准，把比基准小的移到基准左边，比基准大的移到基准右边，然后递归执行两侧区间，每次递归确定枢轴的最终位置
 * 
 * 空间复杂度最好O(log2(n))，最坏O(n)，平均O(log2(n))
 * 时间复杂度最好O(nlog2(n))（基本对称）,最坏O(n^2)（原本有序或逆序，即最不对称的情况），平均O(nlog2(n))
 * 
 * 稳定性：不稳定
 * 
 */ 
int Partition(int A[], int low, int high){
    int pivot = A[low];  //枢轴从low开始
    while(low < high){
        while(low < high && A[high] >= pivot)--high;  //从high开始不断左移直到找到比枢轴小的元素
        A[low] = A[high];     //将该元素填到low里
        while(low < high && A[low] <= pivot) ++low;  //从low开始不断右移直到找到比枢轴大的元素
        A[high] = A[low];     //将该元素填到high里
    }
    A[low] = pivot;        //存放枢轴的最终位置
    return low;           //返回枢轴位置
}
void QuickSort(int A[], int low, int high){
    if(low < high){
        int pivotpos = Partition(A, low, high);
        QuickSort(A, low, pivotpos - 1);
        QuickSort(A,pivotpos + 1, high);
    }
}