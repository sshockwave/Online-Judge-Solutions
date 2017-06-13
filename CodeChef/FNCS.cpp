#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=100010,RT=320;
lint a[N],fsum[RT];
int fl[N],fr[N],ctr[RT][N],n,rt=0;
struct PrefixSum{
	lint pre[N],blk[RT];
	PrefixSum(){
		memset(this,0,sizeof(PrefixSum));
	}
	inline void add(int x,lint v){
		for(int i=x;i<n&&i/rt*rt==x/rt*rt;i++){
			pre[i]+=v;
		}
		for(int i=x/rt;i*rt<n;i++){
			blk[i]+=v;
		}
	}
	inline lint sum(int x){
		return pre[x]+(x/rt?blk[x/rt-1]:0);
	}
	inline lint ask(int l,int r){
		lint ans=sum(r);
		if(l){
			ans-=sum(l-1);
		}
		return ans;
	}
}pa;
inline void add_ctr(int a[],int fl[],int fr[],int rt){
	for(int i=0;i<rt;i++){
		a[fl[i]]++,a[fr[i]+1]--;
	}
	for(int i=1;i<n;i++){
		a[i]+=a[i-1];
	}
}
inline lint f(int x){
	return pa.ask(fl[x],fr[x]);
}
inline lint _f(int x){
	lint ans=0;
	if(x/rt){
		ans=fsum[x/rt-1];
	}
	for(int i=x/rt*rt;i<=x;i++){
		ans+=f(i);
	}
	return ans;
}
int main(){
	n=ni;
	for(;rt*rt<n;rt++);
	for(int i=0;i<n;i++){
		a[i]=nl;
	}
	for(int i=0;i<n;i++){
		fl[i]=ni-1,fr[i]=ni-1;
	}
	memset(ctr,0,sizeof(ctr));
	for(int i=0;i<=(n-1)/rt;i++){
		add_ctr(ctr[i],fl+i*rt,fr+i*rt,min(rt,n-i*rt));
	}
	for(int i=0;i<n;i++){
		pa.pre[i]=i%rt?pa.pre[i-1]+a[i]:a[i];
		pa.blk[i/rt]+=a[i];
	}
	for(int i=1;i<=(n-1)/rt;i++){
		pa.blk[i]+=pa.blk[i-1];
	}
	memset(fsum,0,sizeof(fsum));
	for(int i=0;i<n;i++){
		fsum[i/rt]+=f(i);
	}
	for(int i=1;i<=(n-1)/rt;i++){
		fsum[i]+=fsum[i-1];
	}
	for(int tot=ni;tot--;){
		if(ni==1){
			int x=ni-1;
			lint y=nl-a[x];
			a[x]+=y;
			pa.add(x,y);
			lint sum=0;
			for(int i=0;i<=(n-1)/rt;i++){
				sum+=ctr[i][x];
				fsum[i]+=sum*y;
			}
		}else{
			lint l=ni-1,r=ni-1,ans=_f(r);
			if(l){
				ans-=_f(l-1);
			}
			printf("%lld\n",ans);
		}
	}
}