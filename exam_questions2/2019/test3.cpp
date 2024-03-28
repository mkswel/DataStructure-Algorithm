/*
3. 判断IP地址

输入n行字符串，判断输入的是否为合法的IP地址，如果是有效的IP输出yes，否则输出no

输入样例：

2

1.2.3.4

172.168.0.300

输出样例

yes

no


*/

#include<iostream>
using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        bool isvalid = true; 
        string str;
        cin>>str;
        int tmp = 0;
        for(int i = 0; i < str.length(); i++){
            if(str[i] == '.'){
                if(tmp > 255 || tmp < 0){
                    isvalid = false;
                    break;
                }
                else tmp = 0;
            }
            else tmp = 10 * tmp + str[i] - '0';
        }
        if(tmp > 255 || tmp < 0)isvalid = false;//最后判断一次 
        if(isvalid)cout<<"yes"<<endl;
        else cout<<"no"<<endl;
    } 
    system("pause");
}
