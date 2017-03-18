#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 210
#define INF 0x7f7f7f7f
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
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int diff[N],add[N],minus[N];
int main(){
	int n=ni(),tot=ni();
	for(int i=0,last=0;i<n;i++){
		diff[i]=ni()-last;
		last+=diff[i];
	}
	diff[n]=INF;
	memset(len,127,sizeof(len));
	char op;
	for(int i=0,cur;i<tot;i++){
		while(op=getchar(),op!='+'&&op!='-');
		cur=ni();
		if(op=='+'){
			apmin(add[cur],ni());
		}else{
			apmin(minus[cur],ni());
		}
	}
	
}
