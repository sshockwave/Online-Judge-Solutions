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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=30010;
const lint LINF=0x2f7f7f7f7f7f7f7fll;
int *tmpv;
inline bool cmp_lst(int a,int b){
	return tmpv[a]<tmpv[b];
}
struct Perm{
	int v[N],lst[N],rnk[N];
	inline void init(int n){
		for(int i=1;i<=n;i++){
			lst[i]=i;
		}
		tmpv=v,sort(lst+1,lst+n+1,cmp_lst);
		for(int i=1;i<=n;i++){
			rnk[lst[i]]=i;
		}
	}
	inline int operator [] (int i){
		return i>0?v[lst[i]]:0;
	}
}a,b;
struct Mat{
	const static int N=16;
	lint a[N][N];
	inline void clr(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				a[i][j]=-LINF;
			}
		}
	}
	inline void getmul(const Mat &x,const Mat &y){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				lint ans=-LINF;
				for(int k=0;k<N;k++){
					apmax(ans,x.a[i][k]+y.a[k][j]);
				}
				a[i][j]=ans;
			}
		}
	}
};
Mat* tmpmat;
void psh(int s,int t,lint v){
	if((t&48)!=48)return;
	apmax(tmpmat->a[s][t^48],v);
	/*
	cut<<"\tstate ";
	cut<<((s>>3)&1);
	cut<<((s>>2)&1);
	cut<<((s>>1)&1);
	cut<<((s>>0)&1);
	cut<<"->";
	cut<<((t>>3)&1);
	cut<<((t>>2)&1);
	cut<<((t>>1)&1);
	cut<<((t>>0)&1);
	cut<<"\tv="<<v<<endl;
	*/
}
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		Mat mat;
		inline void up(){
			mat.getmul(lson->mat,rson->mat);
		}
		inline void getinfo(){
			assert(l==r);
			mat.clr(),tmpmat=&mat;
			for(int ts=0;ts<Mat::N;ts++){
				const int s=ts<<2;
				for(int i=1;i<=3;i++){
					if((s>>((i<<1)+1))&1)continue;
					if(i<3&&m-i<1)continue;
					if(i<3&&a.lst[m]==b.lst[m-i])continue;
					for(int j=1;j<=3;j++){
						if((s>>(j<<1))&1)continue;
						if(j<3&&m-j<1)continue;
						if(j<3&&b.lst[m]==a.lst[m-j])continue;
						int t=s;
						lint v=0;
						if(i<3){
							t|=1,t|=1<<((i<<1)+1);
							v+=(lint)a[m]*b[m-i];
						}
						if(j<3){
							t|=2,t|=1<<(j<<1);
							v+=(lint)b[m]*a[m-j];
						}
						psh(ts,t,v);
					}
				}
				if(a.lst[m]!=b.lst[m]){
					psh(ts,s|3,(lint)a[m]*b[m]);
				}
			}
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->getinfo();
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void alt_upd(node x,int l,int r){
		if(x->l==x->r)return x->getinfo();
		if(r<=x->m){
			alt_upd(x->lson,l,r);
		}else if(l>x->m){
			alt_upd(x->rson,l,r);
		}else{
			alt_upd(x->lson,l,x->m);
			alt_upd(x->rson,x->m+1,r);
		}
		x->up();
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	const int n=ni;
	int tot=ni;
	for(int i=1;i<=n;i++){
		a.v[i]=ni;
	}
	for(int i=1;i<=n;i++){
		b.v[i]=ni;
	}
	a.init(n),b.init(n);
	const seg::node rt=seg::build(1,n);
	for(;tot--;){
		int x=ni,y=ni;
		swap(b.v[x],b.v[y]);
		swap(b.lst[b.rnk[x]],b.lst[b.rnk[y]]);
		swap(b.rnk[x],b.rnk[y]);
		seg::alt_upd(rt,b.rnk[x],min(n,b.rnk[x]+3));
		seg::alt_upd(rt,b.rnk[y],min(n,b.rnk[y]+3));
		printf("%lld\n",rt->mat.a[15][15]);
	}
	return 0;
}
