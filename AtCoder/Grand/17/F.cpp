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
const int N=19,O=1000000007;
int f[1<<N];
int a[N+2][N];
int main(){
	int n=ni-1,m=ni;
	memset(a,-1,sizeof(a));
	for(int tot=ni,u,v;tot--;u=ni,v=ni-1,a[u][v]=ni);
	memset(f,0,sizeof(f));
	f[0]=1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<n;j++){
			for(int s=(1<<n)-1;s>=0;s--){
				int F=f[s];
				if(F){
					f[s]=((s>>j)&1)==0&&a[i][j]!=1?F:0;//go left
					if(a[i][j]!=0){//go right
						if((s>>j)&1){
							f[s]=F;
						}else{
							int lo=s&((1<<j)-1),t=s^lo;
							(f[(t^(t&-t))|(1<<j)|lo]+=F)%=O;
						}
					}
				}
			}
		}
	}
	lint ans=0;
	for(int s=0,ts=1<<n;s<ts;s++){
		ans+=f[s];
	}
	printf("%lld\n",ans%O);
	return 0;
}
