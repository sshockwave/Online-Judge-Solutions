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
template<class T>inline T cabs(const T &a){return a>=0?a:-a;}
template<class T>inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
const lint LINF=0x7f7f7f7f7f7f7f7fll;
struct db{
	lint a,b;
	db(lint _a=0,lint _b=1):a(_a),b(_b){}
	inline db& sani(){
		lint d=gcd(cabs(a),b);
		a/=d,b/=d;
		if(b<0){
			a=-a,b=-b;
		}
		return *this;
	}
	inline int sig(){
		return a>0?1:a<0?-1:0;
	}
	inline db operator -(){
		return db(-a,b);
	}
	inline friend db operator + (const db &a,const db &b){
		return db(a.a*b.b+a.b*b.a,a.b*b.b).sani();
	}
	inline friend db operator - (const db &a,const db &b){
		return db(a.a*b.b-a.b*b.a,a.b*b.b).sani();
	}
	inline friend db operator * (const db &a,const db &b){
		return db(a.a*b.a,a.b*b.b).sani();
	}
	inline friend db operator / (const db &a,const db &b){
		return db(a.a*b.b,a.b*b.a).sani();
	}
	inline void operator += (const int &x){a+=x*b;}
	inline void operator -= (const int &x){a-=x*b;}
	inline void operator += (const db &b){*this=*this+b;}
	inline void operator *= (const db &b){*this=*this*b;}
	inline friend bool operator == (const db &a,const db &b){
		return a.a==b.a&&a.b==b.b;
	}
	inline friend bool operator < (const db &a,const db &b){
		return (b-a).sig()==1;
	}
	inline friend ostream & operator << (ostream & out,const db &b){
		out<<(double)b.a/b.b;
		return out;
	}
};
namespace lp{
	const int N=45*2+3,M=45*8+15;
	db a[M][N];
	int n=0,m=0;
	int nvar[N],mvar[M];
	inline int nn(){
		return ++n;
	}
	inline db* newlimit(){
		return a[++m];
	}
	inline void print(){
		cout<<"nvar:\t\t";
		for(int i=1;i<=n;i++){
			cout<<nvar[i]<<"\t";
		}
		cout<<endl;
		for(int j=0;j<=m;j++){
			cout<<"lim "<<mvar[j]<<":\t";
			for(int i=0;i<=n;i++){
				cout<<a[j][i]<<"\t";
			}
			cout<<endl;
		}
	}
	inline void pivot(int x,int y){
		swap(nvar[x],mvar[y]);
		db t=-db(1)/a[y][x];
		a[y][x]=-1;
		for(int i=0;i<=n;i++){
			a[y][i]*=t;
		}
		for(int j=0;j<=m;j++){
			if(j==y)continue;
			t=a[j][x],a[j][x]=0;
			for(int i=0;i<=n;i++){
				a[j][i]+=t*a[y][i];
			}
		}
	}
	inline bool simplex(){
		for(int x,y;;pivot(x,y)){
			x=y=0;
			for(int i=1;i<=n;i++){
				if(a[0][i].sig()==1&&(x==0||nvar[i]<nvar[x])){
					x=i;
				}
			}
			if(x==0)return true;
			db val(LINF);
			for(int j=1;j<=m;j++){
				if(a[j][x].sig()==-1){
					apmin(val,-a[j][0]/a[j][x]);
				}
			}
			if(val==db(LINF))return /* Unbounded */false;
			for(int j=1;j<=m;j++){
				if(a[j][x].sig()==-1&&val==-a[j][0]/a[j][x]&&(y==0||mvar[j]<mvar[y])){
					y=j;
				}
			}
		}
	}
	db b[N];
	inline db solve(){
		for(int i=1;i<=n;i++){
			nvar[i]=i;
		}
		for(int j=1;j<=m;j++){
			mvar[j]=j+n;
		}
		int y=0;
		for(int j=1;j<=m;j++){
			if(a[j][0]<a[y][0]){
				y=j;
			}
		}
		if(y){//initialization
			for(int i=0;i<=n;i++){
				b[i]=a[0][i],a[0][i]=0;
			}
			nvar[++n]=0;
			a[0][n]=-1;
			for(int j=1;j<=m;j++){
				a[j][n]=1;
			}
			pivot(n,y);
			simplex();
			assert(a[0][0].sig()==0);
			for(int i,j=1;j<=m;j++){
				if(mvar[j])continue;
				assert(a[j][0].sig()==0);
				for(i=1;a[j][i].sig()==0;i++);
				pivot(i,j);
				break;
			}
			for(int i=1;i<n;i++){
				if(nvar[i])continue;
				nvar[i]=nvar[n];
				for(int j=0;j<=m;j++){
					a[j][i]=a[j][n];
				}
			}
			n--;
			for(int i=1;i<=n;i++){
				a[0][i]=0;
			}
			for(int i=1;i<=n;i++){
				if(nvar[i]<=n){
					a[0][i]+=b[nvar[i]];
				}
			}
			for(int j=1;j<=m;j++){
				if(mvar[j]<=n){
					for(int i=0;i<=n;i++){
						a[0][i]+=b[mvar[j]]*a[j][i];
					}
				}
			}
		}
		simplex();
		return a[0][0];
	}
}
const int N=15,INF=0x7f7f7f7f;
int dis[N][N];
int inc_node[N][N],dec_node[N][N],disnode[N][N];
inline void add_to_lim(db a[],int u,int v,int w){
	using namespace lp;
	if(u>v){
		swap(u,v);
	}
	if(dis[u][v]<INF){
		a[0]+=dis[u][v]*w;
		a[inc_node[u][v]]+=w;
		a[dec_node[u][v]]-=w;
	}else{
		int x=disnode[u][v];
		assert(x);
		a[x]+=w;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("flydist.in","r",stdin);
	freopen("flydist.out","w",stdout);
#endif
	memset(dis,127,sizeof(dis));
	int n=ni,m=ni;
	for(int i=1;i<=m;i++){
		int u=ni+1,v=ni+1;
		dis[u][v]=dis[v][u]=ni;
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			if(dis[i][j]<INF){
				db* a=lp::newlimit();
				a[0]=dis[i][j];
				inc_node[i][j]=lp::nn();
				dec_node[i][j]=lp::nn();
				a[inc_node[i][j]]=1;
				a[dec_node[i][j]]=-1;
				lp::a[0][inc_node[i][j]]=-1;
				lp::a[0][dec_node[i][j]]=-1;
			}else{
				disnode[i][j]=lp::nn();
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			for(int k=1;k<=n;k++){
				if(i==k||j==k)continue;
				db* a=lp::newlimit();
				//i->k+k->j-i->j>=0
				add_to_lim(a,i,k,1);
				add_to_lim(a,k,j,1);
				add_to_lim(a,i,j,-1);
			}
		}
	}
	db ans=lp::solve();
	printf("%lld/%lld\n",-ans.a,ans.b);
	return 0;
}
