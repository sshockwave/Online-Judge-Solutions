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
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=30010,H=35;
const double EPS=1e-10;
double f[N][H],pw2[H];
char s[10];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sky.in","r",stdin);
	freopen("sky.out","w",stdout);
#endif
	scanf("%s",s);
	int n=ni,h=ni;
	if(s[0]=='B'){
		printf("%.9lf\n",(double)n);
		return 0;
	}
	double ans=n;
	for(int i=1;i<=h;i++){
		double ipw=1-1.0/(1<<i),pw=1,cur=0;
		for(int j=1;j<n;j++){
			cur+=(n-j)*pw*(1-(1+(double)(j-1)/((1<<i)-1))/2);
			pw*=ipw;
		}
		ans+=cur/(1ll<<i);
	}
	printf("%.9lf\n",ans);
	return 0;
}
