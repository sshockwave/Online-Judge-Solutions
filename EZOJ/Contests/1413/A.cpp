#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <fstream>
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
const int N=3000010,M=30000010,D=4,O=1000000007;
char s[N];
namespace sam{
	const int N=::N*2*2;
	struct Node;
	typedef Node* node;
	struct Node{
		node lnk,go[D];
		node son[D];
		int len;
		int pos;
		int cnt;//count of appearances
		lint sum;
		int d;
		inline node ext(int,int,int);
	}pool[N];
	node pol=pool;
	inline node nn(){
		return pol++;
	}
	node ini;
	inline node Node::ext(int c,int pos,int d){
		node p=this,np=nn();
		np->len=p->len+1;
		np->pos=pos;
		np->d=d;
		for(;p&&p->go[c]==0;p=p->lnk){
			p->go[c]=np;
		}
		if(p==0)return np->lnk=ini,np;
		node q=p->go[c];
		if(q->len==p->len+1)return np->lnk=q,np;
		node nq=nn();
		nq->lnk=q->lnk;
		memcpy(nq->go,q->go,sizeof(nq->go));
		nq->pos=pos;
		nq->d=d;
		nq->len=p->len+1;
		q->lnk=np->lnk=nq;
		for(;p!=0&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		return np;
	}
	node que[N];
	int cnt[N];
	inline void buildtree(int n){
		for(node i=pool+1;i<ini;i++){
			i->lnk->son[(int)s[i->pos-i->lnk->len]]=i;
			++cnt[i->len];
		}
		for(node i=ini+1;i<pol;i++){
			i->lnk->son[(int)s[i->pos+i->lnk->len]]=i;
			++cnt[i->len];
		}
		cnt[0]+=2;
		for(int i=1;i<=n;i++){
			cnt[i]+=cnt[i-1];
		}
		for(node i=pool;i<pol;i++){
			que[--cnt[i->len]]=i;
		}
	}
	inline void buildsum(){
		for(node *i=que+(pol-pool)-1,*ti=que+2;i>=ti;--i){
			(*i)->lnk->cnt+=(*i)->cnt;
		}
		for(node *i=que+2,*ti=que+(pol-pool);i<ti;++i){
			node x=*i;
			x->sum=(x->sum+x->lnk->sum+(lint)(x->len-x->lnk->len)*x->cnt)%O;
		}
	}
}
inline int charmap(char c){
	return c=='A'?0:c=='T'?1:c=='C'?2:3;
}
char t[M];
inline void work1(sam::node x){
	int i=0;
	using namespace sam;
	for(node y;t[i]&&(y=x->son[charmap(t[i])])!=0;){
		x=y;
		for(;t[i]&&i<x->len&&charmap(t[i])==s[x->pos-i];++i);
		if(i<x->len)break;
	}
	++x->cnt,x->sum+=i-x->len;
}
inline void work2(sam::node x){
	int i=0;
	using namespace sam;
	for(node y;t[i]&&(y=x->son[charmap(t[i])])!=0;){
		x=y;
		for(;t[i]&&i<x->len&&charmap(t[i])==s[x->pos+i];++i);
		if(i<x->len)break;
	}
	++x->cnt,x->sum+=i-x->len;
}
sam::node pre[N],suf[N];
inline string space(){
	ifstream fin("/proc/self/status");
	return string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dna.in","r",stdin);
	freopen("dna.out","w",stdout);
#endif
	scanf("%s",s+1);
	int n=strlen(s+1);
	sam::node prest=pre[0]=sam::ini=sam::nn();
	for(int i=1;i<=n;i++){
		s[i]=charmap(s[i]);
	}
	for(int i=1;i<=n;i++){
		pre[i]=pre[i-1]->ext(s[i],i,1);
	}
	sam::node sufst=suf[n+1]=sam::ini=sam::nn();
	for(int i=n;i>=1;i--){
		suf[i]=suf[i+1]->ext(s[i],i,-1);
	}
	sam::buildtree(n);
	for(int i=1,m=ni;i<=m;i++){
		scanf("%s",t);
		work1(prest),work2(sufst);
	}
	sam::buildsum();
	int ans=0;
	for(int i=1;i<n;i++){
		ans=(ans+pre[i]->sum*suf[i+1]->sum)%O;
	}
	printf("%d\n",(ans+O)%O);
	return 0;
}
