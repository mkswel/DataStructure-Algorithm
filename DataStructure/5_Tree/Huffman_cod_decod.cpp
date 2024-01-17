#include<iostream>
#include<cstring>
#include<queue>
#include<unordered_map>
#include<algorithm>
#include"HuffmanTree.cpp"
using namespace std;
const int N=5;
pair<char,int> letter_[N]={{'a',2},{'b',5},{'c',3},{'d',7},{'e',2}};
unordered_map<char, string> hashmap;

/**
 * 读取每个字母以及对应出现的频数，用于创建哈夫曼树
 * LeafNode用于编码方法2
*/
struct LeafNode{
    HuffmanNode *leaf;   //链表存储每个哈夫曼树的叶子结点
    struct LeafNode *next;
};
/**
 * n：字符种数
 * n次输入，每次输入字符和频数
 * 返回生成的LeafNode链表头指针
*/
LeafNode* GetData(int n){
    LeafNode *ll = (LeafNode *)malloc(sizeof(LeafNode));
    ll->next = NULL;
    ll->leaf = NULL;
    for(int i = 0; i < n; i++){
        char a;
        int w;
        a=letter_[i].first,w=letter_[i].second;
        HuffmanNode *t = (HuffmanNode *)malloc(sizeof(HuffmanNode));
        t->weight = w;
        t->letter = a;
        t->lchild = NULL;
        t->rchild = NULL;
        heap.push(t);
        LeafNode *le = (LeafNode *)malloc(sizeof(LeafNode));
        le->leaf = t;
        le->next = ll->next;
        ll->next = le;
    }
    return ll;
}


/**
 * 编码方法1：后序遍历(深搜)以创建哈希表
*/
void postorder(HuffmanTree T, string str = ""){
    if(T == NULL)return;
    postorder(T->lchild, str + '0');
    postorder(T->rchild, str + '1');
    if(!T->lchild&&!T->rchild)
        hashmap.emplace(T->letter, str);
} 
string Huffman_coding1(string str, HuffmanTree T){
    hashmap.clear();
    postorder(T);
    for(auto iter = hashmap.begin(); iter != hashmap.end(); iter++)   //打印哈希表，用于调试
        cout<<"***哈希表***\t"<<iter->first<<'\t'<<iter->second<<endl;
    string ans = "";
    for(int i = 0; i < str.length(); i++){
        if(hashmap.count(str[i]))ans += hashmap.at(str[i]);
        else return "Cannot code";
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
        if(!j->lchild && !j->rchild){
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
    HuffmanTree T = CreateHuffmanTree();
    string str = "bcddacee";
    string code1 = Huffman_coding1(str, T);
    //string code2 = Huffman_coding2(str, T, leaf);
    cout<<str<<"编码得："<<code1<<endl;
    cout<<code1<<"译码得："<<Huffman_decoding(code1, T)<<endl;
    code1 = "10100010011001";
    string decode1 = Huffman_decoding(code1, T);
    //string decode2 = Huffman_decoding(code2, T);
    cout<<code1<<"译码得："<<decode1<<endl;
    return 0;
}