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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010;
lint a[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=2;
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	lint dfs(int x,int fa){
		if(bro[head[x]]==0){
			return a[x];
		}
		lint sum=0,mx=0;
		for(int i=head[x],v;i;i=bro[i]){
			if((v=to[i])!=fa){
				lint f=dfs(v,x);
				sum+=f;
				if(f>mx){
					mx=f;
				}
			}
		}
		lint vac=sum-mx>mx?(sum&1):mx-(sum-mx),mat=((sum-vac)>>1);
		if(vac+mat>a[x]||mat<(a[x]-(mat+vac))){
			throw false;
		}
		return ((a[x]-(mat+vac))<<1)+vac;
	}
}
int main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<n;T::add(ni,ni),i++);
	try{
		using namespace T;
		if(bro[head[1]]?dfs(1,0):dfs(to[head[1]],1)!=a[1]){
			throw false;
		}
		puts("YES");
	}catch(bool err){
		puts("NO");
	}
	return 0;
}
