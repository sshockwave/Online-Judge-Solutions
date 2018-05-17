#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
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
const int N=43,M=12,C=4,O=1000000007;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
int prob[M][N][C];
int n,m,c,mc;
int tmpf[M*C][1<<10];
namespace poly{
	typedef int arr[1<<10][M];
	inline void ptmul(arr a,const arr b){
		static int tmpm[N];
		for(int i=0,sn=1<<m;i<sn;i++){
			for(int j=0;j<=m;j++){
				int &ans=tmpm[j]=0;
				for(int k=0;k<=j;k++){
					ans=(ans+(lint)a[i][k]*b[i][j-k])%O;
				}
			}
			memcpy(a[i],tmpm,(m+1)*sizeof(a[i][0]));
		}
	}
	void fwt(arr f,int sh=m){
		if(sh==0)return;
		int n=1<<sh,hn=n>>1;
		for(int i=0;i<hn;i++){
			int *const a0=f[i],*const a1=f[i+hn];
			for(int j=0;j<=m;j++){
				const int p=a0[j],q=a1[j];
				a0[j]=(p+q)%O;
				a1[j]=(p+O-q)%O;
			}
		}
		fwt(f,sh-1),fwt(f+hn,sh-1);
	}
	inline void inv_fwt(arr f,int sh=m){
		const int invn=fpow(2,O-1-sh);
		fwt(f,sh);
		for(int i=0,sn=1<<m;i<sn;i++){
			for(int j=0;j<=m;j++){
				f[i][j]=(lint)f[i][j]*invn%O;
			}
		}
	}
	arr prod[M*C],cur;
	int bitcnt[1<<10];
	inline void pre_work(){
		memset(prod,0,sizeof(prod));
		for(int i=0;i<=mc;i++){
			prod[i][0][0]=1;
			fwt(prod[i]);
		}
		bitcnt[0]=0;
		for(int s=1,ts=1<<m;s<ts;s++){
			bitcnt[s]=bitcnt[s^(s&-s)]+1;
		}
	}
	inline int aft_work(){
		int ans=0,cur,last=0;
		const int sn=1<<m;
		for(int i=0;i<=mc;i++){
			inv_fwt(prod[i]);
			cur=prod[i][sn-1][m];
			ans=(ans+(lint)(cur+O-last)*i)%O;
			last=cur;
		}
		return ans;
	}
	inline void work_join(){
		for(int i=0;i<=mc;i++){
			for(int s=0,sn=1<<m;s<sn;s++){
				mset(cur[s],0,m+1);
				cur[s][bitcnt[s]]=tmpf[i][s];
			}
			fwt(cur);
			ptmul(prod[i],cur);
		}
	}
}
int f[1<<10][M*C];
inline void work(int x){
	f[0][0]=1;
	for(int i=1;i<=m;i++){
		int bitmask=1<<(i-1);
		const int* const P=prob[i][x];
		for(int s=0;s<bitmask;s++){
			int* const nf=f[s|bitmask];
			mset(nf,0,mc+1);
			for(int j=0;j<=mc;j++){
				const lint F=f[s][j];
				if(F==0)continue;
				for(int k=0;k<=c;k++){
					nf[j+k]=(nf[j+k]+F*P[k])%O;
				}
			}
		}
	}
	for(int s=0,ts=1<<m;s<ts;s++){
		int cur=0;
		for(int i=0;i<=mc;i++){
			tmpf[i][s]=cur=(cur+f[s][i])%O;
		}
	}
	poly::work_join();
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("max.in","r",stdin);
	freopen("max.out","w",stdout);
#endif
	n=ni,m=ni,c=ni,mc=m*c;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			for(int k=0;k<=c;k++){
				prob[i][j][k]=ni;
			}
		}
	}
	poly::pre_work();
	for(int i=1;i<=n;i++){
		work(i);
	}
	printf("%d\n",poly::aft_work());
	return 0;
}
