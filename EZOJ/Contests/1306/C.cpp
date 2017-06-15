#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=110,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
int c[N][N],f[N][N],sz[N];
char s[N];
inline void cal(int f[],int fl[],int fr[],int nx,int ny){
	for(int i=0;i<=nx;i++){
		for(int j=0;j<=ny;j++){
			apadd(f[i+j],mul(mul(fl[i],fr[j]),mul(c[i+j][i],c[nx-i+ny-j][nx-i])));
		}
	}
}
inline void init_c(int n){
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=add(c[i-1][j-1],c[i-1][j]);
			assert(j<i-j||c[i][j]==c[i][i-j]);
		}
	}
}
int main(){
	int n=ni;
	init_c(n);
	scanf("%s",s+2);
	memset(f,0,sizeof(f));
	memset(sz,0,sizeof(sz));
	if(n<=2){
		putchar(1),putchar('\n');
		return 0;
	}
	for(int i=n;i>1;i--){
		int l=i<<1,r=l+1;
		if(l>n){
			sz[i]=1;
			f[i][s[i]=='>']=1;
		}else if(r>n){
			sz[i]=2;
			assert((l<<1)>n);
			if(s[i]=='>'){//this < fa
				if(s[l]=='>'){//this > lson
					f[i][2]=1;
				}else{//this < lson
					f[i][1]=f[i][2]=1;
				}
			}else{//this > fa
				if(s[l]=='>'){//this > lson
					f[i][0]=f[i][1]=1;
				}else{//this < lson
					f[i][0]=1;
				}
			}
		}else{
			sz[i]=sz[l]+sz[r]+1;
			int *F=f[i];
			cal(F,f[l],f[r],sz[l],sz[r]);
			assert(F[sz[i]]==0);
			if(s[i]=='>'){//this < fa
				for(int j=1;j<=sz[i];j++){
					apadd(F[j],F[j-1]);
				}
				for(int j=sz[i];j>0;j--){
					F[j]=F[j-1];
				}
				F[0]=0;
			}else{//this > fa
				for(int j=sz[i]-1;j>=0;j--){
					apadd(F[j],F[j+1]);
				}
			}
		}
	}
	sz[1]=sz[2]+sz[3]+1;
	cal(f[1],f[2],f[3],sz[2],sz[3]);
	int ans=0;
	for(int i=0;i<=sz[1];i++){
		apadd(ans,f[1][i]);
	}
	printf("%d\n",ans);
}