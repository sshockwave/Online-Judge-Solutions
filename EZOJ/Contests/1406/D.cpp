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
const int N=100010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
namespace T{
	const int E=::N<<1;
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
}
namespace task4{//allone
	int f[N];
	inline int main(int n){
		f[0]=0;
		for(int i=1;i<=n;i++){
			f[i]=((lint)(i-1)*(f[i-1]+1)%O*inv(i)+i)%O;
		}
		return f[n];
	}
}
namespace task5{//chain
	inline int main(int n){
		int pre=0,cur=0;
		for(int i=1;i<=n;i++){
			cur=((lint)pre*inv(i)*2+i)%O;
			pre=(pre+cur)%O;
		}
		return cur;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("expect.in","r",stdin);
	freopen("expect.out","w",stdout);
#endif
	int n=ni;
	bool allone=true,chain=true;
	T::init();
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		allone&=u==1;
		chain&=u==v-1;
		T::add(u,v);
	}
	if(allone){
		printf("%d\n",task4::main(n));
	}else if(chain){
		printf("%d\n",task5::main(n));
	}
	return 0;
}
