/*
4. 给定n组数，每组数有m个，对每一组数从小到大排序输出

Input：

2 4

3 5 2 8

2 7 9 8

Output：

2 3 5 8

2 7 8 9


*/
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	int T, n;
	cin>>T>>n;
	int A[n];
	while(T--){
		for(int i = 0; i < n; i++)scanf("%d", &A[i]);
		sort(A, A+n);
		for(int i = 0; i < n; i++)printf("%d ", A[i]);
		cout<<endl;
	}	
	system("pause");
}
