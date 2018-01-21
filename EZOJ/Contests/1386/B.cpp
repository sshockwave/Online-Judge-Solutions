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
const int N=6,M=1<<N,O=1000000007;//partial
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int a[M][M];
inline void gauss(int n){//n vars
	for(int i=0;i<n;i++){
		int j=i;
		for(;j<n&&a[j][i]==0;j++);
		assert(j<n);
		for(int k=i;k<=n;k++){
			swap(a[i][k],a[j][k]);
		}
		lint r=inv(a[i][i]);
		for(int k=i;k<=n;k++){
			a[i][k]=r*a[i][k]%O;
		}
		for(j=i+1;j<n;j++){
			if(a[j][i]==0)continue;
			r=O-a[j][i];
			for(int k=i;k<=n;k++){
				a[j][k]=(int)(a[j][k]+r*a[i][k]%O)%O;
			}
		}
	}
	for(int i=n-1;i>=0;i--){
		for(int j=0;j<i;j++){
			if(a[j][i]){
				a[j][n]=(O-(lint)a[i][n]*a[j][i]%O+a[j][n])%O,a[j][i]=0;
			}
		}
	}
}
int invn2;
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
#endif
	int n=ni;
	invn2=inv((lint)n*(n-1)/2%O);
	scanf("%s",s);
	int mask=0;
	for(int i=0;i<n;i++){
		mask|=(s[i]-'A')<<i;
	}
	memset(a,0,sizeof(a));
	for(int s=0,ts=1<<n;s<ts;s++){
		if(s!=0&&s!=(ts-1)){
			for(int i=0;i<n;i++){
				for(int j=i+1;j<n;j++){
					int s2=s;
					bool flag=(s>>i)&1;
					if(flag){
						s2|=1<<j;
					}else if((s2>>j)&1){
						s2^=1<<j;
					}
					a[s][s2]=(a[s][s2]+invn2)%O;
				}
			}
		}
		a[s][s]=(a[s][s]+O-1)%O;
		if(s==mask){
			a[s][ts]=O-1;
		}
	}
	gauss(1<<n);
	lint ans=0;
	for(int s=0,ts=1<<n;s<ts;s++){
		ans+=a[s][ts];
		cout<<"f["<<s<<"]="<<a[s][ts]<<endl;
	}
	printf("%lld\n",ans%O*inv(1<<n)%O);
	return 0;
}
