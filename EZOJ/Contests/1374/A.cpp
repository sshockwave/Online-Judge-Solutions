#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const lint LINF=0x7f7f7f7f7f7f7f7f;
struct bint{
	const static int N=11,D=1000000;
	int d[N],ds;
	inline void clr(){
		memset(d+ds,0,(N-ds)<<2);
	}
	bint(){
		ds=0,clr();
	}
	inline friend bool operator < (const bint &a,const bint &b){
		if(a.ds!=b.ds){
			return a.ds<b.ds;
		}
		for(int i=a.ds-1;i>=0;i--){
			if(a.d[i]!=b.d[i]){
				return a.d[i]<b.d[i];
			}
		}
		return false;
	}
	inline void operator = (lint x){
		for(int &i=ds=0;x;i++,x/=D){
			d[i]=x%D;
		}
	}
	inline void operator = (const bint &x){
		ds=x.ds;
		memcpy(d,x.d,ds<<2);
		clr();
	}
	inline void operator += (lint x){
		clr();
		for(int i=0;x;apmax(ds,++i),x/=D){
			x+=d[i];
			d[i]=x%D;
		}
	}
	inline void operator += (bint &b){
		clr(),b.clr();
		apmax(ds,b.ds);
		int r=0;
		for(int i=0;i<ds;i++){
			d[i]+=b.d[i]+r;
			r=d[i]/D;
			d[i]-=r*D;
		}
		for(int &i=ds;r;i++){
			d[i]=r;
			r/=D;
			d[i]-=r*D;
		}
	}
	inline void operator *= (lint x){
		lint r=0;
		for(int i=0;i<ds;i++){
			lint tmp=d[i]*x+r;
			d[i]=tmp%D;
			r=tmp/D;
		}
		clr();
		for(int &i=ds;r;i++,r/=D){
			d[i]=r%D;
		}
	}
	inline void operator /= (int x){
		int r=0;
		for(int i=ds-1;i>=0;i--){
			r=r*D+d[i];
			d[i]=r/x;
			r-=d[i]*x;
		}
		for(;ds>0&&d[ds-1]==0;ds--);
	}
	inline void print(){
		if(ds==0){
			putchar('0');
			return;
		}
		printf("%d",d[ds-1]);
		for(int i=ds-2;i>=0;i--){
			printf("%06d",d[i]);
		}
	}
}ans,sum,tmp;
int main(){
#ifndef ONLINE_JUDGE
	freopen("rpg.in","r",stdin);
	freopen("rpg.out","w",stdout);
#endif
	lint n=next_num<lint>();
	lint k=next_num<lint>();
	if(n==0||k==0){
		puts("0");
		return 0;
	}
	k--;
	bool flag=true;
	for(lint l=1,r,val;l<=k;l=r+1){
		val=k/l;
		r=k/val;
		tmp=n+1;
		tmp*=val;
		if(flag){
			ans=tmp;
			flag=false;
		}else{
			tmp+=sum;
			apmin(ans,tmp);
		}
		tmp=r-l+1;
		tmp*=val*2;
		sum+=tmp;
	}
	apmin(ans,sum);
	ans*=n;
	ans/=2;
	ans.print();
	putchar('\n');
	return 0;
}
