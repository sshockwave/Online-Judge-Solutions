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
	inline int sum(){
		return a[0]+a[1]+a[2]+a[3];
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
}st[N];
namespace T{
	const int E=N<<1;
	int to[E],bro[E],len[E],head[N],e;
	bool vis[N];
	inline void init(int n){
		memset(head+1,-1,n<<2);
		memset(vis+1,0,n);
		e=0;
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],len[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	stat dfs(int x){
		vis[x]=true;
		stat ans=(stat){1,0,0,0};
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				ans+=dfs(v).shift(len[i]);
			}
		}
		vis[x]=false;
		return ans;
	}
	int bal[N],g;
	int gg(int x,int n){
		bal[x]=0;
		vis[x]=true;
		int sz=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				int t=gg(v,n);
				sz+=t;
				apmax(bal[x],t);
			}
		}
		apmax(bal[x],n-sz);
		if(bal[x]<bal[g]){
			g=x;
		}
		vis[x]=false;
		return sz;
	}
	void solve(int x,int n){
		g=x,gg(x,n),x=g;
		vis[x]=true;
		st[x]=(stat){1,0,0,0};
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				st[x]+=st[v]=dfs(v).shift(len[i]);
			}
		}
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				ans+=(st[x]-st[v])*st[v];
			}
		}
		ans+=st[x].a[0];
		for(int i=head[x],v;~i;i=bro[i]){
			if(!vis[v=to[i]]){
				solve(v,st[v].sum());
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
		T::solve(1,n);
		int t=n*n,d=gcd(ans,t);
		printf("%d/%d\n",ans/d,t/d);
	}
	return 0;
}
