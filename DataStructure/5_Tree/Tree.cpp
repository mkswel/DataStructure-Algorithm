//树的定义：树是n个结点的有限集
//结点的度：结点的孩子个数
//树的度：树中结点的最大度数
//层次：从树根开始，根为第一层
//结点的深度：从根结点开始向下到该结点的层数
//结点的高度：从叶子结点开始向上到该结点的层数

//树的性质：
//树的结点数等于所有度数之和加1
//度为m的树中第i层上至多有m^(i-1)个结点
//高度为h的m叉树至多有(m^h-1)/(m-1)个结点
//具有n个结点的m叉树最小高度为[ logm(n(m-1)+1) ]上取整

//二叉树
//二叉树定义:每个结点至多只有两棵子树，子树有左右之分
//满二叉树高度为h且结点数为(2^h-1)
//完全二叉树：
/**
 * i<= [n/2]下去整，则结点i为分支结点，其余为叶子结点
 * 度为一的结点最多只有一个，其只有左孩子无右孩子
 * 按层编号后若一个结点为叶子或只有一个孩子，那比它大的都是叶子
 */ 
//二叉排序树：左子树上所有结点值均小于根，右子树所有结点值均大于根
//平衡二叉树：树上任意结点的左子树深度和右子树深度只差不超过1

//二叉树性质：
/**
 * 非空二叉树有 n0 = n2 + 1
 * 非空树第k层上至多2^(k-1)结点
 * 高度为h树至多2^h-1结点
 * 完全二叉树第i结点双亲为i/2（偶数），或(i-1)/2（奇数）
 * n个结点的完全二叉树高度为  [log2(n+1)]（上去整）  或  [log2(n)](下去整)+1
 *      6
 *     / \ 
 *   3     7
 *  / \   / \
 * 5   6 7   9
 */

//基本操作：(顺序存储)
//i的左孩子   2i
//i的右孩子   2i+1
//i的父结点   i/2
//i所在的层次  

/**
 * 树的遍历：
 * 唯一确定一棵二叉树：（1）先序+中序
 *                  （2）后序+中序
 *                  （3）层序+中序
 */ 

//------------------------线索二叉树
//目的：加快查找结点前驱和后继的速度
//对于p结点，若 p->lchild = NULL 令 p->lchild = p的前驱
//         若 p->rchild = NULL 令 p->rchild = p的后继
//一棵线索二叉树的结点包含一下结构：
//1）数据
//2）左孩子指针和右孩子指针
//3）左标记和右标记

//------------------------树和森林
//存储结构：
//1)双亲表示法：顺序存储
//2)孩子表示法：顺序+链式存储
//3)孩子兄弟表示法：链式存储

//树与二叉树转换（孩子兄弟表示法）：
//树结点的第一个孩子是二叉树的左孩子；树的右兄弟是二叉树的右孩子

//森林与二叉树转换：将每棵树的根都视为兄弟，然后法同上

//树的遍历
//1)先根遍历  先访问根再遍历递归各个子树 --- 先根遍历序列与其对应的二叉树的先序序列相同
//2)后根遍历  先遍历递归各个子树再访问根 --- 后根遍历序列与其对应的二叉树的中序序列！！！相同
//3)层次遍历  根入队，若队列非空队头出队并访问，并依次入队其孩子，重复直到队空
//森林的遍历
//1)先序遍历：依次对各个树先根遍历，等于对应二叉树先序
//2)中序遍历：依次对各个树后根遍历，等于对应二叉树中序

//哈夫曼树（最优二叉树）
/**
 * 树的带全权路径长度WPL=所有叶子结点的带权路径长度（从根到叶子经过的边数*叶子结点权值）之和
 * 哈夫曼树定义：在含有n个带权叶子结点的二叉树中，WPL最小的树称为哈夫曼树
 * 
 * 哈夫曼树构造：
 *          1）最初共n个带权结点，作为n个只有根的树，构成森林F
 *          2）从F中找两个根节点权值最小的树A、B，将这两棵树构成新树C的左、右子树，
 *              C的根=A根+B根。
 *          3）将A、B从F中删去，将C加入F
 *          4）重复2）3）直到F只剩一棵树
 * 
 * 哈夫曼树特点：最初的n个结点都成了叶子结点，权值越小的到根路径越远
 *             新建了n-1个结点，总结点数2n-1
 *             不存在度为1的结点
 *             除叶子结点外的所有节点都有两个孩子，所以边数为2n-2
 *             
 * 
 */ 

//哈夫曼编码
//可变长编码：允许对不同字符用不等长二进制位表示
//前缀编码：没有一个编码是另一个编码的前缀
//哈夫曼编码构造：将每个字符作为一个叶子结点，出现的频度为其权值，然后构造哈夫曼树
//             从根开始走左孩子边标0，走右孩子边标1
//哈夫曼解码：从根到叶子A经过的路径所组成的01序列为字符A的哈夫曼编码

//并查集
//基本操作：
//1）Initial(S):将集合S中每个元素都初始化为只有单个元素的子集合
//2）Union(S, root1, root2):将S中的子集root2并入root1，要求root1和root2不相交，否则不合并
//3）Find(S,x):查找S中元素x所在子集，并返回该子集根结点