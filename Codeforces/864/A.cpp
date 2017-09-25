#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
int a[110];
int main(){
#ifndef ONLINE_JUDGE
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	int n=ni;
	memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++){
		a[ni]++;
	}
	int last=0;
	for(int i=1;i<=100;i++){
		if(a[i]){
			if(a[i]==a[last]&&a[i]+a[last]==n){
				if(a[i]==a[last]&&a[i]+a[last]==n){
					printf("YES\n%d %d\n",i,last);
				}else{
					puts("NO");
				}
				return 0;
			}else{
				last=i;
			}
		}
	}
	puts("NO");
	return 0;
}
