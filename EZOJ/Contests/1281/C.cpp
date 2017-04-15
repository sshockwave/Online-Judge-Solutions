#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=105,K=6,N2=N*2,MOD=1000000007;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
int kind[K];
int f[N][N][N2],g[N][N][N2],umlim[N][N];
inline void cal_umlim(int n){
	memset(umlim,0,sizeof(umlim));
	umlim[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			int U=umlim[i][j];
			apadd(umlim[i+1][j],mul(U,2));
			for(int l=2;l<=5;l++){
				apadd(umlim[i+l][j],mul(U,kind[l]));
			}
			apadd(umlim[i+1][j+1],U);
			if(j){
				apadd(umlim[i+1][j-1],U);
			}
		}
	}
}
int main(){
	int n=ni(),k=ni();
	memset(kind,0,sizeof(kind));
	if(k>9){
		kind[2]=9;
		if(k>99){
			kind[3]=90;
			if(k>999){
				kind[4]=900;
				kind[5]=k-999;
			}else{
				kind[4]=k-99;
			}
		}else{
			kind[3]=k-9;
		}
	}else{
		kind[2]=k;
	}
	cal_umlim(n);
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	f[0][0][N]=1;
	lint F,G;
	#define NF f[i+1]
	#define NG g[i+1]
	for(int i=0;i<n;i++){//first i
		for(int j=0;j<=i;j++){//[ cnt
			for(int k=-i,k0;k<=i;k++){
				k0=k+N;
				if(F=f[i][j][k0]){
					apadd(NF[j][k0+1],F);
					apadd(NF[j][k0-1],F);
					for(int l=2;l<=5;l++){
						apadd(f[i+l][j][k0],mul(F,kind[l]));
					}
					if(k==0){
						//]
						if(j){
							apadd(NF[j-1][k0],F);
						}
						//[
						for(int l=0;i+l<=n;l++){
							apadd(f[i+l+2][j][k0],mul(F,umlim[l][0]));
						}
					}else{
						//[
						apadd(NF[j+1][k0],F);
						if(k>0){
							for(int d=1;d<k;d++){
								if(k%d==0){
									apadd(NG[j+1][N+d],F);
								}
							}
						}else{
							for(int d=-1;d>k;d--){
								if(k%d==0){
									apadd(NG[j+1][N+d],F);
								}
							}
						}
					}
				}
				if(G=g[i][j][k0]){
					apadd(NG[j][k0+1],G);
					apadd(NG[j][k0-1],G);
					for(int l=2;l<=5;l++){
						apadd(g[i+l][j][k0],mul(G,kind[l]));
					}
					if(k==0){
						apadd(NF[j-1][k0],G);
					}
				}
			}
		}
	}
	int ans=0;
	for(int i=-n;i<=n;i++){
		apadd(ans,f[n][0][i+N]);
	}
	printf("%d\n",ans);
}
