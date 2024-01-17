#include<stdio.h>
/**
 * 插入排序
 * 空间复杂度O(1)
 * 时间复杂度最好O(n)（本来就升序），最坏O(n^2)（原本逆序）
 * 稳定性：稳定
 * 适用性：顺序存储和链式存储的线性表
 */

/**
 * 直接插入排序Direct Insertion Sort（升序）
 * 每次遍历到一个无序的元素k就从k的前一位开始依次后移一格，直到遇到比k小的元素，再将k插入
 */
void DirectInsertSort(int A[], int n){
    int i, j, temp;
    for(i = 1; i < n; i++) //每次循环都将使有序数量加1
        if(A[i] < A[i - 1]){ //遇到不满足升序的元素就将之暂存
            temp = A[i];
            for(j = i - 1; j >= 0 && A[j] > temp; j--) //将其之前的元素依次后挪
                A[j + 1] = A[j];
            A[j + 1]=temp;
        }
} 

/**
 * 折半插入排序Half Insortion Sort
 * 在直接插排的基础上，对已经有序的序列用二分来确定位置
 */
void HalfInsertSort(int A[], int n){
    int i, j, low, high, mid;
    for(i = 2; i <= n; i++){  //A[0]作为哨兵并暂存，所以排序是从A[1]到A[n]
        A[0] = A[i];
        low = 1, high = i - 1;
        while(low <= high){
            mid = low + high >> 1;
            if(A[mid] > A[0])high = mid - 1;
            else low = mid + 1;     //为保证排序稳定
        }
        for(j = i - 1; j >= high + 1; j--) //由于还要移动，所以时间复杂度不变（链表则只能顺序查找也依然不变）
            A[j + 1] = A[j];
        A[high + 1] = A[0];
    }
}