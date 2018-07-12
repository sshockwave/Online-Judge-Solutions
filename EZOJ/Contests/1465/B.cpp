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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=500010;
int d[N],n;
lint ans1[N],ans2[N];//ans1*9+ans2
int dfs_work(int x,int g){
	if(x>=n)return 0;
	int a=dfs_work(x+g,g);
	ans1[x]+=a;
	return a+d[x];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("js.in","r",stdin);
	freopen("js.out","w",stdout);
#endif
	n=ni;
	{//gen d
		unsigned s=next_num<unsigned>();
		for(int i=n-1;i>=0;i--,s=747796405u*s-1403630843){
			d[i]=(s>>10)%10;
		}
		for(;n>1&&d[n-1]==0;n--);
	}
	mset(ans1,0,n);
	mset(ans2,0,N);
	for(int g=2;g<=n;g++){
		static int tmpa[N];
		tmpa[0]=0;
		for(int i=0;i<g;i++){
			tmpa[i]+=dfs_work(i,g);
			tmpa[i+1]=tmpa[i]/10;
			tmpa[i]%=10;
		}
		int dtop=g;
		for(int &i=dtop;tmpa[i];i++){
			tmpa[i+1]=tmpa[i]/10,tmpa[i]%=10;
		}
		for(int i=dtop-1;i>=g-1;i--){
			tmpa[i]+=tmpa[i+1]*10,tmpa[i+1]=0;
			int r=min(tmpa[i],9);
			if(r==0)continue;
			for(int j=i;j>=i-g+1;j--){
				if(tmpa[j]!=r){
					r-=tmpa[j]<r;
					break;
				}
			}
			if(r==0)continue;
			ans2[i-g+1]+=r;
			for(int j=i-g+1;j<=i;j++){
				tmpa[j]-=r;
				for(;tmpa[j]<0;--tmpa[j+1],tmpa[j]+=10);
			}
		}
	}
	for(int i=0;i<n;i++){
		ans1[i]=ans1[i]*9+ans2[i];
		ans2[i+1]+=ans1[i]/10;
		ans1[i]%=10;
	}
	int dtop=n;
	for(int &i=dtop;ans2[i];i++){
		ans1[i]=ans2[i]%10;
		ans2[i+1]+=ans2[i]/10;
	}
	for(;dtop>1&&ans1[dtop-1]==0;dtop--);
	for(int i=dtop-1;i>=0;i--){
		putchar('0'+ans1[i]);
	}
	putchar('\n');
	return 0;
}
