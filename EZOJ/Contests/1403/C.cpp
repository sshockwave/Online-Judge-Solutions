#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <list>
#include <utility>
#include <vector>
#include <algorithm>
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
const int N=2000010;
namespace poly{
	const int SH=20,N=1<<SH,O=998244353;
	int sh,n,invn,o[N],r[N];
	inline void clr(int a[],int x=0){
		memset(a+x,0,(n-x)*sizeof(a[0]));
	}
	inline int fpow(int x,int n){
		int a=1;
		for(;n;n>>=1,x=(lint)x*x%O){
			if(n&1){
				a=(lint)a*x%O;
			}
		}
		return a;
	}
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=fpow(n,O-2);
		r[0]=0,o[0]=1;
		for(int i=1,w=fpow(3,(O-1)>>sh);i<n;i++){
			r[i]=(r[i>>1]>>1)|((i&1)<<(sh-1)),o[i]=(lint)o[i-1]*w%O;
		}
	}
	inline void ntt(int a[],int d=1){
		for(int i=0;i<n;i++){
			if(r[i]<i){
				swap(a[i],a[r[i]]);
			}
		}
		for(int i=1;i<=sh;i++){
			int full=1<<i,half=full>>1;
			for(int j=0;j<half;j++){
				lint w=o[j<<(sh-i)];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=a[k+half]*w%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			reverse(a+1,a+n);
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
	int a[N],b[N];
}
struct frac:list<bool>{//front: low; back: high;
	int sh;//>>sh
	inline friend ostream & operator << (ostream & out,const frac &f){
		for(const_reverse_iterator it=f.rbegin();it!=f.rend();it++){
			out<<*it;
		}
		return out;
	}
	inline void canon(){
		for(;!empty()&&!back();pop_back());
		for(;!empty()&&!front();pop_front(),sh--);
	}
	inline void onesub(){
		int r=1;
		assert((int)size()<=sh);
		for(int i=size();i<sh;push_back(0),i++);
		for(iterator it=begin(),ti=end();it!=ti;it++){
			r+=!*it,*it=r&1,r>>=1;
		}
		for(;r;push_back(r&1),r>>=1);
		canon();
	}
	inline friend frac operator + (const frac &a,const frac &b){
		if(a.sh<b.sh)return b+a;
		frac c=b;
		for(int &i=c.sh;i<a.sh;c.push_front(0),i++);
		const_iterator pa=a.begin(),ta=a.end();
		iterator it=c.begin(),ti=c.end();
		int r=0;
		for(;it!=ti&&pa!=ta;it++,pa++){
			r+=*it+*pa,*it=r&1,r>>=1;
		}
		for(;pa!=ta;pa++){
			r+=*pa,c.push_back(r&1),r>>=1;
		}
		for(;it!=ti&&r;it++){
			r+=*it,*it=r&1,r>>=1;
		}
		for(;r;c.push_back(r&1),r>>=1);
		c.canon();
		return c;
	}
	inline void putbool(int a[])const{//compressed by 2^4
		poly::clr(a);
		int i=0;
		for(const_iterator it=begin(),ti=end();it!=ti;it++,i++){
			a[i>>2]|=(*it)<<(i&3);
		}
	}
	inline friend frac operator * (const frac &a,const frac &b){
		frac c;
		c.sh=a.sh+b.sh;
		poly::init(((a.size()+b.size())>>2)+3);
		a.putbool(poly::a),poly::ntt(poly::a);
		b.putbool(poly::b),poly::ntt(poly::b);
		for(int i=0;i<poly::n;i++){
			poly::a[i]=(lint)poly::a[i]*poly::b[i]%poly::O;
		}
		poly::ntt(poly::a,-1);
		lint r=0;
		for(int i=0;i<poly::n;i++,r>>=4){
			r+=poly::a[i];
			const int t=r&15;
			c.push_back(t&1);
			c.push_back((t>>1)&1);
			c.push_back((t>>2)&1);
			c.push_back((t>>3)&1);
		}
		c.canon();
		return c;
	}
};
int fa[N],deg[N],lst[N];
bool pval[N];
inline void addpt(int x,frac &f){
	if(x==1){
		f.clear(),f.sh=0;
	}else{
		addpt(fa[x],f);
	}
	f.push_back(pval[x]),f.sh++;
}
inline void solve(int l,int r,frac &a,frac &b){//f[r]=a*f[l-1]+b
	if(l==r){
		addpt(lst[l],b);
		b.canon();
		a=b,a.onesub(),a.sh++;
	}else{
		frac a2,b2;
		int m=(l+r)>>1;
		solve(l,m,a,b),solve(m+1,r,a2,b2);
		a=a*a2,b=a2*b+b2;
	}
	if(r-l+1>=10000){
		cout<<"solved("<<l<<","<<r<<")"<<endl;
	}
}
namespace grank{
	namespace SAM{
		const int N=::N<<1,D=2;
		struct Node;
		typedef Node* node;
		node ini,null;
		inline node nn(node x=null);
		struct Node{
			node lnk,go[2];
			int len,pos;
			int c,dfn;
			node head,nxt;
			inline node ext(int c,int pos){
				if(go[c]!=null)return go[c];
				node p=this,np=nn();
				np->len=p->len+1,np->pos=pos;
				for(;p!=null&&p->go[c]==null;p=p->lnk){
					p->go[c]=np;
				}
				if(p==null)return np->lnk=ini,np;
				node q=p->go[c];
				if(q->len==p->len+1)return np->lnk=q,np;
				node nq=nn(q);
				nq->len=p->len+1,nq->pos=pos;
				q->lnk=np->lnk=nq;
				for(;p!=null&&p->go[c]==q;p=p->lnk){
					p->go[c]=nq;
				}
				return np;
			}
		}pool[N],Null;
		node pol=pool;
		inline node nn(node x){
			return *pol=*x,pol++;
		}
		inline void init(){
			memset(null=&Null,0,sizeof(Null));
			null->lnk=null->go[0]=null->go[1]=null;
			null->head=null->nxt=null;
			ini=nn(),ini->len=0,ini->pos=0;
		}
		inline void ae(node u,node v){
			v->nxt=u->head,u->head=v;
		}
		int tim=0;
		void dfs(node x){
			if(x==null)return;
			x->dfn=++tim;
			node son[2]={null,null};
			for(node i=x->head;i!=null;i=i->nxt){
				son[i->c]=i;
			}
			dfs(son[0]),dfs(son[1]);
		}
	}
	namespace T{
		const int E=::N;
		int to[E],bro[E],head[N],e=0;
		inline void init(){
			memset(head,-1,sizeof(head));
		}
		inline void ae(int u,int v){
			to[e]=v,bro[e]=head[u],head[u]=e++;
		}
		SAM::node nd[N];
		vector<SAM::node>qry[N];
		int que[N];
		inline void bfs(){
			SAM::init();
			int qh=0,qt=0;
			nd[1]=SAM::ini->ext(1,1),que[qt++]=1;
			while(qh<qt){
				int x=que[qh++];
				for(int i=head[x],v;~i;i=bro[i]){
					v=to[i],nd[v]=nd[x]->ext(pval[v],v),que[qt++]=v;
				}
			}
		}
		bool stk[N];
		void dfs(int x,int dep){
			stk[dep]=pval[x];
			vector<SAM::node>::iterator it=qry[x].begin(),ti=qry[x].end();
			for(;it!=ti;it++){
				(*it)->c=stk[dep-(*it)->lnk->len];
			}
			for(int i=head[x];~i;i=bro[i]){
				dfs(to[i],dep+1);
			}
		}
	}
	inline void main(int n){
		T::init();
		for(int i=2;i<=n;i++){
			T::ae(fa[i],i);
		}
		T::bfs();
		for(SAM::node i=SAM::pool+1;i<SAM::pol;i++){
			T::qry[i->pos].push_back(i);
			SAM::ae(i->lnk,i);
		}
		T::dfs(1,1);
		SAM::dfs(SAM::ini);
	}
}
inline bool lcmp(int a,int b){
	return grank::T::nd[a]->dfn<grank::T::nd[b]->dfn;
}
namespace tobase10{
	struct bignum:list<char>{
		inline friend ostream & operator << (ostream &out,const bignum &b){
			for(const_reverse_iterator it=b.rbegin();it!=b.rend();it++){
				out<<(char)('0'+*it);
			}
			return out;
		}
		inline void fromInt(int r){
			for(;r;push_back(r%10),r/=10);
		}
		inline void mul(int v){
			int r=0;
			for(iterator it=begin();it!=end();it++){
				r+=v**it,*it=r%10,r/=10;
			}
			for(;r;push_back(r%10),r/=10);
		}
		inline friend bignum operator + (const bignum &a,const bignum &b){
			const_iterator ita=a.begin(),tia=a.end();
			const_iterator itb=b.begin(),tib=b.end();
			int r=0;
			bignum c;
			for(;ita!=tia&&itb!=tib;ita++,itb++){
				r+=*ita+*itb,c.push_back(r%10),r/=10;
			}
			for(;ita!=tia;ita++){
				r+=*ita,c.push_back(r%10),r/=10;
			}
			for(;itb!=tib;itb++){
				r+=*itb,c.push_back(r%10),r/=10;
			}
			for(;r;c.push_back(r%10),r/=10);
			return c;
		}
		inline void putnum(int a[])const{
			for(const_iterator it=begin();it!=end();it++){
				*(a++)=*it;
			}
		}
		inline friend bignum operator * (const bignum &a,const bignum &b){
			int sa=a.size(),sb=b.size();
			poly::init(sa+sb+1);
			a.putnum(poly::a),poly::clr(poly::a,sa),poly::ntt(poly::a);
			b.putnum(poly::b),poly::clr(poly::b,sb),poly::ntt(poly::b);
			for(int i=0;i<poly::n;i++){
				poly::a[i]=(lint)poly::a[i]*poly::b[i]%poly::O;
			}
			poly::ntt(poly::a,-1);
			int r=0;
			bignum c;
			for(int i=0;i<poly::n;i++){
				r+=poly::a[i],c.push_back(r%10),r/=10;
			}
			for(;!c.empty()&&*(c.rbegin())==0;c.pop_back());
			return c;
		}
		inline void output(){
			if(empty()){
				putchar('0');
			}else for(reverse_iterator it=rbegin(),ti=rend();it!=ti;it++){
				putchar('0'+*it);
			}
		}
	};
	struct info{
		bignum num,pw2;
		int lev;
	}stk[N];
	int ss=0;
	inline void collapse(){
		ss--;
		stk[ss].num=stk[ss].num+stk[ss].pw2*stk[ss+1].num;
		stk[ss].pw2=stk[ss].pw2*stk[ss+1].pw2;
		stk[ss+1].num.clear(),stk[ss+1].pw2.clear();
	}
	bignum res;
	void fpow2(int n){
		if(n==0){
			res.clear(),res.push_back(1);
		}else{
			fpow2(n>>1);
			res=res*res;
			if(n&1){
				res.mul(2);
			}
		}
	}
	inline void main(frac &x){
		frac::iterator it=x.begin(),ti=x.end();
		while(it!=ti){
			int a=0,b=1;
			for(int i=0;i<30&&it!=ti;i++,it++){
				a|=(*it)<<i;
				b<<=1;
			}
			ss++,stk[ss].num.fromInt(a),stk[ss].pw2.fromInt(b);
			for(;ss>1&&stk[ss].lev==stk[ss-1].lev;collapse(),stk[ss].lev++);
		}
		for(;ss>1;collapse());
		cout<<"collapse complete"<<endl;
		stk[ss].num.output();
		putchar('/');
		fpow2(x.sh);
		res.output();
		putchar('\n');
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fail.in","r",stdin);
	freopen("fail.out","w",stdout);
#endif
	int n=ni,k=ni;
	for(int i=1;i<=n;i++){
		char c;
		while(!isalpha(c=getchar()));
		pval[i]=c=='W';
	}
	pval[1]=1;
	for(int i=2;i<=n;i++){
		fa[i]=ni;
		deg[fa[i]]++;
	}
	frac ans;
	{
		grank::main(n);
		int ls=0;
		for(int i=1;i<=n;i++){
			if(deg[i]==0){
				lst[++ls]=i;
			}
		}
		sort(lst+1,lst+ls+1,lcmp);
		frac tmp;
		solve(ls-k+1,ls,tmp,ans);
	}
	cout<<"solve complete"<<endl;
	tobase10::main(ans);
	return 0;
}
