#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef long long lint;
#define cout cerr
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
const int N=4,D=60010,ND=N*D;
int MOD;
lint dis[N][D];
int qx[ND],qm[ND],qh,qt;
bool inque[N][D];
inline void psh(int x,lint d){
	int m=d%MOD;
	if(d<dis[x][m]){
		dis[x][m]=d;
		if(!inque[x][m]){
			inque[x][m]=true;
			qx[qt]=x,qm[qt]=m;
			if(++qt==ND){
				qt=0;
			}
		}
	}
}
int d[N];
inline lint Main(){
	lint k=nl;
	for(int i=0;i<N;i++){
		d[i]=ni;
	}
	MOD=2*min(d[0],d[1]);
	for(int i=0;i<4;i++){
		memset(dis[i],127,MOD<<3);
		memset(inque[i],0,MOD);
	}
	qh=qt=0;
	psh(1,0);
	while(qh!=qt){
		int x=qx[qh];
		int m=qm[qh];
		if(++qh==ND){
			qh=0;
		}
		psh((x+1)&3,dis[x][m]+d[x]);
		psh((x+3)&3,dis[x][m]+d[(x+3)&3]);
		inque[x][m]=false;
	}
	for(;dis[1][k%MOD]>k;k++);
	return k;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("run.in","r",stdin);
	freopen("run.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%lld\n",Main()));
	return 0;
}
