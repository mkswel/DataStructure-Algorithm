#include<stdio.h>
#define SIZE 100
int UFSets[SIZE];

void Inital(int S[]){
    for(int i = 0; i < SIZE; i++)
        S[i] = -1;
}
//最坏O(n)
int Find(int S[], int x){
    while(S[x] >= 0)
        x = S[x];
        return x;
}

void Union(int S[], int root1, int root2){
    if(root1 == root2)return;
    S[root2] = root1;
}

//树高不超过[log2(n)]（下取整）+1  因此Find()操作不超过O(log2(n))
void Union_(int S[], int root1, int root2){
    if(root1 == root2)return ;
    if(S[root2] > S[root1]){//因为根都初始化为-1，故只会越加越小，则更大的数代表结点数更少
        S[root1] += S[root2];
        S[root2] = root1;
    }
    else {
        S[root2] += S[root1];
        S[root1] = root2;
    }
}

//压缩路径     使Find操作，也即树高O(a(n))  (a(n)一般小于4)
int Find_(int S[], int x){
    int root = x;
    while(S[root] >= 0)root = S[root];
    while(x != root){  //一路往上把结点都挂到根节点上
        int t = S[x];
        S[x] = root;
        x = t;
    }
    return root;
}