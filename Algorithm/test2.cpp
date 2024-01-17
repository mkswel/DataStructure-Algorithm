#include<iostream> 
using namespace std;

void re_dup(int A[], int &n){
    int i = 0;
    for(int j = 1; j < n; j++)
        if(A[i] != A[j])A[++i] = A[j];
    n = i + 1;
}
int f(int n){
    return f(n+1);
}
int main(){
    //int n = 15;
    //int A[15] = {1,1,2,2,3,3,3,4,5,6,6,7,7,8,9};
    //re_dup(A, n);
    //for(int i = 0; i < n; i++)cout<<A[i]<<" ";
    f(0);
    return 0;
}