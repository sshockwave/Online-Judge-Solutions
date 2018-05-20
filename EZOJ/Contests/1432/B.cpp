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
	inline void compensate(){
		const static db circ=(db)M_PI*2;
		db sum=0;
		for(int i=1;i<=n;i++){
			sum+=nxtv[i];
		}
		sum=(circ-sum)/n;
		for(int i=1;i<=n;i++){
			nxtv[i]+=sum;
		}
	}
	inline void neutralize(int x){
		int r1=r[x],r3=r[nxt[nxt[x]]];
		db theta=nxtv[x]+nxtv[nxt[x]];
		if(eq0(theta))return;
		db up=r1-(db)r3*cos(theta),dn=(db)r3*sin(theta);
		db alpha=atan(up/dn);//cout
		if((db)r1*sin(alpha)+(db)r3*sin(theta-alpha)<0){
			alpha+=M_PI;
		}
		apmax(alpha,0),apmin(alpha,theta);//cout
		nxtv[x]=alpha,nxtv[nxt[x]]=theta-alpha;
	}
	inline void iterate(){
		for(int i=1,t=1;t<=n;i=nxt[i],++t){
			neutralize(i);
		}
	}
	inline db calc(){
		db sum=0;
		for(int i=1;i<=n;i++){
			sum+=(db)r[i]*r[nxt[i]]*sin(nxtv[i]);
		}
		return sum/2;
	}
	inline db main(){
		assert(n>=3);
		const db eq=(db)M_PI*2/n;
		for(int i=1;i<=n;i++){
			nxtv[i]=eq;
		}
		db last=calc();
		for(db cur,dt;;compensate()){
			iterate();
			cur=calc(),dt=cur-last,last=cur;
			if(eq0(dt)||eq0(dt/cur))break;
			if(cur+dt*100<ans)break;//cout
		}
		return last;
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
