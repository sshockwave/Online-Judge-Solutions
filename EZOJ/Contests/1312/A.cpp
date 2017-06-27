#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=500010,D=26,MOD=998244353;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
inline void apsub(int &a,const int &b){
	a=sub(a,b);
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
inline int _n1(int n){
	const static int rev2=(MOD+1)>>1;
	return mul(mul(n,n+1),rev2);
}
inline int _n2(int n){
	const static int rev6=fpow(6,MOD-2);
	return mul(mul(n,n+1),mul(mul(n,2)+1,rev6));
}
int ans=0;
namespace SAM{
	const int TN=N*2,E=TN;
	int lnk[TN],val[TN],go[TN][D],cnt[TN],n=1;
	int to[E],bro[E],head[TN],e=0;
	int f[TN];
	inline void init(){
		memset(lnk,0,sizeof(lnk));
		memset(head,-1,sizeof(head));
		memset(go,0,sizeof(go));
		memset(cnt,0,sizeof(cnt));
		memset(f,0,sizeof(f));
		val[1]=0;
	}
	inline int nn(){
		return ++n;
	}
	inline void ae(const int &u,const int &v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void build(){
		for(int i=2;i<=n;i++){
			ae(lnk[i],i);
		}
	}
	void dfs(int x){
		int cur=0;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]);
			assert(val[v]>val[x]);
			apadd(cnt[x],cnt[v]);
			apadd(cur,mul(f[x],f[v]));
			apadd(f[x],f[v]);
			{//2
				int cur=0,n1=sub(_n1(val[v]),_n1(val[x])),n2=sub(_n2(val[v]),_n2(val[x]));
				apadd(cur,mul(add(mul(val[v],2),1),n1));
				apsub(cur,mul(n2,2));
				apmul(cur,mul(cnt[v],cnt[v]));
				apadd(ans,cur);
			}
		}
		apadd(ans,mul(2,mul(cur,val[x])));//1
		{//3
			int cur,n1=sub(_n1(val[x]),_n1(val[lnk[x]]));
			cur=mul(n1,f[x]);
			apmul(cur,cnt[x]);
			apmul(cur,2);
			apadd(ans,cur);
		}
		apadd(f[x],mul(val[x]-val[lnk[x]],cnt[x]));
	}
	int tail=1;
	inline void ext(int c){
		int p=tail;
		val[tail=nn()]=val[p]+1,cnt[tail]=1;
		for(;p&&go[p][c]==0;p=lnk[p]){
			go[p][c]=tail;
		}
		if(p==0){
			lnk[tail]=1;
			return;
		}
		int q=go[p][c];
		if(val[q]==val[p]+1){
			lnk[tail]=q;
			return;
		}
		assert(val[q]>val[p]+1);
		int nq=nn();
		memcpy(go[nq],go[q],sizeof(go[q]));
		lnk[nq]=lnk[q],val[nq]=val[p]+1;
		lnk[q]=lnk[tail]=nq;
		for(;p&&go[p][c]==q;p=lnk[p]){
			go[p][c]=nq;
		}
	}
}
char s[N];
int main(){
	SAM::init();
	scanf("%s",s);
	int n=0;
	for(;s[n];n++);
	for(int i=n-1;i>=0;i--){
		SAM::ext(s[i]-'a');
	}
	SAM::build(),SAM::dfs(1);
	printf("%d\n",ans);
}
