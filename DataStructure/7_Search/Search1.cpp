#include<stdio.h>
typedef int ElemType;
const ElemType MaxSize = 100;
typedef struct 
{
    ElemType elem[MaxSize];
    int TableLen;
}SSTable;

int Binary_Sraech(SSTable L, ElemType key){
    int low = 0, high = L.TableLen - 1,mid;
    while(low <= high){
        mid = (low + high)/2;
        if(L.elem[mid] == key)return mid;
        else if(L.elem[mid] > key)high = mid - 1;
        else low = mid + 1;
    }
    return -1;
}