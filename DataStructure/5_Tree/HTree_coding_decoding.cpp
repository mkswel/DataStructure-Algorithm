/**
 * 哈夫曼编码思路：
 * 哈夫曼树的叶子额外存储对应字符
 * 用哈希表1存字符到它的编码映射
 * 方法1、从根开始深搜遍历完整颗树。在深搜过程中用string或数组记录编码，搜到叶子就将
 * 映射关系<字符，编码>存入哈希表1
 * 复杂度分析：深搜过程中每个结点都会被遍历，设一共n个字符，因此总结点数为2n-1，边数为2n-2，深搜时间复杂度为O(|V|+|E|)即O(n)，
 * 方法2、建立三叉链表（有父指针），另建一个链表LeafList链接每个叶子
 * 每次遍历LeafList找到叶子，然后往上一直走到根，将得到的序列反转后存入哈希表1
 * 复杂度分析：对于有n个字符的情况，每种字符最多被搜一次（之后存入哈希表），所有字符全部搜过一遍消耗时间是所有叶子的路径长度之和
 * 因为从根算起直到最高的叶子为止，每一层的偶数个边的个数都是n，
 * 因此当哈夫曼树近似完全二叉树时，有最好时间复杂度约O（hn）即O(nlogn);
 * 当哈夫曼树近似斜树时，树高接近n，有最坏时间复杂度约O（n^2）
 * 方法2优化：要尽可能使哈夫曼树高度最小，理论上应该修改优先队列的比较方式为：1级比较：两棵树根权值大小（逆序）、2级比较：两棵树高度（逆序）维护哈夫曼树高度的方式：建立递推式：H = max(HL, HR) + 1;
//  * (prioity_queue不稳定，所以下面的包括证明都不对) 
//  * 但事实上由于priority_queue本身的稳定性已经满足按树高逆排序的特点，无需二级比较：
//  * 只要证明在哈夫曼树构造过程中相同根权的情况下新加入的树永远不会比其他树低
//  * 相当于证明对于同一根权a的树，后达到a的树一定比先达到a的树经历了更多次（或相同）合并操作
//  * 一共有以下两种情况
//  * 1)当初始就有树为a时，其未经过合并，必然不会有比其他同为a的树更多的合并；
//  * 2)当初始没有树为a时，由于每次都是选择两个最小的合并，
//  * 所以当首次有两个权值最小的树T1T2(T1<=T2)先合并成a之后，又有两个树T3T4(T3<=T4)合并成a，
//  * 则有a=T1+T2<=T3+T4=a,得T1+T2=T3+T4,又由T1<=T2<=T3<=T4,得T1=T2=T3=T4=T，
//  * 这意味达到这四个权值相同的树时也必然存在先后关系,即问题改为证明根权为T的树....
//  * 而T=a/2，所以经过有限次循环后可以达到所有树都尚未合并的初始情况，即情况1)，问题得证。
 * 
 * 哈夫曼解码思路：
 * 哈夫曼树的叶子额外存储对应字符
 * 在编码序列起始处建立指针i，对应指向哈夫曼树根的指针j
 * 根据i每次前进的01序列来控制j移动到对应叶子结点，然后j重回根
 * 复杂度分析由于编码序列中的每个值都只会遍历一遍，因此时间复杂度是O(n)
 */ 
#include<iostream>
#include<cstring>
#include<queue>
#include<stdio.h>
#include<stdlib.h>
#include<unordered_map>
#include<algorithm>
using namespace std;
typedef struct Huffman{
    int weight; //权值
    bool leaf;  //是否为叶子
    char letter;//存储字符
     int height;  //树高
    struct Huffman *lchild, *rchild, *parent;//父指针用于上面的编码方法2
}HuffmanNode, *HuffmanTree;
struct cmp{
    bool operator()(HuffmanTree t1, HuffmanTree t2)const{
        if(t1->weight == t2->weight)return t1->height > t2->height;
        return t1->weight > t2->weight;
    }
};
priority_queue<HuffmanTree, vector<HuffmanTree>, cmp > heap;
/**
 * 根据优先队列里的内容创建哈夫曼树
*/
HuffmanTree CreaterTree(){
    while(heap.size() > 1){
        HuffmanNode *t1 = heap.top();
        heap.pop();
        HuffmanNode *t2 = heap.top();
        heap.pop();
        HuffmanNode *t = (HuffmanNode *)malloc(sizeof(HuffmanNode));
        t->lchild = t1;
        t->rchild = t2;
        t->leaf = false;
        t->weight = t1->weight + t2->weight;
         t->height = max(t1->height, t2->height) + 1;
        t->parent = NULL;
        heap.push(t);

        t1->parent = t;  //用于编码方法2
        t2->parent = t;
    }
    return heap.top();
}

/**
 * 读取每个字母以及对应出现的频数，用于创建哈夫曼树
 * LeafNode用于编码方法2
*/
struct LeafNode{
    HuffmanNode *leaf;   //链表存储每个哈夫曼树的叶子结点
    struct LeafNode *next;
};
LeafNode* GetData(int n){
    LeafNode *ll = (LeafNode *)malloc(sizeof(LeafNode));
    ll->next = NULL;
    ll->leaf = NULL;
    while(n--){
        char a;
        int w;
        cin>>a>>w;
        HuffmanNode *t = (HuffmanNode *)malloc(sizeof(HuffmanNode));
        t->weight = w;
        t->height = 1;
        t->letter = a;
        t->leaf = true;
        t->lchild = NULL;
        t->rchild = NULL;
        heap.push(t);
        //本来需要按照权值越低排越前，但这里省略了
        LeafNode *le = (LeafNode *)malloc(sizeof(LeafNode));
        le->leaf = t;
        le->next = ll->next;
        ll->next = le;
    }
    return ll;
}


/**
 * 编码方法1：深搜以创建哈希表
*/
void dfs(HuffmanTree T, unordered_map<char, string> & hash, string str = ""){
    if(T == NULL)return;
    if(T->leaf){
        hash.emplace(T->letter, str);
        return;
    }
    dfs(T->lchild, hash, str + "0");
    dfs(T->rchild, hash, str + "1");
}
string Huffman_coding1(string str, HuffmanTree T){
    unordered_map<char, string> hash;
    dfs(T, hash);
    // for(auto iter = hash.begin(); iter != hash.end(); iter++){   //打印哈希表，用于调试
    //     cout<<"***哈希表***   "<<iter->first<<'\t'<<iter->second<<endl;
    // }
    string ans = "";
    int n = str.length();
    for(int i = 0; i < n; i++){
        if(hash.count(str[i]))ans += hash.at(str[i]);
        else return "Cannot code";
    }
    return ans;
}

/**
 * 编码方法2
*/
string Huffman_coding2(string str, HuffmanTree T, LeafNode * ll){
    unordered_map<char, string> hash;
    string ans = "";
    int n = str.length();
    for(int i = 0; i < n; i++){
        char a = str[i];
        if(hash.count(a)){   //先查表，命中则直接读取
            ans += hash.at(a);
            continue;
        }
        LeafNode *tt = ll;
        tt = tt->next; //跳过头指针;
        while(tt != NULL && tt->leaf->letter != a)tt = tt->next;  //遍历LeafNode链表
        if(tt == NULL)return "Cannot code";
        else {
            HuffmanNode *t = tt->leaf;          //找到叶子后一直往上直到根
            string res = "";
            while(t->parent){
                res += t->parent->lchild == t ? '0' : '1';  //期间根据自己是左或右孩子来选择01
                t = t->parent;
            }
            reverse(res.begin(), res.end());    //由于是从下往上所以最后要倒序
            hash.emplace(tt->leaf->letter, res);
            ans += res;
        }
    }
    return ans;
}

/**
 * 解码
*/
string Huffman_decoding(string str, HuffmanTree T){
    int n = str.length();
    HuffmanTree j = T;
    string ans = "";
    for(int i = 0; i < n; i++){
        switch (str[i])
        {
        case '0':
            j = j->lchild;
            break;
        case '1':
            j = j->rchild;
        }
        if(j->leaf){
            ans += j->letter;
            j = T;
        }
    }
    if(j != T)ans += "...";
    return ans;
}

/**
 * 样例：5个字母a, b, c, d, e，频数分别为2, 5, 3, 7, 2
 * 两种方法编码：bcddacee
*/
int main(){
    LeafNode * leaf= GetData(5);
    HuffmanTree T = CreaterTree();
    string str = "bcddacee";
    string code1 = Huffman_coding1(str, T);
    string code2 = Huffman_coding2(str, T, leaf);
    cout<<code1<<'\n'<<code2<<endl;
    code1 = "101000100000101011011111110000111111110000001010100000100011001";
    string decode1 = Huffman_decoding(code1, T);
    string decode2 = Huffman_decoding(code2, T);
    cout<<decode1<<'\n'<<decode2<<endl;
    return 0;
}