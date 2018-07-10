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
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
const int N=1000010,INF=0x7f7f7f7f;
int a[N];
bool b[N];
int bs,cnt_mx;
inline void reset_b(){
	bs=cnt_mx=0;
}
inline void psh_b(bool x){
	b[++bs]=x;
	cnt_mx+=x;
}
inline int work_b(){
	int ans=INF;
	for(int i=0,cnt_mn=0;apmin(ans,cnt_mn+cnt_mx),++i<=bs;b[i]?--cnt_mx:++cnt_mn);
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
#endif
	const int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	lint mx_diff=0;
	int mn=a[1];
	for(int i=2;i<=n;i++){
		apmax(mx_diff,a[i]-mn);
		apmin(mn,a[i]);
	}
	assert(mx_diff>0);
	reset_b();
	mn=a[1],psh_b(0);
	int ans=0;
	for(int i=2;i<=n;i++){
		assert(a[i]<=mn+mx_diff);
		if(a[i]==mn+mx_diff){
			psh_b(1);
		}else if(a[i]==mn){
			psh_b(0);
		}else if(a[i]<mn){
			ans+=work_b();
			reset_b();
			mn=a[i],psh_b(0);
		}
	}
	ans+=work_b();
	printf("%d\n",ans);
	return 0;
}
