#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline int abs(int a){
	return a>0?a:-a;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=100010,M=110;
int a[N],b[N],mx=0,absmx=0;
inline void input(int n,int *num){
	for(int i=1;i<=n;i++){
		scanf("%d",num+i);
		apmax(mx,num[i]);
		apmax(absmx,abs(num[i]));
	}
}
int f[N],nxta[N],nxtb[N],nxtab[N];
inline int paint(int n,long long mx){
	long long suma=a[1],sumb=b[1],sumab=a[1]+b[1];
	for(int i=1;i<=n;i++){
		for(nxta[i]=nxta[i-1];nxta[i]<=n&&suma<=mx;nxta[i]++,suma+=a[nxta[i]]);
		for(nxtb[i]=nxtb[i-1];nxtb[i]<=n&&sumb<=mx;nxtb[i]++,sumb+=a[nxtb[i]]);
		for(nxtab[i]=nxtab[i-1];nxtab[i]<=n&&sumab<=mx;nxtab[i]++,sumab+=a[nxtab[i]]+b[nxtab[i]]);
		suma-=a[i],sumb-=b[i],sumab-=a[i]+b[i];
	}
	memset(f,127,sizeof(f));
	f[0]=0;
	for(int i=0;i<n;i++){
		apmin(f[nxtab[i]-1],f[i]+1);
		for(int ca=1,cb=1,pa=nxta[i+1],pb=nxtb[i+1];pa<=n||pb<=n;){
			if(pa<pb){
				apmin(f[pa-1],f[i]+ca+cb);
				ca++,pa=nxta[pa];
			}else{
				apmin(f[pb-1],f[i]+ca+cb);
				cb++,pb=nxtb[pb];
			}
		}
	}
	return f[n];
}
int main(){
	freopen("A.in","r",stdin);
	int n=ni(),m=ni();
	nxta[0]=nxtb[0]=nxtab[0]=1;
	input(n,a),input(n,b);
	long long l=mx,r=absmx*n,mid;
	while(l<r){
		mid=(l+r)>>1;
		cout<<"("<<l<<","<<mid<<","<<r<<")"<<endl;
		if(paint(n,mid)>m){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	printf("%lld",l);
}
