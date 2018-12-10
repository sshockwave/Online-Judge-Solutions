#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
#define cout cerr
#define ni (next_num<int>())
using namespace std;
typedef double db;
typedef long long lint;
template<class T>inline T next_num(){
	T i=0;char c;
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=10;
bool mat[N][N];
db val[N][N],pval[N];
int n;
inline db rnd(){
	return (db)rand()/RAND_MAX;
}
inline void calc3(db a1,db b1,db c1,db a2,db b2,db c2,db &x,db &y){
	x=(b2*c1-b1*c2)/(a1*b2-a2*b1);
	y=(a1*c2-a2*c1)/(a1*b2-a2*b1);
}
inline db calc2(db a,db p,db b,db q,db c){
	db ta,tb;
	calc3(p*p,-p,a-b,q*q,q,c-b,ta,tb);
	return b-tb*tb/(ta*4);
}
inline bool calc(){
	vector<db>lst;
	for(int i=1;i<=n;i++){
		pval[i]=rnd();
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(mat[i][j]){
				val[i][j]=val[j][i]=rnd()+1;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(!mat[i][j])continue;
			for(int k=1;k<=n;k++){
				if(k==i||k==j||!mat[j][k])continue;
				lst.push_back(calc2(pval[i],val[i][j],pval[j],val[j][k],pval[k]));
			}
		}
	}
	if(lst.size()==0)return false;
	sort(lst.begin(),lst.end());
	return lst[lst.size()-(lst.size()+1)/2]>0.618;
}
inline db Main(){
	n=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			mat[i][j]=ni;
		}
	}
	int trycnt=1000,succnt=0;
	for(int i=1;i<=trycnt;i++){
		succnt+=calc();
	}
	return (db)succnt/trycnt;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("gamma.in","r",stdin);
	freopen("gamma.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%.6lf\n",Main()));
	return 0;
}
