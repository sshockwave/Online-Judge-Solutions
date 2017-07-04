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
	bool swi[N],mark[N];//swi:within one step stat change to -1
	inline void init(int n){
		memset(head+1,-1,n<<2);
		memset(mark+1,0,n);
		e=0;
	}
	inline void ae(const int &u,const int &v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void dfs(int x){
		swi[x]=false;
		if(head[x]==-1){
			return;
		}
		int cnt=0;
		for(int i=head[x],v;~i;i=bro[i]){
			dfs(v=to[i]);
			if(stat[v]==0){
				cnt++;
			}else if(stat[v]==1){
				cnt--;
			}
		}
		if(cnt){
			stat[x]=cnt<0;
			swi[x]=cnt==-1;
		}
	}
	void dfs2(int x){
		if(stat[x]==0||(stat[x]==1&&!swi[x])){
			mark[x]=false;
			return;
		}
		mark[x]=head[x]==-1&&stat[x]==-1;
		for(int i=head[x];~i;i=bro[i]){
			dfs2(to[i]);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ah.in","r",stdin);
	freopen("ah.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		int n=ni;
		T::init(n);
		ni;//fa 1
		for(int i=2;i<=n;i++){
			T::ae(ni,i);
		}
		for(int i=1;i<=n;i++){
			stat[i]=ni;
		}
		T::dfs(1);
		if(stat[1]==1){
			putchar('-'),putchar('1');
		}else if(stat[1]==0){
			int cnt=0;
			for(int i=1;i<=n;i++){
				if(T::head[i]==-1&&stat[i]==-1){
					cnt++;
				}
			}
			printf("%d",cnt);
			for(int i=1;i<=n;i++){
				if(T::head[i]==-1&&stat[i]==-1){
					printf(" %d",i);
				}
			}
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
		}
		putchar('\n');
	}
}
