#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 20;
int A[N][N];
int str[N];
int n, dis,res = 0x3f3f3f3f;

// void dfs(int u, int r, int dis = 0){
// 	// str[u] = true;
// 	if(u == 1 && r != 1){
// 		res = min(res,dis);
// 		return;
// 	}
	
// 	for(int i = 1; i <= n; i ++){
// 		if(A[u][i] != 0 && !str[i] && i != r){
// 			dis += A[u][i];
// 			str[u] = true;
// 			str[1] = 0;
// 			dfs(i,u, dis);
// 			dis -=A[u][i];
// 			str[u] = false;
// 		}
// 	}
	
// }
void dfs(int &k, int v0, int v, int dis = 0){
	int n = 4;
	if(k == n){
		if(v0 == v){
			res = min(res,dis);
			return ;
		}
	}
	for(int i = 1; i <= n; i ++){
		if(A[v][i] != 0 && !str[i]){
			dis += A[v][i];
			str[i] = true;
			k++;
			dfs(k, v0, i, dis);
			dis -=A[v][i];
			str[i] = false;
			k--;
		}
	}
}

int main(){
	cin >> n;
	
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++)cin>> A[i][j];
	}
	int k  = 0;
	dfs(k, 1, 1);
	
	cout<< res;
	return 0;
}