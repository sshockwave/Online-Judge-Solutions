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
inline int nl(){
	lint i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=200010,MOD=1000000007;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int sub(int a,int b){
	return add(a,MOD-b);
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
char s[N];
int num[N];
inline lint query(int n,lint l,lint r){
	int ans=0;
	for(lint i=l;i<=r;i+=2){
		apadd(ans,mul(num[i%n],(r-i+1)%MOD));
	}
	return ans;
}
int main(){
//	freopen("B.in","r",stdin);
//	freopen("B.ans","w",stdout);
	int n=ni();
	scanf("%s",s);
	for(int i=0;i<n;i++){
		num[i]=s[i]-'0';
	}
	for(int tot=ni();tot--;){
		if(ni()==1){
			int pos=ni()-1;
			num[pos]=ni();
		}else{
			lint l=nl(),r=nl();
			printf("%lld\n",query(n,l-1,r-1));
		}
	}
}
