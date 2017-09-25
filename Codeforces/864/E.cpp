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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=110,D=2010;
int f[N][D];
int t[N],d[N],p[N];
int seq[N];
int lst[N];
inline bool lstsort(int a,int b){
	return d[a]<d[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fire.in","r",stdin);
	freopen("fire.out","w",stdout);
#endif
	memset(f,0,sizeof(f));
	int n=ni,mx=0;
	for(int i=1;i<=n;i++){
		t[i]=ni,d[i]=ni,p[i]=ni;
		if(d[i]>mx){
			mx=d[i];
		}
		lst[i]=i;
	}
	sort(lst+1,lst+n+1,lstsort);
	memset(f,0,sizeof(f));
	for(int x=1;x<=n;x++){
		int i=lst[x];
		memcpy(f[x],f[x-1],(mx+1)<<2);
		for(int j=d[i]-t[i]-1;j>=0;j--){
			if(f[x][j+t[i]]<f[x][j]+p[i]){
				f[x][j+t[i]]=f[x][j]+p[i];
			}
		}
	}
	int curd=mx;
	for(int i=mx;i>=0;i--){
		if(f[n][i]>f[n][curd]){
			curd=i;
		}
	}
	printf("%d\n",f[n][curd]);
	int ss=0;
	for(int x=n;x>=1;x--){
		int i=lst[x];
		if(curd>=t[i]&&f[x-1][curd-t[i]]+p[i]==f[x][curd]){
			seq[ss++]=i;
			curd-=t[i];
		}
	}
	printf("%d\n",ss);
	sort(seq,seq+ss);
	for(int i=0;i<ss;i++){
		printf("%d ",seq[i]);
	}
	putchar('\n');
	return 0;
}
