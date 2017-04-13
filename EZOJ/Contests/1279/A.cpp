//Score:100/100
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=500010;
int a[N],p[N],MOD,n;
inline int add(int a,int b){
	return ((lint)a+b)%MOD;
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
inline void apmul(int &a,int b){
	a=mul(a,b);
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
int gcd(lint a,lint b){
	return b==0?a:gcd(b,a%b);
}
int prime[N],ptop=0,exp[N];
bool np[N];
inline void getprime(int n){
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ptop++]=i;
		}
		for(int j=0,cur=2;j<ptop&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				break;
			}
		}
	}
}
inline void addlcm(int x){
	for(int i=0,cur=2;cur*cur<=x;cur=prime[++i]){
		if(x%cur==0){
			int e=0;
			for(;x%cur==0;x/=cur,e++);
			apmax(exp[cur],e);
		}
	}
	if(x!=1){
		apmax(exp[x],1);
	}
}
bool vis[N];
int main(){
	n=ni(),MOD=ni();
	getprime(n);
	memset(exp,0,sizeof(exp));
	for(int i=1;i<=n;i++){
		a[i]=i,p[i]=ni();
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			int len=0;
			for(int j=i;!vis[j];j=p[j],len++){
				vis[j]=true;
			}
			addlcm(len);
		}
	}
	int ans=1;
	for(int i=0;i<ptop;i++){
		apmul(ans,fpow(prime[i],exp[prime[i]]));
	}
	printf("%d\n",ans);
}
