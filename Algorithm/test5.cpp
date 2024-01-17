#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
using namespace std;

vector<int> di;
int maxDivisor(int a, int b){
    unordered_set<int>hash1;
    int ans = 0;
    for(int i=1;i<=a/i;i++)  //遍历1~sqrt(n)中所有数
        if(a%i==0)           //找到约数
        {
            hash1.emplace(i);
            if(i!=a/i)hash1.emplace(a/i);  //找到另一个约数（不包括sqrt(n)）
        }
    for(int i=1;i<=b/i;i++)  //遍历1~sqrt(n)中所有数
        if(b%i==0)           //找到约数
        {
            di.push_back(i);
            if(i!=b/i)di.push_back(b/i);  //找到另一个约数（不包括sqrt(n)）
        }
    sort(di.begin(), di.end());
    for(int i = di.size()-1; i >= 0; i--)
        if(hash1.count(di[i]))return di[i];
        
}

int main(){
    int a, b;
    cout<<maxDivisor(a, b)<<" ";
}