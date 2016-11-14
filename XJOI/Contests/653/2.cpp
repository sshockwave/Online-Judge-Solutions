#include <iostream>
#include <cstdio>
#include <cstring>
#define N 1000010
#define MOD 1000000007
using namespace std;
int f[N][4];
inline void setf(int l,int r,int val){
	r=r-l+1;
	f[l][r]=(f[l][r]+val)%MOD;
}
int main(){
	int n,t,ans=0;
	scanf("%d",&n);
	f[0][1]=1;
	for(int i=0;i<=n;i++){
		for(int j=max(0,1-i),k=min(n-i+1,3),r;j<=k;j++){
			r=i+j-1;
			ans=(ans+f[i][j])%MOD;
			//case 1
			t=max(i,r-1);
			setf(t+3,t+2,f[i][j]);
			//case 2
			t=max(i-1,r);
			setf(t+2,t+3,f[i][j]);
			//case 3
			t=max(i,r-1);
			setf(t+2,t+3,f[i][j]);
			//case 4
			t=max(i,r);
			setf(t+2,t+2,f[i][j]);
			//case 5
			t=max(i,r-2);
			setf(t+3,t+3,f[i][j]);
			//case 6
			t=max(i,r);
			setf(t+1,t+3,f[i][j]);
		}
	}
	printf("%d",ans);
}
