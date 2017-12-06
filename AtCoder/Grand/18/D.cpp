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
const int N=100010,INF=0x7f7f7f7f;
int n;
lint ans=0;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	int g=0,gbal=INF,ge=-1;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	int dfs(int x,int fa){
		int size=1,bal=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				int cur=dfs(v,x);
				apmax(bal,cur);
				if((cur<<1)==n){
					ge=i;
				}
				ans+=(lint)min(cur,n-cur)*val[i];
				size+=cur;
			}
		}
		apmax(bal,n-size);
		if(bal<gbal){
			g=x,gbal=bal;
		}
		return size;
	}
}
int main(){
	n=ni;
	using namespace T;
	init();
	for(int i=1,u,v;i<n;u=ni,v=ni,add(u,v,ni),i++);
	dfs(1,0);
	ans<<=1;
	if(~ge){
		ans-=val[T::ge];
	}else{
		int tmp=INF;
		for(int i=head[g];~i;i=bro[i]){
			apmin(tmp,val[i]);
		}
		ans-=tmp;
	}
	printf("%lld\n",ans);
	return 0;
}
