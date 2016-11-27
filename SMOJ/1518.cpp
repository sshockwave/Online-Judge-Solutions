#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 100010
#define M 7000010
#define INF 2147483647
using namespace std;
long long u,v;
int origin[N],que[2][N+M],qhead[3],qtail[3];
bool oricmp(const int &a,const int &b){
	return a>b;
}
inline bool empty(int x){
	return qhead[x]==qtail[x];
}
inline int pop(){
	int ret=-INF,q;
	if(!empty(0)&&ret<origin[qhead[0]]){
		ret=origin[qhead[0]];
		q=0;
	}
	if(!empty(1)&&ret<que[0][qhead[1]]){
		ret=que[0][qhead[1]];
		q=1;
	}
	if(!empty(2)&&ret<que[1][qhead[2]]){
		ret=que[1][qhead[2]];
		q=2;
	}
	(++qhead[q])%=(N+M);
	return ret;
}
inline void push(int q,int x){
	que[q-1][qtail[q]++]=x;
	qtail[q]%=(N+M);
}
int main(){
	freopen("1518.in","r",stdin);
	freopen("1518.out","w",stdout);
	int m,q,t,delta=0;
	scanf("%d%d%d%lld%lld%d",qtail,&m,&q,&u,&v,&t);
	for(int i=0;i<qtail[0];i++){
		scanf("%d",origin+i);
	}
	sort(origin,origin+qtail[0],oricmp);
	memset(qhead,0,sizeof(qhead));
	for(int i=1,val;i<=m;i++){
		val=pop()+delta;
		delta+=q;
		if(i%t==0){
			printf("%d ",val);
		}
		push(1,u*val/v-delta);
		push(2,val-(u*val/v)-delta);
	}
	putchar('\n');
	for(int i=1,val;i<=qtail[0]+m;i++){
		val=pop();
		if(i%t==0){
			printf("%d ",val+delta);
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
