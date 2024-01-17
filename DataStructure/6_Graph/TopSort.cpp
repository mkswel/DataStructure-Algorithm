#include<stdio.h>
#include<iostream>
#include<cstring>
#include<stack>
#include<queue>
using namespace std;

const int N = 1000;
int h[N], e[N], ne[N],idx;
int d[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a], h[a] = idx++;
}
bool topsort_queue(int n){
    memset(h, -1, sizeof h);
    queue<int> qu;
    int cnt = n;
    for(int i = 1; i <= n; i++)
        if(d[i] == 0)qu.push(i);
    while(!qu.empty()){
        int t = qu.front();
        qu.pop();
        cout<<t<<'\t';
        cnt--;
        for(int i = h[t]; i != -1; i = ne[i]){
            d[e[i]]--;
            if(d[e[i]] == 0){
                qu.push(e[i]);
            }
        }
    }
    if(cnt > 0)return false;
    return true;
}
bool topsort_stack(int n){
    stack<int> st;
    int cnt = n;
    for(int i = 1; i <= n; i++)
        if(d[i] == 0)st.push(i);
    while(!st.empty()){
        int t = st.top();
        st.pop();
        cout<<t<<'\t';
        cnt--;
        for(int i = h[t]; i != -1; i = ne[i]){
            d[e[i]]--;
            if(d[e[i]] == 0){
                st.push(e[i]);
            }
        }
    }
    if(cnt > 0)return false;
    return true;
}
