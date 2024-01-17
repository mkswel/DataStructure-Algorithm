#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<queue>
using namespace std;
typedef int ElemType; 
typedef struct Huffman{
    ElemType weight;
    struct Huffman *lchild, *rchild;
    char letter;
}HuffmanNode, *HuffmanTree;
/**
 * 自定义小根堆按权值排序
 */ 
struct cmp{
        bool operator()(HuffmanTree t1,HuffmanTree t2) const{
            return t1->weight > t2->weight;//小根堆
        }
};
typedef priority_queue<HuffmanTree, vector<HuffmanTree>, cmp > HEAP;
HEAP heap;
//构造哈夫曼树
HuffmanTree CreateHuffmanTree(){
    while(heap.size() > 1){
        HuffmanTree t1 = heap.top();heap.pop();
        HuffmanTree t2 = heap.top();heap.pop();
        HuffmanTree T = new HuffmanNode;
        T->weight = t1->weight + t2->weight;
        T->lchild = t1;
        T->rchild = t2;
        heap.push(T);
    }
    return heap.top();    
}

//读入结点
void read(int n){
    while(n--){
        int a;
        scanf("%d", &a);
        HuffmanTree p = (HuffmanTree)malloc(sizeof(HuffmanNode));
        p->weight = a;
        p->lchild = NULL;
        p->rchild = NULL;
        heap.push(p);
    }
}

//后序遍历并求出WPL
int PostOrder(HuffmanTree T, int k=0){
    if(T == NULL)return 0;
    int WPLl = PostOrder(T->lchild, k + 1);
    int WPLr = PostOrder(T->rchild, k + 1);
    cout<<T->weight<<endl;
    if(!T->lchild&&!T->rchild)return (T->weight)*k;
    return WPLl + WPLr;
}
//中序遍历
void InOrder(HuffmanTree T){
    if(T == NULL)return ;
    InOrder(T->lchild);
    cout<<T->weight<<endl;
    InOrder(T->rchild);
}
/**
 * 先输入结点个数，再输入各结点权值，将返回哈夫曼树的后序序列和中序序列以及WPL
 */ 
// int main(){
//     int n;
//     scanf("%d", &n);
//     read(n);
//     HuffmanTree T = CreateHuffmanTree();
//     cout<<"PostOrder:"<<endl;
//     int WPL = PostOrder(T, 0);
//     cout<<"\nInOrder:"<<endl;
//     InOrder(T);
//     cout<<"\nWPL="<<WPL;
//     return 0;
// }

/**
 * 哈夫曼编码思路：
 * 用哈希表1存字符到它的编码映射
 * 方法1、从根开始深搜遍历完整颗树。在深搜过程中用string或数组记录编码，搜到叶子就将
 * 映射关系<字符，编码>存入哈希表1
 * 方法2、建立三叉链表（有父指针），并专门预先建立一个从字符到对应叶子结点的映射的哈希表
 * 每次根据字符找到叶子，然后往上一直走到根，将得到的序列反转后存入哈希表1
 * 
 * 哈夫曼解码思路：
 * 修改存储哈夫曼树的链表，需要让叶子结点额外保存对应字符
 * 在编码序列起始处建立两个指针i和j，i固定j前进，
 * 同时创建一个指向哈夫曼树根的指针，根据i到j的01序列来控制指针移动到叶子结点，然后更新ij位置
 */ 