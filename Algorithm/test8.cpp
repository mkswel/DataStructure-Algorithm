#include<iostream>
#include<cstring>
#include <chrono>
using namespace std;
const int N = 1010;
int g[N][N];
bool st[N];
typedef long long LL;
void dfs(int n, int &ans, LL &anslen, LL tmp = 0, int a = 1, int r = 1){
   if(a == 2 || tmp > anslen){
        if(a==2 && tmp < anslen){
                 anslen = tmp;
                 ans = 1;
                 return ;
        }
        else if (a==2 && tmp == anslen){
                ans++;
                return ;
        }
        else return;
   }  
   for(int i = 1; i <= n; i++){
       if(i != r && i != a && !st[i] && g[a][i]){
            st[i] = true;
            tmp += g[a][i];
            dfs(n, ans, anslen, tmp, i, a);
            st[i] = false;
            tmp -= g[a][i];
       }
   }
}

int main(){
    int n, m;
    cin>>n;
    auto start = std::chrono::steady_clock::now();
    while(n){
             cin>>m;
             for(int i = 0; i < m; i++){
                     int a, b, c;
                     scanf("%d%d%d", &a, &b, &c);
                     g[a][b] = c, g[b][a] = c;                  
             }
             int ans = 0;
             LL anslen = 36;
             memset(st, 0, sizeof st);
             st[1] = 1;
             dfs(n, ans, anslen);
             printf("%d\n", ans);
             cin>>n;
    }
    // 记录结束时间
    auto end = std::chrono::steady_clock::now();

    // 计算运行时间
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // 输出运行时间
    std::cout << "程序运行时间：" << duration << " 毫秒" << std::endl;

    return 0;
}
