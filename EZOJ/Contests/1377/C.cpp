#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <vector>
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
const int N=500010,logN=20;
const lint LINF=0x7f7f7f7f7f7f7f7f;
namespace seg{
	const int N=::N*::logN;
	struct Node;
	typedef Node* node;
	node null,ppt[N],*pt;
	struct Node{
		node lson,rson;
		int mex;
		lint sum,diff;
		inline pair<int,lint>gans();
		inline void* operator new(size_t,node x=null){
			return **pt=*x,*(pt++);
		}
		inline void operator delete(void* p){
			*--pt=(node)p;
		}
		inline void up(int l,int r){
			int m=(l+r)>>1;
			mex=lson->mex<=m?max(lson->mex,l):max(rson->mex,m+1);
			sum=lson->sum+rson->sum;
			diff=lson->diff;
			if(rson->diff>-LINF){
				apmax(diff,rson->diff-lson->sum);
			}
		}
		inline void down(){
			lson=lson!=null?lson:new Node;
			rson=rson!=null?rson:new Node;
		}
	}Null,pool[N];
	inline void init(){
		pt=ppt;
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
		null->mex=1,null->diff=-LINF;
		for(int i=0;i<N;i++){
			ppt[i]=pool+i;
		}
	}
	lint ask(node x,int l=1,int r=N-1){
		if(x==null||l==r)return 1;
		int m=(l+r)>>1;
		if(x->lson->diff>1)return ask(x->lson,l,m);
		else return ask(x->rson,m+1,r)+x->lson->sum;
	}
	inline pair<int,lint>Node::gans(){
		return make_pair(mex,ask(this));
	}
	node add(node x,int p,lint v,int l=1,int r=N-1){
		if(x==null){
			x=new Node;
		}
		if(l==r){
			x->sum=max(x->sum+v,0ll);
			x->diff=l;
			x->mex=x->sum?l+1:l;
		}else{
			int m=(l+r)>>1;
			if(p<=m){
				add(x->lson,p,v,l,m);
			}else{
				add(x->rson,p,v,m+1,r);
			}
			x->up(l,r);
		}
		if(x->sum==0){
			delete x;
			return null;
		}else return x;
	}
	node mg(node x,node y,int l=1,int r=N-1){
		if(x==null||y==null)return x!=null?x:y;
		if(l==r){
			x->sum+=y->sum;
			assert(x->diff==l);
			assert(x->mex==l+1);
		}else{
			int m=(l+r)>>1;
			x->lson=mg(x->lson,y->lson,l,m);
			x->rson=mg(x->rson,y->rson,m+1,r);
			x->up(l,r);
			delete y;
		}
		return x;
	}
	void dfs(node x,int l=1,int r=N-1){
		if(x==null)return;
		if(l==r){
			assert(x->sum);
			for(int p=x->sum;p;p-=l){
				printf("%d ",l);
			}
		}else{
			int m=(l+r)>>1;
			dfs(x->lson,l,m);
			dfs(x->rson,m+1,r);
		}
	}
}
seg::node rt[N];
int n,lastans=0;
typedef map<int,pair<int,lint> >mp;
inline void putans(mp &m,int tim){
	pair<int,lint>p=(--m.upper_bound(tim))->second;
	printf("%d %lld\n",p.first,p.second);
}
mp ans[N];
inline int gnum(){
	return (ni+lastans-1)%n+1;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("forgive.in","r",stdin);
	freopen("forgive.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		rt[i]=seg::null;
		ans[i][0]=make_pair(1,1);
	}
	for(int tim=1,tot=ni;tim<=tot;tim++){
		switch(ni){
			case 1:
				{
					int u=gnum(),g=ni;
					seg::add(rt[u],g,g);
					ans[u][tim]=rt[u]->gans();
					break;
				}
			case 2:
				{
					int u=gnum(),g=ni;
					seg::add(rt[u],g,-g);
					ans[u][tim]=rt[u]->gans();
					break;
				}
			case 3:
				{
					int u=gnum(),v=gnum();
					rt[u]=seg::mg(rt[u],rt[v]),rt[v]=seg::null;
					ans[u][tim]=rt[u]->gans();
					ans[v][tim]=rt[v]->gans();
					break;
				}
			case 4:
				{
					int u=gnum();
					putans(ans[u],tim);
					break;
				}
			case 5:
				{
					int u=gnum(),t=ni;
					putans(ans[u],t-1);
				}
		}
	}
	for(int i=1;i<=n;i++){
		seg::dfs(rt[i]);
		puts("0");
	}
	return 0;
}
