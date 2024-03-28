/*
1. 求积：给定n组数，每组两个整数，输出这两个整数的乘积。

Input：

2

1 1

2 3



Output:

1

6


*/
#include<iostream>
using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int a, b;
        cin>>a>>b;
        long long mul =  (long long)(a * b);
        cout<<mul<<endl;           
    }   
    system("pause");
}
