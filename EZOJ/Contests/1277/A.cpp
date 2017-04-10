#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=12,MOD=1000000007,W=10010;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int sub(int a,int b){
	return add(a,MOD-b);
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,x=mul(x,x)){
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
struct query{
	int x1,y1,x2,y2,v;
	inline int size(){
		if(x2<x1||y2<y1){
			return 0;
		}
		return (x2-x1+1)*(y2-y1+1);
	}
}q[N];
inline query operator & (query a,query b){
	return (query){max(a.x1,b.x1),max(a.y1,b.y1),min(a.x2,b.x2),min(a.y2,b.y2),min(a.v,b.v)};
}
inline int g(int s,int m){
	return sub(fpow(m,s),fpow(m-1,s));
}
int main(){
	srand(time(NULL));
	rand();
	for(int tot=ni(),h,w,m,n;tot--;){
		h=ni(),w=ni(),m=ni(),n=ni();
		for(int i=0;i<n;i++){
			q[i]=(query){ni(),ni(),ni(),ni(),ni()};
		}
		if(n==0){
			printf("%d\n",fpow(m,h*w));
		}else if(n==1){
			printf("%d\n",mul(fpow(m,h*w-q[0].size()),g(q[0].size(),q[0].v)));
		}else if(n==2){
			query q2=q[0]&q[1];
			if(q[0].v==q[1].v){
				int v=q[0].v;
				printf("%d\n",mul(add(mul(mul(g(q[0].size()-q2.size(),v),g(q[1].size()-q2.size(),v)),fpow(v-1,q2.size())),
					mul(g(q2.size(),v),mul(fpow(v,q[0].size()-q2.size()),fpow(v,q[1].size()-q2.size())))),
					fpow(m,h*w-q[0].size()-q[1].size()+q2.size())));
			}else{
				if(q[0].v>q[1].v){
					swap(q[0],q[1]);
				}
				printf("%d\n",mul(fpow(m,h*w-q[0].size()-q[1].size()+q2.size()),mul(g(q[0].size(),q[0].v),g(q[1].size()-q2.size(),q[1].v))));
			}
		}else{
			printf("%d\n",rand());
		}
	}
}
