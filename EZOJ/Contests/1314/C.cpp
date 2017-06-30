#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define int unsigned int
#define ni (next_num<int>())
#define nl (next_num<lint>())
#undef assert
#define assert(x) {}
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
inline int gcd(const int &a,const int &b){
	return b==0?a:gcd(b,a%b);
}
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
	inline void init(){
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
struct mapper{
	int a[K];
	inline void operator *= (const mapper &b){
		for(int i=0;i<k;i++){
			a[i]=b.a[a[i]];
		}
	}
};
struct SegmentTree{
	typedef SegmentTree* node;
	int lend,rend,mid;
	node lson,rson;
	struct Info{
		vec ans;
		mat trans;
		inline void init(int t,int l){
			ans.clr(),trans.init();
			ans.a[t]=l;
			for(int i=0;i<k;i++){
				if(i!=t){
					trans.a[i][t]=l;
				}
			}
		}
		inline friend Info operator + (const Info &a,const Info &b){
			Info c;
			c.ans=a.ans+(b.ans*a.trans);
			c.trans=b.trans*a.trans;
			return c;
		}
		inline void operator *= (const mapper &m){
			static Info tmp;
			for(int i=0;i<k;i++){
				tmp.ans.a[m.a[i]]=ans.a[i];
				for(int j=0;j<k;j++){
					tmp.trans.a[m.a[i]][m.a[j]]=trans.a[i][j];
				}
			}
			*this=tmp;
		}
	}info,info2;
	mapper m;
	bool tag0,tagmap,tag2;
	inline node nn();
	inline void up(){
		assert(lend!=rend);
		assert(!tag0&&!tagmap&&!tag2);
		info=lson->info+rson->info;
		if(k==4){
			info2=lson->info2+rson->info2;
		}
	}
	void down(){
		if(lend==rend){
			tag0=tagmap=tag2=false;
		}else if(tag0){
			assert(!tagmap&&!tag2);
			lson->set0(lend,mid);
			rson->set0(mid+1,rend);
			tag0=false;
		}else if(tagmap){
			assert(!tag2);
			lson->map(lend,mid,m);
			rson->map(mid+1,rend,m);
			tagmap=false;
		}else if(tag2){
			lson->pull(lend,mid);
			rson->pull(mid+1,rend);
			tag2=false;
		}
	}
	void build(int l,int r){
		lend=l,rend=r,mid=(l+r)>>1;
		tag0=tagmap=tag2=false;
		if(lend==rend){
			int t=ni;
			info.init(t,1);
			if(k==4){
				info2.init(t&1,1);
			}
		}else{
			(lson=nn())->build(l,mid);
			(rson=nn())->build(mid+1,r);
			up();
		}
	}
	void map(int l,int r,const mapper &v){
		if(lend==l&&rend==r){
			if(tag0||tag2){
				down();
			}
			info*=v;
			if(tagmap){
				m*=v;
			}else{
				tagmap=true;
				m=v;
			}
			if(k==4&&(v.a[0]&1)){
				info2*=(mapper){1,0,2,3};
			}
			return;
		}
		down();
		if(r<=mid){
			lson->map(l,r,v);
		}else if(l>mid){
			rson->map(l,r,v);
		}else{
			lson->map(l,mid,v);
			rson->map(mid+1,r,v);
		}
		up();
	}
	void set0(int l,int r){
		if(lend==l&&rend==r){
			tag0=true,tagmap=tag2=false;
			info.init(0,r-l+1);
			if(k==4){
				info2.init(0,r-l+1);
			}
			return;
		}
		down();
		if(r<=mid){
			lson->set0(l,r);
		}else if(l>mid){
			rson->set0(l,r);
		}else{
			lson->set0(l,mid);
			rson->set0(mid+1,r);
		}
		up();
	}
	void pull(int l,int r){
		assert(k==4);
		if(lend==l&&rend==r){
			if(tag2){
				set0(l,r);
			}
			if(tag0){
				return;
			}
			if(tagmap){
				down();
			}
			tag2=true;
			info=info2,info2.init(0,r-l+1);
			info*=(mapper){0,2,1,3};
			return;
		}
		down();
		if(r<=mid){
			lson->pull(l,r);
		}else if(l>mid){
			rson->pull(l,r);
		}else{
			lson->pull(l,mid);
			rson->pull(mid+1,r);
		}
		up();
	}
	Info ask(int l,int r){
		if(lend==l&&rend==r){
			return info;
		}
		down();
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return lson->ask(l,mid)+rson->ask(mid+1,r);
	}
}seg,pol[N*2],*pool;
inline SegmentTree* SegmentTree::nn(){
	return pool++;
}
#undef int
int main(){
#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
#endif
	for(int tot=ni,n,tot2;tot--;){
		n=ni,k=ni,tot2=ni;
		pool=pol;
		seg.build(1,n);
		while(tot2--){
			int t=ni,l=ni,r=ni;
			if(t==1){
				int v=ni;
				if(v==0){
					continue;
				}
				mapper m;
				for(int i=0;i<k;i++){
					m.a[i]=(i+v)%k;
				}
				seg.map(l,r,m);
			}else if(t==2){
				int v=ni;
				if(v==0){
					seg.set0(l,r);
				}else if(v==2&&k==4){
					seg.pull(l,r);
				}else if(v!=1){
					assert(gcd(v,k)==1);
					mapper m;
					for(int i=0;i<k;i++){
						m.a[i]=(i*v)%k;
					}
					seg.map(l,r,m);
				}
			}else{
				assert(t==3);
				printf("%d\n",seg.ask(l,r).ans.sum());
			}
		}
	}
}
