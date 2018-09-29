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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
namespace disc{
	const int N=::N<<2;
	int *num[N],mmp[N],n=0;
	inline void psh(int &x){
		num[++n]=&x;
	}
	inline bool num_cmp(int* a,int* b){
		return *a<*b;
	}
	inline int main(){
		sort(num+1,num+n+1,num_cmp);
		mmp[0]=0;
		int m=0;
		for(int i=1;i<=n;i++){
			*num[i]=mmp[m]!=*num[i]?mmp[++m]=*num[i],m:m;
		}
		return m;
	}
}
namespace seg{
	const int N=::N<<2;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int sum;
		bool rev;
		inline void putrev(){
			sum=disc::mmp[r]-disc::mmp[l-1]-sum;
			rev^=1;
		}
		inline void up(){
			assert(!rev);
			sum=lson->sum+rson->sum;
		}
		inline void dn(){
			if(rev){
				lson->putrev();
				rson->putrev();
				rev=false;
			}
		}
	}pool[N];
	node build(const int l,const int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->sum=disc::mmp[r]-disc::mmp[l-1];
		x->rev=false;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	void putrev(const node x,int l,int r){
		if(x->l==l&&x->r==r)return x->putrev();
		x->dn();
		if(r<=x->m){
			putrev(x->lson,l,r);
		}else if(l>x->m){
			putrev(x->rson,l,r);
		}else{
			putrev(x->lson,l,x->m);
			putrev(x->rson,x->m+1,r);
		}
		x->up();
	}
}
struct Event{
	int x,l,r;
	inline friend bool operator < (const Event &a,const Event &b){
		return a.x<b.x;
	}
}ev[N<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("f.in","r",stdin);
	freopen("f.out","w",stdout);
#endif
	int n=ni,m=ni;
	int es=0;
	for(int tot=ni;tot--;){
		const int a=ni,b=ni;
		const int c=ni,d=ni;
		ev[++es]=(Event){a-1,c-1,d};
		disc::psh(ev[es].l);
		disc::psh(ev[es].r);
		ev[++es]=(Event){b,c-1,d};
		disc::psh(ev[es].l);
		disc::psh(ev[es].r);
	}
	int mx;
	{
		int tmp=m;
		disc::psh(tmp);
		mx=disc::main();
	}
	sort(ev+1,ev+es+1);
	lint ans=0;
	const seg::node rt=seg::build(1,mx);
	int lx=0;
	for(int i=1;i<=es;i++){
		ans+=(lint)rt->sum*(ev[i].x-lx),lx=ev[i].x;
		seg::putrev(rt,ev[i].l+1,ev[i].r);
	}
	ans+=(lint)rt->sum*(n-lx);
	printf("%lld\n",ans);
	return 0;
}
