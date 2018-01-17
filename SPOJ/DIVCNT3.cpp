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
const int N=1000010,INF=0x7f7f7f7f;
int pri[N],ps=0;
bool np[N];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		if(!np[i]){
			pri[ps++]=i;
		}
		for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
			np[t]=true;
			if(i%p==0)break;
		}
	}
}
int rt;
lint f[N];
int tag[N];
lint lend[N],rend[N];
int bs;
inline lint Main(){
	lint n=next_num<lint>();
	for(rt=0;(lint)rt*rt<n;rt++);
	bs=0;
	for(lint l=1,r;l<=n;l=r+1){
		bs++,lend[bs]=l,rend[bs]=r=n/(n/l);
	}
	for(int i=1;i<=bs;i++){
		f[i]=rend[i];
		tag[i]=INF;
	}
	int i=0;
	for(int p1=1,p2=1;pri[i]<=rt;i++){//G
		lint sq=(lint)pri[i]*pri[i];
		for(int j=bs;rend[j]>=sq;j--){
			lint tmp=rend[j]/pri[i];
			int id=tmp<=rt?tmp:bs-(n/tmp)+1;
			f[j]-=f[id]-max(i-tag[id],0);
		}
		for(;p2<=bs&&rend[p2]<sq;p2++){
			tag[p2]=i;
		}
		for(;p1<=bs&&rend[p1]<pri[i];p1++){
			f[p1]-=max(i-tag[p1],0);
			tag[p1]=INF;
		}
	}
	for(int j=1;j<=bs;j++){
		f[j]=(f[j]-max(i-tag[j],0)-1)*4+1;
		tag[j]=-1;
	}
	for(int p1=bs,p2=bs;--i>=0;){//F
		lint sq=(lint)pri[i]*pri[i];
		for(;p1>=1&&rend[p1]>=pri[i];p1--){
			assert(tag[p1]==-1);
			tag[p1]=i;
		}
		for(;p2>=1&&rend[p2]>=sq;p2--){
			f[p2]+=max(tag[p2]-i,0)<<2;
			tag[p2]=-1;
		}
		for(int j=bs;rend[j]>=sq;j--){
			lint ans=0,nj=rend[j];
			for(int c=1;nj>0;c+=3,nj/=pri[i]){
				int id=nj<=rt?nj:bs-(n/nj)+1;
				ans+=(f[id]+(max(tag[id]-i,0)<<2))*c;
			}
			f[j]=ans;
		}
	}
	return f[bs]+(max(tag[bs]-i,0)<<2);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("divcnt3.in","r",stdin);
	freopen("divcnt3.out","w",stdout);
#endif
	sieve(N-1);
	for(int tot=ni;tot--;){
		printf("%lld\n",Main());
	}
	return 0;
}
