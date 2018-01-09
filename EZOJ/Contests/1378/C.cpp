#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>
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
template<class T>inline T abs(T x){return x>=0?x:-x;}
const int L=105,N=14,O=1000000007;
int f[1<<N][L][N];
int hei[N];
inline void space(){
	ifstream fin("/proc/self/status");
	cout<<string(istreambuf_iterator<char>(fin),istreambuf_iterator<char>());
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
#endif
	//space();
	int n=ni,len=ni;
	memset(f,0,sizeof(f));
	for(int i=0;i<n;i++){
		hei[i]=ni;
		f[1<<i][0][i]=1;
	}
	for(int s=1,ts=(1<<n)-1;s<ts;s++){
		for(int l=0;l<=len;l++){//len
			int* F=::f[s][l];
			for(int i=0;i<n;i++){//last
				if(F[i]==0)continue;
				for(int j=0;j<n;j++){//next
					if(((s>>j)&1)==0){
						int tlen=l+abs(hei[i]-hei[j]);
						if(tlen<=len){
							(f[s|(1<<j)][tlen][j]+=F[i])%=O;
						}
					}
				}
			}
		}
	}
	lint ans=0;
	for(int l=0,s=(1<<n)-1;l<=len;l++){
		for(int i=0;i<n;i++){
			ans+=f[s][l][i];
		}
	}
	printf("%lld\n",ans%O);
	return 0;
}
