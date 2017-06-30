#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
#define cout cerr
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=500010,D=30,SHIFT=32;
ull AND=(1ll<<SHIFT)-1;
struct bigint{
	int dtop;
	ull a[D];
	inline void clr(){
		memset(a,0,sizeof(a));
		dtop=0;
	}
	inline void carry(){
		for(int i=0;i<dtop;i++){
			a[i+1]+=a[i]>>SHIFT;
			a[i]&=AND;
		}
		if(a[dtop]){
			dtop++;
		}
	}
	inline void operator *= (const int &b){
		for(int i=0;i<dtop;i++){
			a[i]*=b;
		}
		carry();
	}
	inline friend bigint operator + (const bigint &a,const bigint &b){
		bigint c;
		c.clr();
		c.dtop=max(a.dtop,b.dtop);
		for(int i=0;i<c.dtop;i++){
			c.a[i]=a.a[i]+b.a[i];
		}
		c.carry();
		return c;
	}
	inline bool operator [] (int x){
		return (a[x>>5]>>(x&31))&1;
	}
}pw,tmp;
queue<bigint>pool[3],*q=pool,*nq=q+1,*tq=nq+1;
int main(){
#ifndef ONLINE_JUDGE
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
#endif
	int n=ni,cnt=0;
	if(n==0){
		puts("0");
		return 0;
	}
	pw.clr(),q->push(pw),pw.dtop=1,pw.a[0]=1;
	for(int i=0;;pw*=10,i++,swap(q,nq)){
		for(;!q->empty();q->pop()){
			if(q->front()[i]==0){
				tq->push(q->front());
				nq->push(q->front());
			}
		}
		for(;!tq->empty();tq->pop()){
			nq->push(tq->front()+pw);
			cnt++;
			if(cnt==n){
				tmp=tq->front()+pw;
				for(int k=i;k>=0;k--){
					putchar('0'+tmp[k]);
				}
				putchar('\n');
				return 0;
			}
		}
	}
}
