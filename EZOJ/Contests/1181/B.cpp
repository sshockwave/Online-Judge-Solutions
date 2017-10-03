#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=100010,K=1000010;
int a[N],rt;
struct Query{
	int l,r;
	lint ans;
}q[N];
inline bool lcmp(int a,int b){
	int lb=q[a].l/rt,rb=q[b].l/rt;
	return lb!=rb?lb<rb:q[a].r<q[b].r;
}
lint ans=0;
int lst[N];
int org[K],trs[K];
int main(){
#ifndef ONLINE_JUDGE
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
#endif
	int n=ni,tot=ni,k=ni;
	for(rt=0;rt*rt<n;rt++);
	a[0]=0;
	for(int i=1;i<=n;i++){
		a[i]=ni^a[i-1];
	}
	for(int i=1;i<=tot;i++){
		q[i]=(Query){ni-1,ni};
		lst[i]=i;
	}
	sort(lst+1,lst+tot+1,lcmp);
	int l=1,r=0;
	memset(org,0,sizeof(org));
	memset(trs,0,sizeof(trs));
	for(int i=1;i<=tot;i++){
		int L=q[lst[i]].l,R=q[lst[i]].r;
		for(;l<L;l++){
			ans-=trs[a[l]];
			org[a[l]]--,trs[a[l]^k]--;
		}
		for(;r>R;r--){
			ans-=org[a[r]^k];
			org[a[r]]--,trs[a[r]^k]--;
		}
		for(;l>L;){
			l--;
			ans+=trs[a[l]];
			org[a[l]]++,trs[a[l]^k]++;
		}
		for(;r<R;){
			r++;
			ans+=org[a[r]^k];
			org[a[r]]++,trs[a[r]^k]++;
		}
		q[lst[i]].ans=ans;
	}
	for(int i=1;i<=tot;i++){
		printf("%lld\n",q[i].ans);
	}
	return 0;
}
