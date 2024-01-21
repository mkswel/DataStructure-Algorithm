#include<iostream>
#include<cstring>
#include<unordered_map>
#include<vector>
using namespace std;
typedef long long LL;
const int MOD = 1000000007;
const int N = 10010;
LL f[N];
int main(){
    int Q;
    cin>>Q;
    while(Q--){
        LL ans = 0;
        string s, t;
        cin>>s>>t;
        int n = t.length();
        memset(f, 0, sizeof(f));
        f[0]=1;
        unordered_map<char, vector<int>> strhash;
        for(int i = 0; i < n; i++){
            if(!strhash.count(t[i])){
                vector<int> val;
                val.push_back(i);
                strhash.emplace(t[i], val);
            }
            else {
                vector<int> &val = strhash.at(t[i]);
                val.push_back(i);
            }
        }
        for(int i = 0; i < s.length(); i++){
            if(strhash.count(s[i])){
                vector<int> &val=strhash.at(s[i]);
                for(int j = val.size()-1; j >= 0; j--){
                    int k = val[j];
                    if(k<n-1)f[k+1]+=f[k];
                    else ans+=f[k];
                }
            }
        }
        cout<<ans%MOD<<endl;
    }
}