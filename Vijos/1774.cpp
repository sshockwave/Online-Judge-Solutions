#include <iostream>
#include <cstdio>
#include <cstring>
#define M 1010
using namespace std;
int que[M],qhead=0,qtail=0,m;
inline bool find(int x){
	int i=qhead;
	do{
		if(que[i]==x){
			return true;
		}
		i=(i+1)%m;
	}while(i!=qtail);
	return false;
}
int main(){
	int n,cnt=0,x;
	scanf("%d%d",&m,&n);
	memset(que,127,sizeof(que));
	while(n--){
		scanf("%d",&x);
		if(find(x)){
			continue;
		}
		cnt++;
		que[qtail]=x;
		if(qtail==qhead){
			qhead=(qhead+1)%m;
		}
		qtail=(qtail+1)%m;
	}
	printf("%d",cnt);
}
