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
const int N=200010,INF=0x7f7f7f7f;
lint ans=1;
char s[N];
int onecnt=0;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int dep[E],cnt[E];
	void dfs1(int x,int e){
		if(~e){
			dep[e]=1;
			cnt[e]=s[x]=='1';
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if(i^e^1){
				dfs1(v=to[i],i);
				if(~e){
					cnt[e]+=cnt[i];
					apmax(dep[e],dep[i]+1);
				}
			}
		}
		if(~e){
			cnt[e^1]=onecnt-cnt[e];
		}
	}
	void dfs2(int x,int fa){
		int mx1=0,mx2=0,mn=s[x]=='1'?0:INF;
		int fr=0;
		for(int i=head[x];~i;i=bro[i]){
			if(dep[i]>mx1){
				mx2=mx1,mx1=dep[i];
				fr=i;
			}else if(dep[i]>mx2){
				mx2=dep[i];
			}
			if(cnt[i]){
				apmin(mn,dep[i]);
			}
		}
		ans+=max(min(mx1-1,mx2+1)-mn+1,0);
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dep[i^1]=(fr!=i?mx1:mx2)+1;
				dfs2(v,x);
			}
		}
	}
}
inline lint Main(){
	int n=ni;
	T::init();
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	scanf("%s",s+1);
	T::dfs1(1,-1),T::dfs2(1,0);
	return ans;
}
int main(){
	printf("%lld\n",Main());
	return 0;
}
