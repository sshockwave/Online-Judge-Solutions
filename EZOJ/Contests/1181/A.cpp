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
const int N=1010;
const lint LINF=0x7f7f7f7f7f7f;
const double EPS=1e-6;
lint f[N][N][2];
struct Pt{
	int x,u;
	inline friend bool operator < (const Pt &a,const Pt &b){
		return a.x<b.x;
	}
}pt[N];
int _u[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("repair.in","r",stdin);
	freopen("repair.out","w",stdout);
#endif
	int n=ni,v=ni,x=ni,csum=0;
	for(int i=1;i<=n;i++){
		pt[i].x=ni;
		csum+=ni;
		pt[i].u=ni;
	}
	pt[++n]=(Pt){x,0};
	sort(pt+1,pt+n+1);
	_u[0]=0;
	for(int i=1;i<=n;i++){
		_u[i]=pt[i].u+_u[i-1];
	}
	int fx;
	for(int i=1;i<=n;i++){
		if(pt[i].x==x){
			fx=i;
			break;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[i][j][0]=f[i][j][1]=LINF;
		}
	}
	f[fx][fx][0]=f[fx][fx][1]=0;
	for(int i=fx;i>=1;i--){
		for(int j=fx;j<=n;j++){
			if(i+1<=fx){//this destroy: i
				lint c=_u[i]-_u[j]+_u[n];
				f[i][j][0]=min(f[i+1][j][0]+c*(pt[i+1].x-pt[i].x),f[i+1][j][1]+c*(pt[j].x-pt[i].x));
			}
			if(j-1>=fx){//this destroy: j
				lint c=_u[i-1]-_u[j-1]+_u[n];
				f[i][j][1]=min(f[i][j-1][0]+c*(pt[j].x-pt[i].x),f[i][j-1][1]+c*(pt[j].x-pt[j-1].x));
			}
		}
	}
	printf("%lld\n",(lint)((double)min(f[1][n][0],f[1][n][1])/v+EPS)+csum);
	return 0;
}
