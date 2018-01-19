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
const int N=1000010,INF=0x7f7f7f7f;
struct Intv{
	int l,r,len;
	inline friend bool operator < (const Intv &a,const Intv &b){
		return a.len<b.len;
	}
}ints[N];
namespace brute1{
	int n,k;
	lint ans=0;
	int col[N];
	void dfs(int x){
		if(x>n){
			lint sum=0;
			for(int i=1;i<=k;i++){
				int l=-INF,r=INF;
				for(int j=1;j<=n;j++){
					if(col[j]==i){
						apmax(l,ints[j].l);
						apmin(r,ints[j].r);
					}
				}
				if(l<r&&r<INF){
					sum+=r-l;
				}
			}
			apmax(ans,sum);
			return;
		}
		for(int &i=col[x]=1;i<=k;i++){
			dfs(x+1);
		}
	}
	inline lint Main(){
		dfs(1);
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("dagon.in","r",stdin);
	freopen("dagon.out","w",stdout);
#endif
	int n=ni,k=ni;
	for(int i=1;i<=n;i++){
		ints[i]=(Intv){ni,ni};
		ints[i].len=ints[i].r-ints[i].l;
	}
	if(k==n){
		lint sum=0;
		for(int i=1;i<=n;i++){
			sum+=ints[i].len;
		}
		printf("%lld\n",sum);
		return 0;
	}
	if(n<=8){
		brute1::n=n,brute1::k=k;
		printf("%lld\n",brute1::Main());
		return 0;
	}
	sort(ints+1,ints+n+1);
	lint ans=0;
	for(int i=n,ti=n-k+1;i>ti;i--){
		ans+=ints[i].len;
	}
	int l=-INF,r=INF;
	for(int i=1,ti=n-k+1;i<=ti;i++){
		apmax(l,ints[i].l);
		apmin(r,ints[i].r);
	}
	if(l<r&&r<INF){
		ans+=r-l;
	}
	printf("%lld\n",ans);
	return 0;
}
