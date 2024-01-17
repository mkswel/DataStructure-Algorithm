/*stl常用

  vector 动态数组,申请次数logn
     size()/length() 返回元素个数
     empty() 返回是否为空
     clear() 清空
     front()/back()返回第一个/最后一个元素
     push_back()/pop_back()在末尾插入一个元素/删除最后一个元素
     begin()/end() 第一个元素/最后一个元素后面一个元素
     erase() 删除指向的元素
     支持比较运算
     []

  string 字符串
     size()/length() 返回元素个数
     empty() 返回是否为空
     substr(a,b) 返回起始位置下标为a，长度为b的内容 
     c_str() 字符数组的起始地址

  queue 队列
     size()/length() 返回元素个数
     empty() 返回是否为空
     push() 向队尾插入一个元素
     front() 返回队头元素
     back() 返回队尾元素
     pop() 删除队头元素

  priority_queue 优先队列，默认是大顶堆
     size()/length() 返回元素个数
     empty() 返回是否为空
     push() 插入一个元素
     top() 返回堆顶元素
     pop() 弹出堆顶元素

  stack 栈
     size()/length() 返回元素个数
     empty() 返回是否为空
     push() 向栈顶插入一个元素
     top() 返回栈顶元素
     pop() 删除栈顶元素

  deque 双端队列
     size()/length() 返回元素个数
     empty() 返回是否为空
     clear() 清空
     front()/back()返回第一个/最后一个元素
     push_front()/pop_front()在队头插入元素/删除队头元素
     push_back()/pop_back()在末尾插入元素/删除队尾元素
     begin()/end() 第一个元素/最后一个元素后面一个元素
     []

  set,map,multiset,multimap 基于平衡二叉树（红黑树），动态维护有序序列
     size()/length() 返回元素个数
     empty() 返回是否为空
     clear() 清空
    set，multiset                    set自动去重并排序 multiset只排序 时间都是O(n)
     insert() 插入一个数
     find() 查找一个数
     count() 返回某一个数的个数
     erase()
         1)输入的是一个数，删除所有这个数         时间O(k+logn) k是删除个数
         2)输入的是一个迭代器，删除该迭代器
     lower_bound(x) 返回不小于x的最小值
     upper_bound(x) 返回不大于x的最大值
    map,multimap                      一对一映射
      insert() 插入的数是pair
      erase() 输入的数是pair或迭代器
      find() 查找一个数
      []           时间O(logn)
     

  unordered_set,unordered_map,unordered_muliset,unordered_kultimap 哈希表
     类似上面，增删改查的时间是O(1)，不支持lower_bound()/upper_bound()

  bitset 压位
     cout() 返回有多少个1
     any() 判断是否至少有一个1
     none() 判断是否全为0
     set() 把所有位置成1
     set(k,v) 把第k位变成v
     reset() 把所有位变成0
     flip() 等价于~
     flip(k) 把第k位取反


  list 双链表

  pair< , >二元组
     支持比较运算

 sort(A,B):对[A,B)升序排序A,B为起始(终止)地址。
 sort(A,B,greater<int>())降序排序
 


*/

#include<iostream>
#include<cstring>
#include<vector>
#include<cstdio>
#include<queue>
#include<algorithm>
#include<set>
#include<map>

using namespace std;

int main()
{
    /*
    ****vector
    vector<int> a;
    for(int i=0;i<10;i++)a.push_back(i);
    for(vector<int>::iterator i=a.begin();i!=a.end();i++)cout<<*i<<' ';
    for(auto i:a)cout<<i<<' ';

    ****pair< , >初始化
    pair<int,string>p;
    p=make_pair(10,"abc");
    p={20,"abc"};

    ****string
    string a="aaaa";
    printf("%s",a.c_str());
    
    ****priority_queue 定义一个小顶堆(如果需要结构体排序则重载大于号)
    priority_queue<int,vector<int>,greater<int>>heap;

    ****set,multiset  
    set<int> s;
    multiset<int> ms;

    ****bitset 
    bitset<10000> s;


    */
}