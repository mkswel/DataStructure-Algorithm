#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<cmath>
using namespace std;
const int N = 10000;
int nums[N];
int main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i = 0; i < n; i++)cin>>nums[i];
		sort(nums, nums+n);
		int j = 0;
		unordered_map<long long, int> hash1;
		for(int i = 0; i < n; i++)
			if(nums[i]!=nums[j]){
				hash1[nums[j]*nums[j]]++;
				nums[++j] = nums[i];	
			}	
		n = j;
		double ans = 0;
		for(int i = 2; i < n; i++){
			for(int j = nums[i]/sqrt(2); j < nums[i]; j++){
				if(hash1[j*j] && hash1[nums[i]*nums[i]-j*j]){
					ans = max(ans, j*sqrt(nums[i]*nums[i]-j*j)/2);
					break;
				}	
			}
		}
		cout<<ans<<endl;
	}	
	system("pause");
}
