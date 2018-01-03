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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=4010,D=26;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int c){
		to[e]=v,bro[e]=head[u],val[e]=c,head[u]=e++;
	}
	inline void add(int u,int v,int c){
		ae(u,v,c),ae(v,u,c);
	}
}
lint tag[N],tim=0;
int stk[N],ss=0;
int vec[D][N],vs[D];
int fa[N];
inline void work(int x,int ans[]){
	assert(ss==0);
	fa[x]=0;
	stk[ss++]=x;
	tag[x]=++tim;
	int sum=0;
	while(ss){
		memset(vs,0,sizeof(vs));
		lint t=tag[stk[ss-1]];
		int cnt=0;
		for(;ss&&tag[stk[ss-1]]==t;cnt++){
			x=stk[--ss];
			ans[x]=sum;
			using namespace T;
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa[x]){
					fa[v]=x;
					vec[val[i]][vs[val[i]]++]=v;
				}
			}
		}
		sum+=cnt;
		for(int i=D-1;i>=0;i--){
			tim++;
			for(int j=0;j<vs[i];j++){
				x=vec[i][j];
				tag[x]=tim;
				stk[ss++]=x;
			}
		}
	}
}
int ans[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("alphabet.in","r",stdin);
	freopen("alphabet.out","w",stdout);
#endif
	int n=ni,tot=ni;
	T::init();
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		char c;
		while(!isalpha(c=getchar()));
		T::add(u,v,c-'a');
	}
	for(int i=1;i<=n;i++){
		work(i,ans[i]);
	}
	for(int u,v;tot--;){
		u=ni,v=ni;
		printf("%d\n",max(ans[u][v]-1,0));
	}
	return 0;
}
