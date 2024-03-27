#include<iostream>
#include<cmath>
using namespace std;
const int N = 30;
int g[N][N];
bool st[N];
int n;
void DFS(int &ans, int &k, int &res, int v = 0){
	if(k == n){
		if(v == n-1){
			ans = min(ans, res);
			return;	
		}
	}
	if(v == n-1 && k < n)return;
	for(int i = 0; i < n; i++){
		if(!st[i] && g[v][i]){
			st[i]=true, k++;
			res += g[v][i];
			DFS(ans, k, res, i);
			res -= g[v][i];
			st[i]=false, k--;	
		}	
	}
}

int main(){
	cin>>n;
	for(int i = 0; i < n; i++)
	    for(int j = 0; j < n; j++)
	        cin>>g[i][j];
	int ans = 2e9, res = 0, k = 0;
	st[0]=1;
	DFS(ans, k, res);
	cout<<ans<<endl;
	return 0;
}
