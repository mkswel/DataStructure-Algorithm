/*
4. 输入两个日期，求两个日期之间的天数，如果两个日期是连续的我们规定他们之间的天数为两天，输入n组数据进行测试。

输入样例：

2

2019 3 20 2019 3 21

2019 1 1 2019 2 28

输出样例

2

59


*/
#include<iostream>
using namespace std;
int month[12] = {31, 28, 31,30, 31, 30, 31, 31, 30, 31, 30, 31};

bool rn(int i){return (i%400 == 0) || (i%100!=0 && i%4==0);}

int dn(int y1, int m1, int d1, int y2, int m2, int d2){
    int daynum = 0;
    if(y2>y1){
        for(int i = y1+1; i <= y2-1; i++){daynum+=365;if(rn(i))daynum++;}
        if(rn(y2))month[1]=29;else month[1]=28;
        for(int i = 1; i < m2; i++)daynum+=month[i-1];
        daynum+=d2;
        if(rn(y1))month[1]=29;else month[1]=28;
        for(int i = m1+1; i <= 12; i++)daynum+=month[i-1];
        daynum+=month[m1-1]-d1+1;
    }
    else if(y2==y1 && m2>m1){
         if(rn(y1))month[1]=29;else month[1]=28;
         for(int i = m1+1; i <= m2-1; i++)daynum+=month[i-1];
         daynum+=d2+month[m1-1]-d1+1;
    }
    else if(y2==y1 && m2==m1 && d2>=d1){
         daynum+=d2-d1+1;
    }
    else return dn(y2,m2,d2,y1,m1,d1);
    return daynum;
}


int main(){
    int T;
    cin>>T;
    while(T--){
        int y1, m1, d1, y2, m2, d2;
        cin>>y1>>m1>>d1>>y2>>m2>>d2; 
        cout<<dn(y1,m1,d1,y2,m2,d2)<<endl;
    }
    system("pause");
}
