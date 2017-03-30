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
const int N=2010,MOD=1000000007;//debug
int c[N][N],stir[N][N];//c[down][up],stir[n][k]
int main(){
	memset(c,0,sizeof(c));
	memset(stir,0,sizeof(stir));
	c[0][0]=1;
	stir[0][0]=1;
	for(int i=1;i<N;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
			stir[i][j]=((long long)(i-1)*stir[i-1][j]%MOD+stir[i-1][j-1])%MOD;
		}
	}
	for(int tot=ni(),n,f,b;tot--;){
		n=ni(),f=ni(),b=ni();
		printf("%d\n",(int)((long long)stir[n-1][f+b-2]*c[f+b-2][f-1]%MOD));
	}
}
