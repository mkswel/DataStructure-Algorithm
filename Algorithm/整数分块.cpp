//向下取整求和

#include<iostream>
#include<algorithm>

using namespace std;
//https://zhuanlan.zhihu.com/p/452977429
//整数分块求和 (n/1) + (n/2) + ... + (n / n)   (下取整)   O(sqrt(n))
//将n/x的结果分成若干区间，每个区间内都是相同的值，用l表示当前区间的最左端，r表示当前区间最右端

/**
 * 例：求n/x下取整 n = 12 时
 * x:    1  | 2  | 3  | 4  | 5   6  | 7   8   9  10  11  12
 * n/x: 12  | 6  | 4  | 3  | 2   2  | 1   1   1   1   1   1
 * 如上，分成6个区间，每个区间内都是相同的 n / x 值
 * 
 * 类似的如累加 n mod x（转换成n - x(n/i)） 、 sqrt(n) 等
*/
int sum(int n){
    int ans = 0;
    for(int l = 1, r; l <= n; l = r + 1){  //每次枚举每个区间的左端点，区间数量级为sqrt(n)
        r = n / ( n / l );   //确定当前区间右端点区间 右端点应为当前结果可能取到的最大值
        ans += (min(r, n) - l + 1) * (n / l);  //每次加上当前区间内所有值，注意r可能超出n，虽然该题中不会超
    }
    return ans;
}


