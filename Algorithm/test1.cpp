#include<algorithm>
#include<queue>
using namespace std;

const int N = 100010;
int q[N];

int main(){
    int hh = 0, tt = -1;
    for(int i = 0; i < n; i++){
        while(hh <= tt && q[hh] < i - k + 1)hh++;
        while(hh <= tt && a[q[tt]] >= a[i])tt--;
        q[++tt] = a[i];

    }
}

int e[N], ne[N], head, idx;

void insert(int x){
    e[idx] = x, ne[idx] = head, head = idx++;
}

int ef(int []q, int n, int x){
    int l = 0, r = n - 1;
    while(l < r){
        int mid = l + r >> 1;
        if(q[mid] >= x)r = mid;
        else l = mid + 1;
    }
    return l;

}

int primes[N], cnt;
int st[N];

int get_primes(int n){
    for(int i = 2; i <= n; i++){
        if(!st[i])primes[cnt++] = i;
        for(int j = 0; primes[j] * i <= n; j++){
            st[primes[j] * i] = true;
            if(i % primes[j] == 0)break;
        }
    }
    return cnt;
}

typedef long long LL;
int quick_mi(int a, int k, int p){
    int res = 0;
    while(k){
        if(k & 1)res = (LL)res * a % p;
        k >> 1;
        a = (LL)a * a % p;
    }
    return res;
}


typedef long long LL;
int quick_mi(int a, int k, int p){
    int res = 0;
    while(k){
        if(k & 1)res = (LL)res * a % p;
        k >> 1;
        a = (LL)a * a % p;
    }
    return res;
}


//BFS
int map[M][M];
int d[M][M];
pair<int, int> q[N];

int bfs(){
    int hh = 0, tt = 0;
    q[0] = {0, 0};
    memset(d, -1, sizeof(d));
    d[0][0] = 0;
    while(hh <= tt){
        auto t = q[hh++];
        int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
        for(int i = 0; i < 4; i++){
            int x = t.first + dx[i], y = t.second + dy[i];
            if(x >= 0 && x < M && y >= 0 && y < M && 
                d[x][y] == -1 && map[x][y] = 1){
                    q[++tt] = {x, y};
                    d[x][y] = d[t.first][t.second] + 1;
                }
        }
    }
    return d[M - 1][M - 1];
}

//并查集
int p[N];
int find(int x){
    if(p[x] != x)p[x] = find(p[x]);
    return p[x];
}
//合并两个集合 p[x] = y;
priority_queue<int> qu;
unordered_map<int, int> hash;

