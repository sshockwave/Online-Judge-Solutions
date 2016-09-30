#include <iostream>
#include <cstdio>
#include <cstring>
#define N 85
using namespace std;
struct bigint{
	int digit[50],dtop;
	void clear(){
		memset(digit,0,sizeof(digit));
		dtop=0;
	}
	bigint(){
		clear();
	}
	void maintain(){
		for(int i=0;i<dtop;i++){
			digit[i+1]+=digit[i]/10;
			digit[i]%=10;
		}
		for(int &i=dtop;digit[i];i++){
			digit[i+1]+=digit[i]/10;
			digit[i]%=10;
		}
	}
	bigint operator + (bigint &b){
		bigint c;
		c.dtop=max(dtop,b.dtop);
		for(int i=0;i<c.dtop;i++){
			c.digit[i]=digit[i]+b.digit[i];
		}
		c.maintain();
		return c;
	}
	bigint operator * (int &b){
		bigint c;
		c.dtop=dtop;
		for(int i=0;i<dtop;i++){
			c.digit[i]*=b;
		}
		c.maintain();
		return c;
	}
	bool operator < (bigint &b){
		if(dtop==b.dtop){
			for(int i=dtop-1;i>=0;i--){
				if(digit[i]!=b.digit[i]){
					return digit[i]<b.digit[i];
				}
			}
			return false;
		}
		return dtop<b.dtop;
	}
	void print(){
		for(int i=dtop-1;i>=0;i--){
			printf("%d",digit[i]);
		}
	}
}f[N][N][N],power[N],ans,cur;
int a[N][N];
int main(){
	power[0].digit[0]=1;
	power[0].dtop=1;
	for(int i=1;i<=83;i++){
		power[i]=power[i-1]*2;
	}
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		cur.clear();
		for(int l=0;l<=m;l++){
			for(int r=m+1;r>=l;r--){
				
			}
			if(cur<f[l][l]){
				cur=f[l][l];
			}
		}
		ans=ans+cur;
	}
	ans.print();
}