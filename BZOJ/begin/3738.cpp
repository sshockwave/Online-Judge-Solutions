#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define K 5000010
#define MOD 1000000007
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
int w[K],f[K];
int main(){
	freopen("highway.in","r",stdin);
	freopen("highway.out","w",stdout);
	int n=ni(),m=ni(),k=ni();
	for(int i=1;i<=m;i++){
		w[i]=ni();
	}
	for(int i=m+1;i<=n;i++){
		w[i]=k;
	}
	memset(f,0,sizeof(f));
	f[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=k;j>=0;j--){
			int nxt=0;
			for(int p=0;p<=w[i]&&p<=j;p++){
				(nxt+=f[j-p])%=MOD;
			}
			f[j]=nxt;
		}
	}
	printf("%d",f[k]);
}
