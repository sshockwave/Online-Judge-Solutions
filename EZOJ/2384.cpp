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
const int N=20,D=26,L=1000010;
int f[1<<N];
namespace SAM{
	const int N=L*2;
	struct Node;
	typedef Node* node;
	struct Node{
		//SAM
		node lnk;
		int len,nxt[D];
		//Info
		int mask;
		inline node go(int c);
	}pool[N];
	node n=pool;
	inline node nn(){
		return ++n;
	}
	inline node Node::go(int c){
		node p=this,np=nn();
		np->len=p->len+1;
		for(;p&&p->nxt[c]==0;p=p->lnk){
			p->nxt[c]=np-pool;
		}
		if(p==0)return np->lnk=pool,np;
		node q=pool+p->nxt[c];
		if(q->len==p->len+1)return np->lnk=q,np;
		assert(q->len>p->len+1);
		node nq=nn();
		*nq=*q;
		nq->len=p->len+1;
		q->lnk=np->lnk=nq;
		for(;p&&pool+p->nxt[c]==q;p=p->lnk){
			p->nxt[c]=nq-pool;
		}
		return np;
	}
	node lst[N];
	int cnt[N];
	inline void work(){
		memset(cnt,0,sizeof(cnt));
		int mx=0;
		for(node x=pool+1;x<=n;x++){
			cnt[x->len]++;
			apmax(mx,x->len);
		}
		for(int i=1;i<=mx;i++){
			cnt[i]+=cnt[i-1];
		}
		for(node x=pool+1;x<=n;x++){
			lst[cnt[x->len]--]=x;
		}
		for(int i=n-pool;i>=1;i--){
			node x=lst[i];
			apmax(f[x->mask],x->len);
			x->lnk->mask|=x->mask;
		}
	}
}
namespace trie{
	const int N=1000010;
	int son[N][D],mask[N],n=1;
	inline int nn(int &x){
		return x==0?x=++n:x;
	}
	char* ins(int x,char s[],int m){
		mask[x]|=m;
		while(true){
			int c=s[0];
			if(c==0)return s;
			if(c=='<')return s+1;
			s=ins(nn(son[x][c-'a']),s+1,m);
		}
	}
	SAM::node node[N];
	int que[N];
	inline void bfs(){
		int qh=0,qt=0;
		node[1]=SAM::pool,que[qt++]=1;
		while(qh<qt){
			int x=que[qh++];
			node[x]->mask=mask[x];
			for(int i=0;i<D;i++){
				int s=son[x][i];
				if(s){
					node[s]=node[x]->go(i),que[qt++]=s;
				}
			}
		}
	}
}
char s[L];
int main(){
#ifndef ONLINE_JUDGE
	freopen("wechat.in","r",stdin);
	freopen("wechat.out","w",stdout);
#endif
	int n=ni;
	for(int i=0;i<n;i++){
		scanf("%s",s);
		trie::ins(1,s,1<<i);
	}
	memset(f,0,sizeof(f));
	trie::bfs(),SAM::work();
	for(int s=(1<<n)-1;s;s--){
		for(int t=s;t;t^=t&-t){
			apmax(f[s^(t&-t)],f[s]);
		}
	}
	for(int tot=ni;tot--;){
		scanf("%s",::s);
		int mask=0;
		for(int i=0;i<n;i++){
			mask|=(::s[i]-'0')<<i;
		}
		printf("%d\n",f[mask]);
	}
	return 0;
}
