#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
struct state{
	int ans;
	long long cnt;
};
inline void apmax(state &a,state b){
	if(a.cnt<b.cnt){
		a=b;
	}
}
int prime[]={2,3,5,7,11,13,17,19,23,29},n,exp[10];
state dfs(long long cur){
	state ret;
	ret.cnt=1;
	if(cur*2>n){
		ret.ans=cur;
		for(int i=0;i<10&&exp[i];i++){
			ret.cnt*=exp[i]+1;
		}
		return ret;
	}
	for(int i=0;i<10;i++){
		if(cur*prime[i]<=n){
			exp[i]++;
			apmax(ret,dfs(cur*prime[i]));
			exp[i]--;
		}
		if(exp[i]==0){
			break;
		}
	}
	return ret;
}
int main(){
	n=ni();
	memset(exp,0,sizeof(exp));
	printf("%d",dfs(1).ans);
}
