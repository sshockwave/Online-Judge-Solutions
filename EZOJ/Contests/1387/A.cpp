#include <iostream>
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <queue>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010;
lint len[N],sum[N];
int cost[N];
bool vis[N];
struct cmp{
	inline bool operator () (const int &a,const int &b){
		return cost[a]<cost[b];
	}
};
int n;
lint alltime;
bool flag=true;
inline int Main(){
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+len[i-1];
	}
	int ans=0;
	if(flag){
		for(int i=0,j=0;i<n;i++){
			lint rest=alltime-sum[i]*2-(i+1);
			if(rest<0)break;
			for(;j<n&&sum[n]-sum[j]+n-j>=rest;j++);
			if(j<n){
				apmax(ans,i+1+n-j);
			}else break;
		}
		return ans;
	}
	for(int i=0;i<n;i++){
		if(sum[i]*2>alltime){
			break;
		}
		typedef priority_queue<int,vector<int>,cmp>que;
		que q;
		lint nowtime=sum[i]*2;
		int cnt=0;
		for(int j=i;j>=0;j--){
			q.push(j);
			nowtime+=cost[j];
			cnt++;
		}
		while(!q.empty()&&nowtime>alltime){
			nowtime-=cost[q.top()];
			q.pop();
			cnt--;
		}
		apmax(ans,cnt);
		for(int j=n-1;j>=0;j--){
			q.push(j);
			nowtime+=cost[j];
			cnt++;
			while(!q.empty()&&sum[n]-sum[j]+nowtime>alltime){
				nowtime-=cost[q.top()];
				q.pop();
				cnt--;
			}
			if(sum[n]-sum[j]+nowtime>alltime){
				break;
			}
			apmax(ans,cnt);
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("decalcomania.in","r",stdin);
	freopen("decalcomania.out","w",stdout);
#endif
	n=ni,alltime=next_num<lint>();
	len[0]=0;
	for(int i=0;i<n;i++){
		len[i]=ni,cost[i]=ni;
		if(cost[i]!=1){
			flag=false;
		}
	}
	int ans=Main();
	reverse(len,len+n);
	reverse(cost+1,cost+n);
	apmax(ans,Main());
	printf("%d\n",ans);
	return 0;
}
