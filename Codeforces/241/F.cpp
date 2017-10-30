#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
const int N=110,D=26,L=1010;
char mat[N][N],s[L];
int posx[D],posy[D],cost[N][N];
int rest,x,y;
inline int sig(int x){
	return x>0?1:x<0?-1:0;
}
inline void walk(int tx,int ty){
	int dx=sig(tx-x),dy=sig(ty-y);
	while(x!=tx||y!=ty){
		if(rest<cost[x][y]){
			printf("%d %d\n",x,y);
			throw 1;
		}
		rest-=cost[x][y],x+=dx,y+=dy;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
#endif
	int n=ni,m=ni;
	rest=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
		for(int j=1;j<=m;j++){
			if(isalpha(mat[i][j])){
				posx[mat[i][j]-'a']=i;
				posy[mat[i][j]-'a']=j;
				cost[i][j]=1;
			}else{
				cost[i][j]=mat[i][j]-'0';
			}
		}
	}
	x=ni,y=ni;
	try{
		scanf("%s",s);
		for(int i=0;s[i];i++){
			walk(posx[s[i]-'a'],posy[s[i]-'a']);
		}
		int tx=ni,ty=ni;
		walk(tx,ty);
		printf("%d %d\n",tx,ty);
	}catch(int a){}
	return 0;
}
