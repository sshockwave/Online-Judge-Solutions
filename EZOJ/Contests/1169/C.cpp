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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=20010;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
int ans;
struct stat{
	int a[4];
	inline stat shift(int x){
		stat ret;
		for(int i=0;i<4;i++){
			ret.a[(i+x)&3]=a[i];
		}
		return ret;
	}
	inline friend stat operator + (const stat &a,const stat &b){
		stat c;
		for(int i=0;i<4;i++){
			c.a[i]=a.a[i]+b.a[i];
		}
		return c;
	}
	inline friend stat operator - (const stat &a,const stat &b){
		stat c;
		for(int i=0;i<4;i++){
			c.a[i]=a.a[i]-b.a[i];
		}
		return c;
	}
	inline friend int operator * (const stat &a,const stat &b){
		int sum=0;
		for(int i=0;i<4;i++){
			sum+=a.a[i]*b.a[(4-i)&3];
		}
		return sum;
	}
	inline void operator += (const stat &b){
		for(int i=0;i<4;i++){
			a[i]+=b.a[i];
		}
	}
};
namespace T{
	const int E=N<<1;
	int to[E],bro[E],len[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],len[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	stat size[N];
	void dfs1(int x,int f){
		size[x]=(stat){1,0,0,0};
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=f){
				dfs1(v,x);
				size[x]+=size[v].shift(len[i]);
			}
		}
	}
	void dfs2(int x,int f,stat oth){
		oth+=size[x];
		ans+=oth.a[0];
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=f){
				dfs2(v,x,(oth-size[v].shift(len[i])).shift(len[i]));
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ak.in","r",stdin);
	freopen("ak.out","w",stdout);
#endif
	for(int n;(n=ni);){
		T::init(n);
		for(int i=1;i<n;i++){
			int u=ni,v=ni;
			T::add(u,v,ni%4);
		}
		ans=0;
		T::dfs1(1,0),T::dfs2(1,0,(stat){0,0,0,0});
		int g=n*n,d=gcd(g,ans);
		printf("%d/%d\n",ans/d,g/d);
	}
	return 0;
}
