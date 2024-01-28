#include<iostream>
#include<cstring>
using namespace std;
const int N = 10010;
int e[N], ne[N], h[N], idx;
bool st[N];
int res;
void add(int a, int b){
    e[idx]=b, ne[idx]=h[a], h[a]=idx++;
}
void dfs(int x, int d = 0){
    res = max(res, d);
    for(int i = h[x]; i != -1; i = ne[i]){//5  1  2  3
        if(!st[e[i]]){
            st[e[i]]=true;
            dfs(x, d+1);
            st[e[i]]=false;
        }
    }
}
int main(){
    memset(h, -1, sizeof(h));
    int n, root;
    cin>>n>>root;
    for(int i = 0; i < n-1; i++){
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }
    st[root]=true;
    dfs(root);
    cout<<res;
    return 0;
}