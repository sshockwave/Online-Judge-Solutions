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
template<class T>inline T sqr(const T &x){return x*x;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=5010,O=998244353,INF=0x7f7f7f7f;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
struct State{
	int mn,rig;
	bool tor;
	inline friend bool operator < (const State &a,const State &b){
		if(a.mn!=b.mn)return a.mn<b.mn;
		if(a.rig!=b.rig)return a.rig<b.rig;
		if(a.tor!=b.tor)return a.tor;
		return false;
	}
};
int s1[N],s2[N];
inline void input(int s[],int &n){
	static char t[N];
	scanf("%s",t+1);
	n=strlen(t+1);
	for(int i=1;i<=n;i++){
		s[i]=t[i]=='P'?-1:t[i]=='V'?1:0;
	}
}
typedef map<State,int>mp;
inline mp dp1(int n){
	mp f,nf;
	f[((State){INF,0,false})]=1;
	for(int i=1;i<=n;i++){
		for(mp::iterator it=f.begin(),ti=f.end();it!=ti;++it){
			int mn=it->first.mn;
			int rig=it->first.rig;
			if(s1[i]>=0){
				apadd(nf[((State){mn,rig+1,false})],it->second);
			}
			if(s1[i]<=0){
				apadd(nf[((State){min(mn,rig-1),rig-1,false})],it->second);
			}
		}
		f=nf,nf.clear();
	}
	return f;
}
inline mp dp2(mp f,int n){
	mp nf;
	for(mp::iterator it=f.begin(),ti=f.end();it!=ti;++it){
		int mn=it->first.mn;
		int rig=it->first.rig;
		apadd(nf[((State){mn,rig,mn>=0})],it->second);
	}
	f=nf,nf.clear();
	for(int i=1;i<=n;i++){
		for(mp::iterator it=f.begin(),ti=f.end();it!=ti;++it){
			int mn=it->first.mn;
			int rig=it->first.rig;
			bool tor=it->first.tor;
			if(s2[i]>=0){
				apadd(nf[((State){mn+1,rig+1,tor||mn+1>=0})],it->second);
			}
			if(s2[i]<=0){
				if(!(mn<0||(tor&&rig==0))){
					apadd(nf[((State){mn-1,rig-1,tor})],it->second);
				}
			}
		}
		f=nf,nf.clear();
	}
	return f;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int n,m;
	input(s1,n);
	mp f=dp1(n);
	input(s2,m);
	f=dp2(f,m);
	lint ans=0;
	for(mp::iterator it=f.begin(),ti=f.end();it!=ti;++it){
		if(it->first.mn>=0){
			ans+=it->second;
		}
	}
	ans%=O;
	printf("%lld\n",ans);
	return 0;
}
