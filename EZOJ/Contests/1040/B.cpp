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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=50;
struct bint{
	static const int D=10000,MOD=100000;
	int d[D],ds;
	bint(){
		ds=0;
		memset(d,0,sizeof(d));
	}
	inline void carry(){
		for(int i=0;i<ds;i++){
			d[i+1]+=d[i]/MOD,d[i]%=MOD;
		}
		for(;d[ds];ds++){
			d[ds+1]+=d[ds]/MOD,d[ds]%=MOD;
		}
	}
	inline void operator += (const bint &b){
		apmax(ds,b.ds);
		for(int i=0;i<ds;i++){
			d[i]+=b.d[i];
		}
		carry();
	}
	inline void operator *= (int b){
		for(int i=0;i<ds;i++){
			d[i]*=b;
		}
		carry();
	}
	inline void operator /= (int b){
		for(int i=ds-1,r=0;i>=0;i--){
			r=r*MOD+d[i];
			d[i]=r/b,r%=b;
		}
		for(;ds&&d[ds];ds--);
	}
	inline void print(){
		printf("%d",d[max(ds-1,0)]);
		for(int i=ds-2;i>=0;i--){
			printf("%05d",d[i]);
		}
		putchar('\n');
	}
}ans,cur;
int main(){
#ifndef ONLINE_JUDGE
	freopen("calc.in","r",stdin);
	freopen("calc.out","w",stdout);
#endif
	int n=ni;
	cur.ds=1,cur.d[0]=1;
	for(int i=1;i<n;i++){
		cur*=n;
	}
	for(int k=1;k<=n;k++){
		if(k>=3){
			ans+=cur;
		}
		cur/=n;
		cur*=n-k;
	}
	ans/=2;
	ans.print();
	return 0;
}
