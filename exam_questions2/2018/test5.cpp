/*
5. 字符串反转：给定n组字符串，每组字符串个数不超过 20，输出每组字符串的反串Input：

3

nwpu

china

xian



Output：

upwn

anihc

naix


*/

#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	int T;
	cin>>T;
	while(T--){
		string str;
		cin>>str;
		reverse(str.begin(), str.end());
		cout<<str<<endl;	
	}	
	system("pause");
}
