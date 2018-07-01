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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=200010,M=2010,O=998244353;
int a[N],n,m;
namespace simpmat{
	int mat[M][M];
	inline void apid(){
		for(int i=0;i<=m+1;i++){
			for(int j=0;j<=m+1;j++){
				mat[i][j]=i==j;
			}
		}
	}
	inline int* g_smat(){
		return (int*)memcpy(new int[m+2],mat[m+1],(m+2)*sizeof(int));
	}
	int col_dt[N];
	inline int* g_imat(){
		int* a=new int[m+2];
		for(int i=0;i<=m+1;i++){
			a[i]=(mat[m][i]+col_dt[i])%O;
		}
		return a;
	}
	inline void main(int* smat[],int* imat[]){
		//get arr
		for(int i=0;i<=n;i++){
			smat[i]=new int[m];
			imat[i]=new int[m];
		}
		{//get smat
			apid(),smat[0]=g_smat();
			static int allsum[M];
			for(int i=0;i<=m+1;i++){
				allsum[i]=1;
			}
			for(int i=1;i<=n;i++){
				const int c=a[i];
				for(int j=0;j<=m;j++){
					const lint v=mat[c][j];
					mat[c][j]=allsum[j];
					allsum[j]=(O-v+(allsum[j]<<1))%O;
					mat[m+1][j]=(mat[m+1][j]+allsum[j])%O;
				}
				smat[i]=g_smat();
			}
		}
		{//get imat
			apid(),mset(col_dt,0,m+2),imat[0]=g_imat();
			for(int i=1;i<=n;i++){
				const int c=a[i];
				for(int j=0;j<=m+1;j++){
					mat[j][c]=(mat[j][c]+col_dt[j])%O;
					col_dt[j]=(col_dt[j]+O-mat[j][c])%O;
					mat[j][c]=(mat[j][c]+O-col_dt[j])%O;
				}
				col_dt[m+1]=(col_dt[m+1]+O-1)%O;
				imat[i]=g_imat();
			}
		}
	}
}
int *mat[2][N],*invmat[2][N];
template<int e>inline int ask(int l,int r){
	if(l>r)return 0;
	int ans=0;
	for(int i=0;i<=m+1;i++){
		ans=(ans+(lint)mat[e][r][i]*invmat[e][l-1][i])%O;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
#endif
	n=ni,m=ni;
	int tot=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	simpmat::main(mat[0],invmat[0]);
	reverse(a+1,a+n+1);
	simpmat::main(mat[1],invmat[1]);
	for(;tot--;){
		const int s=ni,l=ni,r=ni;
		int ans;
		if(s<=l){
			ans=ask<0>(s,r)+O-ask<0>(s,l-1);
		}else if(r<=s){
			ans=ask<1>(n+1-s,n+1-l)+O-ask<1>(n+1-s,n+1-(r+1));
		}else{
			ans=ask<1>(n+1-s,n+1-l)+ask<0>(s,r)-2;
		}
		assert(ans>=0);
		ans=(ans%O+O-(r-l+1))%O;
		printf("%d\n",ans);
	}
	return 0;
}
