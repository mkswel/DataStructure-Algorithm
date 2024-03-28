/*
1. 输入两组时间(时h，分m，秒s)，计算平均时间，两组时间差不超过1小时，h在0-11间。

输入样例：

1 20 30 1 30 30

0 20 30 11 30 30



输出样例：

1 25 30

11 55 30


*/
#include<iostream>
using namespace std;

int main(){
	int h1, m1, s1, h2, m2, s2;
	while(cin>>h1){
		cin>>m1>>s1>>h2>>m2>>s2;
		int t1 = 3600*h1+60*m1+s1, t2 = 3600*h2+60*m2+s2;
		int mean = t1 + t2 >> 1;
		if(t1-t2>3600||t2-t1>3600)mean += 12*3600/2;//0点即12点 
		cout<<mean/3600<<" "<<(mean%3600)/60<<" "<<(mean%3600)%60<<endl;
	}	
	system("pause");
}
