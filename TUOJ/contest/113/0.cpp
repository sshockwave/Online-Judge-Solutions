#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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
const int N=200010;
struct Data{
	lint w,f;
	inline friend Data operator + (const Data &a,const Data &b){
		return (Data){a.w+b.w,max(a.f,b.f-a.w)};
	}
	inline lint eval(){
		return w+f;
	}
};
namespace T{
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lson,rson;
		int size;
		Data val,sum;
		node lend,rend;
		unsigned long long pri;
		inline void init(){
			*this=*null;
			pri=0;
			for(int i=0;i<4;i++){
				pri=pri*RAND_MAX+rand();
			}
		}
		inline void up(){
			size=lson->size+1+rson->size;
			sum=lson->sum+val+rson->sum;
			lend=lson!=null?lson->lend:this;
			rend=rson!=null?rson->rend:this;
		}
	}pool[N],Null;
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
		null->lend=null->rend=null;
		null->val=null->sum=(Data){0,0};
	}
	void sp(node x,int k,node &lhs,node &rhs){
		if(x==null)return lhs=rhs=null,void();
		if(k==0)return lhs=null,rhs=x,void();
		if(k==x->size)return lhs=x,rhs=null,void();
		if(k>x->lson->size){
			lhs=x,sp(x->rson,k-x->lson->size-1,x->rson,rhs);
		}else{
			rhs=x,sp(x->lson,k,lhs,x->lson);
		}
		x->up();
	}
	void sp_f(node x,lint f,node &lhs,node &rhs){
		if(x==null)return lhs=rhs=null,void();
		if(f<x->lend->val.f)return lhs=null,rhs=x,void();
		if(f>=x->rend->val.f)return lhs=x,rhs=null,void();
		if(x->val.f<=f){
			lhs=x,sp_f(x->rson,f,x->rson,rhs);
		}else{
			rhs=x,sp_f(x->lson,f,lhs,x->lson);
		}
		x->up();
	}
	node mg_force(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		if(u->pri<v->pri){
			swap(u,v);
		}
		node lhs,rhs;
		sp_f(v,u->val.f,lhs,rhs);
		u->lson=mg_force(u->lson,lhs);
		u->rson=mg_force(u->rson,rhs);
		u->up();
		return u;
	}
	void dfs_print(node x){
		if(x==null)return;
		dfs_print(x->lson);
		cout<<"("<<x->val.w<<"+="<<x->val.f<<")";
		dfs_print(x->rson);
	}
}
int fa[N];
T::Node pt[N];
T::node nd[N];
lint ans[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	ni;
	int n=ni;
	for(int i=2;i<=n;i++){
		fa[i]=ni;
	}
	T::init();
	for(int i=1;i<=n;i++){
		pt[i].init(),pt[i].val=(Data){ni,0};
		nd[i]=T::null;
	}
	for(int i=n;i>=1;i--){
		pt[fa[i]].val.f+=pt[i].val.w;
		pt[i].val.w-=pt[i].val.f;
		for(;nd[i]!=T::null&&(pt[i].val.w<0||nd[i]->lend->val.f<=pt[i].val.f);){
			T::node x;
			T::sp(nd[i],1,x,nd[i]);
			pt[i].val=pt[i].val+x->val;
		}
		pt[i].up();
		assert(pt[i].val.w>=0);
		nd[i]=T::mg_force(pt+i,nd[i]);
		ans[i]=nd[i]->sum.eval();
		/*
		   cout<<"for node "<<i<<": ";
		   T::dfs_print(nd[i]);
		   cout<<endl;
		   */
		if(i>1){
			nd[fa[i]]=T::mg_force(nd[fa[i]],nd[i]);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",ans[i]);
	}
	putchar('\n');
	return 0;
}
