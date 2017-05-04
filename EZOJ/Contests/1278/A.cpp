#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <map>
#include <ctime>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=410,INF=0x7f7f7f7f;
int f[N][N],a[N],b[N],h[N];
int main(){
	int n=ni(),atk=ni(),ans=INF;
	for(int i=1,tmp;i<=n;i++){
		a[i]=ni(),b[i]=ni(),tmp=ni();
		h[i]=tmp/atk;
		if(tmp%atk){
			h[i]++;
		}
	}
	b[0]=b[n+1]=0;
	memset(f,127,sizeof(f));
	for(int i=0;i<=n;i++){
		f[i][i+1]=0;
	}
	for(int gap=2;gap<=n+1;gap++){
		for(int i=0,j=gap;j<=n+1;i++,j++){
			for(int k=i+1;k<j;k++){
				apmin(f[i][j],f[i][k]+f[k][j]+h[k]*(b[i]+a[k]+b[j]));
			}
		}
	}
	printf("%d",f[0][n+1]);
}
