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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=(1<<16)*9+1;
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int tag[N],tim=0,lst[N],ls,stk[N];
	bool onring[N];
	int nxt[N],go[N];
	lint step;
	void dfs(int x,int dep,int dt){
		stk[dep]=x;
		go[x]=step<=dep?stk[dep-step]:lst[(step-dep+dt)%ls];
		for(int i=head[x];~i;i=bro[i]){
			dfs(to[i],dep+1,dt);
		}
	}
	inline void Main(int n){
		memset(lst,0,sizeof(lst));
		memset(tag,0,sizeof(tag));
		for(int i=0;i<=n;i++){
			if(tag[i])continue;
			int j=i;
			tim++;
			for(;tag[j]==0;j=nxt[j]){
				tag[j]=tim;
			}
			if(tag[j]<tim)continue;
			tim++;
			for(;tag[j]<tim;j=nxt[j]){
				tag[j]=tim;
				onring[j]=true;
			}
		}
		init();
		for(int i=0;i<=n;i++){
			if(!onring[i]){
				ae(nxt[i],i);
			}
		}
		tim++;
		for(int i=0;i<=n;i++){
			if(onring[i]&&tag[i]<tim){
				ls=0;
				for(int j=i;tag[j]<tim;j=nxt[j]){
					tag[j]=tim;
					lst[ls++]=j;
				}
				for(int i=0;i<ls;i++){
					dfs(lst[i],0,i);
				}
			}
		}
	}
}
const int g=3;
int O;
int invnum[N],pw[N];
inline void gmath(int n){
	pw[0]=1;
	for(int i=1;i<=n;i++){
		pw[i]=(lint)pw[i-1]*g%O;
	}
	invnum[1]=1;
	for(int i=2;i<=n;i++){
		invnum[i]=(lint)(O-O/i)*invnum[O%i]%O;
		assert((lint)invnum[i]*i%O==1);
	}
}
namespace poly{
	int n,b[N];
	inline void clr(int a[],int x=0){
		memset(a+x,0,(n-x)<<2);
	}
	inline void cpy(int a[],const int b[],int n){
		memcpy(a,b,n<<2);
	}
	void solve(int a[],const int n,const int wn){
		if(n&1){
			cpy(b,a,n);
			for(int i=0,w=1;i<n;i++,w=(lint)w*wn%O){
				int &ans=a[i]=0;
				for(int j=n-1;j>=0;j--){
					ans=((lint)ans*w+b[j])%O;
				}
			}
		}else{
			int h=n>>1,wn2=(lint)wn*wn%O;
			for(int i=1;i<n;i+=2){
				b[i>>1]=a[i];
			}
			for(int i=0;i<n;i+=2){
				a[i>>1]=a[i];
			}
			cpy(a+h,b,h);
			solve(a,h,wn2),solve(a+h,h,wn2);
			for(int i=0,w=1;i<h;i++,w=(lint)w*wn%O){
				int p=a[i],q=(lint)a[i+h]*w%O;
				a[i]=(p+q)%O;
				a[i+h]=(p+O-q)%O;
			}
		}
	}
	inline void ntt(int a[],const int d=1){
		assert((O-1)%n==0);
		solve(a,n,pw[(O-1)/n]);
		if(d==-1){
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invnum[n]%O;
			}
		}
	}
}
inline int nextfrac(){
	int u=ni,v=ni;
	return (lint)u*invnum[v]%O;
}
int a[N],p[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
#endif
	gmath((O=ni)-1);
	T::step=next_num<lint>();
	for(int i=0;i<O;i++){
		a[i]=nextfrac();
	}
	using poly::ntt;
	poly::n=O-1;
	{//Construct
		memset(p,0,O*sizeof(p[0]));
		for(int i=1,n=ni;i<=n;i++){
			p[i]=nextfrac();
		}
		p[0]=p[O-1],p[O-1]=0;
		ntt(p);
		T::nxt[0]=0;
		for(int i=0;i<poly::n;i++){
			T::nxt[pw[i]]=p[i];
		}
		T::Main(O-1);
	}
	lint ans=0,sum=T::go[a[0]];
	{//Jump
		a[0]=(a[0]+a[O-1])%O,a[O-1]=0;
		ntt(a);
		for(int i=0;i<poly::n;i++){
			a[i]=(T::go[a[i]]+O-sum)*invnum[pw[i]]%O;
		}
		ntt(a,-1);
	}
	{//Answer
		for(int i=0;i<poly::n;i++){
			ans+=(lint)a[i]*(i+1)%O,sum+=a[i];
		}
		assert(sum%O);
		ans=ans%O*invnum[sum%O]%O;
		for(int tot=ni;tot--;){
			printf("%lld\n",ans);
		}
	}
	return 0;
}
