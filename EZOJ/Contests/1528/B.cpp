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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=200010,D=3;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int s[N];
namespace sam{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node go[D];
		node lnk;
		int len,mxlen;
		int pos;
		lint f;
		node son[D];
	}Null,pool[N];
	node null,st,n=pool;
	inline node nn(node x=null){
		return *n=*x,n++;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lnk=null;
		for(int i=0;i<D;i++){
			null->go[i]=null;
			null->son[i]=null;
		}
		st=nn();
	}
	inline node ext(node p,int c){
		node np=nn();
		np->len=p->len+1;
		for(;p!=null&&p->go[c]==null;p=p->lnk){
			p->go[c]=np;
		}
		if(p==null)return np->lnk=st,np;
		const node q=p->go[c];
		if(q->len==p->len+1)return np->lnk=q,np;
		const node nq=nn(q);
		nq->len=p->len+1;
		q->lnk=np->lnk=nq;
		for(;p->go[c]==q;p=p->lnk){
			p->go[c]=nq;
		}
		return np;
	}
	inline int topsort(node lst[],const int len){
		static int cnt[N];
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
sam::node lst[sam::N];
int win[N],tie[N];
lint _win[N];
inline lint dp(int n){
	const int ncnt=sam::topsort(lst,n*2);
	for(int i=ncnt;i>=0;i--){
		const sam::node x=lst[i];
		lint &ans=x->f;
		int soncnt=0;
		x->mxlen=x->len;
		for(int j=0;j<D;j++){
			soncnt+=x->son[j]->mxlen>n;
			apmax(x->mxlen,x->son[j]->mxlen);
		}
		if(soncnt==0){
			ans=0;
		}else for(int j=0;j<D;j++){//use j
			lint curmin=LINF;
			for(int k=0;k<D;k++){
				if(x->son[k]->mxlen<=n)continue;
				lint cur=x->son[k]->f;
				cur+=_win[x->son[k]->len]-_win[x->len+1];
				if(k==j){
					cur+=tie[x->len+1];
				}else if(j==(k+1)%D){
					cur+=win[x->len+1];
				}
				apmin(curmin,cur);
			}
			assert(curmin<LINF);
			apmax(ans,curmin);
		}
		if(i){
			const sam::node fa=x->lnk;
			fa->pos=x->pos;
			fa->son[s[x->pos+fa->len]]=x;
		}
	}
	return sam::st->f;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dexterity.in","r",stdin);
	freopen("dexterity.out","w",stdout);
#endif
	sam::init();
	const int n=ni;
	for(int i=1;i<=n;i++){
		char ch;
		for(;ch=getchar(),!(ch=='r'||ch=='s'||ch=='p'););
		s[i]=s[i+n]=ch=='p'?0:ch=='s'?1:2;
	}
	for(int i=1;i<=n;i++){
		win[i]=ni,tie[i]=ni;
	}
	mset(win+n+1,0,n);
	mset(tie+n+1,0,n);
	for(int i=1;i<=n*2;i++){
		_win[i]=_win[i-1]+win[i];
	}
	sam::node p=sam::st;
	for(int i=n*2;i>=1;i--){
		p=sam::ext(p,s[i]);
		p->pos=i;
	}
	printf("%lld\n",dp(n));
	return 0;
}
