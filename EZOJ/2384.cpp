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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=20,L=1000010,D=26;
inline int lb(int x){
	return x&(-x);
}
struct SAM{
	typedef SAM* node;
	node lnk,go[D];
	int len,tag;
	node head,nxt;
	inline void ae(node x){
		x->nxt=head,head=x;
	}
	void dfs(){
		for(node i=head;i;i=i->nxt){
			i->dfs();
			tag|=i->tag;
		}
	}
	inline node add(int);
}pol[L*2],*pool=pol;
inline SAM* SAM::add(int c){
	node p=this,np=++pool;
	np->len=p->len+1;
	for(;p&&p->go[c]==0;p=p->lnk){
		p->go[c]=np;
	}
	if(p==0){
		np->lnk=pol;
		return go[c];
	}
	node q=p->go[c];
	if(q->len==p->len+1){
		np->lnk=q;
		return go[c];
	}
	node nq=++pool;
	*nq=*q,q->lnk=np->lnk=nq;
	nq->len=p->len+1;
	for(;p&&p->go[c]==q;p=p->lnk){
		p->go[c]=nq;
	}
	return go[c];
}
char s[L];
int ans[1<<N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("wechat.in","r",stdin);
	freopen("wechat.out","w",stdout);
#endif
	int n=ni;
	for(int i=0;i<n;i++){
		scanf("%s",s);
		static SAM* stk[L];
		int t=0;
		stk[0]=pol;
		for(int j=0;s[j];j++){
			if(isalpha(s[j])){
				stk[t+1]=stk[t]->add(s[j]-'a');
				stk[++t]->tag|=1<<i;
			}else{
				t--;
			}
		}
	}
	for(SAM* i=pol+1;i<=pool;i++){
		i->lnk->ae(i);
	}
	pol->dfs();
	for(SAM* i=pol+1;i<=pool;i++){
		apmax(ans[i->tag],i->len);
	}
	for(int i=(1<<n)-1;i;i--){
		for(int j=i;j;j^=lb(j)){
			apmax(ans[i^lb(j)],ans[i]);
		}
	}
	for(int tot=ni;tot--;){
		scanf("%s",s);
		int tim=0;
		for(int i=0;i<n;i++){
			tim|=(s[i]-'0')<<i;
		}
		printf("%d\n",ans[tim]);
	}
	return 0;
}
