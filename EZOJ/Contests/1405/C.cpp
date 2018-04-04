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
	bool f=c=='-'&&(c=getchar());
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return f?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
lint p,ppw,O;
inline lint fmul(lint x,lint y,lint O=::O){
	lint a=0;
	for(;y;y>>=1,x=(x<<1)%O){
		if(y&1){
			a=(a+x)%O;
		}
	}
	return a;
}
inline lint fpow(lint x,lint n,lint O=::O){
	lint a=1;
	for(;n;n>>=1,x=fmul(x,x,O)){
		if(n&1){
			a=fmul(a,x,O);
		}
	}
	return a;
}
lint ans[60],mo[60];
int main(){
#ifndef ONLINE_JUDGE
	freopen("constitution.in","r",stdin);
	freopen("constitution.out","w",stdout);
#endif
	p=next_num<lint>(),ppw=ni,O=1;
	for(int i=1;i<=ppw;i++){
		O*=p;
	}
	lint n=next_num<lint>();
	memset(ans,0,sizeof(ans));
	int mxe;
	lint t=n/p;
	mo[0]=O;
	for(int &i=mxe=1;t;i++,t/=p){
		mo[i]=mo[i-1]*p;
	}
	for(int i=1;i<=n;i++){
		int e=0;
		for(t=i;t%p==0;t/=p,e++);
		ans[e]=(ans[e]+fpow(t,mo[e]/p*(p-1)-1,mo[e]))%mo[e];
	}
	lint rans=0;
	for(int i=mxe-1;i>=0;i--){
		rans=(rans+ans[i])%mo[i];
		if(i){
			assert(rans%p==0);
			rans/=p;
		}
	}
	rans=((n<<1)%O+O-rans)%O;
	printf("%lld\n",rans);
	return 0;
}
