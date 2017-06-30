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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=30010,K=5,MOD=998244353;
inline int add(const int &a,const int &b){
	int ans=a+b;
	if(ans>MOD){
		ans-=MOD;
	}
	return ans;
}
inline int mul(const int &a,const int &b){
	lint ans=(lint)a*b;
	return ans<MOD?ans:ans%MOD;
}
inline void apadd(int &a,const int &b){
	a+=b;
	if(a>MOD){
		a-=MOD;
	}
}
int k;
struct vec{
	int a[K];
	inline void clr(){
		memset(a,0,sizeof(a));
	}
	inline int sum(){
		int ans=0;
		for(int i=0;i<k;i++){
			apadd(ans,a[i]);
		}
		return ans;
	}
};
struct mat{
	int a[K][K];
	inline void ini(){
		memset(a,0,sizeof(a));
		for(int i=0;i<k;i++){
			a[i][i]=1;
		}
	}
};
inline vec operator + (const vec &a,const vec &b){
	vec c;
	for(int i=0;i<k;i++){
		c.a[i]=add(a.a[i],b.a[i]);
	}
	return c;
}
inline vec operator * (const vec &a,const mat &b){
	vec c;
	for(int i=0;i<k;i++){
		c.a[i]=0;
		for(int j=0;j<k;j++){
			apadd(c.a[i],mul(a.a[j],b.a[j][i]));
		}
	}
	return c;
}
inline mat operator * (const mat &a,const mat &b){
	mat c;
	for(int i=0;i<k;i++){
		for(int j=0;j<k;j++){
			c.a[i][j]=0;
			for(int p=0;p<k;p++){
				apadd(c.a[i][j],mul(a.a[i][p],b.a[p][j]));
			}
		}
	}
	return c;
}
int kmap[K];
struct SegmentTree{
	typedef SegmentTree* node;
	int lend,rend,mid;
	node lson,rson;
	struct Info{
		vec ans;
		mat trans;
		inline friend Info operator + (const Info &a,const Info &b){
			Info c;
			c.ans=a.ans+(b.ans*a.trans);
			c.trans=b.trans*a.trans;
			return c;
		}
	}info;
	inline node nn();
	inline void up(){
		assert(lend!=rend);
		info=lson->info+rson->info;
	}
	void build(int l,int r){
		lend=l,rend=r,mid=(l+r)>>1;
		if(lend==rend){
			info.ans.clr(),info.trans.ini();
			int t=ni;
			info.ans.a[t]=1;
			for(int i=0;i<k;i++){
				info.trans.a[i][t]=1;
			}
		}else{
			(lson=nn())->build(l,mid);
			(rson=nn())->build(mid+1,r);
			up();
		}
	}
	inline Info ask(int l,int r){
		assert(l<=r);
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			return info;
		}
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return lson->ask(l,mid)+rson->ask(mid+1,r);
	}
	inline void apmul(int l,int r){
		assert(l<=r);
		assert(lend<=l&&r<=rend);
		if(lend==rend){
			int t;
			for(int i=0;i<k;i++){
				if(info.ans.a[i]){
					t=kmap[i];
					break;
				}
			}
			info.ans.clr(),info.trans.ini();
			info.ans.a[t]=1;
			for(int i=0;i<k;i++){
				info.trans.a[i][t]=1;
			}
			return;
		}
		if(r<=mid){
			lson->apmul(l,r);
		}else if(l>mid){
			rson->apmul(l,r);
		}else{
			lson->apmul(l,mid);
			rson->apmul(mid+1,r);
		}
		up();
	}
	inline void apadd(int l,int r){
		assert(l<=r);
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			Info nf=info;
			for(int i=0;i<k;i++){
				info.ans.a[kmap[i]]=nf.ans.a[i];
			}
			for(int i=0;i<k;i++){
				for(int j=0;j<k;j++){
					info.trans.a[kmap[i]][kmap[j]]=nf.trans.a[i][j];
				}
			}
			return;
		}
		if(r<=mid){
			lson->apadd(l,r);
		}else if(l>mid){
			rson->apadd(l,r);
		}else{
			lson->apadd(l,mid);
			rson->apadd(mid+1,r);
		}
		up();
	}
}seg,pol[N*2],*pool;
inline SegmentTree* SegmentTree::nn(){
	return pool++;
}
namespace brute{
	int a[N];
	int kmap[K];
	int nxt[N][K];
	int f[N];
	inline int calc(int l,int r){
		int pos[K];
		for(int i=0;i<k;i++){
			pos[i]=r+1;
		}
		for(int i=r;i>=l;i--){
			for(int j=0;j<k;j++){
				nxt[i][j]=pos[j];
			}
			pos[a[i]]=i;
		}
		memset(f+l,0,(r-l+1)<<2);
		for(int i=0;i<k;i++){
			f[pos[i]]=1;
		}
		int ans=0;
		for(int i=l;i<=r;i++){
			apadd(ans,f[i]);
			for(int j=0;j<k;j++){
				apadd(f[nxt[i][j]],f[i]);
			}
		}
		return ans;
	}
	inline void work(int n,int tot){
		for(int i=1;i<=n;i++){
			a[i]=ni;
		}
		while(tot--){
			int t=ni,l=ni,r=ni;
			if(t<=2){
				int v=ni;
				if(t==1){
					for(int i=0;i<k;i++){
						kmap[i]=(i+v)%k;
					}
				}else{
					for(int i=0;i<k;i++){
						kmap[i]=(i*v)%k;
					}
				}
				for(int i=l;i<=r;i++){
					a[i]=kmap[a[i]];
				}
			}else{
				printf("%d\n",calc(l,r));
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("data1.in","r",stdin);
	freopen("data.out","w",stdout);
#endif
	for(int tot=ni,n,tot2;tot--;){
		n=ni,k=ni,tot2=ni;
		if(n<=3010){
			brute::work(n,tot2);
			continue;
		}
		pool=pol;
		seg.build(1,n);
		while(tot2--){
			int t=ni,l=ni,r=ni;
			if(t==1){
				int v=ni;
				for(int i=0;i<k;i++){
					kmap[i]=(i+v)%k;
				}
				seg.apadd(l,r);
			}else if(t==2){
				int v=ni;
				for(int i=0;i<k;i++){
					kmap[i]=(i*v)%k;
				}
				seg.apmul(l,r);
			}else{
				assert(t==3);
				printf("%d\n",seg.ask(l,r).ans.sum());
			}
		}
		cout<<" ";
	}
}
