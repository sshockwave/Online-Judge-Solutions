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
const int N=100010,D=26;
lint ans=0;
namespace sam{
	const int N=::N*2;
	struct Node;
	typedef Node* node;
	struct Node{
		node lnk,go[D];
		int len,mxl;//mxl::max valid length
		node head,bro;
		inline node ext(int,int);
	}pool[N],Null;
	node null,ini,pol=pool;
	inline node nn(node x=null){
		static node &n=pol;
		return *n=*x,n++;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lnk=null;
		for(int i=0;i<D;i++){
			null->go[i]=null;
		}
		null->head=null,null->bro=null;
		ini=nn();
	}
	inline node Node::ext(int c,int e){
		node p=this,np=nn();
		np->len=p->len+1,np->mxl=e;
		for(;p!=null&&p->go[c]==null;p=p->lnk){
			p->go[c]=np;
		}
		if(p==null)return np->lnk=ini,np;
		node q=p->go[c];
		if(q->len==p->len+1)return np->lnk=q,np;
		node nq=nn(q);
		nq->len=p->len+1;
		apmin(nq->mxl,nq->len);
		q->lnk=np->lnk=nq;
		for(;p!=null&&p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		return np;
	}
	inline void ae(node u,node v){
		v->bro=u->head,u->head=v;
	}
	inline void build(){
		for(node i=pool+1;i<pol;i++){
			ae(i->lnk,i);
		}
	}
	int dfs(node x){
		int mxl=x->mxl;
		for(node i=x->head;i!=null;i=i->bro){
			apmax(mxl,dfs(i));
		}
		apmin(mxl,x->len);
		if(x!=ini&&mxl>x->lnk->len){
			ans+=mxl-x->lnk->len;
		}
		return mxl;
	}
}
char s[N],b[N];
int _b[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	scanf("%s%s",s+1,b+1);
	int n=strlen(s+1),k=ni;
	sam::init();
	sam::node p=sam::ini;
	for(int i=1,j=0;i<=n;i++){
		_b[i]=_b[i-1]+(b[i]=='0');
		for(;_b[i]-_b[j]>k;j++);
		p=p->ext(s[i]-'a',i-j);
	}
	sam::build();
	sam::dfs(sam::ini);
	printf("%lld\n",ans);
	return 0;
}
