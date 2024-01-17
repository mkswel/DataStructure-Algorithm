#include<iostream>
#include<cstring>
#include<stack>
#include<algorithm>
using namespace std;
/**
 * 将四则运算中缀表达式转成后缀表达式（一位数运算）
 * 遇到')'就一直出栈S1入S2直到遇到'('
 * 当S1为空或栈顶是'('或栈顶优先级绝对小于当前操作符时可以直接入栈S1
 * ，否则要一直出栈S1入S2(同一优先级也得出栈)到满足条件为止
 * 最后把S1余下全入S2
*/
string IPolishForm(string str){
    stack<char> S1, S2;//S1运算符栈 S2操作数栈
    for(int i = 0; i < str.length(); i++){
        if(str[i] - '0' >= 0 && str[i] - '0' <= 9)S2.push(str[i]);
        else {
            switch (str[i])
            {
            case '(':
                S1.push(str[i]);
                break;
            case ')':
                while(!S1.empty() && S1.top() != '(')
                    S2.push(S1.top()), S1.pop();
                if(!S1.empty())S1.pop();
                break;
            case '+':
            case '-':
                while(!S1.empty() && S1.top() != '(')
                    S2.push(S1.top()), S1.pop();
                S1.push(str[i]);
                break;
            case '*':
            case '/':
                while(!S1.empty() && S1.top() != '(' && 
                       S1.top() != '+' && S1.top() != '-')
                    S2.push(S1.top()), S1.pop();
                S1.push(str[i]);
                break;
            default:
                break;
            }
        }
    }
    while(!S1.empty())S2.push(S1.top()), S1.pop();
    string ans = "";
    while(!S2.empty())ans += S2.top(), S2.pop();
    reverse(ans.begin(), ans.end());
    return ans;
}

double cal(string str){
    stack<double> S3;
    for(int i = 0; i < str.length(); i++){
        if(str[i] - '0' >= 0 && str[i]- '0' <= 9)S3.push(str[i] - '0');
        else {
            switch (str[i])
            {
            case '+':
                if(S3.size() > 1){
                    double t = S3.top();S3.pop();
                    t = S3.top() + t;S3.pop();
                    S3.push(t);
                }
                break;
            case '-':
                if(S3.size() > 1){
                    double t = S3.top();S3.pop();
                    t = S3.top() - t;S3.pop();
                    S3.push(t);
                }
                break;
            case '*':
                if(S3.size() > 1){
                    double t = S3.top();S3.pop();
                    t = S3.top() * t;S3.pop();
                    S3.push(t);
                }
                break;
            case '/':
                if(S3.size() > 1){
                    double t = S3.top();S3.pop();
                    t = S3.top() / t;S3.pop();
                    S3.push(t);
                }
                break;
            default:
                break;
            }
        }
    }
    return S3.top();
}

int main(){
    string str = "1+1*1/1";
    cout<<IPolishForm(str)<<endl;
    cout<<cal(IPolishForm(str))<<endl;
    return 0;
}