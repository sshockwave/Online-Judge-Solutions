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
const int N=100010,logN=20;
lint f[N][logN];
int ldep[N];
lint cnt[N];
lint b[N];
inline int gpre(int x,lint val){
	for(int j=ldep[x];x&&j>=0;j--){
		if(f[x][j]>val){
			x-=1<<j;
		}
	}
	return x;
}
int main(){
	int n=ni,m=ni;
	ldep[0]=-1;
	for(int i=1;i<=m;i++){
		f[i][0]=next_num<lint>();
		cnt[i]=0;
		ldep[i]=ldep[i-1]+(i==(i&-i));
		for(int j=0;j<ldep[i];j++){
			f[i][j+1]=min(f[i][j],f[i-(1<<j)][j]);
		}
	}
	f[0][0]=n;
	cnt[m]=1;
	for(;m>=1;m--){
		if(cnt[m]==0)continue;
		lint val=f[m][0];
		for(int i=m;i=gpre(i-1,val),cnt[i]+=val/f[i][0]*cnt[m],val%=f[i][0],i>0;);
		b[1]+=cnt[m],b[val+1]-=cnt[m];
	}
	b[1]+=cnt[0];
	for(int i=1;i<=n;i++){
		printf("%lld\n",b[i]+=b[i-1]);
	}
	return 0;
}
