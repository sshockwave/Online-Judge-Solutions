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
const int N=300010,INF=0x7f7f7f7f;
int f[N],fpt[N],cnt[N],rst[N],n;
inline void up(int x){
	f[x]=INF;
	if(rst[x]){
		f[x]=0,fpt[x]=x;
	}
	int lson=x<<1,rson=lson^1;
	if(lson<=n&&f[lson]<INF){
		int v=f[lson]+(cnt[lson]>=0?1:-1);
		if(v<f[x]){
			f[x]=v,fpt[x]=fpt[lson];
		}
	}
	if(rson<=n&&f[rson]<INF){
		int v=f[rson]+(cnt[rson]>=0?1:-1);
		if(v<f[x]){
			f[x]=v,fpt[x]=fpt[rson];
		}
	}
}
inline int work(int x){
	int fv=f[x],ft=fpt[x];
	int pre=0;
	for(int y=x;y>1;y>>=1){
		pre+=cnt[y]<=0?1:-1;
		int fa=y>>1,bro=y^1;
		if(rst[fa]&&pre<fv){
			fv=pre,ft=fa;
		}
		if(bro<=n&&f[bro]<INF){
			int tmp=pre+(cnt[bro]>=0?1:-1)+f[bro];
			if(tmp<fv){
				fv=tmp,ft=fpt[bro];
			}
		}
	}
	assert(rst[ft]>0);
	rst[ft]--;
	while(x!=ft){
		if(x>ft){
			cnt[x]--,up(x),x>>=1;
		}else{
			cnt[ft]++,up(ft),ft>>=1;
		}
	}
	for(;x;up(x),x>>=1);
	return fv;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("bird.in","r",stdin);
	freopen("bird.out","w",stdout);
#endif
	n=ni;
	int tot=ni;
	for(int i=1;i<=n;i++){
		rst[i]=ni;
	}
	for(int i=n;i>=1;i--){
		up(i);
	}
	for(int sum=0;tot--;printf("%d\n",sum+=work(ni)));
	return 0;
}
