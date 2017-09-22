#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010,SH=60;
int nxt[N][SH];
int main(){
#ifndef ONLINE_JUDGE
	freopen("skate.in","r",stdin);
	freopen("skate.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		nxt[i][0]=ni;
	}
	for(int i=1;i<SH;i++){
		for(int j=1;j<=n;j++){
			nxt[j][i]=nxt[nxt[j][i-1]][i-1];
		}
	}
	while(tot--){
		int t=ni;
		lint k=nl;
		for(int j=0;j<SH;j++){
			if(k&(1<<j)){
				t=nxt[t][j];
			}
		}
		printf("%d\n",t);
	}
	return 0;
}
