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
const int N=15,N2=200,MOD=1000000007;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int mul(int a,int b){
	return (long long)a*b%MOD;
}
inline int apadd(int &a,int b){
	a=add(a,b);
}
inline int apmul(int &a,int b){
	a=mul(a,b);
}
int n,k,l,num[N],lpow[N][N2],c[N][N],ans;//lpow:bigger than i
int fpow(int x,int n){
	if(n==0){
		return 1;
	}
	int ret=fpow(x,n>>1);
	apmul(ret,ret);
	if(n&1){
		apmul(ret,x);
	}
	return ret;
}
inline int cal(){
	num[k]++;
	int ret=1;
	for(int i=1;i<=k+1;i++){
		if(num[i]==0){
			continue;
		}
		apmul(ret,lpow[0][num[i]*(num[i]-1)/2]);
		int cnt1=1,cnt2=1;
		for(int j=0;j<i;j++){
			if(num[j]){
				apmul(cnt1,lpow[i-j-1][num[j]]);
				apmul(cnt2,lpow[i-j][num[j]]);
			}
		}
		if(i<k+1){
			cnt1=(cnt1-cnt2+MOD)%MOD;
		}
		apmul(ret,fpow(cnt1,num[i]));
	}
	num[k]--;
	int rest=n-2;
	for(int i=1;i<=k;i++){
		if(num[i]){
			apmul(ret,c[rest][num[i]]);
			rest-=num[i];
		}
	}
	return ret;
}
void dfs(int pos,int rest){
	if(pos==k+1){
		if(rest==0){
			apadd(ans,cal());
		}
		return;
	}
	pos++;
	for(num[pos]=0;num[pos]<=rest;num[pos]++){
		dfs(pos,rest-num[pos]);
	}
}
int main(){
	n=ni(),k=ni(),l=ni();
	if(n==1){
		putchar(k?'0':'1');
		return 0;
	}
	if(l<k){
		putchar('0');
		return 0;
	}
	memset(lpow,0,sizeof(lpow));
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=0;i<=n&&i<l;i++){
		lpow[i][0]=1;
		for(int j=1;j<N2;j++){
			lpow[i][j]=mul(lpow[i][j-1],l-i);
		}
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=c[i-1][j-1]+c[i-1][j];
		}
	}
	num[0]=1;
	ans=0;
	dfs(0,n-2);
	printf("%d",ans);
}
