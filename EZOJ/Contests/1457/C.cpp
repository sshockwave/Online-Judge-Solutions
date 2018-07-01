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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010,INF=0x7f7f7f7f;
struct Val{
	int v,cnt;
	inline friend bool operator < (const Val &a,const Val &b){
		return a.v!=b.v?a.v<b.v:a.cnt<b.cnt;
	}
};
struct Event{
	int x,r,v;
	inline friend bool operator < (const Event &a,const Event &b){
		return a.x<b.x;
	}
}ev[N<<1];
int es=0;
Val f[N];
int pr[N],nx[N];
int gnx(int x){
	return ~nx[x]?nx[x]=gnx(nx[x]):x;
}
inline void mgpre(const int v){
	for(;pr[v]!=-1&&f[v].v>=0;mgpre(v)){
		const int u=pr[v];
		assert(f[u].cnt<=f[v].cnt);
		assert(nx[u]==-1&&nx[v]==-1);
		pr[v]=pr[u],nx[u]=v;
		f[v].v+=f[u].v;
	}
}
inline Val calc(const int n,const int v){
	Val ans=(Val){0,0};
	int las=0;
	nx[0]=pr[0]=-1;
	f[0]=(Val){0,0};
	for(int i=1,j=1;i<=n;i++){
		for(;j<=es&&ev[j].x==i;j++){
			if(ev[j].v==0)continue;
			f[gnx(0)].v+=ev[j].v;
			if(ev[j].v>0){
				assert(ev[j].r==i-1);
				las+=ev[j].v;
			}else{
				assert(ev[j].r<i-1);
				const int x=gnx(ev[j].r+1);
				f[x].v-=ev[j].v;
				mgpre(x);
			}
		}
		f[i]=f[gnx(0)],f[i].v-=v,++f[i].cnt;
		apmax(ans,f[i]);
		swap(las,f[i].v),f[i].v=las-f[i].v;
		pr[i]=i-1,nx[i]=-1;
		mgpre(i);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("party.in","r",stdin);
	freopen("party.out","w",stdout);
#endif
	const int n=ni,m=ni;
	int sum=0,mxr=0;
	for(int i=1;i<=n;i++){
		const int l=ni,r=ni,c=ni;
		sum+=c,apmax(mxr,r);
		ev[++es]=(Event){l,l-1,c};
		ev[++es]=(Event){r,l-1,-c};
	}
	sort(ev+1,ev+es+1);
	int l=0,r=sum;
	for(;l<r;){
		const int mid=((l+r)>>1)+1;
		if(calc(mxr,mid).cnt<m){
			r=mid-1;
		}else{
			l=mid;
		}
	}
	const Val ans=calc(mxr,l);
	assert(ans.v+(lint)min(ans.cnt,m)*l<=sum);
	printf("%d\n",ans.v+min(ans.cnt,m)*l);
	return 0;
}
