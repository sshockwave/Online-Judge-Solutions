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
const int N=1000010;
int size[N],mx=0;
namespace T{
	const int E=N;
	int to[E],bro[E],head[N],e=0;
	int dep[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	void dfs(int x,int dep){
		apmax(mx,dep);
		size[dep++]++;
		for(int i=head[x];~i;i=bro[i]){
			dfs(to[i],dep);
		}
	}
}
int K[N];
int que[N],ans[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sup.in","r",stdin);
	freopen("sup.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=tot;i++){
		K[i]=ni;
	}
	T::init();
	for(int i=2;i<=n;i++){
		T::ae(ni,i);
	}
	T::dfs(1,1);
	for(int i=1;i<=mx;i++){
		size[i]+=size[i-1];
	}
	int *qh=que,*qt=que;
	for(int i=1;i<=mx;i++){
		for(;qt>que&&size[*(qt-1)]*i>=size[i]**(qt-1);qt--);
		*(qt++)=i;
	}
	for(int i=1;i<=n;i++){
		for(;qh+1<qt&&(size[*(qh+1)]-size[*qh])<i*(*(qh+1)-*qh);qh++);
		const int r=n-size[*qh];
		ans[i]=*qh+r/i+(r%i!=0);
	}
	for(int i=1;i<=tot;i++){
		printf("%d ",K[i]>n?mx:ans[K[i]]);
	}
	putchar('\n');
	return 0;
}
