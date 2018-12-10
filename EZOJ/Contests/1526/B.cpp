#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
using namespace std;
typedef long long lint;
typedef long double db;
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
const int N=110;
int sigma,a,b;
struct Mat{
	db a[N][N];
	inline void clr(){
		for(int i=0;i<=b;i++){
			for(int j=0;j<=b;j++){
				a[i][j]=0;
			}
		}
	}
	inline void operator = (const Mat &mb){
		for(int i=0;i<=b;i++){
			for(int j=0;j<=b;j++){
				a[i][j]=mb.a[i][j];
			}
		}
	}
	inline void getmul(const Mat &x,const Mat &y){
		for(int i=0;i<=b;i++){
			for(int j=0;j<=b;j++){
				db ans=0;
				for(int k=0;k<=b;k++){
					ans+=x.a[i][k]*y.a[k][j];
				}
				a[i][j]=ans;
			}
		}
	}
}mat;
int go[N][N];
db vec[N];
inline void putpow(int n){
	mset(vec,0,b+1);
	vec[0]=1;
	static Mat tmpmat;
	for(;n;n>>=1,tmpmat.getmul(mat,mat),mat=tmpmat){
		if(n&1){
			static db tmp[N];
			for(int i=0;i<=b;i++){
				tmp[i]=0;
				for(int j=0;j<=b;j++){
					tmp[i]+=mat.a[i][j]*vec[j];
				}
			}
			for(int i=0;i<=b;i++){
				vec[i]=tmp[i];
			}
		}
	}
}
int ch[N];
db dfs(int x,int mxc){
	if(x>b){
		mat.clr();
		for(int i=0;i<b;i++){
			for(int j=1;j<=sigma;j++){
				mat.a[go[i][j]][i]+=db(1)/sigma;
			}
		}
		mat.a[b][b]+=1;
		putpow(a);
		db ans=vec[b];
		for(int i=0;i<mxc;i++){
			ans*=sigma-i;
		}
		return ans;
	}
	db ans=0;
	for(int i=1;i<=sigma&&i<=mxc+1;i++){
		int lnk=go[x-1][i];
		go[x-1][i]=x;
		for(int j=1;j<=sigma;j++){
			go[x][j]=go[lnk][j];
		}
		ch[x]=i;
		ans+=dfs(x+1,max(i,mxc));
		go[x-1][i]=lnk;
	}
	return ans;
}
const db mxlim=1e7;
struct state{
	int n,a,b;
	inline friend bool operator < (const state &a,const state &b){
		return a.n!=b.n?a.n<b.n:a.a!=b.a?a.a<b.a:a.b<b.b;
	}
};
map<state,db>mp;
inline db Main(){
	sigma=ni,b=ni,a=ni;
	if(a<b)return 0;
	if(sigma==1)return 1;
	db calcsize=0;
	for(int t=a;t;t>>=1,calcsize++);
	calcsize*=b*b*b;
	if(calcsize>=mxlim)return 0;
	db ratio=1;
	for(int i=1;i<=b;i++){
		calcsize*=sigma;
		if(calcsize>=mxlim)return 0;
		ratio*=sigma;
	}
	if(calcsize>=mxlim)return 0;
	state sta=(state){sigma,a,b};
	map<state,db>::iterator it=mp.find(sta);
	if(it!=mp.end())return it->second;
	return mp[sta]=dfs(1,0)/ratio;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("beta.in","r",stdin);
	freopen("beta.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%.15Lf\n",Main()));
	return 0;
}
