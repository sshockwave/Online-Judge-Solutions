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
const int SH=18,N=(1<<(SH-1))|10,D=26;
namespace trie{
	const int N=52;
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
	inline friend Trans operator + (const Trans &a,const Trans &b){
		Trans tmp;
		for(int i=1;i<=trie::n;i++){
			tmp.to[i]=b.to[a.to[i]],tmp.f[i]=a.f[i]+b.f[a.to[i]];
			assert(tmp.to[i]);
		}
		return tmp;
	}
}lett[D],str[N][SH];
char s[N];
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r,sh;
		Trans tr;
		int st,pos,ed;//[st,ed)
		inline void puttag(int s,int p,int e){
			st=s,pos=p,ed=e;
			tr=str[p][sh];
		}
		inline void up(){
			for(int i=1;i<=trie::n;i++){
				assert(lson->tr.to[i]);
				assert(rson->tr.to[i]);
			}
			tr=lson->tr+rson->tr;
		}
		inline void dn(){
			if(pos!=-1){
				lson->puttag(st,pos,ed);
				rson->puttag(st,(pos-st+(1<<(sh-1)))%(ed-st)+st,ed);
				pos=-1;
			}
		}
	}pool[N];
	node build(int l,int r,int sh){
		static node n=pool;
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r,x->sh=sh;
		x->pos=-1;
		if(l==r){
			x->tr=lett[s[l]-'a'];
		}else{
			x->lson=build(l,x->m,sh-1);
			x->rson=build(x->m+1,r,sh-1);
			x->up();
		}
		return x;
	}
	void cov(node x,int l,int r,int st,int pos,int ed){
		if(x->l==l&&x->r==r)return x->puttag(st,pos,ed);
		x->dn();
		if(r<=x->m){
			cov(x->lson,l,r,st,pos,ed);
		}else if(l>x->m){
			cov(x->rson,l,r,st,pos,ed);
		}else{
			cov(x->lson,l,x->m,st,pos,ed);
			cov(x->rson,x->m+1,r,st,(pos-st+x->m+1-l)%(ed-st)+st,ed);
		}
		x->up();
	}
	Trans ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->tr;
		x->dn();
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
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
	int n=strlen(s),sh=0;
	for(;(1<<sh)<n;sh++);
	memset(s+n,'a',(1<<sh)-n);
	seg::node rt=seg::build(0,(1<<sh)-1,sh);
	for(int st=0,ed=0;tot2--;){
		int op=ni,l=ni-1,r=ni-1;
		if(op==1){
			scanf("%s",s);
			ed=st+strlen(s);
			for(int i=st;i<ed;i++){
				str[i][0]=lett[s[i-st]-'a'];
			}
			for(int j=0;j<sh;j++){
				for(int i=st;i<ed;i++){
					str[i][j+1]=str[i][j]+str[(i-st+(1<<j))%(ed-st)+st][j];
				}
			}
			seg::cov(rt,l,r,st,st,ed);
			st=ed;
		}else{
			printf("%d\n",seg::ask(rt,l,r).f[1]);
		}
	}
	return 0;
}
