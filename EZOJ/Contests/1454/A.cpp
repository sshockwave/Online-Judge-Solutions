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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
namespace gmath{
	const int N=30;
	unsigned inv[N];
	inline void main(int n=N-1){
		for(int i=1;i<=n;i+=2){
			inv[i]=1;
			unsigned pw=i;
			for(;pw!=1;inv[i]*=pw,pw*=pw);
			assert((unsigned)i*inv[i]==1);
		}
	}
}
namespace parsum{
	const int N=200010;
	namespace sieve{
		int pri[N],ps=0;
		bool np[N];
		inline void main(int n){
			mset(np+1,0,n);
			pri[0]=0;
			for(int i=2;i<=n;i++){
				if(!np[i]){
					pri[++ps]=i;
				}
				for(int j=1,p,t;j<=ps&&(p=pri[j],t=i*p,t<=n);j++){
					np[t]=true;
					if(i%p==0)break;
				}
			}
		}
	}
	lint n;
	int rt;
	lint sn[N];
	int bcnt;
	inline int idx(const lint x){
		return x<=rt?x:bcnt-n/x+1;
	}
	template<unsigned (*s)(unsigned)>inline void redu(unsigned f[]){
		using sieve::pri;
		f[0]=0;
		for(int i=1;i<=sieve::ps;i++){
			const lint tj=(lint)pri[i]*pri[i];
			const unsigned v=s(pri[i]);
			for(int j=bcnt;sn[j]>=tj;j--){
				f[j]-=v*(f[idx(sn[j]/pri[i])]-f[pri[i-1]]);
			}
		}
	}
	template<unsigned (*g)(unsigned)>inline void supp(unsigned f[]){
		using sieve::pri;
		static unsigned tmpf[N];
		memcpy(tmpf+1,f+1,bcnt*sizeof(f[0]));
		tmpf[0]=f[0]=0;
		for(int i=sieve::ps;i>=1;i--){
			const lint tj=(lint)pri[i]*pri[i];
			for(int j=bcnt;sn[j]>=tj;j--){
				unsigned ans=0;
				lint tn=sn[j];
				for(int c=0;tn;c++,tn/=pri[i]){
					ans+=g(c)*(f[idx(tn)]-f[min<lint>(pri[i],tn)]+(c!=0));
				}
				f[j]=ans+tmpf[pri[i-1]];
			}
		}
	}
	unsigned f[N];
	unsigned ret_one(unsigned){return 1;}
	unsigned calc_v(unsigned c){return c?(81u*c-27u)*c+9u:1;}
	inline void main(){
		for(rt=1;(lint)rt*rt<n;rt++);
		sieve::main(rt);
		bcnt=0;
		for(lint l=1,r;l<=n;l=r+1){
			sn[++bcnt]=r=n/(n/l);
		}
		for(int i=1;i<=bcnt;i++){
			f[i]=sn[i]-1;
		}
		redu<ret_one>(f);
		for(int i=1;i<=bcnt;i++){
			f[i]*=63u;
		}
		supp<calc_v>(f);
		for(int i=1;i<=bcnt;i++){
			++f[i];
		}
	}
}
namespace G{
	const int N=21;
	int to[N],n;
	void dfs(const int x,int &bitm){
		if((bitm>>(x-1))&1)return;
		bitm|=1<<(x-1);
		for(int i=1;i<=n;i++){
			if((to[x]>>(i-1))&1){
				dfs(i,bitm);
			}
		}
	}
	int rep[N],req[N],ls=0;
	unsigned g[N],gm[1<<20],tmpgm[1<<20];
	inline void main(int e){
		for(;e--;){
			const int u=ni,v=ni;
			to[v]|=1<<(u-1);
		}
		for(int i=1;i<=n;i++){
			int bitm=0;
			dfs(i,bitm);
			to[i]=bitm;
		}
		for(int i=1;i<=n;i++){
			bool flag=false;
			for(int j=1;j<=ls;j++){
				if(to[i]==req[j]){
					rep[j]|=1<<(i-1);
					flag=true;
					break;
				}
			}
			if(!flag){
				++ls,rep[ls]=1<<(i-1),req[ls]=to[i];
			}
		}
		for(int i=1;i<=ls;i++){
			assert((rep[i]|req[i])==req[i]);
			req[i]^=rep[i];
		}
		int curm=0;
		for(int i=1;i<=ls;i++){
			int j=i;
			for(;(curm|req[j])!=curm;j++);
			swap(req[i],req[j]);
			swap(rep[i],rep[j]);
			curm|=rep[i];
		}
		const int sn=1<<n;
		mset(gm,0,sn);
		g[0]=0,gm[0]=1;
		for(int i=1;i<=ls;i++){
			for(int s=0;s<sn;s++){
				tmpgm[s]=gm[s],gm[s]=0;
			}
			for(int j=1;j<=ls;j++){
				const int ts=(sn-1)^req[j]^rep[j];
				for(int s=ts;;s=(s-1)&ts){
					gm[s|req[j]|rep[j]]+=gm[s|req[j]]+tmpgm[s|req[j]];
					if(s==0)break;
				}
			}
			g[i]=gm[sn-1];
		}
	}
	inline unsigned f(lint x){
		unsigned sh=0,prod=1,ans=0;
		for(unsigned i=1;i<=(unsigned)ls&&i<=x;i++){
			unsigned long long t=x-i+1;
			for(;(t&1)==0;t>>=1,sh++);
			prod*=t;
			t=i;
			for(;(t&1)==0;t>>=1,sh--);
			prod*=gmath::inv[t];
			if(sh<32){
				ans+=(prod<<sh)*g[i];
			}
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("statue.in","r",stdin);
	freopen("statue.out","w",stdout);
#endif
	gmath::main();
	G::n=ni;
	parsum::n=next_num<lint>();
	G::main(ni);
	parsum::main();
	unsigned ans=0,cur,last=0;
	using parsum::n;
	for(lint l=1,r,d;l<=n;l=r+1,last=cur){
		r=n/(d=n/l);
		cur=parsum::f[parsum::idx(r)];
		ans+=(cur-last)*G::f(d);
	}
	printf("%u %u\n",G::f(parsum::n),ans);
	return 0;
}
