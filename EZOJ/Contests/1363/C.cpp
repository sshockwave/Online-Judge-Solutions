#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
const int N=50010,B=43;
int rt;
inline int grt(lint x){
	lint ans=sqrt(x);
	for(;ans*ans<x;ans++);
	for(;ans*ans>x;ans--);
	return ans;
}
lint a[N];
lint cacheval=-1,afterval;
int idx[N];
int lst[N],ls;
bool flag;
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		bool one;
		lint sum;
		inline void up(){
			one=lson->one&&rson->one;
			sum=lson->sum+rson->sum;
		}
	}*rt[B][B];
	node build(int l,int r,int m,int d){
		static node n=new Node[(N*B)<<2];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->sum=a[idx[l*m+d]];
			x->one=x->sum==1;
		}else{
			x->lson=build(l,x->m,m,d);
			x->rson=build(x->m+1,r,m,d);
			x->up();
		}
		return x;
	}
	void app(node x,int l,int r){
		if(x->one)return;
		if(x->l==l&&x->r==r){
			if(cacheval!=x->sum){
				cacheval=x->sum;
				afterval=grt(x->sum);
			}
			x->sum=afterval;
			x->one=x->sum==1;
			if(flag){
				lst[++ls]=l;
			}
			return;
		}
		if(r<=x->m){
			app(x->lson,l,r);
		}else if(l>x->m){
			app(x->rson,l,r);
		}else{
			app(x->lson,l,x->m);
			app(x->rson,x->m+1,r);
		}
		x->up();
	}
	lint ask(node x,int l,int r){
		if(x->one)return r-l+1;
		if(x->l==l&&x->r==r)return x->sum;
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
}
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],size[N],dep[N],top[N];
	int dfn[N],tim=0;
	inline void init(){
		memset(head,-1,sizeof(head));
		size[0]=son[0]=0;
		dfn[0]=-1;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs1(int x){
		size[x]=1;
		dep[x]=dep[fa[x]]+1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa[x]){
				fa[v]=x;
				dfs1(v);
				size[x]+=size[v];
				if(size[v]>size[son[x]]){
					son[x]=v;
				}
			}
		}
	}
	void dfs2(int x){
		idx[dfn[x]=tim++]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		cout<<"top["<<x<<"]="<<top[x]<<endl;
		if(son[x]){
			dfs2(son[x]);
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]&&v!=son[x]){
					dfs2(v);
				}
			}
		}
	}
	inline int lca(int u,int v){
		while(top[u]!=top[v]){
			if(dep[top[u]]>dep[top[v]]){
				u=fa[top[u]];
			}else{
				v=fa[top[v]];
			}
		}
		return dep[u]<dep[v]?u:v;
	}
	inline int fly(int x,int n){
		assert(n<dep[x]);
		for(int d;d=dep[x]-dep[fa[top[x]]],d<=n;n-=d,x=fa[top[x]]);
		return idx[dfn[x]-n];
	}
	int op;
	lint ans;
	inline void workp(int x){//TODO
		cout<<"Workingp("<<x<<")"<<endl;
		if(op==1)return ans+=a[x],void();
		if(a[x]==1)return;
		for(int i=1;i<=rt;i++){
			int d=dfn[x]%i,t=dfn[x]/i;
			seg::app(seg::rt[i][d],t,t);
		}
		a[x]=afterval;
	}
	inline int realdiv(int a,int b){
		return (a-a%b)/b;
	}
	inline void workintv(int l,int r,int m,int d){//dfn % m == d
		int nl=l<d?-1:(l-d)/m,nr=r<d?-1:(r-d)/m;
		if(nl*m+d<l){
			nl++;
		}
		assert(nl*m+d>=l);
		assert(nr*m+d<=r);
		if(nl>nr)return;
		if(m>rt){
			for(int i=nl*m+d,ti=nr*m+d;i<=ti;i+=m){
				workp(idx[i]);
			}
			return;
		}
		if(op){
			ans+=seg::ask(seg::rt[m][d],nl,nr);
			cout<<"asking ["<<nl<<","<<nr<<"] from ["<<m<<"]["<<d<<"]"<<endl;
			cout<<"ans="<<ans<<endl;
		}else{
			ls=0,flag=true;
			seg::app(seg::rt[m][d],nl,nr);
			flag=false;
			for(int i=1;i<=ls;i++){
				int x=lst[i]*m+d;
				for(int j=1;j<=rt;j++){
					if(j!=m){
						seg::app(seg::rt[j][x%j],x/j,x/j);
					}
				}
				a[idx[x]]=afterval;
			}
		}
	}
	inline void work(){
		op=ni,ans=0;
		int u=ni,v=ni,k=ni;
		int w=lca(u,v);
		int du=dep[u]%k,dv=(((dep[w]<<1)-dep[u])%k+k)%k;
		cout<<"working! u="<<u<<" v="<<v<<" du="<<du<<" dv="<<dv<<" k="<<k<<endl;
		cout<<"\top="<<op<<endl;
		if(dep[v]%k!=dv){
			workp(v);
		}
		cout<<"new lca"<<endl;
		while(top[u]!=top[v]){
			cout<<"("<<u<<","<<v<<")"<<endl;
			if(dep[top[u]]<dep[top[v]]){
				swap(u,v),swap(du,dv);
			}
			workintv(dfn[top[u]],dfn[u],k,((du-dep[top[u]]+dfn[top[u]])%k+k)%k);
			u=fa[top[u]];
		}
		cout<<"out of loop"<<endl;
		if(u==v){
			if(dep[w]%k==du){
				workp(w);
			}
		}else{
			if(dep[u]<dep[v]){
				swap(u,v),swap(du,dv);
			}
			cout<<"("<<u<<","<<v<<")"<<endl;
			workintv(dfn[v],dfn[u],k,((du-dep[v]+dfn[v])%k+k)%k);
		}
		if(op){
			printf("%lld\n",ans);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("down.in","r",stdin);
	freopen("down.out","w",stdout);
#endif
	int n=ni;
	rt=min(n,B-1);
	for(int i=1;i<=n;i++){
		a[i]=next_num<lint>();
	}
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::fa[1]=0,T::dfs1(1),T::dfs2(1);
	for(int i=1;i<=rt;i++){
		for(int j=0;j<i;j++){//x % i == j
			assert(j<n);
			seg::rt[i][j]=seg::build(0,(n-1-j)/i,i,j);
		}
	}
	for(int tot=ni;tot--;T::work());
	return 0;
}
