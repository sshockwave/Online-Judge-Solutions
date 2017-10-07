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
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T>inline T cabs(T x){
	return x>0?x:-x;
}
const int N=103,M=30,K=53,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
int f[N][K][K][M][2][2];//f[i][vis][plug][mod][st][ed]
int main(){
#ifndef ONLINE_JUDGE
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
#endif
	int n=ni,m=ni,k=ni;
	memset(f,0,sizeof(f));
	f[0][0][0][0][0][0]=1;
	for(int i=1;i<=n;i++){
		int d=i==1?0:ni;
		for(int vis=0,tv=min(i,k+1);vis<tv;vis++){
			for(int plug=0;plug<i;plug++){
				for(int mod=0;mod<m;mod++){
					for(int st=0;st<=1;st++){
						for(int ed=0;ed<=1;ed++){
							int val=f[i-1][vis][plug][mod][st][ed];
							int rp=((plug<<1)+st-ed);
							int curm=((lint)d*rp+mod)%m;
							apadd(f[i][vis][plug][curm][st][ed],val);
							if(vis<k){
								if(!st){
									//as new plug
									apadd(f[i][vis+1][plug][curm][true][ed],val);
									//implement a plug
									if(plug){
										apadd(f[i][vis+1][plug-1][curm][true][ed],val);
									}
								}
								if(!ed){
									//as new plug
									apadd(f[i][vis+1][plug+1][curm][st][true],val);
									//implement a plug
									if(plug){
										apadd(f[i][vis+1][plug][curm][st][true],val);
									}else if(st){
										apadd(f[i][vis+1][plug][curm][true][true],val);
									}
								}
								//as new plug
								apadd(f[i][vis+1][plug+1][curm][st][ed],mul(val,plug+1-ed));
								//implement a plug
								apadd(f[i][vis+1][plug][curm][st][ed],mul(val,rp));
								//connect two plugs
								if(plug){
									apadd(f[i][vis+1][plug-1][curm][st][ed],mul(val,plug-1+st));
								}
							}
						}
					}
				}
			}
		}
	}
	printf("%d\n",f[n][k][0][0][1][1]);
	return 0;
}
