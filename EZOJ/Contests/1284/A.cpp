#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <utility>
#include <algorithm>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
typedef pair<int,int> pii;
const int N=200010;
int n,f[N],g[N],mid,ans[N],val[N],pos[N];
inline void up(int x){
	f[x]=val[x];
	int l=x<<1,r=l|1;
	if(l<=n&&f[l]>0){
		f[x]+=f[l];
	}
	if(r<=n&&f[r]>0){
		f[x]+=f[r];
	}
	g[x]=f[x];
	if(l<=n){
		apmax(g[x],g[l]);
		if(r<=n){
			apmax(g[x],g[r]);
		}
	}
}
inline void update(int x){
	assert(val[x]==-1);
	val[x]=1;
	for(;x>=1;x>>=1){
		up(x);
	}
}
int main(){
	n=ni();
	for(int i=1;i<=n;i++){
		pos[ni()]=i;
	}
	memset(f+1,-1,n<<2);
	memset(g+1,-1,n<<2);
	memset(val+1,-1,n<<2);
	for(int i=n,a=0;i>=1;i--){
		mid=i;
		update(pos[i]);
		for(;a<=g[1];a++){
			ans[a]=mid;
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ",ans[i]);
	}
}
