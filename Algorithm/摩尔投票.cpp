#include <iostream>
#include <algorithm>
#include<vector>

using namespace std;
//https://zhuanlan.zhihu.com/p/104609555
//返回一列数中的众数     T: O(n)   S: O(1)
int zs(vector<int> & nums){
    int c = nums[0];   //当前候选人，从第一个开始
    int count = 0;
    int n = nums.size();

    //决出可能的候选人
    for(auto t:nums){
        if(t == c){
            count++;
        }   
        else{
            count--;
            if(count < 0){
                c = t;
                count = 1;
            }
        }
    }

    //统计选票是否超过半数
    int num = 0;
    for(auto t:nums){
        if(t == c)num++;
        if(num > n / 2)return c;
    }
    return -1;
}