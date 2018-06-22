#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef vector<int>vi;
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
const int N=32010,INF=0x7f7f7f7f;
vi opx,opy;
int a[N];
inline void psh(const int l,const int r){
	if(l==r)return;
	static int cnt=4000000;
	if(cnt<r-l+1)throw "Not enough operations";
	cnt-=r-l+1;
	opx.push_back(l),opy.push_back(r);
	reverse(a+l,a+r+1);
}
void solve(int l,int r);
void solve2(int l,int r){
	if(l==r)return;
	int mx=0;
	for(int i=l;i<=r;i++){
		apmax(mx,a[i]);
	}
	int i=r;
	for(;a[i]!=mx;i--);
	psh(i,r);
	solve(l,r);
}
int mn_[N];
void solve(int l,int r){
	if(l==r)return;
	int mn=INF;
	for(int i=r;i>=l;i--){
		mn_[i]=mn=min(a[i],mn);
	}
	int mx=0;
	for(int i=l;i<r;i++){
		apmax(mx,a[i]);
		if(mx<=mn_[i+1]){
			solve2(l,i);
			l=i+1;
		}
	}
	solve2(l,r);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("rev.in","r",stdin);
	freopen("rev.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	try{
		solve(1,n);
	}catch(const char* str){
		//cout<<str<<endl;
	}
	printf("%d\n",(int)opx.size());
	for(int i=0,tot=opx.size();i<tot;i++){
		printf("%d %d\n",opx[i],opy[i]);
	}
	return 0;
}
