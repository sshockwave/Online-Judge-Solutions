#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
inline lint nl(){
	lint i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int D=1000010;
int MOD;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int sub(int a,int b){
	return (a-b+MOD)%MOD;
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline lint sqr(int a){
	return (lint)a*a;
}
inline int apadd(int &a,int b){
	a=add(a,b);
}
inline int apmul(int &a,int b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
int prime[D],ptop=0;
bool np[D];
lint p,ans;
inline int cal(int p,int e){
	return sub(mul(fpow(p,e*3-1),p+1),fpow(p,e*2-1));
}
int main(){
	memset(np,0,sizeof(np));
	for(int i=2;i<D;i++){
		if(!np[i]){
			prime[ptop++]=i;
		}
		for(int j=0;j<ptop&&i*prime[j]<D;j++){
			np[i*prime[j]]=true;
			if(i%prime[j]==0){
				break;
			}
		}
	}
	int tot=ni(),e,ans,ans2;
	MOD=ni();
	while(tot--){
		p=nl()-1;
		ans2=mul(p%MOD,p%MOD);
		ans=1;
		for(int j=0,cur=2;sqr(cur)<=p;cur=prime[++j]){
			if(p%cur==0){
				e=0;
				for(;p%cur==0;p/=cur,e++);
				apmul(ans,cal(cur,e));
			}
		}
		if(p!=1){
			apmul(ans,cal(p%MOD,1));
		}
		printf("%d\n",add(ans,ans2));
	}
}
