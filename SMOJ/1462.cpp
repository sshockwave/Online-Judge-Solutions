#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef ll long long;
ll f[19][512][5][7][8][9];
int k,digits[19],dtop;
inline void getdig(ll n){
	dtop=0;
	for(int &i=dtop;n;i++,n/=10){
		digits[i]=n%10;
	}
}
inline ll dp(int i){
	
}
inline ll solve(ll t){
	getdig(t);
	memset(f,0,sizeof(f));
	f[dtop][0][0][0][0][0]=1;
	ll ans=0;
	for(int i=dtop;i>0;i--){
		for(int j=digit[i]-1;j>=0;j--){
			for(int k=0;k<512;k++){
				for(int l=0;l<5;l++){
					for(int m=0;m<7;m++){
						for(int n=0;n<8;n++){
							for(int o=0;o<9;o++){
								if(j){
									f[i-1][k|(1<<(j-1))][(l+j)%5][(m+j)%7][(n+j)%8][(o+j)%9]+=f[i][k][l][m][n][o];
								}else{
									f[i-1][k][l][m][n][o]=f[i][k][l][m][n][o];
								}
							}
						}
					}
				}
			}
		}
		ans+=dp(i-1);
	}
	return ans;
}
int main(){
//	freopen("1462.in","r",stdin);
//	freopen("1462.out","w",stdout);
	ll l,r,ans;
	cin>>k>>l>>r;
	cout<<solve(r)-solve(l);
}
