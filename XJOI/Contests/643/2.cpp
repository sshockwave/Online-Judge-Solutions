#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
using namespace std;
char s[N];
int amt[N],n,m;
inline int simlar(char* s1,char* s2){
	int ret=0;
	for(int i=0;i<m;i++){
		if(s1[i]==s2[i]){
			ret++;
		}
	}
	return ret;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%s",s+i*m);
	}
	memset(amt,0,sizeof(amt));
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			amt[simlar(s+i*m,s+j*m)]++;
		}
	}
	for(int i=0;i<=m;i++){
		printf("%d\n",amt[i]);
	}
}
