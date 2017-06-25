#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
inline int abs(int x){
	return x>=0?x:-x;
}
const int N=100010;
namespace G{
	const int E=N*2;
	int to[E],bro[E],head[N],e;
	int color[N],sum[N],diff[N];
	int a,b;
	inline void init(int n){
		a=b=e=0;
		memset(head+1,-1,n<<2);
		memset(color+1,0,n<<2);
		memset(sum+1,0,n<<2);
		memset(diff+1,0,n<<2);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	void dfs(int x,int e){
		sum[x]=color[x];
		for(int i=head[x],v;~i;i=bro[i]){
			if(i!=e){
				v=to[i];
				if(color[v]){
					a=x,b=v;
				}else{
					color[v]=-color[x];
					dfs(v,i^1);
					sum[x]+=sum[v];
					diff[x]+=diff[v];
				}
			}
		}
	}
	int c[N];
	inline int work(){
		int n=ni,m=ni;
		init(n);
		for(int i=1;i<=m;i++){
			add(ni,ni);
		}
		if(n&1){
			return -1;
		}
		color[1]=1;
		dfs(1,-1);
		if(m<n){
			assert(m+1==n);
			if(sum[1]){
				return -1;
			}
			int ans=0;
			for(int i=2;i<=n;i++){
				ans+=abs(sum[i]);
			}
			return ans;
		}
		if(color[a]==color[b]){
			if((sum[1]&1)||(sum[1]<-2)||(sum[1]>2)){
				return -1;
			}
			int ans=0;
			if(sum[1]){
				ans=1;
				color[a]-=sum[1]/2;
				color[b]-=sum[1]/2;
				dfs(1,-1);
			}
			assert(sum[1]==0);
			for(int i=2;i<=n;i++){
				ans+=abs(sum[i]);
			}
			return ans;
		}else{
			if(sum[1]){
				return -1;
			}
			diff[a]=1,diff[b]=-1;
			memset(color+1,0,n<<2);
			color[1]=1;
			dfs(1,-1);
			int cs=0,ans=0;
			for(int i=1;i<=n;i++){
				if(diff[i]){
					c[cs++]=sum[i]*diff[i];
				}else{
					ans+=sum[i];
				}
			}
			nth_element(c,c+(cs>>1)-1,c+cs);
			int x=c[(cs>>1)-1];
			for(int i=0;i<cs;i++){
				ans+=abs(c[i]-x);
			}
			return ans;
		}
	}
}
int main(){
	for(int tot=ni;tot--;){
		printf("%d\n",G::work());
	}
}
