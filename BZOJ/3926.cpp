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
	node p=this,np=nn();
	np->val=val+1;
	for(;p&&p->go[c]==NULL;p=p->lnk){
		p->go[c]=np;
	}
	if(p==0){
		np->lnk=&sam;
		return np;
	}
	node q=p->go[c];
	assert(q!=NULL);
	if(q->val==p->val+1){
		np->lnk=q;
		return np;
	}
	assert(q->val>p->val+1);
	node nq=nn();
	*nq=*q;
	nq->val=p->val+1;
	q->lnk=np->lnk=nq;
	for(;p&&p->go[c]==q;p=p->lnk){
		p->go[c]=nq;
	}
	return np;
}
namespace G{
	const int E=N*2;
	int deg[N],head[N],to[E],bro[E],e=0;
	int c[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(deg,0,sizeof(deg));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
		deg[u]++,deg[v]++;
	}
	void dfs(int x,int f,SAM *node){
		node=node->ext(c[x]);
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(v!=f){dfs(v,x,node);}
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
	sam.val=0;
	for(int i=1;i<=n;i++){
		if(G::deg[i]==1){
			G::dfs(i,0,&sam);
		}
	}
	lint ans=0;
	for(SAM *i=pool;i<ptop;i++){
		ans+=i->val-i->lnk->val;
	}
	printf("%lld\n",ans);
}