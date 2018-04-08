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
const int SH=20,N=1<<SH;
void solve(lint p[],lint q[],int n){
	if(n==1)return;
	int half=n>>1;
	lint ax,by,sum;
	{
		lint a=0,b=p[0],y=p[half];
		lint x=q[0]-y;
		ax=a+x,by=b+y;
		sum=ax+by;
		p[0]=a,p[half]=b;
		q[0]=x,q[half]=y;
	}
	for(int i=1;i<half;i++){
		lint &a=p[i],&b=p[i+half];
		lint &x=q[i],&y=q[i+half];
		lint ab=p[i],ay=p[i+half];
		lint xy=q[i],bx=q[i+half];
		a=((sum<<1)-bx-by-xy)>>1;
		b=((sum<<1)-ax-ay-xy)>>1;
		x=((sum<<1)-ay-by-ab)>>1;
		y=((sum<<1)-ax-bx-ab)>>1;
		assert(ab==a+b);
		assert(xy==x+y);
		assert(ay==a+y);
		assert(bx==b+x);
	}
	solve(p,q,half);
	solve(p+half,q+half,half);
}
lint p[N],q[N];
inline void Main(){
	int sh=ni,n=1<<sh;
	for(int i=0;i<n;i++){
		q[i^(n-1)]=next_num<lint>();
	}
	for(int i=0;i<n;i++){
		p[i]=q[0]-q[i];
	}
	solve(p,q,n);
	for(int i=0;i<n;i++){
		printf(" %lld",q[i]);
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("it.in","r",stdin);
	freopen("it.out","w",stdout);
#endif
	for(int i=1,tot=ni;i<=tot;i++){
		printf("Case #%d:",i);
		Main();
	}
	return 0;
}
