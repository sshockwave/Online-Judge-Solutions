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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=1000010;
template<int sat[]>inline bool sat_cmp(int a,int b){
	return sat[a]<sat[b];
}
inline lint calc(int n){
	return ((lint)n*(n+1))>>1;
}
lint f[N];
int a[N],arnk[N];
inline lint g(int i){
	return f[i]-calc(i);
}
inline bool turn_left(int i,int j,int k){
	return (g(j)-g(i))*(k-j)<=(g(k)-g(j))*(j-i);
}
void solve(int lst[],int n){
	if(n<=1)return;
	int mnrnk=arnk[lst[1]],mxrnk=mnrnk;
	for(int i=2;i<=n;i++){
		apmin(mnrnk,arnk[lst[i]]);
		apmax(mxrnk,arnk[lst[i]]);
	}
	int rnkmid=(mnrnk+mxrnk)>>1,nmid=0;
	if(mnrnk!=mxrnk){
		for(int i=1;i<=n;i++){
			nmid+=arnk[lst[i]]<=rnkmid;
		}
		int* const nlst=new int[nmid]-1;
		int td=0;
		for(int i=1;i<=n;i++){
			if(arnk[lst[i]]<=rnkmid){
				nlst[++td]=lst[i];
			}
		}
		assert(td==nmid);
		assert(nmid);
		solve(nlst,nmid);
		delete (nlst+1);
	}
	{//dp
		static int que[N];
		int qh=0,qt=0;
		for(int p=1;p<=n;p++){
			const int i=lst[p];
			for(;qh+2<=qt&&f[que[qh]]-calc(i-que[qh]-1)<f[que[qh+1]]-calc(i-que[qh+1]-1);qh++);
			if(arnk[i]>=rnkmid&&qh<qt){
				const int j=que[qh];
				apmax(f[i],a[i]+f[j]-calc(i-j-1));
			}
			if(arnk[i]<=rnkmid){
				for(;qh+2<=qt&&turn_left(que[qt-2],que[qt-1],i);qt--);
				que[qt++]=i;
			}
		}
	}
	if(mnrnk!=mxrnk){//cout get right
		assert(nmid<n);
		int* const nlst=new int[n-nmid]-1;
		int td=0;
		for(int i=1;i<=n;i++){
			if(arnk[lst[i]]>rnkmid){
				nlst[++td]=lst[i];
			}
		}
		assert(td==n-nmid);
		solve(nlst,n-nmid);
		delete (nlst+1);
	}
}
int lst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
#endif
	const int n=ni;
	f[0]=0;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		f[i]=a[i]-calc(i-1);
		lst[i]=i;
	}
	sort(lst+1,lst+n+1,sat_cmp<a>);
	for(int i=1,j=0,v=-1;i<=n;i++){
		arnk[lst[i]]=v!=a[lst[i]]?v=a[lst[i]],++j:j;
	}
	for(int i=1;i<=n;i++){
		lst[i]=i;
	}
	solve(lst,n);
	lint ans=-calc(n);
	for(int i=1;i<=n;i++){
		apmax(ans,f[i]-calc(n-i));
	}
	printf("%lld\n",ans);
	return 0;
}
