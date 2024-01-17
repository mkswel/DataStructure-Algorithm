#include<iostream>
#include<stack>
#include<cstring>
using namespace std;
const int N = 1000;
int e[N], ne[N], h[N], idx;
bool visited[N];
void add(int a, int b){  //a --> b
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}
void visit(int t){
    cout<<t<<'\t';
    //visited[t] = true;
};
void dfs_stack(){
    stack<int> st;
    st.push(1);
    visited[1] = true;
    while(!st.empty()){
        int t = st.top();st.pop();
        visit(t);
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(!visited[j])st.push(j), visited[j] = true;
        }
    }
}
int main(){
    memset(h, -1, sizeof h);
    int n;
    cin>>n;
    while(n--){
        int a, b;
        cin>>a>>b;
        add(a, b);
    }
    dfs_stack();
    return 0;
}

