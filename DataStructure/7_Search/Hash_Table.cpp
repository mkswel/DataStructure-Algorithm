//哈希表：数据元素的关键字与存储地址直接相关
//散列函数：Addr=H(key)
/**
 * 1、直接定址法H(key)=a*key+b
 * 2、除留余数法H(key)=key%p
 * 3、数字分析法
 * 4、平方取中法
 */ 

//处理冲突
/**
 * 开放定址法  Hi=(H(key)+di)%m
 *      线性探测法：插入：di取0,1，2，3，...每次冲突就移下一格
 *                删除：对删除的位置标记
 *                查找：取余后一直往后比较，直到遇到空格子（也算一次比较）
 *      平方探测法：di取0,1,-1,4,-4,9,-9...k^2,-k^2其中k<=m/2散列表长度m必须是可以表示成4j+3的素数如7
 *      伪随机法：di为伪随机序列
 *      再散列法：多准备几个散列函数，当冲突时就换下一个散列函数
 * 拉链法：空指针的格子不算一次比较
 */ 

//装填因子α=表中记录数n/散列表长度m  平均查找长度ASL依赖于α而不直接依赖于n或m
//α越大越容易冲突
//ASL成功=关键字比较次数总和/关键字个数
//ASL失败=每个入口地址的比较次数（一直走到空，空也算一次比较）/ 哈希表值域（例如 模7那就只可能取0-6共7个） 
//入口地址数：如果散列函数模7，但是散列表长10，那入口数就是7，因为任何数模7后都是0-6，7-9只是用于线性探测而补的

//链地址法里算ASL中，第一层指针不算一次比较。