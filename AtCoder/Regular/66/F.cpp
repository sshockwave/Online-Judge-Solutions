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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=300010;
int n;
lint a[N],_a[N],fl[N],fr[N],g[N],h[N];
int stk[N],ss;
inline void psh(int x){
	for(;ss>=2&&(g[x]-g[stk[ss-1]])*(x-stk[ss-2])>=(g[x]-g[stk[ss-2]])*(x-stk[ss-1]);ss--);
	stk[ss++]=x;
}
inline void pop(int i){
	for(;ss>=2&&g[stk[ss-1]]-g[stk[ss-2]]<=(lint)i*(stk[ss-1]-stk[ss-2]);ss--);
}
inline void gpre(){
	_a[0]=0;
	for(int i=1;i<=n;i++){
		_a[i]=_a[i-1]+a[i];
	}
}
inline void gg(lint f[],int x){
	g[x]=f[x]+_a[x]+(((lint)x*(x-1))>>1);
}
inline void dp(lint f[]){
	gpre();
	g[0]=0;
	ss=0;
	stk[ss++]=0;
	for(int i=1,j;i<=n;i++){
		pop(i),j=stk[ss-1];
		f[i]=max(f[i-1],g[j]-(lint)i*j+(((lint)i*(i+1))>>1)-_a[i]);
		gg(f,i),psh(i);
	}
}
lint tmp[N];
inline void solve(int l,int r,bool flag){
	if(l==r){
		if(l==0)return;
		apmax(h[l],fl[l-1]+(1-a[l])+fr[r+1]);
		return;
	}
	int m=(l+r-flag)>>1;
	solve(l,m,flag),solve(m+1,r,flag);
	ss=0;
	for(int i=l;i<=m;i++){
		gg(fl,i);
		psh(i);
	}
	for(int i=m+1,j;i<=r;i++){
		pop(i),j=stk[ss-1];
		tmp[i]=g[j]-(lint)i*j+(((lint)i*(i+1))>>1)-_a[i]+fr[i+1];
	}
	for(int i=r;i>m;i--){
		apmax(tmp[i-1],tmp[i]);
		apmax(h[i],tmp[i]);
	}
}
inline void work(bool flag){
	reverse(a+1,a+n+1);
	reverse(h+1,h+n+1);
	reverse(fl+1,fl+n+1);
	reverse(fr+1,fr+n+1);
	for(int i=1;i<=n;i++){
		swap(fl[i],fr[i]);
	}
	gpre();
	solve(0,n,flag);
}
int main(){
	n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	dp(fl);
	reverse(a+1,a+n+1);
	dp(fr);
	reverse(a+1,a+n+1);
	reverse(fr+1,fr+n+1);
	memset(h,128,sizeof(h));
	work(0),work(1);
	for(int tot=ni;tot--;){
		int p=ni,x=ni;
		printf("%lld\n",max(fl[p-1]+fr[p+1],h[p]+a[p]-x));
	}
	return 0;
}
