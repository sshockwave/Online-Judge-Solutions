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
	neg&&(c=getchar());
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=5000010;
char s[N],t[N];
int ext_s[N],ext_t[N];
inline void ext_kmp(int n,int m){
	//work on s first
	ext_s[0]=0;
	ext_s[1]=n;
	for(int i=2,p=0;i<=n;i++){
		if(i<p+ext_s[p]){
			ext_s[i]=min(ext_s[i-p+1],p+ext_s[p]-i);
		}else{
			ext_s[i]=0;
		}
		for(int &j=ext_s[i];j<n&&s[i+j]==s[j+1];j++);
		if(i+ext_s[i]>p+ext_s[p]){
			p=i;
		}
	}
	for(int i=1,p=0;i<=m;i++){
		if(i<p+ext_t[p]){
			ext_t[i]=min(ext_s[i-p+1],p+ext_t[p]-i);
		}else{
			ext_t[i]=0;
		}
		for(int &j=ext_t[i];j<n&&t[i+j]==s[j+1];j++);
		if(i+ext_t[i]>p+ext_t[p]){
			p=i;
		}
	}
}
int * const ext=ext_t;
int pre[N],nxt[N];
int cnt[N],lst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("stamp.in","r",stdin);
	freopen("stamp.out","w",stdout);
#endif
	int m=ni,n=ni;
	scanf("%s%s",t+1,s+1);
	ext_kmp(n,m);
	mset(cnt+1,0,n);
	for(int i=1;i<=m;i++){
		if(i+ext[i]>m){
			ext[i]=n;
		}
		++cnt[ext[i]];
	}
	for(int i=1;i<=n;i++){
		cnt[i]+=cnt[i-1];
	}
	for(int i=1;i<=m;i++){
		lst[cnt[ext[i]]--]=i;
	}
	nxt[0]=1,pre[n+1]=m;
	for(int i=1;i<=m;i++){
		pre[i]=i-1,nxt[i]=i+1;
	}
	int ans=0;
	for(int i=1,j=1,gap=1;i<=n;i++){
		for(;j<=m&&ext[lst[j]]<i;j++){
			int x=lst[j];
			pre[nxt[x]]=pre[x],nxt[pre[x]]=nxt[x];
			apmax(gap,nxt[x]-pre[x]);
		}
		if(nxt[0]!=1)break;
		ans+=gap<=i;
	}
	printf("%d\n",ans);
	return 0;
}
