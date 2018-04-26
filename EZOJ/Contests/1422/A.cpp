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
const int N=5010;
int ext[N];//to upper left
int ver[N];
int nxt[N];
int gnxt(int i,int r){
	if(i==r)return i;
	if(nxt[i]==i&&i+ver[i]-1<r){
		nxt[i]=i+1;
	}
	return nxt[i]!=i?nxt[i]=gnxt(nxt[i],r):i;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
#endif
	int n=ni;
	mset(ext+1,0,n);
	mset(ver+1,0,n);
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			nxt[j]=j;
		}
		for(int j=i;j>=1;j--){
			ext[j]=ext[j-1];
		}
		int las=0;
		for(int j=1;j<=i;j++){
			char c;
			while(!isdigit(c=getchar()));
			bool mat=c=='0';
			ext[j]=mat?ext[j]+1:0;
			ver[j]=mat?ver[j]+1:0;
			if(mat){
				apmax(ans,j-gnxt(max(j-ext[j]+1,las+1),j)+1);
			}else{
				las=j;
			}
		}
	}
	printf("%d\n",(ans*(ans+1))>>1);
	return 0;
}
