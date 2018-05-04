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
const int N=200010;
int sg[N];
int a[N];
int vis[N],tim=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("right.in","r",stdin);
	freopen("right.out","w",stdout);
#endif
	int n=ni,q=ni,p=ni;
	sg[0]=0;
	for(int i=1;i<=200000;i++){
		tim++;
		for(lint j=1;j<=i;j*=p){
			vis[sg[i-j]]=tim;
		}
		for(int &j=sg[i]=0;vis[j]==tim;j++);
	}
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	while(q--){
		int tp=ni;
		if(tp==0){
			int l=ni,r=ni,x=ni;
			for(int i=l;i<=r;i++){
				a[i]+=x;
			}
		}else{
			int l=ni,r=ni;
			int t=0;
			for(int i=l;i<=r;i++){
				t^=sg[a[i]];
			}
			putchar('0'+(t!=0));
			putchar('\n');
		}
	}
	return 0;
}
