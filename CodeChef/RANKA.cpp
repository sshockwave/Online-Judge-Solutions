#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
int stepcnt;
inline void __putmove(int x,int y){
	printf("%d %d\n",x,y);
	if(--stepcnt==0){
		exit(0);
	}
}
inline void putmove(int x,int y,bool p){
	static bool curop=0;
	if(p!=curop){
		__putmove(0,0);
		curop^=1;
	}
	__putmove(x,y);
	curop^=1;
}
int vaccnt=0;
int posx[10],posy[10];
void dfs(bool dir,int x=vaccnt){
	if(x==0)return;
	dfs(0,x-1);
	if(dir==0){
		putmove(posx[x],posy[x]+1,0);
	}else{
		putmove(posx[x],posy[x],1);
	}
	dfs(1,x-1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ranka.in","r",stdin);
	freopen("ranka.out","w",stdout);
#endif
	stepcnt=ni;
	bool dir=0;
	putmove(1,2,0);
	putmove(1,3,1);
	for(int i=2;i<=8;i+=2){
		putmove(i,1,0),dfs(dir),dir^=1;
		putmove(i+1,2,0),dfs(dir),dir^=1;
		putmove(i+1,3,1),dfs(dir),dir^=1;
		putmove(i,4,1),dfs(dir),dir^=1;
		putmove(i,2,1);
		vaccnt++;
		posx[vaccnt]=i,posy[vaccnt]=2;
	}
	putmove(1,7,0),dfs(dir),dir^=1;
	putmove(1,8,1),dfs(dir),dir^=1;
	for(int i=2;i<=8;i+=2){
		putmove(i,6,0),dfs(dir),dir^=1;
		putmove(i+1,7,0),dfs(dir),dir^=1;
		putmove(i+1,8,1),dfs(dir),dir^=1;
		putmove(i,9,1),dfs(dir),dir^=1;
		putmove(i,7,1);
		vaccnt++;
		posx[vaccnt]=i,posy[vaccnt]=7;
	}
	assert(dir==0);
	dfs(dir),dir^=1;
	for(int i=1;i<=7;i+=2){
		putmove(i,1,0),dfs(dir),dir^=1;
	}
	for(int i=1;i<=7;i+=2){
		putmove(i,4,1),dfs(dir),dir^=1;
	}
	for(int i=1;i<=9;i++){
		putmove(i,5,1),dfs(dir),dir^=1;
	}
	for(int i=1;i<=7;i+=2){
		putmove(i,6,0),dfs(dir),dir^=1;
	}
	for(int i=1;i<=7;i+=2){
		putmove(i,9,1),dfs(dir),dir^=1;
	}
	assert(false);
	return 0;
}
