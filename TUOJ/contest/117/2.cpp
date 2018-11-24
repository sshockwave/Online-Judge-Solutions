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
const int L=30,N=100010,O=1000000007;
template<class T>inline void apadd(int &a,const T &b){
	a=(a+b)%O;
}
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
int pri[N];
typedef map<int,lint>mii;
mii mp;
inline int bitcnt(int n){
	int a=0;
	for(;n;n&=n-1,a++);
	return a;
}
int lst[L],f[L];
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	int slen,bmask=0;
	{
		char s[30];
		scanf("%s",s);
		slen=strlen(s);
		for(int i=0;i<slen;i++){
			bmask|=(s[i]=='0')<<i;
		}
	}
	int n=0;
	int ans=1;
	mp[0]=1;
	for(int tot=ni;tot--;){
		const int p=ni,e=ni;
		ans=(lint)ans*fpow(p,e-1)%O;
		if(p<slen){
			for(int i=0;i<p;i++){
				lst[i]=0;
				for(int j=i;j<slen;j+=p){
					lst[i]|=1<<j;
				}
			}
			for(mii::iterator it=mp.end();it!=mp.begin();){
				--it;
				const int F=it->second%O;
				it->second=0;
				const int s=it->first;
				for(int i=0;i<p;i++){
					if(((s|lst[i])|bmask)==bmask){
						mp[s|lst[i]]+=F;
					}
				}
			}
			for(mii::iterator it=mp.begin(),ti=mp.end();it!=ti;){
				if(it->second==0){
					mp.erase(it++);
				}else{
					++it;
				}
			}
		}else{
			pri[++n]=p;
		}
	}
	const int onecnt=bitcnt(bmask);
	mset(f,0,onecnt+1);
	for(mii::iterator it=mp.begin(),ti=mp.end();it!=ti;++it){
		apadd(f[bitcnt(it->first)],it->second);
	}
	for(int i=1;i<=n;i++){
		for(int j=onecnt;j>=0;j--){
			apadd(f[j+1],(lint)f[j]*(onecnt-j)%O);
			f[j]=(lint)f[j]*(pri[i]-slen+j)%O;
		}
	}
	ans=(lint)ans*f[onecnt]%O;
	printf("%d\n",ans);
	return 0;
}
