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
template<class T>inline T abs(T x){return x>=0?x:-x;}
const int L=1010,N=110,O=1000000007;
inline void apadd(int &a,const int &b){
	a=(a+b)%O;
}
int h[N];
int f[L][N][2][2];
int g[N][2][2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
#endif
	const int n=ni,len=ni;
	for(int i=1;i<=n;i++){
		h[i]=ni;
	}
	sort(h+1,h+n+1);
	h[n+1]=h[n];
	memset(f,0,sizeof(f));
	f[0][0][0][0]=1;
	for(int i=n;i>=2;i--){
		int sz=sizeof(g[0])*(n-i+1),dt=h[i+1]-h[i];
		for(int l=len;l>=0;l--){
			memcpy(g,f[l],sz);
			memset(f[l],0,sz);
			for(int j=0;j<=n-i&&l+dt*(j<<1)<=len;j++){
				for(int a=0;a<2;a++){
					for(int b=0;b<2;b++){
						lint F=g[j][a][b];
						if(F==0)continue;
						int sd=(j<<1)+a+b;
						int jmp=l+dt*sd;
						if(jmp>len)continue;
						int (*f)[2][2]=::f[jmp];
						apadd(f[j+1][a][b],F);//new peak
						apadd(f[j][a][b],F*sd);//slope
						if(a==0){
							apadd(f[j][1][b],F);
						}
						if(b==0){
							apadd(f[j][a][1],F);
						}
						if(j){//join
							apadd(f[j-1][1][b],F*j%O);
							apadd(f[j-1][a][1],F*j%O);
							if(j>=2){
								apadd(f[j-1][a][b],F*j%O*(j-1)%O);
							}
						}
					}
				}
			}
		}
	}
	lint ans=0;
	int dt=h[2]-h[1];
	for(int l=0;l<=len;l++){
		for(int a=0;a<2;a++){
			for(int b=0;b<2;b++){
				int F=f[l][0][a][b];
				if(F==0)continue;
				int jmp=l+dt*(a+b);
				if(jmp>len)continue;
				ans+=F;
			}
		}
	}
	printf("%lld\n",ans%O);
	return 0;
}
