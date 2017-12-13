#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
const int N=1000010,BUF=1<<23,INF=0x7f7f7f7f;
char B[BUF],*S=B,*Ti=B;
char getc(){
	if(S==Ti){
		Ti=(S=B)+fread(B,1,BUF,stdin);
	}
	if(S==Ti)return 0;
	return *S++;
}
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getc())&&c!='-');
	bool flag=c=='-';
	flag?c=getc():0;
	while(i=i*10-'0'+c,isdigit(c=getc()));
	return flag?-i:i;
}
char Buff[BUF],*st=Buff;
template<class T>void write(T a){
	if(a==0){
		*st++='0';
	}else{
		if(a<0)*st++='-',a=-a;
		static char c[20];
		static int c0;
		c0=0;
		while(a)c[c0++]=a%10+'0',a/=10;
		while(c0--)*st++=c[c0];
	}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
int n,deg[N],ans[N],as=0;
bool fir=true;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int f[N];
	bool g[N];//require to be on top
	void dfs1(int x,int fa){
		f[x]=INF;
		g[x]=false;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs1(v,x);
				apmin(f[x],f[v]);
			}
		}
		int lson=0,rson=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				if(lson==0){
					lson=v;
				}else{
					assert(rson==0);
					rson=v;
				}
			}
		}
		int d=deg[x]-(fa!=0);
		if(d==2){
			g[x]=x<f[x];
		}else{
			assert(rson==0);
			assert(d<2);
			if(d==1){
				assert(lson);
				g[x]=x<f[lson]&&g[lson];
			}
			apmin(f[x],x);
		}
		//cout<<"x="<<x<<"\tf="<<f[x]<<"\tg="<<g[x]<<endl;
	}
	void dfs2(int x,int fa){
		int lson=0,rson=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				if(lson==0){
					lson=v;
				}else{
					assert(rson==0);
					rson=v;
				}
			}
		}
		if((lson&&rson&&f[lson]>f[rson])||(lson&&rson==0&&f[lson]>x)){
			swap(lson,rson);
		}
		if(lson){
			dfs2(lson,x);
		}
		ans[++as]=x;
		if(rson){
			dfs2(rson,x);
		}
	}
	inline void Main(int x){
		T::dfs1(x,0);
		for(int last=0,lson,rson;x;last=x,x=rson){
			ans[++as]=x;
			lson=0,rson=0;
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=last){
					if(lson==0){
						lson=v;
					}else{
						assert(rson==0);
						rson=v;
					}
				}
			}
			if(lson==0)return;
			if(rson){
				if(f[lson]>f[rson]){
					swap(lson,rson);
				}
			}else if(g[lson]){
				swap(lson,rson);
			}
			if(lson){
				dfs2(lson,x);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("binary.in","r",stdin);
	freopen("binary.out","w",stdout);
#endif
	n=ni;
	T::init();
	int rt=0;
	for(int i=1;i<=n;i++){
		deg[i]=ni;
		if(deg[i]<3&&rt==0){
			rt=i;
		}
		for(int j=1;j<=deg[i];j++){
			T::ae(i,ni);
		}
	}
	assert(rt);
	T::Main(rt);
	for(int i=1;i<=n;i++){
		write(ans[i]);
		*st++=i==n?'\n':' ';
	}
	fwrite(Buff,1,st-Buff,stdout);
	return 0;
}
