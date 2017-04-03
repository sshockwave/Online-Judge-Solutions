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
const int N=1010;
int n,m,f[N][N];
char s[N],t[N];
inline int dfs(int i){
	if(i>n){
		return f[n][n]==n-1;
	}
	int ans=0,mx;
	for(t[i]='a';t[i]<'a'+m;t[i]++){
		mx=0;
		for(int j=1;j<=n;j++){
			if(s[i]==t[j]){
				f[i][j]=f[i-1][j-1]+1;
			}else{
				f[i][j]=max(f[i-1][j],f[i][j-1]);
			}
			apmax(mx,f[i][j]);
		}
		if(mx>=i-1){
			ans+=dfs(i+1);
		}
	}
	return ans;
}
int main(){
	n=ni(),m=ni();
	scanf("%s",s+1);
	printf("%d",dfs(1));
}
