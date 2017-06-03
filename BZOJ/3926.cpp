#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){
		a=b;
	}
}
const int N=100010,SIGMA=10;
struct SAM{
	typedef SAM* node;
	int val;
	node lnk,go[SIGMA];
	SAM(){
		memset(this,0,sizeof(SAM));
	}
	inline node nn();
	inline node ext(int);
}sam,pool[N*20],*ptop=pool;
inline SAM* SAM::nn(){
	return ptop++;
}
inline ostream & operator << (ostream & out,SAM*p){
	if(p==&sam){
		out<<"ini";
	}else{
		out<<(int)(p-pool);
	}
	return out;
}
inline SAM* SAM::ext(int c){
	if(go[c]){
		return go[c];
	}
	go[c]=nn();
	go[c]->val=val+1;
	node p=lnk;
	for(;p&&p->go[c]==NULL;p=p->lnk){
		p->go[c]=go[c];
	}
	if(p==NULL){
		go[c]->lnk=&sam;
		return go[c];
	}
	node q=p->go[c];
	assert(q!=NULL);
	if(q->val==p->val+1){
		go[c]->lnk=q;
		return go[c];
	}
	assert(q->val>p->val+1);
	node nq=nn();
	*nq=*q;
	nq->val=p->val+1;
	q->lnk=go[c]->lnk=nq;
	for(;p&&p->go[c]==q;p=p->lnk){
		p->go[c]=nq;
	}
	return go[c];
}
struct Trie{
	typedef Trie* node;
	node son[SIGMA];
	Trie(){
		memset(son,0,sizeof(son));
	}
	inline node nn(){
		static node n=new Trie[N*20];
		return n++;
	}
	inline node go(int c){
		if(son[c]==NULL){
			son[c]=nn();
		}
		return son[c];
	}
	void dfs(SAM *node){
		for(int i=0;i<SIGMA;i++){
			if(son[i]){
				son[i]->dfs(node->ext(i));
			}
		}
	}
}trie;
namespace G{
	const int E=N*2;
	int deg[N],head[N],to[E],bro[E],etop=0;
	int c[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(deg,0,sizeof(deg));
	}
	inline void add_edge(int u,int v){
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
		deg[u]++;
	}
	inline void add(int u,int v){
		add_edge(u,v);
		add_edge(v,u);
	}
	void dfs(int x,int f,Trie& fa){
		Trie &cur=*fa.go(c[x]);
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){
				dfs(v,x,cur);
			}
		}
	}
}
int main(){
	G::init();
	int n=ni;ni;
	for(int i=1;i<=n;i++){
		G::c[i]=ni;
	}
	for(int i=1;i<n;i++){
		G::add(ni,ni);
	}
	for(int i=1;i<=n;i++){
		if(G::deg[i]==1){
			G::dfs(i,0,trie);
		}
	}
	sam.val=0;
	trie.dfs(&sam);
	lint ans=0;
	for(SAM *i=pool;i<ptop;i++){
		ans+=i->val-i->lnk->val;
	}
	printf("%lld\n",ans);
}