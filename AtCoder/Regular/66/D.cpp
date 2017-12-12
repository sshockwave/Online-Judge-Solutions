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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100,O=1000000007;
bool num[N];
int f[N][2][3];//[u avail][v avail]
int pw3[N];
inline void gmath(int n){
	pw3[0]=1;
	for(int i=1;i<=n;i++){
		pw3[i]=(lint)pw3[i-1]*3%O;
	}
}
int main(){
	lint n=next_num<lint>();
	int sh=0;
	memset(num,0,sizeof(num));
	for(;n;num[sh]=n&1,sh++,n>>=1);
	gmath(sh);
	memset(f,0,sizeof(f));
	f[sh][0][0]=1;
	for(int i=sh-1;i>=0;i--){
		for(int a=0;a<2;a++){//u avail
			for(int b=0;b<3;b++){//v avail
				int F=f[i+1][a][b];
				if(F==0)continue;
				int ra=(a<<1)|num[i],rb=(b<<1)|num[i];
				for(int c=0;c<=ra&&c<=1;c++){
					if(c==1){
						int fa=min(1,ra-1),fb=min(2,rb-1);
						if(fa>=0&&fb>=0){
							(f[i][fa][fb]+=F)%=O;
						}
					}else for(int d=0,td=min(rb,2);d<=td;d+=2){
						int fa=min(1,ra),fb=min(2,rb-d);
						(f[i][fa][fb]+=F)%=O;
					}
				}
			}
		}
	}
	lint ans=0;
	for(int a=0;a<2;a++){
		for(int b=0;b<3;b++){
			ans+=f[0][a][b];
		}
	}
	printf("%lld\n",ans%O);
	return 0;
}
