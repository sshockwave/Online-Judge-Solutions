#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <algorithm>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=600010;
struct SAM{
	struct state{
		state *lnk,*go[26];
		int val,dfn,dfe,leaf,right;
		set<state*>son;
		state():lnk(0),leaf(-1),right(0){
			memset(go,0,sizeof(go));
		}
	}ini,*tail;
	SAM():tail(&ini),tim(0){}
	inline void extend(int c,int pos){
		static state *pool=new state[N];
		state *p=tail;
		tail=pool++;
		tail->val=p->val+1;
		tail->right=1;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=tail;
		}
		if(p==0){
			tail->lnk=&ini;
			ini.leaf=-1;
			tail->leaf=pos;
			ini.son.insert(tail);
			return;
		}
		state *q=p->go[c];
		if(q->val==p->val+1){
			tail->lnk=q;
			q->leaf=-1;
			tail->leaf=pos;
			q->son.insert(tail);
			return;
		}
		state *nq=pool++;
		memcpy(nq->go,q->go,sizeof(q->go));
		nq->lnk=q->lnk;
		nq->val=p->val+1;
		q->lnk->son.erase(q);
		q->lnk->son.insert(nq);
		q->lnk=tail->lnk=nq;
		nq->son.insert(q);
		nq->son.insert(tail);
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
	}
	int tim,pos[N];
	void dfs(state *x){
		x->dfn=++tim;
		if(~x->leaf){
			pos[x->leaf]=tim;
		}
		for(set<state*>::iterator it=x->son.begin();it!=x->son.end();it++){
			dfs(*it);
			x->right+=(*it)->right;
		}
		x->dfe=tim;
	}
}sam1,sam2;
char s[N];
inline void addall(){
	int i=0;
	for(;s[i];i--){
		sam1.extend(s[i]-'a',i);
	}
	while(--i>=0){
		sam2.extend(s[i]-'a',i);
	}
}
struct point{
	int x,y;
}pt[N];
inline bool operator < (const point &a,const point &b){
	return a.y<b.y;
}
struct query{
	int y,l,r,bln;
	bool end;
}q[N*26];
inline bool operator < (const query &a,const query &b){
	return a.y<b.y;
}
int ans[N],qtop=0;
inline void add_query(SAM::state* s1,SAM::state* s2,int i){
	if(s1==0||s2==0){
		return;
	}
	q[qtop++]=(query){s2->dfn-1,s1->dfn,s1->dfe,i,0};
	q[qtop++]=(query){s2->dfe,s1->dfn,s1->dfe,i,1};
}
SAM::state *gor[N],*gol[N];
struct BIT{
	int c[N],n;
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
		for(;x>0;x-=lowbit(x)){
			ans+=c[x];
		}
		return ans;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}bt;
int main(){
	scanf("%s",s);
	int tn=strlen(s);
	addall();
	sam1.dfs(&sam1.ini);
	sam2.dfs(&sam2.ini);
	bt.n=sam1.tim;
	for(int i=0;s[i];i++){
		pt[i]=(point){sam1.pos[i],sam2.pos[i]};
	}
	memset(ans,0,sizeof(ans));
	int tot=ni();
	for(int toti=1;toti<=tot;toti++){
		scanf("%s",s+1);
		int n=strlen(s+1);
		gor[0]=&sam1.ini,gol[n+1]=&sam2.ini;
		for(int i=1;i<=n&&(gor[i]=gor[i-1]->go[s[i]-'a']);i++);
		for(int i=n;i>=1&&(gol[i]=gol[i+1]->go[s[i]-'a']);i++);
		if(gor[n]){
			ans[toti]=-(n-1)*gor[n]->right;
		}
		for(int i=1;i<=n;i++){
			for(int j=0;j<26;j++){
				add_query(gor[i-1]->go[j],gol[i+1]->go[j],toti);
			}
		}
	}
	sort(pt,pt+tn);
	sort(q,q+qtop);
	for(int i=1,pp=0,pq=0;i<=sam2.tim;i++){
		for(;pp<tn&&pt[pp].y==i;bt.add(pt[pp++].x,1));
		for(;pq<qtop&&q[pq].y==i;pq++){
			if(q[pq].end){
				ans[q[pq].bln]+=bt.ask(q[pq].l,q[pq].r);
			}else{
				ans[q[pq].bln]-=bt.ask(q[pq].l,q[pq].r);
			}
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",ans[i]);
	}
}
