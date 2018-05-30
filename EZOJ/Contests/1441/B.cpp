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
const int N=2010,INF=0x7f7f7f7f;
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		int val[5];//%3==0 ; v; (v+1)/2
		inline void init(int v){
			assert(l==r);
			for(int i=0;i<3;i++){
				val[i]=v+(m+i+2)/3;
			}
			val[3]=v,val[4]=v+((m+1)>>1);
		}
		inline void up(){
			for(int i=0;i<5;i++){
				val[i]=min(lson->val[i],rson->val[i]);
			}
		}
	}pool[N];
	node pt;
	inline void reset(){
		pt=pool;
	}
	node build(int l,int r,int f[]){
		node x=pt++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->init(f[x->m]);
		}else{
			x->lson=build(l,x->m,f);
			x->rson=build(x->m+1,r,f);
			x->up();
		}
		return x;
	}
	int ask(node x,int l,int r,int k){
		if(x->l==l&&x->r==r)return x->val[k];
		if(r<=x->m)return ask(x->lson,l,r,k);
		if(l>x->m)return ask(x->rson,l,r,k);
		return min(ask(x->lson,l,x->m,k),ask(x->rson,x->m+1,r,k));
	}
}
inline int ask(const seg::node rt,const int y){
	int f=INF;
	int l=0,r;
	{//max==y/2
		r=(y+1)>>1,apmin(r,rt->r);
		if(l>r)return f;
		apmin(f,seg::ask(rt,l,r,3)+((y+1)>>1));
		l=r+1;
	}
	{//max==(x+y)/3
		r=y*2,apmin(r,rt->r);
		if(l>r)return f;
		apmin(f,seg::ask(rt,l,r,y%3)+y/3);
		l=r+1;
	}
	{//max==x/2
		r=rt->r;
		if(l>r)return f;
		apmin(f,seg::ask(rt,l,r,4));
		l=r+1;
	}
	return f;
}
int a[N],f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("ni.in","r",stdin);
	freopen("ni.out","w",stdout);
#endif
	int n;
	{
		int mxhei=ni;
		n=ni;
		static char s[N];
		mset(a,0,n+1);
		for(int i=1;i<=mxhei;i++){
			scanf("%s",s+1);
			for(int j=1;j<=n;j++){
				if(s[j]=='*'){
					apmax(a[j],mxhei-i+1);
				}
			}
		}
	}
	f[0]=0;
	for(int i=1;i<=n;i++){
		seg::reset();
		seg::node rt=seg::build(0,a[i-1],f);
		for(int j=0;j<=a[i];j++){
			f[j]=ask(rt,a[i]-j);
			assert(f[j]<INF);
		}
	}
	printf("%d\n",f[0]);
	return 0;
}
