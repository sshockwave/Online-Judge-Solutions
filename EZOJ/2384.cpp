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
const int N=20,D=26;
int f[1<<N];
namespace SAM{
	struct Node;
	typedef Node* node;
	struct Node{
		node lnk,go[D];
		int len;
		int mask;
		inline node ext(int c);
	}pool[N];
	node n=pool;
	inline node nn(){
		return ++n;
	}
	inline node Node::ext(int c){
		node p=this,np=nn();
		np->len=p->len+1;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=np;
		}
		if(p==0)return np->lnk=pool,np;
		node q=p->go[c];
		if(q->len==p->len+1)return np->lnk=q,np;
		assert(q->len>p->len+1);
		node nq=nn();
		*nq=*q;
		nq->len=p->len+1;
		q->lnk=np->lnk=nq;
		for(;p&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		return np;
	}
	inline void work(){
		for(node p=n;p>pool;p--){
			apmax(f[p->mask],p->len);
			p->lnk->mask|=p->mask;
		}
	}
}
namespace trie{
	const int N=1000010;
	const int rt=1;
	int son[N][D],mask[N],n=1;
	inline int nn(int &x){
		return x==0?x=++n:x;
	}
	char* ins(int x,char s[],int m){
		mask[x]|=m;
		while(true){
			char c=s[0];
			if(c==0)return s;
			if(c=='<')return s+1;
			s=ins(nn(son[x][c-'a']),s+1,m);
		}
	}
	void dfs(int x,SAM::node y){
		y->mask=mask[x];
		for(int i=0;i<D;i++){
			if(son[x][i]){
				dfs(son[x][i],y->ext(i));
			}
		}
	}
}
char s[trie::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("wechat.in","r",stdin);
	freopen("wechat.out","w",stdout);
#endif
	int n=ni;
	for(int i=0;i<n;i++){
		scanf("%s",s);
		trie::ins(trie::rt,s,1<<i);
	}
	memset(f,0,sizeof(f));
	trie::dfs(trie::rt,SAM::pool);
	SAM::work();
	for(int s=(1<<n)-1;s;s--){
		for(int t=s;t;t^=t&-t){
			apmax(f[s^(t&-t)],f[s]);
		}
	}
	for(int tot=ni;tot--;){
		scanf("%s",s);
		int mask=0;
		for(int i=0;i<n;i++){
			mask|=(s[i]-'0')<<i;
		}
		printf("%d\n",f[mask]);
	}
	return 0;
}
