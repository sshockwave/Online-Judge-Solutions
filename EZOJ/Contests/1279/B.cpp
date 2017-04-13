#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=200010,logN=20,M=310,INF=0x7f7f7f7f;
int fa[N][logN],hash[N][logN],dep[N],ldep[N],ch[N];
namespace SA{
	int sa[N],w[N],*rank,*sa2;//rank[i>0]>=0 sa[i>=0]>0
	inline bool equal(int a,int b,int j){
		return rank[a]==rank[b]&&rank[fa[a][j]]==rank[fa[b][j]];
	}
	inline int extend(int n,int m,int j){
		rank[0]=0;
		memset(w,0,m<<2);
		for(int i=1;i<=n;i++){
			w[rank[fa[i][j]]]++;
		}
		for(int i=1;i<m;i++){
			w[i]+=w[i-1];
		}
		for(int i=n;i>=1;i--){
			sa2[--w[rank[fa[i][j]]]]=i;
		}
		memset(w,0,m<<2);
		for(int i=1;i<=n;i++){
			w[rank[i]]++;
		}
		for(int i=1;i<m;i++){
			w[i]+=w[i-1];
		}
		for(int i=n-1;i>=0;i--){
			sa[--w[rank[sa2[i]]]]=sa2[i];
		}
		int p=0;
		sa2[sa[0]]=0;
		for(int i=1;i<n;i++){
			sa2[sa[i]]=equal(sa[i],sa[i-1],j)?p:++p;
		}
		swap(rank,sa2);
		return p+1;
	}
	int len[N],tmp[N];
	inline void work(int n){
		rank=ch,sa2=tmp;
		memset(w,0,M<<2);
		for(int i=1;i<=n;i++){
			w[rank[i]]=1;
		}
		for(int i=1;i<M;i++){
			w[i]+=w[i-1];
		}
		for(int i=1;i<=n;i++){
			rank[i]=w[rank[i]];
		}
		memset(w,0,M<<2);
		for(int i=1;i<=n;i++){
			w[rank[i]]++;
		}
		for(int i=1;i<M;i++){
			w[i]+=w[i-1];
		}
		for(int i=n;i>=1;i--){
			sa[--w[rank[i]]]=i;
		}
		for(int j=1,m=M;(m=extend(n,m,j))<n;j<<=1);
		memset(len,0,sizeof(len));
		for(int i=1;i+1<n;i++){
			int u=sa[i],v=sa[i+1];
			for(int j=min(ldep[u],ldep[v]);j>=0;j--){
				if(hash[u][j]==hash[v][j]){
					len[i]|=1<<j;
					u=fa[u][j],v=fa[v][j];
				}
			}
		}
	}
}
struct InfoSegmentTree{
	typedef InfoSegmentTree node;
	int l,r,mid,val;
	node *lson,*rson;
	void build(int lend,int rend){
		static node* pool=new node[N*2];
		l=lend,r=rend,mid=(l+r)>>1;
		if(l==r){
			val=SA::len[l];
		}else{
			(lson=pool++)->build(l,mid);
			(rson=pool++)->build(mid+1,r);
			val=min(lson->val,rson->val);
		}
	}
}I;
int ans=0;
struct SegmentTree{
	typedef SegmentTree node;
	int tol,tor;
	node *lson,*rson;
	SegmentTree():lson(0),rson(0){}
	void set(int x,InfoSegmentTree* val){
		if(val->l==val->r){
			tol=INF,tor=val->val;
		}
		static node* pool=new node[N*logN];
		if(x<=val->mid){
			(lson=pool++)->set(x,val->lson);
			tol=lson->tol;
			tor=min(val->rson->val,lson->tor);
		}else{
			(rson=pool++)->set(x,val->rson);//todo
			tol=min(val->lson->val,rson->tol);
			tor=rson->tor;
		}
	}
	friend node* merge(node* x,node* y,int d){
		if(x==0){
			return y;
		}
		if(y==0){
			return x;
		}
		x->lson=merge(x->lson,y->lson,d);
		x->rson=merge(x->rson,y->rson,d);
		apmax(x->tol,y->tol);
		apmax(x->tor,y->tor);
		apmax(ans,d+min(x->lson->tor,x->rson->tol));
	}
}T[N];
int main(){
	int n=ni();
	dep[1]=0;
	memset(fa,0,sizeof(fa));
	memset(ldep,0,sizeof(ldep));
	memset(ch,0,sizeof(ch));
	static int *pw=new int[N];
	static const int MOD=1000000007;
	pw[0]=1;
	for(int i=1;i<=n;i++){
		pw[i]=(lint)pw[i-1]*M%MOD;
	}
	for(int i=2;i<=n;i++){
		dep[i]=dep[fa[i][0]=ni()]+1;
		hash[i][0]=ch[i]=ni();
		for(int &k=ldep[i];fa[i][k+1]=fa[fa[i][k]][k];k++){
			hash[i][k+1]=((lint)pw[1<<k]*hash[fa[i][k]][k]%MOD+hash[i][k])%MOD;
		}
	}
	SA::work(n);
	I.build(0,n-1);
	for(int i=1;i<=n;i++){
		T[i].set(SA::rank[i],&I);
	}
	for(int i=n;i>1;i--){
		merge(T+fa[i][0],T+i,dep[fa[i][0]]);
	}
	printf("%d\n",ans);
}
