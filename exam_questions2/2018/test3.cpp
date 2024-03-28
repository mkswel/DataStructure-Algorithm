/*
3. C(n,m)：求出n个数中任取m个数的不同的取法个数

Input：

10 3

Output：

120
*/
#include<iostream>
using namespace std;
typedef long long LL;

//LL quick_mi(int a, int k){
//   LL res = 1;
//   while(k){
//       if(k & 1)res = res * a;
//       k = k >> 1;
//      a = a * a;         
//   }
//   return res;
//}

const int N = 1000;
LL c[N][N];

int main(){
	c[1][0]=1, c[1][1]=1;
    for(int i = 1; i < N; i++)
        for(int j = 0; j <= i; j++){
			if(j == 0 || j == i)c[i][j] = 1;
			else c[i][j] = c[i-1][j]+c[i-1][j-1];
		}
        		
    int n, m;
    cin>>n>>m;
    cout<<c[n][m]<<endl;
    system("pause");
}
