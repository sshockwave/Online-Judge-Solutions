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
const int logN=64,T=7,NT=logN+T;
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
int n,mxlog=0;
int ans[NT];
inline void dfs(int x,int e,ull cur){
	if(x>n){
		ans[e]++;
		return;
	}
	for(int i=0;i<=mxlog;i++){
		if((all>>i)&1){
			//find independent
			int j=i;
			for(;j<=mxlog;j++){
				if(((LB::a[j]>>i)&1)&&!LB::vis[j]){
					break;
				}
			}
			if(j<=mxlog){
				LB::vis[j]=true;
				dfs(x+1,e+i-1,cur^LB::a[j]);
				LB::vis[j]=false;
			}else if((cur>>i)&1){
				dfs(x+1,e+i,cur);
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
		for(;(((1ull<<mxlog)-1)&tmp)!=tmp;mxlog++);
	}
	memset(ans,0,sizeof(ans));
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
