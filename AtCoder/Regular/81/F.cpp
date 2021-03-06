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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=2010;
char mat[N][N];
int ext[N][N];
int stk[N];
int tol[N],tor[N];
int main(){
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
	}
	memset(ext,0,sizeof(ext));
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<m;j++){
			ext[i][j]=i!=1&&(mat[i-1][j]^mat[i-1][j+1])==(mat[i][j]^mat[i][j+1])?ext[i-1][j]+1:1;
		}
		int ss=0;
		stk[0]=0;
		for(int j=1;j<m;j++){
			for(;ss&&ext[i][stk[ss]]>=ext[i][j];ss--);
			tol[j]=stk[ss]+1;
			stk[++ss]=j;
		}
		stk[ss=0]=m;
		for(int j=m-1;j>=1;j--){
			for(;ss&&ext[i][stk[ss]]>=ext[i][j];ss--);
			tor[j]=stk[ss];
			stk[++ss]=j;
		}
		for(int j=1;j<m;j++){
			apmax(ans,(tor[j]-tol[j]+1)*ext[i][j]);
		}
	}
	printf("%d\n",max(ans,max(n,m)));
	return 0;
}
