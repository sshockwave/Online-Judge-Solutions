#include <iostream>
#include <cstdio>
#include <cstring>
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
namespace sam{
	const int N=::N*2*2;
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lnk,go[D];
		node head,bro;
		int tlen[D];//bef trans d shortened to
		int len;
		int cnt;//count of appearances
		lint sum;
		inline node ext(int);
	}pool[N],Null;
	node pol=pool;
	inline node nn(node x=null){
		static node &n=pol;
		return *n=*x,n++;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lnk=null;
		null->head=null->bro=null;
		for(int i=0;i<D;i++){
			null->go[i]=null;
		}
	}
	node ini;
	inline node Node::ext(int c){
		node p=this,np=nn();
		np->len=p->len+1;
		for(;p!=null&&p->go[c]==null;p=p->lnk){
			p->go[c]=np;
		}
		if(p==null)return np->lnk=ini,np;
		node q=p->go[c];
		if(q->len==p->len+1)return np->lnk=q,np;
		node nq=nn(q);
		nq->len=p->len+1;
		q->lnk=np->lnk=nq;
		for(;p!=null&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		return np;
	}
	node que[N];
	int qh=0,qt=0;
	inline void ae(node u,node v){
		v->bro=u->head,u->head=v;
	}
	inline void bfs(){
		for(node i=pool;i<pol;i++){
			if(i->lnk==null){
				que[qt++]=i;
			}else{
				ae(i->lnk,i);
			}
		}
		while(qh<qt){
			node x=que[qh++];
			for(node i=x->head;i!=null;i=i->bro){
				que[qt++]=i;
			}
			for(int j=0;j<D;j++){
				if(x->go[j]==null){
					if(x->lnk==null){
						x->go[j]=x;
						x->tlen[j]=-1;
					}else{
						x->go[j]=x->lnk->go[j];
						x->tlen[j]=x->lnk->tlen[j];
					}
				}else{
					x->tlen[j]=x->len;
				}
			}
		}
	}
	inline void buildsum(){
		for(int i=qt-1;i>=0;i--){
			node x=que[i];
			if(x->lnk!=null){
				x->lnk->cnt+=x->cnt;
			}
		}
		for(int i=0;i<qt;i++){
			node x=que[i];
			x->sum=(x->sum+x->lnk->sum+(lint)(x->len-x->lnk->len)*x->cnt)%O;
		}
	}
}
char s[M];
sam::node pre[N],suf[N];
inline int charmap(char c){
	return c=='A'?0:c=='T'?1:c=='G'?2:3;
}
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
	sam::init();
	sam::node prest=pre[0]=sam::ini=sam::nn();
	for(int i=1;i<=n;i++){
		pre[i]=pre[i-1]->ext(charmap(s[i]));
	}
	sam::node sufst=suf[n+1]=sam::ini=sam::nn();
	for(int i=n;i>=1;i--){
		suf[i]=suf[i+1]->ext(charmap(s[i]));
	}
	sam::bfs();
	for(int i=1,m=ni;i<=m;i++){
		scanf("%s",s);
		sam::node p=prest,q=sufst;
		using sam::null;
		int len=0;
		for(;s[len];len++);
		int plen=0,qlen=0;
		for(int j=len-1;j>=0;j--){
			int c=charmap(s[j]);
			plen=min(plen,p->tlen[c])+1,p=p->go[c];
			qlen=min(qlen,q->tlen[c])+1,q=q->go[c];
		}
		if(p!=prest){
			++p->cnt,p->sum+=plen-p->len;
		}
		if(q!=sufst){
			++q->cnt,q->sum+=qlen-q->len;
		}
	}
	sam::buildsum();
	int ans=0;
	for(int i=1;i<n;i++){
		ans=(ans+pre[i]->sum*suf[i+1]->sum)%O;
	}
	printf("%d\n",(ans+O)%O);
	return 0;
}
