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
const int N=100010,INF=0x7f7f7f7f;
namespace B{
	lint c[N];
	int n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)*sizeof(c[0]));
	}
	inline void add(int x,lint v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline lint sum(int x){
		lint ans=0;
		for(;x;ans+=c[x],x^=x&-x);
		return ans;
	}
	inline lint ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}
int a[N],n,k;
inline lint calc(int x){
	lint ans=0;
	int atk=a[x];
	for(int l=x-1,r=x+1;1<=l||r<=n;){
		for(;l>=1&&atk>=a[l];l--);
		for(;r<=n&&atk>=a[r];r++);
		atk=INF;
		if(l>=1){
			apmin(atk,a[l]);
		}
		if(r<=n){
			apmin(atk,a[r]);
		}
		if(atk==INF)break;
		ans+=k;
	}
	return ans;
}
lint ans[N];
int pre[N],nxt[N];
inline void intvadd(int l,int r,lint v){
	if(l>r)return;
	ans[l]+=v,ans[r+1]-=v;
}
int samcnt[N];
int lstl[N],lsl;
int lstr[N],lsr;
void solve(int l,int r){
	if(l==r)return;
	int m=(l+r)>>1;
	solve(l,m),solve(m+1,r);
	int lsl=0,lsr=0;
	for(int j=m;j>=l;j=pre[j]){
		lstl[lsl++]=j;
	}
	for(int j=m+1;j<=r;j=nxt[j]){
		lstr[lsr++]=j;
	}
	int last=0;
	for(int i=lsl-1,j=lsr-1;j>=0;j--){
		for(;i>=0&&a[lstl[i]]>a[lstr[j]];i--);
		samcnt[lstr[j]]=last+=i>=0&&a[lstl[i]]==a[lstr[j]];
	}
	last=0;
	for(int i=lsl-1,j=lsr-1;i>=0;i--){
		for(;j>=0&&a[lstr[j]]>a[lstl[i]];j--);
		samcnt[lstl[i]]=last+=j>=0&&a[lstl[i]]==a[lstr[j]];
	}
	for(int i=0,j=0;i<lsl;i++){
		last=j;
		for(;j<lsr&&a[lstr[j]]<a[lstl[i]];j++);
		intvadd(lstr[last],j<lsr?lstr[j]-1:r,(lint)(lsl-i-samcnt[lstl[i]])*k);
		if(j==lsr)break;
	}
	for(int i=0,j=0;j<lsr;j++){
		last=i;
		for(;i<lsl&&a[lstl[i]]<a[lstr[j]];i++);
		intvadd(i<lsl?lstl[i]+1:l,lstl[last],(lint)(lsr-j-samcnt[lstr[j]])*k);
		if(i==lsl)break;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("attack.in","r",stdin);
	freopen("attack.out","w",stdout);
#endif
	n=ni,k=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	for(int i=1;i<=n;i++){
		for(int &j=pre[i]=i-1;j>0&&a[j]<=a[i];j=pre[j]);
	}
	for(int i=n;i>=1;i--){
		for(int &j=nxt[i]=i+1;j<=n&&a[j]<=a[i];j=nxt[j]);
	}
	memset(ans,0,sizeof(ans));
	solve(1,n);
	B::init(n);
	lint sum=0;
	for(int i=1;i<=n;i++){
		sum=ans[i]+=ans[i-1];
		B::add(i,sum);
	}
	for(int op;scanf("%d",&op)!=EOF;){
		if(op==1){
			int x=ni;
			B::add(x,-ans[x]),B::add(x+1,-ans[x+1]);
			swap(a[x],a[x+1]);
			ans[x]=calc(x),ans[x+1]=calc(x+1);
			B::add(x,ans[x]),B::add(x+1,ans[x+1]);
		}else{
			int l=ni,r=ni;
			printf("%lld\n",B::ask(l,r)+(lint)(r-l+1)*(n-1));
		}
	}
	return 0;
}
