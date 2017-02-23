#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100010
#define M 7000010
#define INF 0x7f7f7f7f
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
int len[N],lque[N+M],rque[N+M],qhead=1,lhead=0,rhead=0,tail=0;
bool lencmp(int a,int b){
	return a>b;
}
int main(){
	int n=next_int(),m=next_int(),q=next_int(),t,delta=0;
	long long u=next_int(),v=next_int();
	t=next_int();
	for(int i=1;i<=n;i++){
		len[i]=next_int();
	}
	sort(len+1,len+n+1,lencmp);
	for(int i=1,cur,*head,px;i<=m;i++){
		cur=-INF;
		if(qhead<=n&&len[qhead]>cur){
			head=&qhead;
			cur=len[qhead];
		}
		if(lhead<tail&&lque[lhead]>cur){
			head=&lhead;
			cur=lque[lhead];
		}
		if(rhead<tail&&rque[rhead]>cur){
			head=&rhead;
			cur=rque[rhead];
		}
		(*head)++;
		cur+=delta;
		if(i%t==0){
			printf("%d",cur);
		}
		px=u*cur/v;
		delta+=q;
		lque[tail]=px-delta,rque[tail]=cur-px-delta,tail++;
	}
	putchar('\n');
	for(int i=1,cur,*head;i<=n+m;i++){
		cur=-INF;
		if(qhead<=n&&len[qhead]>cur){
			head=&qhead;
			cur=len[qhead];
		}
		if(lhead<tail&&lque[lhead]>cur){
			head=&lhead;
			cur=lque[lhead];
		}
		if(rhead<tail&&rque[rhead]>cur){
			head=&rhead;
			cur=rque[rhead];
		}
		(*head)++;
		if(i%t==0){
			printf("%d",cur+delta);
		}
	}
}
