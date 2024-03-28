/*
5. 输出从M开始的N个素数

输入样例：

2  5

输出样例

3

5

7

11

13

*/
#include<iostream>
#include<set>
using namespace std;
const int N = 1000;
bool st[N];
//int primes[N], cnt;
set<int> primes;
/*
void get_primes(int n){
     for(int i = 2; i <= n; i++){
             if(!st[i])primes[cnt++] = i;
             for(int j = 0; primes[j] <= n / i; j++){
                     st[primes[j]*i] = true;
                     if(i % primes[j] == 0)break;        
             }        
     }     
}
int main(){
    get_primes(N-10);
    int a, n;
    cin>>a>>n;
    for(int i = 0; i < cnt; i++){
            if(primes[i] > a){
                cout<<primes[i]<<endl;
                n--;
            }
            if(n==0)break;
    }
    system("pause");
}

*/
void get_primes(int n){
     for(int i = 2; i <= n; i++){
             if(!st[i])primes.emplace(i);
             for(auto k = primes.begin(); *k <= n / i; k++){
                     st[(*k)*i] = true;
                     if(i%(*k)==0)break;        
             }        
     }     
}

int main(){
    get_primes(N-10);
    int a, n;
    cin>>a>>n;
    for(auto k:primes){
            if(k > a){
                cout<<k<<endl;
                n--;
            }
            if(n==0)break;
    }
    system("pause");
}
