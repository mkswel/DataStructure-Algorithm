#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int N = 1000;
int e[N], h[N], ne[N], w[N], idx;  //邻接表
int ie[N], ih[N], ine[N];          //逆邻接表
int ve[N],vl[N], ae[N], al[N];     //最早开始时间和最迟开始时间
int rd[N], cd[N];                  //入度出度
int path[N], display[N];           //存关键路径

//建立邻接表和逆邻接表
void add(int a, int b, int c){
    e[idx] = b, w[idx] = c,ne[idx]= h[a], h[a] = idx;
    ie[idx] = a, ine[idx] = ih[b], ih[b] = idx++;
    rd[b]++,cd[a]++;
}

//求所有点的最早开始时间顺带判断是否有环
bool get_ve(int m){
    queue<int> qu;
    qu.push(1);
    // for(int i = 1; i <= m; i++)
    //     if(rd[i] == 0)qu.push(i);
    while(!qu.empty()){
        int t = qu.front();
        qu.pop();
        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            ve[j] = max(ve[j], ve[t] + w[i]);
            if(--rd[j] == 0)qu.push(j);
        }        
    }
    for(int i = 1; i <= m; i++)if(rd[i])return false;
    return true;
}

//求所有点的最迟开始时间
void get_vl(int m){
    queue<int> qu;
    for(int i = 1; i<= m; i++)vl[i] = ve[m];//全部变成最长时间，便于后面的min(,)比较
    qu.push(m);
    // for(int i = m; i>= 1; i--)
    //     if(cd[i] == 0)qu.push(i);
    while(!qu.empty()){
        int t = qu.front();
        qu.pop();
        for(int i = ih[t]; i != -1;i = ine[i]){
            int j = ie[i];
            vl[j] = min(vl[j], vl[t] - w[i]);
            if(--cd[j] == 0)qu.push(j);
        }
    }
}

//深搜输出所有关键路径
void dfs(int a, int &m, int cnt){
    if(a == m){
        cout<<1<<'\t';
        for(int i = 0; i < cnt; i++)
            cout<<display[i]<<'\t';
        cout<<endl;
        return;
    }
    for(int i = h[a]; i != -1; i = ne[i]){
        if(path[i] == 0){
            display[cnt] = e[i];
            dfs(e[i], m, cnt + 1);
        }
    }
}

//求每个活动的最早和最迟开始时间
void get_criticalpath(int m){
    for(int i = 1; i<= m; i++){
        for(int j = h[i]; j != -1; j = ne[j]){
            ae[j] = ve[i];
            al[j] = vl[e[j]] - w[j];
            path[j] = al[j] - ae[j];
        }
    }
    dfs(1, m, 0);
}


/**
 * 读入n=边数, m=点数
 * 后面n次读入有向边的起点 终点 权值
 * 输出从源点1到汇点m的所有关键路径序列
 */ 
int main(){
    memset(h, -1, sizeof h);
    memset(ih, -1, sizeof ih);
    int n, m;
    cin>>n>>m;
    while(n--){
        int a, b, w; //从a到b
        cin>>a>>b>>w;
        add(a,b,w);
    }
    if(get_ve(m)){
        get_vl(m);
        get_criticalpath(m);
    }
    else
        cout<<"这不是有向无环图"<<endl;
    return 0;
}

//王道样例
// 8 6
// 1 2 3
// 1 3 2
// 2 4 2
// 2 5 3
// 3 4 4
// 3 6 3
// 4 6 2
// 5 6 1

//两条关键路径
// 7 6
// 1 2 1
// 1 3 3
// 2 3 2
// 3 4 2
// 3 5 1
// 4 6 2
// 5 6 2

//有环
// 4 4
// 1 2 1
// 2 3 2
// 3 4 1
// 4 2 1