#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=100010;
int fa[N],sz[N];//unifind
int root(int x){
	return fa[x]?fa[x]=root(fa[x]):x;
}
inline void mg(int u,int v){
	u=root(u),v=root(v);
	if(u==v)return;
	if(sz[u]>sz[v]){
		swap(u,v);
	}
	fa[u]=v,sz[v]+=sz[u];
}
int x[N],y[N],z[N],binl[N],binm[N],binr[N],lst[N];//queries
struct Edge{
	int u,v;
}e[N];
inline bool lcmp(int a,int b){
	if(binl[a]==binr[a])return false;
	if(binl[b]==binr[b])return true;
	return binm[a]<binm[b];
}
int main(){
	int n=ni,es=ni;
	memset(fa+1,0,n<<2);
	for(int i=1;i<=es;i++){
		e[i]=(Edge){ni,ni};
	}
	int tot=ni;
	for(int i=1;i<=tot;i++){
		x[i]=ni,y[i]=ni,z[i]=ni,lst[i]=i;
		binl[i]=1,binr[i]=es,binm[i]=(binl[i]+binr[i])>>1;
	}
	while(sort(lst+1,lst+tot+1,lcmp),binl[lst[1]]!=binr[lst[1]]){
		for(int i=1;i<=n;i++){
			fa[i]=0,sz[i]=1;
		}
		for(int i=1,j,k=1;j=lst[i],i<=tot&&binl[j]!=binr[j];i++){
			for(;k<=binm[j];mg(e[k].u,e[k].v),k++);
			int u=root(x[j]),v=root(y[j]);
			if((u==v?sz[u]:sz[u]+sz[v])>=z[j]){
				binr[j]=binm[j];
			}else{
				binl[j]=binm[j]+1;
			}
			binm[j]=(binl[j]+binr[j])>>1;
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",binm[i]);
	}
	return 0;
}
