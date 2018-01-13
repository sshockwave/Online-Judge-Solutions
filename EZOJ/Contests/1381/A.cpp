#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <vector>
#include <map>
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
const int N=100010,INF=0x7f7f7f7f;
int n,tim;
namespace seg{
	const int N=::N*324*1.5;//TODO::*3
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		int lson,rson;
		int sum,tag;
		inline void up();
	}pool[N],Null;
	inline void Node::up(){
		sum=pool[lson].sum+pool[rson].sum;
	}
	inline node nn(node x=null){
		static node n=pool+1;
		assert(n-pool<N);
		return x->tag>tim?*n=*x,n->tag=tim,n++:x;
	}
	inline void init(){
		memset(null=pool,0,sizeof(pool[0]));
		null->lson=null->rson=0;
		null->tag=INF;
	}
	node add(node x,int p,int v,int l=0,int r=n-1){
		x=nn(x);
		if(l==r){
			x->sum+=v;
		}else{
			int m=(l+r)>>1;
			if(p<=m){
				x->lson=add(pool+x->lson,p,v,l,m)-pool;
			}else{
				x->rson=add(pool+x->rson,p,v,m+1,r)-pool;
			}
			x->up();
		}
		return x;
	}
	typedef vector<node>vi;
	int sum;
	int kth(const vi &x,int k,int l=0,int r=n-1){
		sum=0;
		for(int i=0,ti=x.size();i<ti;i++){
			sum+=x[i]->sum;
		}
		if(sum<k)return r+1;
		if(l==r)return l;
		int m=(l+r)>>1,ans;
		{//left
			vi vec;
			for(int i=0,ti=x.size();i<ti;i++){
				if(x[i]->lson){
					vec.push_back(pool+x[i]->lson);
				}
			}
			ans=kth(vec,k,l,m);
		}
		if(ans>m){//right
			vi vec;
			for(int i=0,ti=x.size();i<ti;i++){
				if(x[i]->rson){
					vec.push_back(pool+x[i]->rson);
				}
			}
			ans=kth(vec,k-sum,m+1,r);
		}
		return ans;
	}
}
int a[N<<1];
int type,lastans=0;
inline int getnum(){
	return ni^(type*lastans);
}
typedef map<int,seg::node>mp;
mp rt[N];//time->rt
int pos[N],pre[N<<1],idx[N<<1],nxt[N<<1];
inline void addv(int x,int col,int v){
	for(;x<=n;x+=x&(-x)){
		assert(rt[x].lower_bound(tim)!=rt[x].end());
		seg::node t=rt[x].lower_bound(tim)->second;
		rt[x][tim]=seg::add(t,col,v);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("kth.in","r",stdin);
	freopen("kth.out","w",stdout);
#endif
	n=ni;
	int w=ni,tot=ni;
	type=ni;
	seg::init();
	memset(pos,0,sizeof(pos));
	for(int i=1;i<=n;i++){
		a[i]=ni;
		rt[i][n+1]=seg::null;
		pre[i]=pos[a[i]];
		idx[i]=idx[pre[i]]+1;
		pos[a[i]]=i;
		if(pre[i]){
			nxt[pre[i]]=i;
		}
	}
	for(int i=n+1;i<=(n<<1);i++){
		a[i]=i-n-1;
		pre[i]=pos[a[i]];
		idx[i]=idx[pre[i]]+1;
		pos[a[i]]=i;
		nxt[i]=i;
		if(pre[i]){
			nxt[pre[i]]=i;
		}
	}
	for(int i=n;i>=1;i--){
		//add to the first
		tim=i;
		addv(i,a[i],1);
		if(idx[pos[a[i]]]-idx[i]+1>w){//delete the last
			addv(pos[a[i]],a[i],-1-w);
			addv(nxt[pos[a[i]]],a[i],w);
			pos[a[i]]=pre[pos[a[i]]];
		}
	}
	while(tot--){
		int l=getnum(),r=getnum(),k=getnum();
		seg::vi vec;
		for(int x=r;x;x^=x&-x){
			seg::node nd=rt[x].lower_bound(l)->second;
			if(nd!=seg::null){
				vec.push_back(nd);
			}
		}
		printf("%d\n",lastans=seg::kth(vec,k));
	}
	return 0;
}
