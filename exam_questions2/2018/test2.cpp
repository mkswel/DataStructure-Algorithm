/*
2. 阶乘：给定n组数，每组一个整数，输出该组数的阶乘

Input：

2

3

5



Output：

6

120


*/

#include<iostream>
using namespace std;
typedef long long LL;
const int N = 20;
LL fac[N];
int main(){
    fac[0] = 1;
    for(int i = 1; i < N; i++)fac[i] = fac[i-1]*i;
    int T;
    cin>>T;
    while(T--){
        int k;
        cin>>k;
        cout<<fac[k]<<endl;           
    }   
    system("pause");
}
