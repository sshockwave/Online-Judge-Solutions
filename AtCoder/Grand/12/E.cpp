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
const int N=200010,SH=19,SN=1<<SH,INF=0x7f7f7f7f;
int tol[N][SH],tor[N][SH];
int fl[SN],fr[SN];
int x[N],v[N];
int ext[N];
int main(){
	int n=ni,vs=0;
	v[0]=ni;
	for(int &i=vs;v[i];i++){
		v[i+1]=v[i]>>1;
	}
	for(int i=1;i<=n;i++){
		x[i]=ni;
	}
	for(int j=0;j<=vs;j++){
		for(int i=1;i<=n;i++){
			tol[i][j]=i>1&&x[i]-x[i-1]<=v[j]?tol[i-1][j]:i;
		}
		for(int i=n;i>=1;i--){
			tor[i][j]=i<n&&x[i+1]-x[i]<=v[j]?tor[i+1][j]:i;
		}
	}
	for(int s=0,ts=1<<vs;s<ts;s++){
		fl[s]=0;
		for(int i=1;i<=vs;i++){
			if((s>>(i-1))&1){
				apmax(fl[s],tor[fl[s^(1<<(i-1))]+1][i]);
			}
		}
	}
	for(int s=0,ts=1<<vs;s<ts;s++){
		fr[s]=n+1;
		for(int i=1;i<=vs;i++){
			if((s>>(i-1))&1){
				apmin(fr[s],tol[fr[s^(1<<(i-1))]-1][i]);
			}
		}
	}
	memset(ext,127,sizeof(ext));
	for(int s=0,ts=1<<vs;s<ts;s++){
		apmin(ext[fl[s]],fr[s^(ts-1)]);
	}
	for(int i=n;i>=1;i--){
		apmin(ext[i-1],ext[i]);
	}
	for(int i=1;i<=n;i++){
		puts(ext[tol[i][0]-1]<=tor[i][0]+1?"Possible":"Impossible");
	}
	return 0;
}
