#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
int ans;
namespace lib{
	const int O=1000000007;
	int a;
	inline int gen(){
		return a=(1714636915ll*a+1681692777)%O*((846930886ll*ans+1804289383)%O)%O;
	}
}
priority_queue<int>q1,q2;
namespace chain{
	const int N=210;
	int nxt[N],pre[N];
	int val[N];
	inline int nn(){
		static int n=0;
		assert(n<N);
		return ++n;
	}
	inline int nn(int v){
		int p=nn();
		val[p]=v;
		return p;
	}
	int hd,tl;
	inline void init(){
		hd=nn(),tl=nn();
		nxt[hd]=tl,pre[tl]=hd;
	}
	int __initer__=(init(),0);
	inline void ins_aft(int x,int u){
		nxt[u]=nxt[x],pre[nxt[u]]=u,nxt[x]=u,pre[u]=x;
	}
	inline void del(int x){
		nxt[pre[x]]=nxt[x],pre[nxt[x]]=pre[x];
	}
}
int p,bufcnt;
const int buflim=chain::N-3;
inline void ins_to_buf(int v){
	using namespace chain;
	bufcnt++;
	for(int x=p;;){
		if(val[v]<val[x]){
			if(pre[x]==hd||val[v]>=val[pre[x]])return ins_aft(pre[x],v);
			x=pre[x];
		}else{
			if(nxt[x]==tl||val[v]<=val[nxt[x]])return ins_aft(x,v);
			x=nxt[x];
		}
	}
}
inline void work(int v){
	using namespace chain;
	if(bufcnt<buflim)return ins_to_buf(nn(v));
	if(v<=val[nxt[hd]])return q1.push(v);
	if(v>=val[pre[tl]])return q2.push(-v);
	int x;
	if(v<ans){
		x=nxt[hd];
		q1.push(val[x]);
	}else{
		x=pre[tl];
		q2.push(-val[x]);
	}
	del(x),bufcnt--;
	val[x]=v;
	ins_to_buf(x);
}
inline void mv(int dt){
	if(dt==0)return;
	using namespace chain;
	if(dt==1){
		if(nxt[p]==tl){
			assert(!q2.empty());
			int x=nxt[hd];
			q1.push(val[x]);
			del(x);
			val[x]=-q2.top();
			q2.pop();
			ins_aft(p,x);
		}
		p=nxt[p];
	}else if(dt==-1){
		if(pre[p]==hd){
			assert(!q1.empty());
			int x=pre[tl];
			q2.push(-val[x]);
			del(x);
			val[x]=q1.top();
			q1.pop();
			ins_aft(hd,x);
		}
		p=pre[p];
	}else{
		assert(false);
	}
}
inline ostream & operator << (ostream & out,const priority_queue<int>&q){
	priority_queue<int>tq=q;
	for(;!tq.empty();tq.pop()){
		out<<tq.top()<<" ";
	}
	return out;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("mid.in","r",stdin);
	freopen("mid.out","w",stdout);
#endif
	int n=ni;
	int prtans=ans=lib::a=ni;
	p=chain::nn(ans),bufcnt=1;
	chain::ins_aft(chain::hd,p);
	for(int i=2;i<=n;i++){
		int a=lib::gen();
		work(a);
		mv((i&1)-(a<ans));
		prtans^=ans=chain::val[p];
	}
	printf("%d\n",prtans);
	return 0;
}
