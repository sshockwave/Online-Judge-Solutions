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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=3010,M=1000010;
namespace LIB{
	const int N=30;
	int dim[N],dimcnt;
	template<class T>void dfs(int dep,T g,int x,int y,int z,int n){
		if(dep>dimcnt)return g[x][y]=z,void();
		int d=n/dim[dep];
		for(int i=0;i<n;i+=d){
			for(int j=0;j<n;j+=d){
				dfs(dep+1,g,x+i,y+j,z+(i+j)%n,d);
			}
		}
	}
	template<class T1,class T2>inline int put_reaction(int t,T1 a,T2 g){
		dimcnt=t;
		int n=1;
		for(int i=1;i<=t;i++){
			n*=dim[i]=a[i];
		}
		dfs(1,g,1,1,1,n);
		return n;
	}
}
namespace gmath{
	int pri[N],ps=0;
	bool np[N];
	int mnpw[N];
	inline void sieve(int n){
		memset(np,0,sizeof(np));
		mnpw[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				mnpw[i]=i;
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				if(i%p){
					mnpw[t]=p;
				}else{
					mnpw[t]=mnpw[i]*p;
					break;
				}
			}
		}
	}
	int gcd[N][N],inv[N][N];
	inline void Main(int n){
		sieve(n);
		for(int i=1;i<=n;i++){
			gcd[i][0]=i,inv[i][0]=0;
			for(int j=1;j<i;j++){
				int r=i%j,d=gcd[j][r];
				int y2=inv[j][r],x2=(d-r*y2)/j;
				gcd[i][j]=gcd[j][i]=d;
				inv[i][j]=((x2-i/j*y2)%i+i)%(i/d);
			}
			gcd[i][i]=i,inv[i][i]=0;
		}
	}
}
namespace lb{
	const int logN=20;
	int g[N][N],pw[N][N];
	int vec[N][logN],hb[N];
	int md[logN],bs[logN],dim=0;
	int curans;
	inline void reset(){
		curans=1;
		fill(bs+1,bs+dim+1,1);
	}
	int rdu[N],cno[N];
	inline void init(int n){
		for(int i=2;i<=n;i++){
			int m=md[hb[i]],v=vec[i][hb[i]];
			rdu[i]=pw[i][m/gmath::gcd[m][v]];
			cno[i]=pw[i][gmath::inv[m][v]];
		}
	}
	bool ins(int e){
		assert(e);
		using gmath::gcd;
		bool flag=false;
		while(e!=1){
			int x=hb[e],v=vec[e][x],b=bs[x];
			if(vec[b][x]>gcd[md[x]][v]){
				curans*=vec[b][x]/gcd[md[x]][v];
				ins(rdu[e]),e=cno[e];
				swap(bs[x],e);
				flag=true;
			}else{
				e=g[e][pw[b][(md[x]-v)/vec[b][x]]];
			}
		}
		return flag;
	}
}
struct Query{
	int l,r,id;
	inline friend bool operator < (const Query &a,const Query &b){
		return a.l!=b.l?a.l<b.l:a.r>b.r;
	}
}qry[M];
int a[M],nxt[M],ans[M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("chemistry.in","r",stdin);
	freopen("chemistry.out","w",stdout);
#endif
	int t=ni,m=ni,q=ni;
	for(int i=1;i<=t;i++){
		a[i]=ni;
	}
	int n=LIB::put_reaction(t,a,lb::g);
	gmath::Main(n);
	{//init lb
		using namespace lb;
		using gmath::mnpw;
		for(int i=t;i>=1;i--){
			for(int x=a[i];x!=1;x/=mnpw[x]){
				md[++dim]=mnpw[x];
			}
		}
		for(int i=1;i<=n;i++){
			int num=i-1,pt=0;
			for(int j=t;j>=1;j--){
				int cmd=num%a[j];
				num/=a[j];
				for(int x=a[j];x!=1;x/=mnpw[x]){
					vec[i][++pt]=cmd%mnpw[x];
				}
			}
			pw[i][0]=1;
			for(int j=1;pw[i][j]=g[i][pw[i][j-1]],pw[i][j]!=1;j++);
			for(int &j=hb[i]=dim;j>=1&&vec[i][j]==0;j--);
		}
		for(int i=1;i<=dim;i++){
			vec[1][i]=md[i];
		}
		lb::init(n);
	}
	nxt[0]=1;
	for(int i=1;i<=m;i++){
		a[i]=ni;
		nxt[i]=i+1;
	}
	for(int i=1;i<=q;i++){
		qry[i]=(Query){ni,ni,i};
	}
	sort(qry+1,qry+q+1);
	for(int i=q;i>=1;){
		lb::reset();
		for(int ti=qry[i].l,*pt=nxt+ti-1;qry[i].l==ti;i--){
			for(;lb::curans<n&&*pt<=qry[i].r;lb::ins(a[*pt])?*(pt=nxt+*pt):(*pt=nxt[*pt]));
			ans[qry[i].id]=lb::curans;
		}
	}
	for(int i=1;i<=q;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
