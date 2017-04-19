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
int n,f[N],g[N],mid,mx,ans[N],val[N];
pii pval[N];
inline void up(int x){
	f[x]=val[x];
	if((x<<1)<=n&&f[x<<1]>0){
		f[x]+=f[x<<1];
	}
	if(((x<<1)|1)<=n&&f[(x<<1)|1]>0){
		f[x]+=f[(x<<1)|1];
	}
	g[x]=f[x];
	if((x<<1)<=n){
		apmax(g[x],f[x<<1]);
	}
	if(((x<<1)|1)<=n){
		apmax(g[x],f[(x<<1)|1]);
	}
}
inline void update(int x){
	assert(val[x]==-1);
	val[x]=1;
	for(;x>=1;x>>=1){
		up(x);
		apmax(mx,g[x]);
	}
}
int main(){
	int n=ni();
	for(int i=1;i<=n;i++){
		pval[i]=make_pair(ni(),i);
	}
	sort(pval+1,pval+n+1);
	memset(f+1,-1,n<<2);
	memset(g+1,-1,n<<2);
	memset(val+1,-1,n<<2);
	for(int i=n,a=0;i>=1;i--){
		mid=pval[i].first;
		update(pval[i].second);
		for(;a<=mx;a++){
			ans[a]=mid;
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d ",ans[i]);
	}
}
