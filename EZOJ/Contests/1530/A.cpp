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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=2010;
int n;
lint ans=0;
int f[N][N];
inline int getf(int i,int x){
	int a=0;
	for(;x;a+=f[i][x],x&=x-1);
	return a;
}
inline void addf(int i,int x,int v){
	for(;x<=n;f[i][x]+=v,x+=x&-x);
}
inline void print(){
	cout<<"curf:"<<endl;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<getf(i,j)<<" ";
		}
		cout<<endl;
	}
}
int a[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("run.in","r",stdin);
	freopen("run.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=max(a[i-1][j],a[i][j-1])+ni;
			ans+=a[i][j];
			addf(i,j,a[i][j]-a[i][j-1]);
		}
	}
	for(int tot=n;printf("%lld\n",ans),tot--;){
		int dt;
		{
			char c;
			for(;!isalpha(c=getchar()););
			dt=c=='U'?1:-1;
		}
		bool fir=true;
		int lastl=0,lastr=0;
		for(int i=ni,l=ni,r=l+1;i<=n;i++){
			for(;r<=n;r++){
				const int a=getf(i,r-1),b=getf(i-1,r);
				if(max(a,b-(lastl<=r&&r<lastr)*dt)==max(a+dt,b))break;
			}
			if(fir){
				fir=false;
			}else for(;l<r;l++){
				const int a=getf(i,l-1),b=getf(i-1,l);
				if(max(a,b-(lastl<=l&&l<lastr)*dt)!=max(a,b))break;
			}
			addf(i,l,dt),addf(i,r,-dt);
			ans+=(r-l)*dt;
			lastl=l,lastr=r;
		}
	}
	return 0;
}
