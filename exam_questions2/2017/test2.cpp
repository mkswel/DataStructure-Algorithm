/*
2. 排序。输入n，有n组测试数



输入样例：

2

1 4 7 2 5

8 9 4 3



输出样例：

1 2 4 5 7

3 4 8 9


*/
#include<iostream>
#include<algorithm>
using namespace std;
const int N = 1000;
int A[N];
int main(){
	int T;
	cin>>T;
	while(T--){
		int n = 0;
		while(cin>>A[n++])//cin>>会直接跳过缓冲区的空格、tab、换行符，但是cin.get()和getline不会 
			if(cin.get()=='\n')break;	
		sort(A, A+n);
		for(int i = 0; i < n; i++)cout<<A[i]<<" ";
		cout<<endl;
	}	
	system("pause");
}
