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
const int N=100010,M=110,INF=0x7f7f7f7f;
int a[N],b[N];
long long _a[N],_b[N],_ab[N];
inline void input(int n,int *num,long long *pre,int &mx){
	num[0]=pre[0]=0;
	for(int i=1;i<=n;i++){
		num[i]=ni();
		apmax(mx,num[i]);
		pre[i]=pre[i-1]+num[i];
	}
}
int f[N],jmpa[N],jmpb[N],jmpab[N];
inline int paint(int n,int mx,int steps){
	for(int i=1;i<=n;i++){
		for(jmpa[i]=jmpa[i-1];_a[i]-_a[jmpa[i]]>mx;jmpa[i]++);
		for(jmpb[i]=jmpb[i-1];_b[i]-_b[jmpb[i]]>mx;jmpb[i]++);
		for(jmpab[i]=jmpab[i-1];_ab[i]-_ab[jmpab[i]]>mx;jmpab[i]++);
		f[i]=(i==jmpab[i]?INF:(f[jmpab[i]]+1));
		for(int j=1,pa=i,pb=i;j<=steps&&(pa||pb);j++){
			if(pa&&jmpa[pa]>=jmpb[pb]){
				pa=jmpa[pa];
			}else{
				pb=jmpb[pb];
			}
			apmin(f[i],f[max(pa,pb)]+j+(pa!=pb));
		}
	}
	return f[n];
}
int main(){
	freopen("A.in","r",stdin);
	int n=ni(),m=ni(),mx=0;
	long long sum=0;
	input(n,a,_a,mx),input(n,b,_b,mx);
	f[0]=_ab[0]=jmpa[0]=jmpb[0]=jmpab[0]=0;
	for(int i=1;i<=n;i++){
		_ab[i]=_a[i]+_b[i];
	}
	long long l=mx,r=_ab[n],mid;
	while(l<r){
		mid=(l+r)>>1;
		if(paint(n,mid,m)>m){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	printf("%lld",l);
}
