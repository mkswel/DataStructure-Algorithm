/*
6. 判断是否“回文”：给定n组字符串，对每一组字符申判断是否回文(从左往右看、从右往左看都一样，包括空格、英文、数字、符号)，若是则输出yes，否则输出 no

Input：

4

nwpu

madam

1001

xiix



Output:

no

yes

yes

yes


*/
#include<iostream>
using namespace std;

bool ishw(string str){
	int n = str.length();
	for(int i = 0, j = n - 1; i <= j; i++, j--)if(str[i]!=str[j])return false;
	return true;
}

int main(){
	int n;
	cin>>n;
	while(n--){
		string str;
		cin>>str;
		if(ishw(str))cout<<"yes"<<endl;
		else cout<<"no"<<endl;	
	}
	system("pause");
}
		
