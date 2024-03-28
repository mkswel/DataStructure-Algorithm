/*
7. 判断括号是否匹配：给定n组数，每组为一个字符串，测试3种括号:{}、[]、()，且顺序只能是前左括号，后右括号，括号间可以嵌套。若匹配则输出yes，否则输出 no。



如：{@}[a](4)、{[0]}都是匹配的

{[[]}、{}{ 都是不匹配的



Input：

2

{a}[b](d)

{[(]}

Output：

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
		stack<int> S;//1是小括号，2是中括号，3是大括号 
		bool ismatch = true;
		string str;
		cin>>str;
		for(auto c:str){
			switch(c){
				case '{':
					S.push(3);
					break;
				case '[':
					S.push(2); 	
					break;
				case '(':
					S.push(1);
					break;
				case '}':
					if(!S.empty()&&S.top()==3)S.pop();
					else ismatch = false;
					break;
				case ']':
					if(!S.empty()&&S.top()==2)S.pop();
					else ismatch = false;
					break;
				case ')':
					if(!S.empty()&&S.top()==1)S.pop();
					else ismatch = false;
						 
			} 
			if(!ismatch)break;
		}
		if(S.empty() && ismatch)cout<<"yes"<<endl;//括号全部匹配完 
		else cout<<"no"<<endl;	
	}	
	system("pause");
}
