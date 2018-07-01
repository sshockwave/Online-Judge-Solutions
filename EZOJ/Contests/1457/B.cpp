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
const int N=500010;
int n,k;
int a[N],b[N];
int __ask(int l,int r,int n){
	if(l==0)return b[r];
	if(l<=r)return b[l-1]^b[r];
	return b[r]^__ask(l,n-1,n);
}
inline int ask(int st,int len,int n){
	if(len<=n)return __ask(st,(st+len-1)%n,n);
	return b[n-1]^__ask(st,(st+len-n-1)%n,n);
}
inline void take_step(lint step){
	int g=min<lint>(n&-n,step),ng=n/g;
	step%=n;
	int tmpk=k%(ng*2);
	for(int i=0;i<g;i++){
		for(int j=0;j<ng;j++){
			b[j]=a[(i+j*step)%n];
		}
		for(int j=1;j<ng;j++){
			b[j]^=b[j-1];
		}
		for(int j=0;j<ng;j++){
			a[(i+j*step)%n]=ask(j,tmpk,ng);
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("xortwo.in","r",stdin);
	freopen("xortwo.out","w",stdout);
#endif
	n=ni,k=ni;
	lint tot=next_num<lint>();
	for(int i=0;i<n;i++){
		a[i]=ni;
	}
	for(int i=0;tot;i++){
		if((tot>>i)&1){
			tot^=1ll<<i;
			take_step(1ll<<i);
		}
	}
	for(int i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	putchar('\n');
	return 0;
}
