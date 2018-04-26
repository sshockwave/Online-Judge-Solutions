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
int pv[N];//pv::first one to be bigger than r
int gpv(int x,int mn){
	assert(x);
	if(ext[x]>=mn)return x;
	if(pv[x]==x){
		pv[x]=x-1;
	}
	return pv[x]=gpv(pv[x],mn);
}
inline bool judge(int m,int x){
	if(ext[1]<x)return false;
	int curat=1;
	while(true){
		if(curat+x>m)return true;
		int p=gpv(curat+x,x);
		if(p==curat)return false;
		curat=p;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("stamp.in","r",stdin);
	freopen("stamp.out","w",stdout);
#endif
	int m=ni,n=ni;
	scanf("%s%s",t+1,s+1);
	ext_kmp(n,m);
	for(int i=1;i<=m;i++){
		if(i+ext[i]>m){
			ext[i]=n;
		}
	}
	int cnt=0;
	for(int i=1;i<=m;i++){
		pv[i]=i;
	}
	for(int i=1;i<=n;i++){
		cnt+=judge(m,i);
	}
	printf("%d\n",cnt);
	return 0;
}
