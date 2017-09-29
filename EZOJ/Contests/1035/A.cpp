#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
#define cout cerr
#define ni (next_num<int>())
#define no (next_num<ull>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int K=6,logN=64,T=7,NT=logN+T;
namespace LB{
	ull a[logN];
	bool vis[logN];
	inline void init(){
		memset(a,0,sizeof(a));
		memset(vis,0,sizeof(vis));
	}
	inline void ins(ull x){
		for(int i=logN-1;x;i--){
			if((x>>i)&1){
				if(a[i]){
					x^=a[i];
				}else{
					a[i]=x;
					return;
				}
			}
		}
	}
}
ull all=0;
int n,mxlen=0;
int vis[logN],ans[NT];
struct sbase{
	ull a[K];
	int k,pos[K];
	inline void ins(ull x){
		for(int i=k-1;x;i--){
			if((x>>pos[i])&1){
				if(a[i]){
					x^=a[i];
				}else{
					a[i]=x;
					return;
				}
			}
		}
	}
	sbase(ull cur):k(0){
		memset(a,0,sizeof(a));
		for(int i=0;i<=mxlen;i++){
			if((cur>>i)&1){
				a[k]=0,pos[k]=i,k++;
			}
		}
		for(int i=mxlen;i>=0;i--){
			ins(LB::a[i]&cur);
		}
	}
	inline bool test(ull x){
		for(int i=k-1;i>=0&&x;i--){
			ull v=x^a[i];
			if(v<x){
				x=v;
			}
		}
		return x==0;
	}
};
inline void dfs(int x,int e,ull cur){
	if(x>n){
		ans[e]++;
		return;
	}
	for(int i=0;i<=mxlen;i++){
		if((all>>i)&1){
			if((cur>>i)&1){
				dfs(x+1,e+i,cur);
			}else{
				ull join=cur|(1ull<<i);
				sbase lb(join);
				if(lb.test(join)){
					dfs(x+1,e+i-lb.test(cur),join);
				}
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("malygos.in","r",stdin);
	freopen("malygos.out","w",stdout);
#endif
	int tot=ni;
	n=ni;
	LB::init();
	while(tot--){
		ull tmp=no;
		all|=tmp;
		LB::ins(tmp);
		for(;(((1ull<<mxlen)-1)&tmp)!=tmp;mxlen++);
	}
	memset(ans,0,sizeof(ans));
	memset(vis,0,sizeof(vis));
	dfs(1,T,0);
	for(int i=0;i<NT-1;i++){
		ans[i+1]+=ans[i]>>1;
		ans[i]&=1;
	}
	ull tmp=0;
	for(int i=0;i<logN;i++){
		tmp|=(ull)ans[i+T]<<i;
	}
	printf("%llu",tmp);
	tmp=0;
	ull pw=1;
	for(int i=0;i<T;i++){
		pw*=10;
	}
	for(int i=T-1;i>=0;i--){
		pw>>=1;
		tmp+=ans[i]*pw;
	}
	if(tmp){
		for(;tmp%10==0;tmp/=10);
		printf(".%llu",tmp);
	}
	putchar('\n');
	return 0;
}
