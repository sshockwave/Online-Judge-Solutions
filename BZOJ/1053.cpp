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
	int num;
	long long g;
};
inline void apmax(state &a,state b){
	if(a.g<b.g||(a.g==b.g&&a.num<b.num)){
		a=b;
	}
}
int prime[]={2,3,5,7,11,13,17,19,23,29,31},n;
state dfs(int p,long long cur,long long g){
	if(p>10){
		return (state){cur,g};
	}
	state ret=(state){1,1};
	for(int i=0;cur<=n;i++,cur*=prime[p]){
		apmax(ret,dfs(p+1,cur,g*(i+1)));
	}
	return ret;
}
int main(){
	n=ni();
	printf("%d",dfs(0,1,1).num);
}
