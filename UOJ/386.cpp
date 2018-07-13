#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=200010;
inline lint getv(lint x,int e){
	if(e==1)return x;
	if(e==2)return x*x;
	assert(false);
}
struct Item{
	int s,v;
}a[N];
inline bool s_cmp(const Item &a,const Item &b){
	return a.s<b.s;
}
int nx[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("pigeon.in","r",stdin);
	freopen("pigeon.out","w",stdout);
#endif
	const int n=ni,m=ni,es=ni,ev=ni;
	for(int i=1;i<=n;i++){
		a[i]=(Item){ni,ni};
	}
	sort(a+1,a+n+1,s_cmp);
	lint ans=0;
	for(int i=0;i<=n;i++){
		nx[i]=i+1;
	}
	for(int i=n;i>=1;i--){
		priority_queue<int,vector<int>,greater<int> >q;
		lint sum=0;
		int *pt=nx+i-1;
		for(int j=i;j<=n;pt=nx+j,j=*pt){
			if(q.size()==(size_t)m){
				if(a[j].v<=q.top()){
					*pt=nx[j];
					continue;
				}else if(q.top()==a[i].v)break;
				else{
					sum-=q.top(),q.pop();
				}
			}
			q.push(a[j].v),sum+=a[j].v;
			apmax(ans,getv(sum,ev)-getv(a[j].s-a[i].s,es));
		}
	}
	printf("%lld\n",ans);
	return 0;
}
