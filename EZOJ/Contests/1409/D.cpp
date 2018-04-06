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
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int lend[N],rend[N];
inline lint getval(int l,int r,int q){
	lint ans=0;
	for(int i=1;i<=q;i++){
		if(rend[i]<l||lend[i]>r)continue;
		if(lend[i]<=l&&rend[i]>=r){
			ans++;
		}else if(lend[i]<l){
			ans+=min(r-lend[i]+1,rend[i]-r);
		}else if(rend[i]>r){
			ans+=min(l-lend[i],rend[i]-l+1);
		}else{
			ans+=l-lend[i]+rend[i]-r;
		}
	}
	assert(ans>=0);
	return ans;
}
lint f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("ship.in","r",stdin);
	freopen("ship.out","w",stdout);
#endif
	int n=ni,q=ni;
	for(int i=1;i<=q;i++){
		lend[i]=ni,rend[i]=ni-1;
	}
	f[1]=0;
	for(int i=2;i<=n;i++){
		f[i]=LINF;
		for(int j=1;j<i;j++){
			apmin(f[i],f[j]+getval(j,i-1,q));
		}
	}
	printf("%lld\n",f[n]);
	return 0;
}
