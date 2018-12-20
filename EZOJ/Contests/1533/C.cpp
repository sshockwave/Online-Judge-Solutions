#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
const int N=6,O=1e9+7;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
int tp_calc[1<<N],ps=0;
inline int eid(int i,int j){
	if(i>j)swap(i,j);
	return ps+i*ps+j;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("six.in","r",stdin);
	freopen("six.out","w",stdout);
#endif
	{
		static int ep[N];
		{
			lint n=next_num<lint>();
			for(int i=2;(lint)i*i<=n;i++){
				if(n%i==0){
					int e=1;
					n/=i;
					for(;n%i==0;n/=i,e++);
					ep[ps++]=e;
				}
			}
			if(n>1){
				ep[ps++]=1;
			}
		}
		{
			tp_calc[0]=1;
			for(int i=0;i<ps;i++){
				tp_calc[1<<i]=ep[i];
			}
			int sn=1<<ps;
			for(int s=1;s<sn;s++){
				const int ts=s&-s;
				if(ts==s)continue;
				tp_calc[s]=(lint)tp_calc[ts]*tp_calc[s^ts]%O;
			}
		}
	}
	typedef map<lint,int>mp;
	mp f,nf;
	f[0]=1;
	int ans=0;
	for(;!f.empty();){
		lint cur=0;
		for(mp::iterator it=f.begin(),ti=f.end();it!=ti;++it){
			const lint s=it->first;
			const lint F=it->second;
			assert(F);
			cur+=F;
			int bm=0;
			for(int i=0;i<ps;i++){
				if(((s>>eid(i,i))&1)==0){
					bm|=1<<i;
				}
			}
			for(int t=bm;t;t=(t-1)&bm){
				bool ok=true;
				for(int i=0;i<ps;i++){
					if(((t>>i)&1)==0)continue;
					for(int j=i+1;j<ps;j++){
						if(((t>>j)&1)==0)continue;
						if((s>>eid(i,j))&1){
							ok=false;
							break;
						}
					}
					if(!ok)break;
				}
				if(!ok)continue;
				lint ns=s|t;
				for(int i=0;i<ps;i++){
					if(((t>>i)&1)==0)continue;
					for(int j=0;j<ps;j++){
						if(((s>>j)&1)==0)continue;
						ns|=1ll<<eid(i,j);
					}
				}
				apadd(nf[ns],F*tp_calc[t]);
			}
		}
		apadd(ans,cur);
		f=nf,nf.clear();
	}
	apadd(ans,O-1);
	printf("%d\n",ans);
	return 0;
}
