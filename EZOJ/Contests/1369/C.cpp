#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int SH=8,N=1<<SH,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int n;
int a[N],b[N],tmp[N],pos[N+1];
int cnt[N][N];
void mgsort(int l,int r){
	if(l+1==r)return;
	int m=(l+r)>>1;
	assert(m-l+1==r-m);
	mgsort(l,m),mgsort(m+1,r);
	int tl=l,tr=m+1,ts=0;
	for(int i=l;i<=r;i++){
		if(tr>r||(tl<=m&&b[tl]<b[tr])){
			tmp[ts++]=b[tl++];
		}else{
			tmp[ts++]=b[tr++];
		}
	}
	for(int i=l;i<=r;i++){
		b[i]=tmp[i-l];
	}
}
void dfs(int x){
	if(x==n){
		memcpy(b,a,n<<2);
		mgsort(0,n-1);
		for(int i=0;i<n;i++){
			pos[b[i]]=i;
		}
		for(int i=0;i<n;i++){
			cnt[i][pos[a[i]]]++;
		}
		return;
	}
	dfs(x+2);
	swap(a[x],a[x+1]);
	dfs(x+2);
	swap(a[x],a[x+1]);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
#endif
	n=ni;
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	int invn=fpow(inv(2),n>>1);
	for(int i=0;i<n;i++){
		memset(cnt[i],0,n<<2);
	}
	dfs(0);
	for(int tot=ni;tot--;){
		if(ni==1){
			int x=ni-1,y=ni-1;
			if(x>y){
				swap(x,y);
			}
			swap(a[x],a[y]);
			for(int i=0;i<n;i++){
				memset(cnt[i],0,n<<2);
			}
			dfs(0);
		}else{
			int fr=ni-1,to=ni-1;
			printf("%lld\n",(lint)invn*cnt[fr][to]%O);
		}
	}
	return 0;
}
