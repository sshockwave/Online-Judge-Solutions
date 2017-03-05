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
int prime[]={2,3,5,7,11,13,17,19,23,29,31},n,num=1,gx=1;
void dfs(int p,long long cur,long long g){
	if(p>10){
		if(gx<g){
			gx=g,num=cur;
		}else if(gx==g&&cur<num){
			num=cur;
		}
	}else for(int i=0;cur<=n;i++,cur*=prime[p]){
		dfs(p+1,cur,g*(i+1));
	}
}
int main(){
	n=ni();
	dfs(0,1,1);
	printf("%d",num);
}
