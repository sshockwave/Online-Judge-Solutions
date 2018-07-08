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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=20;
int anslen=0;
bool stk[N+2];
int ss=0;
namespace T{
	const int N=1<<23;
	int f[N];
	inline void init(const int n){
		mset(f,0,1<<(n+1));
	}
	inline void ins(int s,int i){
		for(int x=1;;x=(x<<1)|((s>>--i)&1)){
			++f[x];
			if(i==0)break;
		}
	}
	int tmp_f[N];
	void dfs_store(const int x){
		tmp_f[x]=f[x];
		if(f[x]==0)return;
		dfs_store(x<<1);
		dfs_store((x<<1)|1);
	}
	void dfs_mg(const int x,const int v){
		if(tmp_f[v]==0)return;
		f[x]+=tmp_f[v];
		dfs_mg(x<<1,v<<1);
		dfs_mg((x<<1)|1,(v<<1)|1);
	}
	void solve(const int x){
		if(f[x]==0)return;
		const int lson=x<<1,rson=lson|1;
		solve(lson),solve(rson);
		dfs_store((lson<<1)|1),dfs_store(rson<<1);
		dfs_mg(lson,rson<<1),dfs_mg(rson,(lson<<1)|1);
	}
	void findans(const int x,const int dep,const int k){
		if(f[x]<k)return;
		apmax(anslen,dep);
		findans(x<<1,dep+1,k);
		findans((x<<1)|1,dep+1,k);
	}
	bool putans(const int x,const int k){
		if(f[x]<k)return false;
		if(ss==anslen)return true;
		ss++;
		stk[ss]=0;
		if(putans(x<<1,k))return true;
		stk[ss]=1;
		if(putans((x<<1)|1,k))return true;
		ss--;
		return false;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("simple.in","r",stdin);
	freopen("simple.out","w",stdout);
#endif
	const int n=ni;
	T::init(n);
	const int k=ni;
	for(int i=0;i<=n;i++){
		static char str[(1<<N)+10];
		scanf("%s",str);
		for(int s=0,ts=1<<i;s<ts;s++){
			if(str[s]=='1'){
				T::ins(s,i);
			}
		}
	}
	T::solve(1);
	T::findans(1,0,k);
	T::putans(1,k);
	for(int i=1;i<=ss;i++){
		putchar('0'+stk[i]);
	}
	putchar('\n');
	return 0;
}
