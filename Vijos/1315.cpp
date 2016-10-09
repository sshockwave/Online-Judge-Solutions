#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct bigint{
	int digit[210],dtop;
	bigint(){
		dtop=0;
		memset(digit,0,sizeof(digit));
	}
	void maintain(){
		for(;digit[dtop];dtop++){
			digit[dtop+1]=digit[dtop]/10;
			digit[dtop]%=10;
		}
	}
	bigint operator +(bigint &b){
		bigint c;
		c.dtop=max(dtop,b.dtop);
		for(int i=0;i<c.dtop;i++){
			c.digit[i]+=digit[i]+b.digit[i];
			c.digit[i+1]+=c.digit[i]/10;
			c.digit[i]%=10;
		}
		c.maintain();
		return c;
	}
	bigint operator -(bigint &b){
		bigint c;
		c.dtop=max(dtop,b.dtop);
		for(int i=0;i<c.dtop;i++){
			c.digit[i]+=digit[i]-b.digit[i];
			if(c.digit[i]<0){
				c.digit[i+1]--;
				c.digit[i]+=10;
			}
		}
		for(;digit[dtop]==0&&dtop>0;dtop--);
		dtop++;
		return c;
	}
	void print(){
		for(int i=dtop-1;i>=0;i--){
			cout<<digit[i];
		}
	}
}c[520][520],ans;
int main(){
	int k,w,len;
	cin>>k>>w;
	c[0][0].digit[0]=1,c[0][0].dtop=1;
	for(int i=1;i<=(1<<k);i++){
		c[0][i].digit[0]=1,c[0][i].dtop=1;
		for(int j=1;j<=i;j++){
			c[j][i]=c[j][i-1]+c[j-1][i-1];
		}
	}
	for(int i=2;i<=w/k&&i<=(1<<k);i++){
		ans=ans+c[i][(1<<k)-1];
	}
	if(w%k&&w/k<(1<<k)){
		ans=ans+c[w/k+1][(1<<k)-1]-c[w/k+1][(1<<k)-(1<<(w%k))];
	}
	ans.print();
}
