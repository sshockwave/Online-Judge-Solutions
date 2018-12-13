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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=1010,INF=0x7f7f7f7f;
struct Item{
	int s,p,t,idx;
	inline friend bool operator < (const Item &a,const Item &b){
		return a.s<b.s;
	}
}item[N];
int f[N][N];
bool trans_f[N][N];
void dfs_print(int n,int i){
	if(n==0)return;
	if(trans_f[n][i]){
		dfs_print(n-1,i-item[n].t);
		printf("%d ",item[n].idx);
	}else{
		dfs_print(n-1,i);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dandelion.in","r",stdin);
	freopen("dandelion.out","w",stdout);
#endif
	int n=ni,tlim=ni;
	f[0][0]=ni;
	for(int i=1;i<=n;i++){
		item[i]=(Item){ni,ni,ni,i};
	}
	sort(item+1,item+n+1);
	for(int i=1;i<=tlim;i++){
		f[0][i]=-INF;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=tlim;j++){
			f[i][j]=f[i-1][j],trans_f[i][j]=false;
			if(j>=item[i].t){
				const int sp=f[i-1][j-item[i].t];
				if(sp>=item[i].s&&sp+item[i].p>f[i][j]){
					f[i][j]=sp+item[i].p,trans_f[i][j]=true;
				}
			}
		}
	}
	int p=0;
	for(int i=0;i<=tlim;i++){
		if(f[n][i]>f[n][p]){
			p=i;
		}
	}
	printf("%d\n",f[n][p]);
	dfs_print(n,p);
	putchar('\n');
	return 0;
}
