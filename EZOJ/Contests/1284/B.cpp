#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=200010;
struct State{
	State *lnk,*go[26];
	int val,right,head,dfn,dfe;
	State():lnk(0),val(0),right(0),head(-1){
		memset(go,0,sizeof(go));
	}
}pools[N*6],*pool=pools;
struct Graph{
	State* to[N*6];
	int bro[N*6],tim;
	inline void add_edge(State* u,State* v){
		static int eid=0;
		to[eid]=v;
		bro[eid]=u->head;
		u->head=eid++;
	}
	void dfs(State *x){
		x->dfn=++tim;
		for(int i=x->head;~i;i=bro[i]){
			dfs(to[i]);
			x->right+=to[i]->right;
		}
		x->dfe=tim;
	}
}T;
struct SAM{
	State ini,*tail;
	int n;
	SAM():tail(&ini){}
	inline State* extend(int c){
		State *p=tail;
		tail=pool++;
		tail->val=p->val+1;
		tail->right=1;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=tail;
		}
		if(p==0){
			tail->lnk=&ini;
			return tail;
		}
		State *q=p->go[c];
		if(q->val==p->val+1){
			tail->lnk=q;
			return tail;
		}
		State *nq=pool++;
		*nq=*q;
		nq->right=0;
		nq->val=p->val+1;
		tail->lnk=q->lnk=nq;
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		return tail;
	}
}sam1,sam2;
struct Point{
	int x,y;
	inline friend bool operator < (const Point &a,const Point &b){
		return a.y<b.y;
	}
}pt[N];
struct Query{
	int l,r,y,bln;
	bool end;
	static Query q[N*2],*qid;
	static void add(State* a,State* b,int i){
		if(a&&b){
			*(qid++)=(Query){a->dfn,a->dfe,b->dfn-1,i,0};
			*(qid++)=(Query){a->dfn,a->dfe,b->dfe,i,1};
		}
	}
	inline friend bool operator < (const Query &a,const Query &b){
		return a.y<b.y;
	}
};
Query Query::q[N*2],*Query::qid=Query::q;
struct BIT{
	int c[N*2],n;
	BIT(){
		memset(c,0,sizeof(c));
	}
	inline int lowbit(int x){
		return x&(-x);
	}
	inline int add(int x,int v){
		for(;x<=n;x+=lowbit(x)){
			c[x]+=v;
		}
	}
	inline int sum(int x){
		int ans=0;
		for(;x;x^=lowbit(x)){
			ans+=c[x];
		}
		return ans;
	}
	inline int sum(int l,int r){
		return sum(r)-sum(l-1);
	}
}bt;
State *gor[N],*gol[N];
char s[N];
int ans[N];
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1),tot=ni();
	gor[0]=&sam1.ini;
	for(int i=1;i<=n;i++){
		gor[i]=sam1.extend(s[i]-'a');
	}
	gol[n+1]=&sam2.ini;
	for(int i=n;i>=1;i--){
		gol[i]=sam2.extend(s[i]-'a');
	}
	for(State* i=pools;i<pool;i++){
		T.add_edge(i->lnk,i);
	}
	T.tim=0,T.dfs(&sam1.ini),sam1.n=T.tim;
	T.tim=0,T.dfs(&sam2.ini),sam2.n=T.tim;
	for(int i=1;i<=n;i++){
		pt[i]=(Point){gor[i-1]->dfn,gol[i+1]->dfn};
	}
	memset(ans,0,sizeof(ans));
	for(int toti=1;toti<=tot;toti++){
		scanf("%s",s+1);
		int n=strlen(s+1);
		memset(gor,0,(n+1)<<2);
		memset(gol+1,0,(n+1)<<2);
		gor[0]=&sam1.ini,gol[n+1]=&sam2.ini;
		for(int i=1;i<=n&&(gor[i]=gor[i-1]->go[s[i]-'a']);i++);
		for(int i=n;i>=1&&(gol[i]=gol[i+1]->go[s[i]-'a']);i--);
		for(int i=1;i<=n;i++){
			Query::add(gor[i-1],gol[i+1],toti);
		}
		if(gor[n]){
			ans[toti]=-gor[n]->right*(n-1);
		}
	}
	sort(pt+1,pt+n+1);
	sort(Query::q,Query::qid);
	bt.n=sam1.n;
	Query *q=Query::q;
	for(;q<Query::qid&&q->y==0;q++);
	for(int i=1,j=1;i<=sam2.n;i++){
		for(;j<=n&&pt[j].y==i;bt.add(pt[j].x,1),j++);
		for(;q<Query::qid&&q->y==i;q++){
			if(q->end){
				ans[q->bln]+=bt.sum(q->l,q->r);
			}else{
				ans[q->bln]-=bt.sum(q->l,q->r);
			}
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",ans[i]);
	}
}
