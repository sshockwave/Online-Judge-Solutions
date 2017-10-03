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
const int N=100010,K=2000010;
int a[N],rt,k;
struct Query{
	int l,r;
	lint ans;
}q[N];
inline bool lcmp(int a,int b){
	int lb=q[a].l/rt,rb=q[b].l/rt;
	return lb!=rb?lb<rb:q[a].r<q[b].r;
}
lint ans=0;
int lst[N],cnt[K];
inline void inc(int x){
	ans+=cnt[x^k],cnt[x]++;
}
inline void dec(int x){
	cnt[x]--,ans-=cnt[x^k];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
#endif
	int n=ni,tot=ni;
	k=ni;
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
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=tot;i++){
		int L=q[lst[i]].l,R=q[lst[i]].r;
		for(;l>L;inc(a[--l]));
		for(;r<R;inc(a[++r]));
		for(;l<L;dec(a[l++]));
		for(;r>R;dec(a[r--]));
		q[lst[i]].ans=ans;
	}
	for(int i=1;i<=tot;i++){
		printf("%lld\n",q[i].ans);
	}
	return 0;
}
