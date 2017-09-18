#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=200010,M=500010,K=50,S=10000010,D=6,MOD=998244353;
namespace T{
	const int N=M*20;//tocheck
	int fa[N],son[N][D],lnk[N],val[N],n=1;
	inline void init(){
		memset(fa,0,sizeof(fa));
		memset(son,0,sizeof(son));
		memset(lnk,0,sizeof(lnk));
		memset(val,0,sizeof(val));
	}
	int go(int x,int c){
		if(x==0){
			return 1;
		}
		if(son[x][c]==0){
			son[x][c]=++n;
			fa[n]=x;
			lnk[n]=go(lnk[x],c);
		}
		return son[x][c];
	}
	inline void add(int x,int v,int k){
		for(;k--;x=fa[x]){
			val[x]+=v;
		}
	}
}
int col[N],pre[N],nxt[N],maxk=0;
inline void con(int u,int w){
	int v=nxt[u],len=2,tu=v;
	if(maxk<len){
		if(maxk==1){
			T::add(T::go(1,col[u]),w,1);
			T::add(T::go(1,col[v]),w,1);
		}
		return;
	}
	assert(v);
	while(len<maxk){
		if(pre[u]){
			u=pre[u];
			len++;
		}else{
			break;
		}
	}
	int cnt=len-1;
	while(len<maxk){
		if(nxt[v]){
			v=nxt[v];
			len++;
		}else{
			break;
		}
	}
	assert(u&&v);
	int x=1;
	for(int i=u;i!=v;i=nxt[i]){
		x=T::go(x,col[i]);
	}
	x=T::go(x,col[v]);
	do{
		T::add(x,w,len-cnt);
		u=nxt[u],x=T::lnk[x],len--,cnt--;
		if(nxt[v]){
			v=nxt[v],x=T::go(x,col[v]),len++;
		}
	}while(u!=tu);
}
inline void lnk(int u,int v){
	assert(nxt[u]==0&&pre[v]==0);
	nxt[u]=v,pre[v]=u;
	con(u,1);
}
inline void cut(int u){
	assert(nxt[u]);
	con(u,-1);
	pre[nxt[u]]=0,nxt[u]=0;
}
inline int work(char s[],int k){
	int x=1;
	for(int i=0;i<k;i++){
		x=T::go(x,s[i]-'1');
	}
	lint ans=T::val[x];
	for(int i=k;s[i];i++){
		x=T::go(T::lnk[x],s[i]-'1');
		if(T::val[x]==0){
			return 0;
		}
		ans=(ans*T::val[x])%MOD;
	}
	return ans;
}
struct Query{
	int op,i,j;
	char *s;
}q[M];
char *s=new char[S+M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("queue.in","r",stdin);
	freopen("queue.out","w",stdout);
#endif
	T::init();
	memset(pre,0,sizeof(pre));
	memset(nxt,0,sizeof(nxt));
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		col[i]=ni-1;
		T::add(T::go(1,col[i]),1,1);
	}
	for(int i=1;i<=tot;i++){
		q[i].op=ni;
		if(q[i].op==1){
			q[i].i=ni,q[i].j=ni;
		}else if(q[i].op==2){
			q[i].i=ni;
		}else{
			scanf("%s",s);
			q[i].s=s;
			q[i].i=ni;
			apmax(maxk,q[i].i);
			for(;*s;s++);
			s++;
		}
	}
	if(maxk==1){
		int cnt[D];
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++){
			cnt[col[i]]++;
		}
		for(int i=1;i<=tot;i++){
			if(q[i].op==3){
				lint ans=1;
				for(int j=0;q[i].s[j];j++){
					ans=(ans*cnt[q[i].s[j]-'1'])%MOD;
					if(ans==0){
						break;
					}
				}
				printf("%lld\n",ans);
			}
		}
		return 0;
	}
	for(int i=1;i<=tot;i++){
		if(q[i].op==1){
			lnk(q[i].i,q[i].j);
		}else if(q[i].op==2){
			cut(q[i].i);
		}else{
			printf("%d\n",work(q[i].s,q[i].i));
		}
	}
	return 0;
}
