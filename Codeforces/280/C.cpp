#include <bits/stdc++.h>
using namespace std;
typedef double db;
const int N=1e5+10;
template<class T>inline void mset(T a[],const T& v,size_t n){memset(a,v,n*sizeof(T));}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(int n){
		mset(head+1,-1,n);
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	db dfs(int x,int fa,int dep){
		db ans=1.0/dep;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa)continue;
			ans+=dfs(v,x,dep+1);
		}
		return ans;
	}
}
int main(){
	int n;
	scanf("%d",&n);
	T::init(n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		T::add(u,v);
	}
	printf("%.20lf\n",T::dfs(1,0,1));
}
