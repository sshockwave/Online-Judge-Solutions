#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <map>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline lint nl(){
	lint i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int MOD=258280327,_N=10000010;
const lint N=10000000010ll;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int sub(int a,int b){
	return (a-b+MOD)%MOD;
}
inline int mul(int a,int b){
	return (long long)a*b%MOD;
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,x=mul(x,x)){
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
int mu[_N],prime[_N],_g[_N],ptop=0;
bool np[_N];
map<lint,int>gcache;
inline int g(lint n){
	if(n<_N){
		return _g[n];
	}
	map<lint,int>::iterator it=gcache.find(n);
	if(it!=gcache.end()){
		return it->second;
	}
	int ans=1;
	for(lint i=2,l,r;i<=n;i=r+1){
		l=i,r=(n/(n/i));
		ans=sub(ans,g(n/i)*(r-l+1));
	}
	return gcache[n]=ans;
}
inline int t(lint n){
	static int rev=fpow(9,MOD-2);
	return mul(add(mul(n%MOD,fpow(10,(n+1)%(MOD-1))),mul(sub(10,fpow(10,(n+1)%(MOD-1))),rev)),rev);
}
inline void init(){
	memset(np,0,sizeof(np));
	mu[1]=1;
	_g[0]=0;
	_g[1]=1;
	for(int i=2;i<_N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			mu[i]=-1;
		}
		_g[i]=add(_g[i-1],mu[i]*i);
		for(int j=0,cur=2;j<ptop&&i*cur<_N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%prime[j]==0){
				mu[i*cur]=0;
				break;
			}else{
				mu[i*cur]=-mu[i];
			}
		}
	}
}
int main(){
	init();
	lint n=nl();
	int ans=0;
	for(lint i=1,l,r;i<=n;i=r+1){
		l=i,r=min(n,(n/(n/i)));
		ans=add(ans,mul(t(n/i),sub(g(r),g(l-1))));
	}
	printf("%d\n",ans);
}
