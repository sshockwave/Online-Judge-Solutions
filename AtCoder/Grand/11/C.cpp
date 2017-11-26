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
const int N=100010;
namespace G{
	const int E=400010;
	int to[E],bro[E],head[N],e=0;
	int col[N];
	inline void init(){
		memset(head,-1,sizeof(head));
		memset(col,-1,sizeof(col));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int pcnt[2];
	bool dfs(int x,bool c){
		if(~col[x])return col[x]!=c;
		pcnt[col[x]=c]++;
		bool flag=false;
		for(int i=head[x];~i;i=bro[i]){
			flag|=dfs(to[i],!c);
		}
		return flag;
	}
}
int main(){
	int n=ni;
	G::init();
	for(int tot=ni;tot--;G::add(ni,ni));
	lint sing=0,bi=0,whole=0;
	for(int i=1;i<=n;i++){
		using namespace G;
		if(col[i]==-1){
			pcnt[0]=pcnt[1]=0;
			if(dfs(i,0)){
				whole++;
			}else if(pcnt[1]==0){
				assert(pcnt[0]==1);
				sing++;
			}else{
				bi++;
			}
		}
	}
	lint ans=sing*sing+sing*(n-sing)*2+bi*bi*2+whole*whole+bi*whole*2;
	printf("%lld\n",ans);
	return 0;
}
