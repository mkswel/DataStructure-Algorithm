/*
1. 排序：输入n，有n组测试数据

输入样例：

2
5 7 3 2 11 23 6 33
9 8 5 2 1 3 0 4

输出样例

2 3 5 6 7 11 23 33

0 1 2 3 4 5 8 9
*/

#include<iostream>
#include<algorithm>
using namespace std;
const int N = 100;
int A[N];
int main(){
    int T;
    cin>>T;
    while(T--){
        string str;
        getline(cin, str);
        int n = 0, tmp = 0;
        for(int i = 0; i < str.length(); i++){
            if(str[i] = ' '){
                A[n++] = tmp;
                tmp = 0;
            }
            else{
                tmp = tmp * 10 + str[i] - '0';
            }
        }
        A[n] = tmp;
        sort(A, A+n);
        for(int i = 0; i < n; i++)printf("%d ", A[i]);
        cout<<endl;
    }
    system("pause");
}
