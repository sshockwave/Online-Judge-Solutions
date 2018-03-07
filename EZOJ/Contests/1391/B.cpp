#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=300010,O=998244353;
inline int fpow(int x,lint n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
bool r[N];
namespace C{
	int sz[N],nxt[N],tail[N];
	inline void init(int n){
		for(int i=1;i<=n;i++){
			sz[i]=1,nxt[i]=0,tail[i]=i;
		}
	}
	inline void jn(int &x,int y){
		if(x==0)return x=y,void();
		nxt[tail[x]]=y;
		tail[x]=tail[y];
		sz[x]+=sz[y];
		r[x]^=r[y];
	}
}
int n,m;
inline bool conn(int x,int y){
	return (x<=n)^(y<=n);
}
struct st{
	vector<int>vec;
	inline void init(){
		sort(vec.begin(),vec.end());
	}
	inline void insert(int x){
		vec.push_back(x);
	}
	inline bool find(int x){
		int l=0,r=vec.size()-1;
		while(l<r){
			int m=(l+r)>>1,v=vec[m];
			if(v<x){
				l=m+1;
			}else if(v>x){
				r=m-1;
			}else return true;
		}
		if(l==r&&vec[l]==x)return true;
		return false;
	}
	inline bool chainvac(int x){
		for(;x;x=C::nxt[x]){
			if(!find(x))return true;
		}
		return false;
	}
}edg[N];
int com[N],com2[N],cs,othcs=0;
inline bool ins(int x){
	edg[x].init();
	for(int i=1;i<=cs;i++){
		if(!edg[x].chainvac(com[i]))continue;
		C::jn(com2[i],x);
		int ncs=i;
		for(int j=i+1;j<=cs;j++){
			if(edg[x].chainvac(com[j])){
				C::jn(com[i],com[j]);
				C::jn(com2[i],com2[j]);
			}else{
				ncs++,com[ncs]=com[j],com2[ncs]=com2[j];
			}
		}
		cs=ncs;
		return true;
	}
	othcs++;
	return r[x]==0;
}
inline int Main(){
	n=ni,m=ni;
	int k=ni;
	C::init(n+m);
	memset(r+1,1,n+m);
	for(int i=1;i<=k;i++){
		int x=ni,y=ni+n;
		edg[y].insert(x);
		bool t=ni;
		r[x]^=t,r[y]^=t;
	}
	for(int i=1;i<=n;i++){
		com[i]=i,com2[i]=0;
	}
	cs=n;
	for(int i=n+1;i<=n+m;i++){
		if(!ins(i))return 0;
	}
	for(int i=1;i<=cs;i++){
		if(r[com[i]]^r[com2[i]])return 0;
	}
	return fpow(2,(lint)n*m-k-(n+m-(cs+othcs)));
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
#endif
	printf("%d\n",Main());
	return 0;
}
