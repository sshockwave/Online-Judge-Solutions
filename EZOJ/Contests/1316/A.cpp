#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=100010;
int stat[N];
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e;
	inline void init(int n){
		memset(head+1,-1,n<<2);
		e=0;
	}
	inline void ae(const int &u,const int &v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	bool f[N][2];//0:me 1:oppo f:who wins?
	void dfs(int x){
		if(~stat[x]){
			f[x][0]=f[x][1]=stat[x];
			return;
		}else if(head[x]==-1){
			f[x][0]=0,f[x][1]=1;
			return;
		}
		int cnt[2]={0},tie=0;
		for(int i=head[x],v;~i;i=bro[i]){
			assert(to[i]!=x);
			dfs(v=to[i]);
			if(f[v][0]==f[v][1]){
				cnt[f[v][0]]++;
			}else{
				assert(f[v][0]==0&&f[v][1]==1);
				tie++;
			}
		}
		tie&=1;
		f[x][0]=cnt[0]+tie>cnt[1]?0:1;
		f[x][1]=cnt[1]+tie>cnt[0]?1:0;
	}
	bool mark[N];
	void markall(int x){
		mark[x]=stat[x]==-1;
		for(int i=head[x];~i;i=bro[i]){
			mark[x]=false;
			markall(to[i]);
		}
	}
	void dfs2(int x){
		if(f[x][0]==f[x][1]){
			assert(f[x][0]==0);
			markall(x);
			return;
		}
		if(head[x]==-1){
			assert(stat[x]==-1);
			mark[x]=true;
			return;
		}
		bool flag=false;//debug
		for(int i=head[x],v;~i;i=bro[i]){
			v=to[i];
			if(f[v][0]!=f[v][1]){
				flag=true;
				dfs2(v);
			}
		}
		assert(flag);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ah1.in","r",stdin);
	freopen("ah.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		int n=ni;
		T::init(n);
		ni;//fa 1
		for(int i=2;i<=n;i++){
			int tmp;
			T::ae(tmp=ni,i);
		}
		for(int i=1;i<=n;i++){
			stat[i]=ni;
		}
		T::dfs(1);
		if(T::f[1][0]){
			puts("-1");
		}else{
			T::dfs2(1);
			int cnt=0;
			for(int i=1;i<=n;i++){
				if(T::mark[i]){
					cnt++;
				}
			}
			printf("%d",cnt);
			for(int i=1;i<=n;i++){
				if(T::mark[i]){
					printf(" %d",i);
				}
			}
			putchar('\n');
		}
	}
}
