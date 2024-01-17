#include<iostream>
#include<queue>
#include<ctime>
using  namespace std;

struct W{
    int a, b;  //a表示序号，b用于比较
};
struct cmp{
    bool operator()(const W &t1, const W &t2)const{
        return t1.b > t2.b; //小根堆
    }
};
priority_queue<W, vector<W>, cmp> heap;
/**
 * 程序用来测试priority_queue是否稳定，
 * 实现方法：让优先队列按小根堆方式存入若干有序的结构体变量，
 * 循环出队并比较b相同的a是否有序
*/
bool ifStable(){
    int n = 5;
    for(int i = 1; i <= n; i++){
        W t;
        t.a = i;
        t.b = rand()%20;
        heap.push(t);
    }
    bool ifs = true;
    while(heap.size() > 1){
        W t = heap.top();heap.pop();
        cout<<t.a<<'\t'<<t.b<<endl;
        if(t.b != heap.top().b)continue;
        if(t.a > heap.top().a){//按照入队顺序，应该是序号更小的先入队
            //cout<<t.a<<" "<<heap.top().a<<" "<<t.b<<"  ";
            ifs = false;
        }
    }
    return ifs;
}
int main(){
    unsigned seed;
    seed = time(0);
    srand(seed);
    int T = 20;
    for(int i = 1; i <= T; i++){
        if(ifStable()){
            cout<<"Stable"<<endl;
        }
        else{
            cout<<"Unstable"<<endl;
        }
    }
    
    return 0;
}