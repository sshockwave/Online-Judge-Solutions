#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
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
const int N=200010;
int a[N],b[N],pos[N];
int q;
inline void sim(const lint l,const lint r){
	for(int i=l;i<=r;i++){
		const int t=pos[b[(i-1)%q]];
		swap(a[1],a[t]);
		pos[a[1]]=1,pos[a[t]]=t;
	}
}
int tmpa[N],tmppos[N];
int nx[N];
bool vis[N];
int lst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sim.in","r",stdin);
	freopen("sim.out","w",stdout);
#endif
	const int n=ni;
	q=ni;
	lint m=next_num<lint>();
	for(int i=1;i<=n;i++){
		pos[a[i]=ni]=i;
	}
	for(int i=0;i<q;i++){
		b[i]=ni;
	}
	if(m<q*2){
		sim(1,m);
	}else{
		sim(1,q);
		m-=q;
		memcpy(tmpa+1,a+1,n*sizeof(a[0]));
		sim(1,q),m-=q;
		const lint step=m/q;
		for(int i=1;i<=n;i++){
			nx[i]=tmpa[pos[i]];
		}
		memcpy(tmppos+1,pos+1,n*sizeof(pos[0]));
		mset(vis+1,0,n);
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				int ls=0;
				for(int j=i;!vis[j];j=nx[j]){
					lst[ls++]=j;
					vis[j]=true;
				}
				for(int j=0;j<ls;j++){
					int x=lst[j];
					pos[x]=tmppos[lst[(j+step)%ls]];
				}
			}
		}
		for(int i=1;i<=n;i++){
			a[pos[i]]=i;
		}
		sim(1,m%q);
	}
	for(int i=1;i<=n;i++){
		printf("%d ",a[i]);
	}
	putchar('\n');
	return 0;
}
