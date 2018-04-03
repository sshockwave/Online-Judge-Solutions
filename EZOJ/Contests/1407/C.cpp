#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;
typedef double db;
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
const int N=20010,D=8,X=10010;
const db EPS=1e-7;
inline int sgn(db x){
	return x>EPS?1:x<EPS?-1:0;
}
int dim;
struct Pt{
	db a[D];
	inline db d2(){
		db b=0;
		for(int i=0;i<dim;i++){
			b+=a[i]*a[i];
		}
		return b;
	}
	inline friend Pt operator + (const Pt &a,const Pt &b){
		Pt c;
		for(int i=0;i<dim;i++){
			c.a[i]=a.a[i]+b.a[i];
		}
		return c;
	}
	inline friend Pt operator - (const Pt &a,const Pt &b){
		Pt c;
		for(int i=0;i<dim;i++){
			c.a[i]=a.a[i]-b.a[i];
		}
		return c;
	}
	inline friend ostream & operator << (ostream & out,const Pt &p){
		out<<"("<<p.a[0];
		for(int i=1;i<dim;i++){
			out<<","<<p.a[i];
		}
		out<<")";
		return out;
	}
}pt[N];
struct Circ{
	Pt o;
	db r;
	inline bool has(const Pt &x){
		return (x-o).d2()<r*r+EPS;
	}
};
namespace gcen{
	db eqn[D][D];
	inline void gauss(int n){
		for(int i=1;i<=n;i++){
			int j=i;
			for(;sgn(eqn[j][i])==0;j++);
			if(j!=i){
				for(int k=i;k<=n+1;k++){
					swap(eqn[i][k],eqn[j][k]);
				}
			}
			db r=1/eqn[i][i];
			for(int k=i;k<=n+1;k++){
				eqn[i][k]*=r;
			}
			for(j=i+1;j<=n;j++){
				if(sgn(eqn[j][i])==0)continue;
				db r=eqn[j][i];
				for(int k=i;k<=n+1;k++){
					eqn[j][k]-=r*eqn[i][k];
				}
			}
		}
		for(int i=n;i>=1;i--){
			for(int j=i-1;j>=1;j--){
				if(sgn(eqn[j][i])){
					db r=eqn[j][i];
					eqn[j][i]=0,eqn[j][n+1]-=r*eqn[i][n+1];
				}
			}
		}
	}
	Pt lst[D],vec[D];
	int n;
	inline void putvec(db eqn[],int d,db mul){
		eqn[n+1]+=mul*lst[n].a[d];
		for(int i=1;i<n;i++){
			eqn[i]+=vec[i].a[d]*mul;
		}
	}
	inline Circ main(const set<int>&s){
		if(s.empty()){
			Circ ans;
			for(int i=0;i<dim;i++){
				ans.o.a[i]=0;
			}
			ans.r=0;
			return ans;
		}
		n=0;
		for(set<int>::const_iterator it=s.begin();it!=s.end();it++){
			lst[++n]=pt[*it];
		}
		for(int i=1;i<n;i++){
			vec[i]=lst[i]-lst[n];
		}
		for(int i=1;i<=n;i++){//for lst[i]
			for(int j=1;j<n;j++){
				eqn[i][j]=0;
			}
			eqn[i][n]=1,eqn[i][n+1]=-lst[i].d2();
			for(int j=0;j<dim;j++){
				putvec(eqn[i],j,lst[i].a[j]*2);
			}
		}
		gauss(n);
		Circ ans;
		ans.o=lst[n];
		for(int i=1;i<n;i++){
			db v=-eqn[i][n+1];
			for(int j=0;j<dim;j++){
				ans.o.a[j]+=vec[i].a[j]*v;
			}
		}
		ans.r=sqrt((ans.o-lst[1]).d2());
		return ans;
	}
}
set<int>s;
Circ ria(int n){
	Circ ans=gcen::main(s);
	for(int i=1;i<=n;i++){
		if(ans.has(pt[i]))continue;
		s.insert(i);
		ans=ria(i-1);
		s.erase(i);
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("burn.in","r",stdin);
	freopen("burn.out","w",stdout);
#endif
	int n=ni;
	dim=ni;
	for(int i=1;i<=n;i++){
		for(int j=0;j<dim;j++){
			scanf("%lf",pt[i].a+j);
		}
	}
	random_shuffle(pt+1,pt+n+1);
	Circ ans=ria(n);
	for(int i=0;i<dim;i++){
		printf("%.10lf ",ans.o.a[i]);
	}
	putchar('\n');
	return 0;
}
