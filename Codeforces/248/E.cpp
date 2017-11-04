#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef long double ld;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010,A=110;
const ld EPS=1e-12;
int a[N],posi[N];
ld f[N][A];
inline ld C(int n,int k){
	if(n<k){
		return 0;
	}
	ld ans=1;
	for(int i=0;i<k;i++){
		ans*=(ld)(n-i)/(i+1);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("piglet.in","r",stdin);
	freopen("piglet.out","w",stdout);
#endif
	int n=ni;
	memset(f,0,sizeof(f));
	ld ans=0;
	for(int i=1;i<=n;i++){
		f[i][a[i]=posi[i]=ni]=1;
		ans+=f[i][0];
	}
	for(int tot=ni;tot--;){
		int u=ni,v=ni,k=ni;
		ans-=f[u][0];
		const ld div=C(a[u],k);
		for(int i=0;i<=posi[u];i++){
			for(int j=min(k,i);j>=1;j--){
				f[u][i-j]+=C(i,j)/div*C(a[u]-i,k-j)*f[u][i];
			}
			f[u][i]*=C(a[u]-i,k)/div;
		}
		a[u]-=k,a[v]+=k;
		apmin(posi[u],a[u]);
		for(int &i=posi[u];i>=0&&f[u][i]<EPS;i--);
		printf("%.10lf\n",(double)(ans+=f[u][0]));
	}
	return 0;
}
