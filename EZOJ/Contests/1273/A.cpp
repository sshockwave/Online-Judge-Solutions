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
inline int abs(int a){
	return a>0?a:-a;
}
const int N=100010,M=110,INF=0x7f7f7f7f;
long long a[N],b[N],c[N];
inline void input(int n,long long *num,int &mx){
	num[0]=0;
	for(int i=1;i<=n;i++){
		num[i]=ni();
		apmax(mx,num[i]);
	}
}
int f[N],jmpa[N],jmpb[N],jmpc[N];
inline int paint(int n,int mx,int steps){
	for(int i=1;i<=n;i++){
		#define getjmp(x,jmpx) for(jmpx[i]=jmpx[i-1];x[i]-x[jmpx[i]]>mx;jmpx[i]++)
		getjmp(a,jmpa);getjmp(b,jmpb);getjmp(c,jmpc);
		f[i]=(i==jmpc[i]?INF:(f[jmpc[i]]+1));
		for(int j=1,pa=i,pb=i;j<=steps;j++){
			if(pa>pb){
				pa=jmpa[pa];
			}else{
				pb=jmpb[pb];
			}
			apmin(f[i],f[max(pa,pb)]+j);
			if(pa==pb){
				break;
			}
		}
		if(f[i]>steps){
			return false;
		}
	}
	return f[n]<=steps;
}
int main(){
	int n=ni(),m=ni(),mx=0;
	long long sum=0;
	input(n,a,mx),input(n,b,mx);
	f[0]=a[0]=b[0]=c[0]=jmpa[0]=jmpb[0]=jmpc[0]=0;
	for(int i=1;i<=n;i++){
		a[i]+=a[i-1];
		b[i]+=b[i-1];
		c[i]=a[i]+b[i];
	}
	long long l=mx,r=c[n],mid;
	while(l<r){
		mid=(l+r)>>1;
		if(paint(n,mid,m)){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	printf("%lld",l);
}
