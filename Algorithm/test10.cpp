#include<iostream>
#include<queue>
using namespace std;
const int N = 50010;
int nums[N];
typedef pair<int, int> PII;
struct cmp_b{
	bool operator()(const PII &x, const PII &y)const{
		if(x.first == y.first)return x.second > y.second;
		return x.first < y.first;	
	}
};
struct cmp_s{
	bool operator()(const PII &x, const PII &y)const{
		if(x.first == y.first)return x.second > y.second;
		return x.first > y.first;	
	}
};
int perfect(int nums[], int n, int k){
	priority_queue<PII, vector<PII>, cmp_b> *heap_b = new priority_queue<PII, vector<PII>, cmp_b>;
	priority_queue<PII, vector<PII>, cmp_s> *heap_s = new priority_queue<PII, vector<PII>, cmp_s>;
	int ans = 0, cnt = 0;
	for(int i = 0; i < n; i++){
		if(heap_b->empty() || heap_b->top().first>=nums[i])heap_b->push({nums[i], i});
		if(heap_s->empty() || heap_s->top().first<=nums[i])heap_s->push({nums[i], i});
		if(nums[i] > heap_b->top().first){
			if(nums[i] - heap_s->top().first > k){
				int s = heap_s->top().second;heap_s->pop();
				while(!heap_s->empty() && !(nums[i]-heap_s->top().first<=k && heap_s->top().second>s)){
					heap_s->pop();
					s = max(s,heap_s->top().second);
				}
				ans = max(ans, cnt);
				if(heap_s->empty())cnt = 0;
				else cnt = i - heap_s->top().second;
			}
			delete heap_b;
			heap_b = new priority_queue<PII, vector<PII>, cmp_b>;
			heap_b->push({nums[i], i});		
			cnt++;
		}
		else if(nums[i] < heap_s->top().first){
			if(heap_b->top().first - nums[i] > k){
				int s = heap_b->top().second;heap_b->pop();
				while(!heap_b->empty() && !(heap_b->top().first-nums[i]<=k && heap_b->top().second>s)){
					heap_b->pop();
					s = max(s,heap_b->top().second);
				}
				ans = max(ans, cnt);
				if(heap_b->empty())cnt = 0;
				else cnt = i - heap_b->top().second;
			}
			delete heap_s;
			heap_s = new priority_queue<PII, vector<PII>, cmp_s>;
			heap_s->push({nums[i], i});		
			cnt++;
		}
		else cnt++;
	}	
	return ans;
}

int main(){
	int T;
	cin>>T;
	while(T--){
		int n, k;
		cin>>n>>k;
		for(int i = 0; i < n; i++)scanf("%d", &nums[i]);
		cout<<perfect(nums, n, k)<<endl;	
	}	
	system("pause");
}
