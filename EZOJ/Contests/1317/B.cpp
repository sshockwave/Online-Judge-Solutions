#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=500010,D=26,INF=0x7f7f7f7f;
namespace SAM{
	const int TN=N*2,E=TN;
	struct node{
		node *lnk,*go[D];
		int val,head,mnright;
	}pol[TN],*pool=pol+1,*tail=pol;
	inline void init(){
		memset(pol,0,sizeof(pol));
		pol->mnright=-1;
	}
	inline void ext(int i,int c){
		node *p=tail,*np=pool++;
		np->val=p->val+1;
		np->mnright=i;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=np;
		}
		if(p==0){
			(tail=np)->lnk=pol;
			return;
		}
		node *q=p->go[c];
		if(q->val==p->val+1){
			(tail=np)->lnk=q;
			return;
		}
		assert(q->val>p->val+1);
		node *nq=pool++;
		*nq=*q;
		nq->val=p->val+1;
		q->lnk=np->lnk=nq;
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		tail=np;
	}
	node *to[E];
	int bro[E],e=0;
	inline void ae(node *u,node *v){
		e++,to[e]=v,bro[e]=u->head,u->head=e;
	}
	inline void build(){
		for(node *pt=pol+1;pt<pool;pt++){
			ae(pt->lnk,pt);
		}
	}
	void dfs(node *x){//get mnright
		for(int i=x->head;i;i=bro[i]){
			dfs(to[i]);
			apmin(x->mnright,to[i]->mnright);
		}
	}
}
char s[N];
int len[N],pos[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("encrypt.in","r",stdin);
	freopen("encrypt.out","w",stdout);
#endif
	scanf("%s",s);
	int n=0;
	for(;s[n];n++);
	{//SAM
		SAM::init();
		for(int i=n-1;i>=0;SAM::ext(i,s[i]-'a'),i--);
		SAM::build(),SAM::dfs(SAM::pol);
	}
	{//get len&&pos
		SAM::node *p=SAM::pol;
		for(int i=n-1;i>=0;i--){
			for(;p&&(p->go[s[i]-'a']==0||p->go[s[i]-'a']->mnright>=i);p=p->lnk);
			if(p){
				p=p->go[s[i]-'a'];
				len[i]=p->val;
				pos[i]=p->mnright;
			}else{
				len[i]=0;
				p=SAM::pol;
			}
		}
	}
	for(int i=0;s[i];){
		if(len[i]==0){
			printf("-1 %d ",(int)s[i]);
			i++;
		}else{
			printf("%d %d ",len[i],pos[i]);
			i+=len[i];
		}
	}
	putchar('\n');
}
