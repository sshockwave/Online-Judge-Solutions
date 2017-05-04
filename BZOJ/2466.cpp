#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <bitset>
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
const int N=110;
bitset<N>eqn[N];
inline int gauss(int n){
	for(int i=1,j;i<=n;i++){
		for(j=i;j<=n;j++){
			if(eqn[j][i]){
				break;
			}
		}
		if(j>n){
			continue;
		}
		swap(eqn[i],eqn[j]);
		for(j=i+1;j<=n;j++){
			if(eqn[j][i]){
				eqn[j]^=eqn[i];
			}
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=i-1;j>=1;j--){
			if(eqn[j][i]){
				eqn[j]^=eqn[i];
			}
		}
	}
}
int main(){
	int n;
	while(n=ni()){
		memset(eqn,0,sizeof(eqn));
		for(int i=1;i<=n;i++){
			eqn[i].set(i);
			eqn[i].set(n+1);
		}
		for(int i=1;i<n;i++){
			int u=ni(),v=ni();
			eqn[u].set(v),eqn[v].set(u);
		}
		gauss(n);
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(eqn[i][i]&&eqn[i][n+1]){
				cnt++;
			}
		}
		printf("%d\n",cnt);
	}
}
