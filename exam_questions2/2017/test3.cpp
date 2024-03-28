/*
3. 输入行数，再在每行输入一个表达式

输入示例：

3

1+1

2.2/3

1+2*3



输出示例：

2

0.7

7


*/

#include<iostream>
#include<stack>
#include<queue>
using namespace std;
const int N = 100;
typedef struct equ{
	bool isnum;//1为操作数，0为运算符 
	char oper;
	double num;	
	struct equ *next;
}equ;

equ* PreTransform(string str){
	equ *head = (equ*)malloc(sizeof(equ));
	equ *r = head;
	head->next = NULL;
	for(int i = 0; i < str.length(); i++){
		bool is_a_num = false;
		if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='('||str[i]==')'){
			is_a_num = false;
			equ *t = (equ*)malloc(sizeof(equ));
			t->isnum = false;
			t->oper = str[i];
			t->next = NULL;	
			r->next = t;
			r = t;
		}	
		else if(str[i]-'0'>=0&&str[i]-'0'<=9){
			if(is_a_num)r->num = 10*r->num+(str[i]-'0');
			else {
				is_a_num = true;
				equ *t = (equ*)malloc(sizeof(equ));
				t->isnum = true;
				t->num = str[i]-'0';
				t->next = NULL;
				r->next = t;
				r = t;
			}
		}
		else if(str[i]=='.'){
			double dec = 0;
			int n = 10, j;
			for(j = i+1; str[j]-'0'>=0&&str[j]-'9'<=0; j++){
				dec += (double)(str[j]-'0')/n;
				n*=10;
			}	
			r->num += dec;
			i = j-1;
		}
	}
	return head;
}

queue<equ*> IPolishForm(equ *E){
	stack<equ*> S1;//S1运算符栈，S2操作数栈 
	queue<equ*> S2;
	equ *head = (equ*)malloc(sizeof(equ));
	equ *s = E->next;
	while(s){
		if(s->isnum)S2.push(s);
		else {
			switch(s->oper){
				case '(':
					S1.push(s);
					break;
				case ')':
					while(!S1.empty()&&S1.top()->oper!='(')S2.push(S1.top()),S1.pop();	
					if(!S1.empty())S1.pop();
					break;
				case '+':
				case '-':
					while(!S1.empty()&&S1.top()->oper!='(')S2.push(S1.top()),S1.pop();	
					S1.push(s);
					break;
				case '*':
				case '/':
					while(!S1.empty()&&S1.top()->oper!='+'&&S1.top()->oper!='-'&&S1.top()->oper!='(')
						S2.push(S1.top()),S1.pop();	
					S1.push(s);
					break;
			}
		}
		s = s->next;	
	} 
	while(!S1.empty())S2.push(S1.top()),S1.pop();
	return S2;
}

double Calculate(queue<equ*> Q){
	stack<double> S3;
	while(!Q.empty()){
		auto t = Q.front();Q.pop();
		//if(t->isnum)cout<<t->num<<"  ";else cout<<t->oper<<"  ";
		if(t->isnum)S3.push(t->num);
		else if(S3.size()>1){
			double a, b;
			a = S3.top(), S3.pop();
			b = S3.top(), S3.pop();
			switch(t->oper){
				case '+':
					S3.push(b+a);
					break;
				case '-':
					S3.push(b-a);
					break;	
				case '*':
					S3.push(b*a);
					break;
				case '/':
					S3.push(b/a);
			}	
		}	
	}
	return S3.top();
}

int main(){
	int T;
	cin>>T;
	while(T--){
		string str;
		cin>>str;
		cout<<Calculate(IPolishForm(PreTransform(str)))<<endl;
	}
	system("pause");
}
