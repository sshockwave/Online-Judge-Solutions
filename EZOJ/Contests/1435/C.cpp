#include <cassert>
#include <cstdlib>
#include "maze.h"
inline int gen(int l,int r){
	return rand()%(r-l+1)+l;
}
const int N=100010,S=8;
int stk[N],ss=0;
inline void pshstk(int d){
	stk[ss++]=d;
	if(move(d))throw true;
}
inline void popstk(int cnt){
	for(;cnt--;assert(ss>=0),move(stk[--ss]));
}
inline int except(int d){
	int t=gen(0,1);
	if(d==0)return t+1;
	if(d==1)return t<<1;
	if(d==2)return t;
	return -1;
}
inline void work(int &dep,int &las){
	stk[0]=las,ss=1;
	for(int i=1;i<=S;i++){
		pshstk(except(stk[ss-1]));
	}
	int dncnt=(query()-(dep-S))>>1;
	popstk(dncnt),dep-=S-dncnt;
	if(dncnt){
		pshstk(0^1^2^stk[ss]^stk[ss-1]);
		--dep;
	}
	las=stk[ss-1];
}
void findpath(int initialDeep,int){
	ss=0;
	try{
		pshstk(gen(0,2));
		int dep=query(),las=stk[0];
		if(dep>initialDeep){
			popstk(1),dep=initialDeep;
		}
		for(;;work(dep,las));
	}catch(bool end){
		assert(end);
	}
}
