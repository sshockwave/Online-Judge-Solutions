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
const int N=1010,M=7;
int mat[N][M];
int main(){
#ifndef ONLINE_JUDGE
	freopen("trip.in","r",stdin);
	freopen("trip.out","w",stdout);
#endif
	int n=ni,m=ni;
	memset(mat,0,sizeof(mat));
	for(int tot=ni;tot--;){
		int x=ni,y=ni;
		mat[x][y]=true;
	}
	for(int tot=ni;tot--;){
		int x=ni,y=ni;
		if(m==1){
			puts("0");
		}else if(m==2){
			if(!mat[x][y]&&!mat[x+1][y]){
				int l=0,r=0;
				for(;x+1-l>=1&&!mat[x+1-l][0]&&!mat[x+1-l][1];l++);
				for(;x+r<=n&&!mat[x+r][0]&&!mat[x+r][1];r++);
				l--,r--;
				printf("%d\n",l*r);
			}else{
				puts("0");
			}
		}
	}
	return 0;
}
