#include<stdio.h>
int nsum_for(int n){
    int i, a[n];
    int result = 0;
    for(i = 0; i < n; i++){
        a[i] = i;
        result += a[i];
    }
    return result;
}
int main(){
    int ans = nsum_for(7);
    printf("%d\n", ans);
    return 0;
}