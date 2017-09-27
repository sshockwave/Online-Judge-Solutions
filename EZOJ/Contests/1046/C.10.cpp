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
bool selct[101][101];
bool vis[101][101];
int mx=7;
inline bool check(){
	for(int i=0;i<=100;i++){
		for(int j=0;j<=100;j++){
			if(!vis[i][j]){
				int tx=i+mx,ty=j+mx;
				if(tx>100){
					tx=100;
				}
				if(ty>100){
					ty=100;
				}
				selct[tx][ty]=true;
				for(int dx=-mx;dx<=mx;dx++){
					for(int dy=-mx;dy<=mx;dy++){
						if(dx+tx<=100&&dy+ty<=100){
							vis[dx+tx][dy+ty]=true;
						}
					}
				}
				return true;
			}
		}
	}
	return false;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("defense10.in","r",stdin);
	freopen("defense10.out","w",stdout);
#endif
	while(check());
	int cnt=0;
	for(int i=0;i<=100;i++){
		for(int j=0;j<=100;j++){
			if(selct[i][j]){
				cnt++;
			}
		}
	}
	printf("%d\n",cnt);
	for(int i=0;i<=100;i++){
		for(int j=0;j<=100;j++){
			if(selct[i][j]){
				printf("%d\n",i*101+j+1);
			}
		}
	}
	return 0;
}
