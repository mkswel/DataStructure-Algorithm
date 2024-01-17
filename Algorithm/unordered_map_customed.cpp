#include<unordered_map>
using namespace std;
const int MaxSize = 10;
struct SparseMatrix{ //稀疏矩阵存储
    int i, j;
    int value;
};

struct HashFunc  //哈希函数，将键运算到对应的size_t(无符号长整形)
{
	std::size_t operator()(const SparseMatrix &key) const 
    {
   		using std::size_t;
  		using std::hash;
 		return hash<int>()(key.i)
       			// ^ (hash<int>()(key.j) << 1)) >> 1)
                ^ (hash<int>()(key.j) << 1);
    }
};

struct EqualKey //处理冲突
{
	bool operator () (const SparseMatrix &lhs, const SparseMatrix &rhs) const
	{
		return lhs.i == rhs.j
			&& lhs.j == rhs.j;
	}
};

/**
 * 样例：将两个稀疏矩阵相加，利用三元组存储；
 * 思路：建立从(i, j)到该三元组数组下标的映射的哈希表
*/
int main(){
    SparseMatrix A[MaxSize];
    int t;
    unordered_map<SparseMatrix, int, HashFunc, EqualKey> hashmap;
}