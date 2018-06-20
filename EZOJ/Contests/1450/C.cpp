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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=73,K=4,O=1000000007;
int k,sk,ssk;//count of variables
void fwt(int a[],int sh=sk){
	if(sh==0)return;
	const int full=1<<sh,half=full>>1;
	for(int i=0;i<ssk;i+=full){
		for(int j=i;j<i+half;j++){
			(a[j+half]+=a[j])%=O;
		}
	}
	fwt(a,sh-1);
}
void ifwt(int a[],int sh=sk){
	if(sh==0)return;
	const int full=1<<sh,half=full>>1;
	for(int i=0;i<ssk;i+=full){
		for(int j=i;j<i+half;j++){
			(a[j+half]+=O-a[j])%=O;
		}
	}
	ifwt(a,sh-1);
}
char* pt;
bool var[K],Q;
bool dfs(){
	if(pt[0]=='x'){
		++pt;
		int i=pt[0]-'1';
		++pt;
		return var[i];
	}
	if(pt[0]=='Q')return ++pt,Q;
	assert(pt[0]=='(');
	++pt;
	if(pt[0]=='~'){
		++pt;
		bool t=dfs();
		assert(pt[0]==')');
		++pt;
		return t;
	}
	bool a=dfs();
	assert(pt[0]=='-');
	++pt;
	assert(pt[0]=='>');
	++pt;
	bool b=dfs();
	assert(pt[0]==')');
	++pt;
	return b||!a;
}
int f[1<<(1<<K)],g[2][1<<K];
int wf[N][2][1<<(1<<K)];
char str[4010];
inline void put_wf(int (*const wf)[1<<(1<<K)]){
	memcpy(wf[0],f,ssk*sizeof(f[0])),fwt(wf[0]);
	memcpy(wf[1],f,ssk*sizeof(f[0])),reverse(wf[1],wf[1]+ssk),fwt(wf[1]);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("proposition.in","r",stdin);
	freopen("proposition.out","w",stdout);
#endif
	const int n=ni;
	k=ni,sk=1<<k,ssk=1<<sk;
	for(int i=0;i<k;i++){
		int btmsk=0;
		for(int s=0;s<sk;s++){
			if((s>>i)&1){
				btmsk|=1<<s;
			}
		}
		f[btmsk]=1;
	}
	put_wf(wf[0]);
	for(int i=1;i<=n;i++){
		reverse(f,f+ssk);
		static int tmpf[1<<(1<<K)];
		mset(tmpf,0,ssk);
		for(int j=0;j<i;j++){
			for(int k=0;k<ssk;k++){
				tmpf[k]=(tmpf[k]+(lint)wf[j][1][k]*wf[i-1-j][0][k])%O;
			}
		}
		ifwt(tmpf);
		for(int j=0;j<ssk;j++){
			f[j]=(f[j]+tmpf[j])%O;
		}
		put_wf(wf[i]);
	}
	for(int tot=ni;tot--;){
		scanf("%s",str);
		for(int i=0;i<2;i++){
			Q=i;
			for(int s=0;s<sk;s++){
				pt=str,g[i][s]=dfs();
			}
		}
		lint ans=0;
		for(int i=0;i<ssk;i++){
			bool flag=true;
			for(int j=0;j<sk;j++){
				if(!g[(i>>j)&1][j]){
					flag=false;
					break;
				}
			}
			if(flag){
				ans+=f[i];
			}
		}
		printf("%lld\n",ans%O);
	}
	return 0;
}
