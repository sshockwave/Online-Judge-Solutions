#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef long double db;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=200010,D=26;
namespace sam{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	node null,ini,n;
	struct Node{
		node lnk,go[D];
		int len;
		bool end;
		db f;
		inline node ext(int);
	}pool[N],Null;
	inline node nn(node x=null){
		return *n=*x,n++;
	}
	inline node Node::ext(int c){
		node p=this;
		const node np=nn();
		np->len=len+1;
		np->end=true;
		for(;p!=null&&p->go[c]==null;p=p->lnk){
			p->go[c]=np;
		}
		if(p==null)return np->lnk=ini,np;
		const node q=p->go[c];
		if(q->len==p->len+1)return np->lnk=q,np;
		const node nq=nn(q);
		nq->len=p->len+1;
		nq->end=false;
		q->lnk=np->lnk=nq;
		for(;p!=null&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		return np;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lnk=null;
		for(int i=0;i<D;i++){
			null->go[i]=null;
		}
	}
	inline void reset(){
		n=pool,ini=nn();
	}
	int cnt[N];
	inline int topsort(node lst[],int len){
		mset(cnt,0,len+1);
		for(node i=pool+1;i<n;i++){
			++cnt[i->len];
		}
		for(int i=1;i<=len;i++){
			cnt[i]+=cnt[i-1];
		}
		for(node i=pool;i<n;i++){
			lst[cnt[i->len]--]=i;
		}
		return n-pool-1;
	}
}
char s[N];
sam::node lst[sam::N];
inline db Main(){
	scanf("%s",s+1);
	const int n=strlen(s+1);
	sam::reset();
	sam::node p=sam::ini;
	for(int i=n;i>=1;i--){
		p=p->ext(s[i]-'a');
	}
	int ndcnt=sam::topsort(lst,n);
	for(int i=ndcnt;i>=0;i--){
		const sam::node x=lst[i];
		if(x->end){
			x->f=0;
		}else{
			x->f=1/x->f;
		}
		if(i){
			x->lnk->f+=1/(x->f+(x->len-x->lnk->len));
		}
	}
	return lst[0]->f;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	sam::init();
	for(int tot=ni;tot--;){
		printf("%.13Lf\n",Main());
	}
	return 0;
}
