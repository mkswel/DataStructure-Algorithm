/*
4. 括号匹配，输入测试数目n，接着n行输入n组样例

输入样例：

2

([3])

([[[)



输出样例：

yes

no
*/
#include<iostream>
#include<stack>
using namespace std;

int main(){
	int T;
	cin>>T;
	while(T--){
		stack<int> S;//0:() 1:[]
		bool ismatch = true;
		char c;
		while(cin>>c){
			switch(c){
				case '(':
					S.push(0);
					break;
				case '[':
					S.push(1);
					break;
				case ')':
					if(!S.empty()&&S.top()==0)S.pop();
					else ismatch = false;
					break;
				case ']':
					if(!S.empty()&&S.top()==1)S.pop();
					else ismatch = false;
			}
			if(!ismatch)break;
			if(cin.get()=='\n')break; 
		}	
		if(S.empty()&&ismatch)cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}	
	system("pause");
}
