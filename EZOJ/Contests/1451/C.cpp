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
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=32010,INF=0x7f7f7f7f;
vi opx,opy;
int a[N];
inline void psh(const int l,const int r){
	if(l==r)return;
	static int cnt=4000000;
	cnt-=r-l+1;
	assert(cnt>=0);
	opx.push_back(l),opy.push_back(r);
	reverse(a+l,a+r+1);
}
void solve2(int l,int r,int v){
	if(l==r)return;
	const int m=(l+r)>>1;
	solve2(l,m,v),solve2(m+1,r,v);
	int tl=l,tr=r;
	for(;tl<=tr&&a[tl]<=v;tl++);
	for(;tl<=tr&&a[tr]>v;tr--);
	if(tl<=tr){
		psh(tl,tr);
	}
}
int lst[N];
void solve(int l,int r){
	if(l==r)return;
	memcpy(lst+l,a+l,(r-l+1)*sizeof(a[0]));
	sort(lst+l,lst+r+1);
	if(lst[l]==lst[r])return;
	int p=0;
	const int m=(r+l)>>1;
	for(int i=l;i<r;i++){
		if(lst[i]!=lst[i+1]){
			if(p==0||cabs(i-m)<cabs(p-m)){
				p=i;
			}
		}
	}
	assert(p);
	solve2(l,r,lst[p]);
	solve(l,p),solve(p+1,r);
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
	solve(1,n);
	printf("%d\n",(int)opx.size());
	for(int i=0,tot=opx.size();i<tot;i++){
		printf("%d %d\n",opx[i],opy[i]);
	}
	return 0;
}
