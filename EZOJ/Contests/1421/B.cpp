#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=1000010,T=53,M=1010,facN=260,lenN=22;
const int INF=0x7f7f7f7f;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace sieve{
	int fact[N],factcnt[N],factlen[N];
	bool np[N];
	int pri[N],ps=0;
	int mxcnt[N],ccnt[N],mxp[N],curcnt[N],mnpw[N];
	int rep[N];
	int dfn[N],idx[N],repcnt=0;
	inline void main(int n){
		mset(np+1,0,n);
		rep[1]=1,idx[dfn[1]=++repcnt]=1;
		factlen[1]=0;
		factcnt[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				np[i]=true;
				pri[ps++]=i;
				factlen[i]=1;
				mxcnt[i]=1;
				ccnt[i]=1;
				mxp[i]=i;
				curcnt[i]=1;
				mnpw[i]=i;
			}
			rep[i]=rep[i/mxp[i]]*pri[ccnt[i]-1];
			factcnt[i]=(curcnt[i]+1)*factcnt[i/mnpw[i]];
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				factlen[t]=factlen[i]+1;
				mxcnt[t]=mxcnt[i];
				ccnt[t]=ccnt[i];
				mxp[t]=mxp[i];
				curcnt[t]=i%p==0?curcnt[i]+1:1;
				if(curcnt[t]>mxcnt[t]){
					mxcnt[t]=curcnt[t],ccnt[t]=1,mxp[t]=p;
				}else if(curcnt[t]==mxcnt[t]){
					++ccnt[t];
				}
				if(i%p){
					mnpw[t]=p;
				}else{
					mnpw[t]=p*mnpw[i];
					break;
				}
			}
			if(rep[i]==i){
				idx[dfn[i]=++repcnt]=i;
			}
		}
	}
	inline void gfact(int n){
		fact[0]=1;
		int cnt=1;
		for(;n!=1;){
			int p=mxp[n],e=0;
			for(;n%p==0;n/=p,e++);
			int pcnt=cnt;
			for(int i=1,pw=1;i<=e;i++){
				pw*=p;
				for(int j=0;j<pcnt;j++){
					fact[cnt++]=fact[j]*pw;
				}
			}
		}
	}
}
int mpp[300][300];
lint f1[300][lenN],f2[5800][T][lenN];
lint liney[5800][T];
int len[M],lensum[M],lencnt[lenN],qrycnt;
struct Bonus{
	int x,v;
	inline friend bool operator < (const Bonus &a,const Bonus &b){
		return a.v>b.v;
	}
}st[T];
struct Line{
	lint k,b;
	inline lint operator () (lint x){
		return k*x+b;
	}
}llst[T];
inline bool ign(const Line &a,const Line &b,const Line &c){
	const lint k1=a.k,b1=a.b;
	const lint k2=b.k,b2=b.b;
	const lint k3=c.k,b3=c.b;
	return (b1-b2)*(k1-k3)<=(b1-b3)*(k1-k2);
}
inline void get_hull(int &n){
	for(int i=1,ti=n,&j=n=0;i<=ti;i++){
		if(j>=1&&llst[j].k==llst[i].k){
			apmin(llst[j].b,llst[i].b);
			continue;
		}
		for(;j>=2&&ign(llst[j-1],llst[j],llst[i]);--j);
		llst[++j]=llst[i];
	}
}
int clst[T],stopcnt;
inline lint Main(int a,int b){
	if(a%b)return -qrycnt;
	int dt=a/b;
	int ls=0;
	for(int c=1;c<=stopcnt;c++){
		int d=st[c].x;
		if(a%d==0&&d%b==0){
			using namespace sieve;
			int x=d/b,y=a/d;
			x=dfn[rep[x]],y=dfn[rep[y]];
			++ls,clst[ls]=c;
			llst[ls]=(Line){st[c].v,liney[mpp[x][y]][c]};
		}
	}
	lint ans=0;
	for(int i=1;i<=sieve::factlen[dt];i++){
		if(lencnt[i]==0)continue;
		using namespace sieve;
		lint cur=f1[dfn[rep[dt]]][i];
		for(int j=1;j<=ls;j++){
			int c=clst[j],d=st[c].x;
			int x=d/b,y=a/d;
			x=dfn[rep[x]],y=dfn[rep[y]];
			apmin(cur,f2[mpp[x][y]][c][i]);
		}
		ans+=lencnt[i]*(cur<LINF?cur:-1);
	}
	int j=upper_bound(len+1,len+qrycnt+1,sieve::factlen[dt])-len;
	get_hull(ls);
	for(int i=1,l,m,r;i<=ls&&j<=qrycnt;i++,j=l){
		if(i<ls){
			l=j,r=qrycnt+1;
			while(l<r){
				m=((l+r)>>1);
				if(llst[i](len[m])<=llst[i+1](len[m])){
					l=m+1;
				}else{
					r=m;
				}
			}
		}else{
			l=m=r=qrycnt+1;
		}
		ans+=llst[i].k*(lensum[r-1]-lensum[j-1])+(r-j)*llst[i].b;
	}
	ans-=qrycnt-j+1;
	return ans;
}
int costf[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("gauss.in","r",stdin);
	freopen("gauss.out","w",stdout);
#endif
	{//K
		memset(costf,0,sizeof(costf));
		for(int i=1,ti=ni;i<=ti;i++){
			costf[i]=ni;
		}
	}
	{//M
		qrycnt=ni;
		for(int i=1;i<=qrycnt;i++){
			len[i]=ni;
			if(len[i]<lenN){
				++lencnt[len[i]];
			}
		}
		sort(len+1,len+qrycnt+1);
		for(int i=1;i<=qrycnt;i++){
			lensum[i]=lensum[i-1]+len[i];
		}
	}
	{//T
		stopcnt=ni;
		for(int i=1;i<=stopcnt;i++){
			st[i]=(Bonus){ni,ni};
		}
		sort(st+1,st+stopcnt+1);
	}
	{//init
		int n=1000000;
		sieve::main(n);
		using namespace sieve;
		memset(f1,127,sizeof(f1));
		memset(f2,127,sizeof(f2));
		f1[1][0]=0;
		for(int i=2;i<=repcnt;i++){
			int x=idx[i];
			sieve::gfact(x);
			for(int j=0,tj=factcnt[x]-1;j<tj;j++){
				int v=fact[j];
				for(int k=v!=1;k<=factlen[v];k++){
					apmin(f1[i][k+1],f1[dfn[rep[v]]][k]+costf[factcnt[x/v]]);
				}
			}
		}
		int mps=0;
		memset(liney,127,sizeof(liney));
		for(int i=1;i<=repcnt;i++){
			for(int j=1;j<=repcnt;j++){
				if(idx[i]*idx[j]>n)break;
				mpp[i][j]=++mps;
				int x=idx[i],y=idx[j];
				for(int a=x!=1;a<=factlen[x];a++){
					for(int b=y!=1;b<=factlen[y];b++){
						apmin(f2[mps][0][a+b],f1[i][a]+f1[j][b]);
					}
				}
				for(int c=1;c<=stopcnt;c++){
					if((lint)st[c].x*y>n)continue;
					memcpy(f2[mps][c],f2[mps][0],(factlen[x]+factlen[y]+1)*sizeof(f2[mps][c][0]));
					for(int l=0;l<lenN;l++){
						if(f2[mps][c][l]<LINF){
							apmin(liney[mps][c],f2[mps][c][l]-(lint)st[c].v*l);
							if(l<lenN-1){
								apmin(f2[mps][c][l+1],f2[mps][c][l]+st[c].v);
							}
						}
					}
				}
			}
		}
	}
	for(int tot=ni;tot--;){
		int a=ni,b=ni;
		printf("%lld\n",Main(a,b));
	}
	return 0;
}
