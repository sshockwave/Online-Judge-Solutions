#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <vector>
#include <set>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(a));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(a));}
const int N=1010;
typedef vector<int>vi;
vi vec[N];
int cnt[N];
int n=0;
inline void addn(int u){
	++n;
	++cnt[u];
	vec[n].push_back(u);
}
inline void addn(int u,int v){
	++n;
	++cnt[u];
	vec[n].push_back(u);
	vec[n].push_back(v);
}
inline void addn(int u,int v,int w){
	++n;
	++cnt[u];
	vec[n].push_back(u);
	vec[n].push_back(v);
	vec[n].push_back(w);
}
inline void output(){
	int m=0;
	for(int i=1;i<=n;i++){
		for(int j=0;j<(int)vec[i].size();j++){
			apmax(m,vec[i][j]);
		}
	}
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++){
		printf("%d",(int)vec[i].size());
		for(int j=0;j<(int)vec[i].size();j++){
			printf(" %d",vec[i][j]);
		}
		putchar('\n');
	}
}
int tcnt[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int m=41;
	for(int i=m;i>1;i--){
		tcnt[i]=4+m-i;
	}
	tcnt[1]=tcnt[3];
	for(int i=1,j=m;i<j;i++,j--){
		for(int k=i+1;k<j;k++){
			addn(i,k,j);
		}
		addn(i,j);
		addn(i,j);
		addn(i,j);
		if(i+1<j){
			addn(i+1,j);
			addn(i+1,j);
		}
	}
	for(int i=1;i<=m;i++){
		assert(cnt[i]<=tcnt[i]);
		for(;cnt[i]<tcnt[i];addn(i));
	}
	output();
	return 0;
}
