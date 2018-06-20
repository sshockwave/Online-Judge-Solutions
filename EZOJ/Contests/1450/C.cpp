#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef vector<int>vi;
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
const int N=73,K=4,O=1000000007;
int k,sk,ssk;//count of variables
inline ostream & operator << (ostream & out,const vi &b){
	out<<"{";
	for(int i=0;i<ssk;i++){
		if(b[i]){
			out<<i<<":"<<b[i]<<",";
		}
	}
	out<<"}";
	return out;
}
vi var[K];
inline void initv(vi &v){
	v.resize(0),v.resize(ssk);
}
inline void rev(vi &v){
	reverse(v.begin(),v.end());
}
void fwt(vi &a,int sh=sk){
	if(sh==0)return;
	const int full=1<<sh,half=full>>1;
	for(int i=0;i<ssk;i+=full){
		for(int j=i;j<i+half;j++){
			(a[j+half]+=a[j])%=O;
		}
	}
	fwt(a,sh-1);
}
void ifwt(vi &a,int sh=sk){
	if(sh==0)return;
	const int full=1<<sh,half=full>>1;
	for(int i=0;i<ssk;i+=full){
		for(int j=i;j<i+half;j++){
			(a[j+half]+=O-a[j])%=O;
		}
	}
	ifwt(a,sh-1);
}
inline vi getconv(vi p,vi q){
	rev(p),fwt(p),fwt(q);
	for(int i=0;i<ssk;i++){
		p[i]=(lint)p[i]*q[i]%O;
	}
	ifwt(p);
	return p;
}
inline void join(vi &f,const vi &p,const vi &q){
	vi tmp=getconv(p,q);
	for(int i=0;i<ssk;i++){
		f[i]=(f[i]+tmp[i])%O;
	}
}
vi Q;
char* pt;
vi dfs(){
	if(pt[0]=='x'){
		++pt;
		int i=pt[0]-'1';
		++pt;
		return var[i];
	}
	if(pt[0]=='Q')return ++pt,Q;
	assert(pt[0]=='(');
	++pt;
	if(pt[0]=='~'){
		++pt;
		vi t=dfs();
		assert(pt[0]==')');
		++pt;
		rev(t);
		return t;
	}
	vi a=dfs();
	assert(pt[0]=='-');
	++pt;
	assert(pt[0]=='>');
	++pt;
	vi b=dfs();
	assert(pt[0]==')');
	++pt;
	return getconv(a,b);
}
vi f[N];
char str[4010];
int main(){
#ifndef ONLINE_JUDGE
	freopen("proposition.in","r",stdin);
	freopen("proposition.out","w",stdout);
#endif
	const int n=ni;
	k=ni,sk=1<<k,ssk=1<<sk;
	initv(f[0]);
	for(int i=0;i<k;i++){
		initv(var[i]);
		int btmsk=0;
		for(int s=0;s<sk;s++){
			if((s>>i)&1){
				btmsk|=1<<s;
			}
		}
		var[i][btmsk]=1;
		f[0][btmsk]=1;
	}
	for(int i=1;i<=n;i++){
		f[i]=f[i-1],rev(f[i]);
		for(int j=0;j<i;j++){
			join(f[i],f[j],f[i-1-j]);
		}
	}
	Q=f[n];
	for(int i=0;i<=n;i++){
		f[i].clear();
	}
	for(int tot=ni;tot--;){
		scanf("%s",str);
		pt=str;
		vi g=dfs();
		printf("%d\n",g[ssk-1]);
	}
	return 0;
}
