#include <iostream>
#include <cstdio>
#include <cstring>
#define N 10010
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int gcd(int a,int b){
	return b?gcd(b,a%b):a;
}
bool vis[N*2];
int main(){
	memset(vis,0,sizeof(vis));
	int n=next_int(),ans=1;
	for(int i=1,j;i<=2*n;i++){
		if(!vis[i]){
			j=0;
			for(int k=i;!vis[k];k=(k&1)?(n+((k+1)>>1)):(k>>1)){
				j++;
				vis[k]=true;
			}
			ans=ans/gcd(ans,j)*j;
		}
	}
	printf("%d",ans);
}
