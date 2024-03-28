/*
2. 输入三角形的三条边，判断它们能否构成三角形，如果不能，输出NaN,如果能，输出三角形面积，结果保留两位小数。

输入样例：

2

1.0  2.0  3.0

3.0  4.0  5.0



输出样例

NaN

6.00
*/
#include<iostream>
#include<cmath>
using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        bool iftri = false;
        double a, b, c, S = 0;
        cin>>a>>b>>c;
        if(a+b>c && a+c>b && b+c>a)iftri = true;
        if(iftri){
            double len = (a+b+c)/2;
            S = sqrt(len*(len-a)*(len-b)*(len-c));
            printf("%.2f\n", S);
        }
        else cout<<"NaN"<<endl;
    }   
    system("pause");
}
