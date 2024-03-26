#include<iostream>
#include<set>
using namespace std;
const int N = 10010;
bool st[N];
set<int> primes;
set<int> facai;
//从8层开始，到20层（前10000最大18层）
void dfs(int k, int n = 1){
    if(!k){
        facai.emplace(n);
        return ;
    }
    for(auto prime:primes){
        dfs(k-1, n * prime);
    }
}


int main(){
    for(int i = 2; i < N && primes.size() < 400; i++){
        if(!st[i])primes.emplace(i);
        for(auto j = primes.begin(); *j <= N / i; j++){
            st[*j * i] = true;
            if(i % *j == 0)break;
        }
    }
    cout<<primes.size();
    for(int i = 8; i < 20; i++)dfs(i);
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(auto k = facai.begin(); k != facai.end(); k++, n--){
            if(!n){
                cout<<*k<<endl;
                break;
            }
        }
    }
}