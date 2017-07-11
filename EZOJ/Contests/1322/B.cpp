#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=10010;
int n;
lint sum[N],cnt[N],ans[N];
int as;
inline int bitchop(lint s){
	int l=1,r=n,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(sum[mid]<s){
			l=mid+1;
		}else if(sum[mid]>s){
			r=mid-1;
		}else{
			return mid;
		}
	}
	return l;
}
inline void pushans(lint x){
	ans[as++]=x;
	lint nxt;
	for(int i=1;nxt=sum[i]+x,nxt>=sum[1]&&nxt<=sum[n];i++){
		cnt[bitchop(sum[i]+x)]-=cnt[i];
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("subset.in","r",stdin);
	freopen("subset.out","w",stdout);
#endif
	for(int tcnt=1,tot=ni;tcnt<=tot;tcnt++){
		n=ni,as=0;
		for(int i=1;i<=n;i++){
			sum[i]=nl;
		}
		for(int i=1;i<=n;i++){
			cnt[i]=nl;
		}
		{//0
			int sh=0;
			for(;(1<<sh)<cnt[1];sh++);
			if(sh){
				for(int i=1;i<=n;i++){
					cnt[i]>>=sh;
				}
				for(;sh--;ans[as++]=0);
			}
		}
		for(int i=1;i<=n;i++){
			if(sum[i]&&cnt[i]){
				pushans(sum[i]);
			}
		}
		printf("Case #%d:",tcnt);
		for(int i=0;i<as;i++){
			printf(" %lld",ans[i]);
		}
		putchar('\n');
	}
}
