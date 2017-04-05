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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=100010;
long long f[N][8];
char s[N];
int main(){
	int n=ni();
	char m=ni();
	memset(s,0,sizeof(s));
	memset(f,0,sizeof(f));
	scanf("%s",s+1);
	if(s[1]==s[2]){
		f[1][6]=1;//0 1 1:+1 +1 0
		f[1][4]=m-1;//0 0 0:+1 0 0
	}else{
		f[1][6]=1;//0 1 1:+1 +1 0
		f[1][5]=1;//0 0 1:+1 0 +1
		f[1][4]=m-2;//0 0 0:+1 0 0
	}
	m+='a';
	for(int i=1;i<n;i++){
		for(int v=0;v<8;v++){
			if(f[i][v]==0){
				continue;
			}
			int j=((v>>2)&1)+i-2,k=((v>>1)&1)+j,l=(v&1)+k,nj,nk,nl;
			for(char t='a';t<m;t++){
				nj=k;
				if(t==s[i]){
					apmax(nj,j+1);
				}
				if(nj<i-1){
					continue;
				}
				nk=max(nj,l);
				if(t==s[i+1]){
					apmax(nk,k+1);
				}
				nl=nk;
				if(t==s[i+2]){
					apmax(nl,l+1);
				}
				f[i+1][((nj>i-1)<<2)|((nk>nj)<<1)|(nl>nk)]+=f[i][v];
			}
		}
	}
	printf("%lld",f[n][2]+f[n][3]+f[n][4]+f[n][5]);
}
