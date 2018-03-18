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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010,D=26;
namespace trie{
	const int N=55;
	int son[N][D],ed[N],fail[N],fa[N],n=0;
	inline int nn(int &x){
		return x==0?x=++n:x;
	}
	inline void init(){
		memset(son,0,sizeof(son));
		memset(ed,0,sizeof(ed));
		int rt;
		nn(rt);
	}
	inline void ins(char s[]){
		int x=1;
		for(;s[0];x=nn(son[x][s++[0]-'a']));
		ed[x]++;
	}
	int que[N];
	inline void bfs(){
		int qh=0,qt=0;
		que[qt++]=1;
		fail[1]=0,fa[1]=0;
		for(int i=0;i<D;i++){
			son[0][i]=1;
		}
		while(qh<qt){
			int x=que[qh++];
			ed[x]+=ed[fail[x]];
			for(int i=0;i<D;i++){
				int &s=son[x][i];
				if(s){
					fail[s]=son[fail[x]][i];
					fa[s]=x;
					que[qt++]=s;
				}else{
					s=son[fail[x]][i];
				}
			}
		}
	}
}
struct Trans{
	int to[trie::N],f[trie::N];
	inline void id(){
		for(int i=1;i<=trie::n;i++){
			to[i]=i,f[i]=0;
		}
	}
	inline friend Trans operator + (Trans a,Trans b){
		Trans tmp;
		for(int i=1;i<=trie::n;i++){
			tmp.to[i]=b.to[a.to[i]],tmp.f[i]=a.f[i]+b.f[a.to[i]];
			assert(tmp.to[i]);
		}
		return tmp;
	}
	inline Trans fpow(int e){
		if(e==0){
			Trans tr;
			tr.id();
			return tr;
		}
		Trans tr=fpow(e>>1);
		return e&1?(tr+tr+*this):(tr+tr);
	}
}lett[D];
char s[N];
namespace seg{
	const int N=::N<<2;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		Trans tr;
		node tagrt;
		int tagl;
		inline void up(){
			assert(tagrt==0);
			tr=lson->tr+rson->tr;
		}
		inline void dn();
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->tagrt=0;
		if(l==r){
			x->tr=lett[s[l]-'a'];
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	Trans ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->tr;
		x->dn();
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
	void cov(node x,int l,int r,node rt,int sh){
		if(x->l==l&&x->r==r){
			x->tagrt=rt,x->tagl=sh;
			int lenrt=rt->r+1;
			int lend=sh,rend=sh+r-l;
			if(rend<lenrt){
				x->tr=ask(rt,lend,rend);
			}else{
				x->tr=ask(rt,lend,rt->r)+rt->tr.fpow(rend/lenrt-1)+ask(rt,0,rend%lenrt);
			}
			return;
		}
		x->dn();
		if(r<=x->m){
			cov(x->lson,l,r,rt,sh);
		}else if(l>x->m){
			cov(x->rson,l,r,rt,sh);
		}else{
			cov(x->lson,l,x->m,rt,sh);
			cov(x->rson,x->m+1,r,rt,(sh+x->m+1-l)%(rt->r+1));
		}
		x->up();
	}
	inline void Node::dn(){
		if(tagrt){
			cov(lson,l,m,tagrt,tagl);
			cov(rson,m+1,r,tagrt,(tagl+m+1-l)%(tagrt->r+1));
			tagrt=0;
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	int tot1=ni,tot2=ni;
	trie::init();
	while(tot1--){
		scanf("%s",s);
		trie::ins(s);
	}
	trie::bfs();
	for(int i=0;i<D;i++){
		for(int j=1;j<=trie::n;j++){
			int x=lett[i].to[j]=trie::son[j][i];
			lett[i].f[j]=trie::ed[x];
		}
	}
	scanf("%s",s);
	seg::node rt=seg::build(0,strlen(s)-1);
	while(tot2--){
		int op=ni,l=ni-1,r=ni-1;
		if(op==1){
			scanf("%s",s);
			seg::cov(rt,l,r,seg::build(0,strlen(s)-1),0);
		}else{
			printf("%d\n",seg::ask(rt,l,r).f[1]);
		}
	}
	return 0;
}
