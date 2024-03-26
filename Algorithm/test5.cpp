#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const int N = 5010;
int sum[N];
pair<int, int> minsum[N];
int main(){
    int n;
    while(cin>>n){
        for(int i = 0; i < n; i++)minsum[i].second = -1;
        for(int i = 0; i < n; i++){
            int a;
            scanf("%d", &a);
            sum[i] = a+(i ? sum[i-1] : 0);
            if(i){
                minsum[i].first = min(sum[i], minsum[i-1].first);//minsum[i]表示前i个数中前缀和最小的值
                minsum[i].second = sum[i]<minsum[i-1].first ? i : minsum[i-1].second;
            }
        }
        int maxsum = INT_MIN, left, right;
        for(int i = 0; i < n; i++){
            if(sum[i] - minsum[i].first > maxsum){
                maxsum = sum[i] - minsum[i].first;
                left = minsum[i].second+1;
                right = i;
            }
        }
        if(maxsum <= 0)cout<<"0 0 0"<<endl;
        else cout<<maxsum<<" "<<left<<" "<<right<<endl;
    }
}