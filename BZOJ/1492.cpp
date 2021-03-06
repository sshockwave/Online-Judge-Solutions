#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=100010;
double a[N],b[N],rate[N],f[N];
int main(){
	int n=ni,s=ni;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",a+i,b+i,rate+i);
	}
	f[1]=s*rate[1]/(a[1]*rate[1]+b[1]);
	double ans=s;
	for(int i=2;i<=n;i++){
		for(int j=1;j<i;j++){
			apmax(ans,f[j]*a[i]+f[j]*b[i]/rate[j]);
		}
		f[i]=ans*rate[i]/(a[i]*rate[i]+b[i]);
	}
	printf("%.3lf\n",ans);
}
