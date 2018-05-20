#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long lint;
typedef long double db;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=10;
const db EPS=1e-7;
inline bool eq0(const db &x){
	return x>=-EPS&&x<=EPS;
}
db ans=0;
namespace calc{
	int n,r[N],nxt[N];//to set
	db nxtv[N];
	inline db calc(){
		db sum=0;
		for(int i=1;i<=n;i++){
			sum+=(db)r[i]*r[nxt[i]]*sin(nxtv[i]);
		}
		return sum/2;
	}
	inline db calc(db lambda){
		db sum=0;
		for(int i=1;i<=n;i++){
			sum+=nxtv[i]=acos(lambda/(r[i]*r[nxt[i]]));
		}
		return sum;
	}
	inline db main(){
		assert(n>=3);
		db lend=0,rend=1e100;
		for(int i=1;i<=n;i++){
			apmin(rend,r[i]*r[nxt[i]]);
		}
		lend=-rend;
		if(calc(lend)<M_PI*2||calc(rend)>M_PI*2)return -1;
		while(rend-lend>EPS){
			db m=(lend+rend)/2;
			if(calc(m)<M_PI*2){
				rend=m;
			}else{
				lend=m;
			}
		}
		return calc();
	}
}
bool vis[N];
void dfs(int x,int curnd){
	using namespace calc;
	if(x==n)return nxt[curnd]=1,apmax(ans,calc::main());
	for(int &i=nxt[curnd]=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=true;
			dfs(x+1,i);
			vis[i]=false;
		}
	}
}
inline bool rcmp(int a,int b){
	return a>b;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("yja.in","r",stdin);
	freopen("yja.out","w",stdout);
#endif
	int n=ni;
	if(n<3){
		puts("0");
		return 0;
	}
	int * const r=calc::r;
	for(int i=1;i<=n;i++){
		r[i]=ni;
	}
	sort(r+1,r+n+1,rcmp);
	memset(vis,0,sizeof(vis));
	vis[1]=true;
	for(int i=1;i<=n-2;i++){
		calc::n=n-i+1;
		dfs(1,1);
	}
	printf("%.10lf\n",(double)ans);
	return 0;
}
