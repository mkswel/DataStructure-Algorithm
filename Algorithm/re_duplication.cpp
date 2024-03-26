#include<iostream>
using namespace std;
//冒泡 时间O(n), 空间O(n)
void bubble_sort(int A[], int n){
    for(int i = 0; i < n; i++){
        bool res = true;
        for(int j = n - 1; j > i; j--)
            if(A[j] < A[j - 1])swap(A[j], A[j - 1]), res = false;
        if(res)break;
    }
    for(int i = 0; i < n; i++)cout<<A[i]<<'\t';
    cout<<endl;
}

int re_dup(int A[], int n){//有序序列去重
    int i = 0;
    for(int j = 1; j < n; j++)if(A[i] != A[j])A[++i] = A[j];
    return i+1;
}

int main(){
    int a[] = {2, 3, 9, 4, 5, 6, 4, 3, 11, 11, 4, 3, 1, 1, 3, 6};
    bubble_sort(a, 14);
    int cnt = re_dup(a, 14);
    for(int i = 0; i <= cnt; i++)cout<<a[i]<<'\t';
    return 0;
}