#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=12;
bool choose[N];
int n,pval[N];
inline bool valid(){
	for(int i=2;i<=n;i++){
		if(choose[i]&&!choose[i>>1]){
			return false;
		}
	}
	return true;
}
int seq[N];
int main(){
	n=ni();
	for(int i=1;i<=n;i++){
		pval[i]=ni();
	}
	for(int a=0;a<n;a++){
		int ans=0;
		for(int state=0;state<(1<<(n-1));state++){
			for(int i=1;i<=n;i++){
				choose[i]=(state>>(i-1))&1;
			}
			if(!valid()){
				continue;
			}
			int stop=0;
			for(int i=1;i<=n;i++){
				if(choose[i]){
					seq[++stop]=pval[i];
				}
			}
			sort(seq+1,seq+stop+1);
			apmax(ans,seq[(stop-a+1)/2]);
		}
		printf("%d ",ans);
	}
}
