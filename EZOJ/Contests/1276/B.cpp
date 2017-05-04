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
const int MOD=258280327,N=10000010;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int sub(int a,int b){
	return add(a,MOD-b);
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
int mu[N],prime[N/10],_g[N],ptop=0;
bool np[N];
map<lint,int>gcache;
inline int g(lint n){
	if(n<N){
		return _g[n];
	}
	map<lint,int>::iterator it=gcache.find(n);
	if(it!=gcache.end()){
		return it->second;
	}
	int ans=1;
	static int rev=(MOD+1)>>1;
	for(lint l=2,r,x;l<=n;l=r+1){
		x=n/l;
		r=n/x;
		ans=sub(ans,mul(x<N?_g[x]:gcache[x],(r-l+1)%MOD*(l+r)%MOD*rev%MOD));
	}
	return gcache[n]=ans;
}
inline int t(lint n){
	static int rev=fpow(9,MOD-2);
	int fac=fpow(10,(n+1)%(MOD-1));
	return mul(add(mul(n%MOD,fac),mul(sub(10,fac),rev)),rev);
}
inline void init(){
	memset(np,0,sizeof(np));
	mu[1]=1;
	_g[0]=0;
	_g[1]=1;
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ptop++]=i;
			mu[i]=-1;
		}
		if(mu[i]>0){
			_g[i]=add(_g[i-1],i);
		}else if(mu[i]<0){
			_g[i]=sub(_g[i-1],i);
		}else{
			_g[i]=_g[i-1];
		}
		for(int j=0,cur=2;j<ptop&&i*cur<N;cur=prime[++j]){
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
	for(lint l=1,r;l<=n;l=r+1){
		r=n/(n/l);
		ans=add(ans,mul(t(n/l),sub(g(r),g(l-1))));
	}
	printf("%d\n",ans);
}
