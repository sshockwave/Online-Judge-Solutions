#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <map>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=10,O=1000000007;
inline int fpow(int x,int n){
	lint ret=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			(ret*=x)%=O;
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,O-2);
}
map<int>m;
vector<int>vec;
int bitcnt[1<<N];
int num[N],k,invk;
int dfs(vector<int>&cur){
	if(cur.size()==1){
		m.insert(cur);
	}
	lint ans=0;
	int cnt=0;
	for(int i=0;i<(int)vec.size();i++){
		if(vec[i]<(1<<cur.size())){
			cnt++;
			vector<int>nxt;
			lint sum=0;
			for(int j=0;j<(int)cur.size();j++){
				if((vec[i]>>j)&1){
					sum+=cur[j];
				}else{
					nxt.push_back(cur[j]);
				}
			}
			nxt.push_back(sum%O);
			ans+=dfs(nxt);
		}
	}
	return ans%O*inv(cnt)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("classroom.in","r",stdin);
	freopen("classroom.out","w",stdout);
#endif
	int n=ni,m=ni;
	k=ni,invk=inv(k);
	for(int s=1,ts=1<<n;s<ts;s++){
		bitcnt[s]=bitcnt[s^(s&-s)]+1;
		if(bitcnt[s]==k){
			vec.push_back(s);
		}
	}
	vector<int>cur;
	for(int i=0;i<n;i++){
		cur.push_back(0);
	}
	for(int j=0;j<m;j++){
		cur.push_back(1);
	}
	printf("%d\n",dfs(cur));
	return 0;
}
