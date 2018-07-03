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
const int N=2000010;
inline void getnum(bool a[],int n){
	static char str[N];
	scanf("%s",str);
	for(int i=0;i<n;i++){
		a[n-i-1]=str[i]-'0';
	}
}
inline void putnum(bool a[],int n){
	bool fir=true;
	for(int i=n-1;i>=0;i--){
		if(a[i]||!fir){
			putchar('0'+a[i]);
			fir=false;
		}
	}
	if(fir){
		putchar('0');
	}
	putchar('\n');
}
bool a[N],b[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("add.in","r",stdin);
	freopen("add.out","w",stdout);
#endif
	int n,k;
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	{
		int tn=ni,tm=ni;
		n=max(tn,tm);
		k=ni;
		getnum(a,tn);
		getnum(b,tm);
	}
	for(int i=n-1;i>=0;i--){
		for(int j=i,tt=k;tt--&&a[j]&&b[j];){
			a[j]=b[j]=0;
			++j;
			assert(!a[j]||!b[j]);
			if(a[j]){
				b[j]=1;
				for(;a[j];j++){
					a[j]=0;
				}
				a[j]=1;
			}else if(b[j]){
				a[j]=1;
				for(;b[j];j++){
					b[j]=0;
				}
				b[j]=1;
			}else{
				a[j]=b[j]=1;
			}
		}
	}
	putnum(a,n+k);
	putnum(b,n+k);
	return 0;
}
