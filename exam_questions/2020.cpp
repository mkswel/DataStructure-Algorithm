/**
 * 寻找n个数里最小的k个数
 * 思路1：将n个数的前k个数建立大根堆，然后继续遍历后续的数，并比较：如果比堆顶大，跳过；如果比堆顶小，将其替换堆顶并更新整个堆。时间复杂度O(nlogk)，适用于k相对较大情况
 * 思路2：堆排序，只输出前k个最小的数，即建堆O(n)，k次调堆O(klogn)，共O(n+klogn)，适用于k相对较小情况
*/