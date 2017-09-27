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
const int MOD=1000000007;
inline int Main(){
	int n=ni,m=ni;
	int cnt=0;
	for(int a=0;a<=n;a++){
		for(int b=0;b<=m;b++){
			for(int c=0;c<=n;c++){
				for(int d=0;d<=m;d++){
					for(int e=0;e<=n;e++){
						for(int f=0;f<=m;f++){
							if((f-b)*(c-a)!=(d-b)*(e-a)){
								cnt++;
							}
						}
					}
				}
			}
		}
	}
	return cnt/6;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("triangle.in","r",stdin);
	freopen("triangle.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
