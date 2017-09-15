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
const int N=20;
double p[N],h[N][N],_p[N][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("travel.in","r",stdin);
	freopen("travel.out","w",stdout);
#endif
	int m=ni,n=ni;//people city
	memset(_p,0,sizeof(_p));
	for(int i=0;i<m;i++){
		scanf("%lf",p+i);
		_p[i][1]=1;
		for(int j=2;j<=n;j++){
			_p[i][j]=_p[i][j-1]*p[i];
		}
	}
	double ans=0;
	for(int i=0;i<m;i++){
		for(int j=1;j<=n;j++){
			scanf("%lf",h[i]+j);
			ans+=_p[i][j]*h[i][j];
		}
	}
	for(int j=1;j<n;j++){
		for(int s=1,ts=1<<m;s<ts;s++){//arrive at j
			static bool arr[N];
			int cnt=0;
			double ecj=0,sum=0,prob=1;
			for(int i=0;i<m;i++){
				cnt+=arr[i]=(s>>i)&1;
				if(arr[i]){
					ecj+=p[i];
					prob*=_p[i][j];
				}else{
					prob*=1-_p[i][j];
				}
			}
			for(int i=0;i<m;i++){
				if(arr[i]){
					sum+=p[i]*(ecj-p[i]+1)*h[i][j+1];
				}
			}
			ans+=sum*prob/cnt;
		}
	}
	printf("%.10lf\n",ans);
	return 0;
}
