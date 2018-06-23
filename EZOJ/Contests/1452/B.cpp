#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
typedef vector<int>vi;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=100010,INF=0x7f7f7f7f;
int n,p;
int val[N];
int perm[N];
inline int eval(){
	int cnt=0;
	for(int i=1;i<=n;i++){
		cnt+=(lint)cnt*n<(lint)(i-1)*val[perm[i]];
	}
	return cnt;
}
int pers[N];
inline void putperm(lint ord){
	int revst;
	for(int i=n;;i--){
		const int cur=n-i;
		if(ord<cur){
			assert(i<n);
			revst=i+1;
			break;
		}
		ord-=cur;
	}
	memcpy(perm+1,pers+1,n*sizeof(pers[0]));
	reverse(perm+revst,perm+n+1);
	for(int i=revst-1;ord--;i++){
		assert(i>=1&&i<n);
		swap(perm[i],perm[i+1]);
	}
}
inline bool valcmp(int a,int b){
	return val[a]>val[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("cs.in","r",stdin);
	freopen("cs.out","w",stdout);
#endif
	n=ni,p=ni;
	for(int i=1;i<=n;i++){
		val[i]=ni;
		pers[i]=i;
	}
	sort(pers+1,pers+n+1,valcmp);
	lint l=0,r=((lint)n*(n-1))>>1;
	while(l<r){
		const lint m=(l+r)>>1;
		putperm(m);
		const int v=eval();
		if(v<p){
			l=m+1;
		}else if(v>p){
			r=m;
		}else{
			l=r=m;
			break;
		}
	}
	putperm(l);
	for(int i=1;i<=n;i++){
		printf("%d ",perm[i]);
	}
	putchar('\n');
	return 0;
}
