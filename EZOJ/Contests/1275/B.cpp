#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
const int MOD=1000000007,N=30,Q=200010;
long long t[N][N],_lcm[N][N];
long long gcd(long long a,long long b){
	return b==0?a:gcd(b,a%b);
}
int c[Q],d[Q];
int main(){
	for(int i=1;i<N;i++){
		t[i][1]=i;
		_lcm[i][1]=i;
		for(int j=2;j<=i;j++){
			t[i][j]=t[i][j-1]*t[i-1][j-1]/(t[i][j-1]-t[i-1][j-1]);
			_lcm[i][j]=_lcm[i][j-1]/gcd(t[i][j],_lcm[i][j-1])*t[i][j];
		}
	}
	int tot=ni(),n=ni(),k=ni(),ans,a=ni(),b=ni(),mod=ni();
	for(int i=2;i<=tot;i++){
		c[i]=ni();
	}
	for(int i=2;i<=tot;i++){
		d[i]=ni();
	}
	printf("%d\n",ans=_lcm[n][k]%MOD);
	for(int i=2;i<=tot;i++){
		n=(a*ans+c[i])%mod+1;
		k=(b*ans+d[i])%n+1;
		printf("%d\n",ans=_lcm[n][k]%MOD);
	}
}
