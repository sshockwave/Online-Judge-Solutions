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
const int N=1010,MOD=1000000007;
int pow(int x,int n){
	if(n==0){
		return 1;
	}
	int ret=pow(x,n>>1);
	ret=(long long)ret*ret%MOD;
	if(n&1){
		ret=(long long)ret*x%MOD;
	}
	return ret;
}
int c[N][N],f[N];//c[down][up]
int main(){
	int a=ni(),b=ni(),c=ni(),d=ni();
	if(c<d){
		swap(c,d);
	}
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<N;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
		}
	}
}
