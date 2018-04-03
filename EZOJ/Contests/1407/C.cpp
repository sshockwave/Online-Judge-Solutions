#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cmath>
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
const int N=20010,D=5,X=10010;
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
inline Pt work(int n){
	Pt pos;
	for(int i=0;i<dim;i++){
		pos.a[i]=rand()%X;
	}
	for(db step=1;step>1e-6;step*=0.9){
		Pt vec;
		int cnt=0;
		db mxv=0;
		for(int i=1;i<=n;i++){
			Pt dt=pt[i]-pos;
			db cur=dt.d2();
			if(cur>mxv+1e-6){
				vec=dt,cnt=1,mxv=cur;
			}else if(cur>=mxv-1e-6){
				vec=vec+dt,cnt++;
			}
		}
		for(int i=0;i<dim;i++){
			vec.a[i]=vec.a[i]/cnt*step;
		}
		pos=pos+vec;
	}
	return pos;
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
	Pt ans;
	db tval=1e100;
	for(int tot=3;tot--;){
		Pt cur=work(n);
		db cval=0;
		for(int i=1;i<=n;i++){
			apmax(cval,sqrt((pt[i]-cur).d2()));
		}
		if(cval<tval){
			ans=cur,tval=cval;
		}
	}
	for(int i=0;i<dim;i++){
		printf("%.10lf ",ans.a[i]);
	}
	putchar('\n');
	return 0;
}
