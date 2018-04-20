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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
namespace lb{
	const int D=62;
	lint a[D];
	int alltop=0;
	inline void init(){
		memset(a,0,sizeof(a));
		alltop=0;
	}
	inline lint gans(){
		int cnt=0;
		for(int i=0;i<D;i++){
			cnt+=a[i]!=0;
		}
		return 1ll<<cnt;
	}
	inline void fmt(){
		for(int &i=alltop;i<D&&a[i];i++);
	}
	inline void ins(lint x,int hb=D-1){
		for(int i=hb;x&&i>=alltop;i--){
			if((x>>i)&1){
				if(a[i]){
					x^=a[i];
				}else{
					a[i]=x;
					fmt();
					return;
				}
			}
		}
	}
	void ins(lint l,lint r,lint xsum=0,int hb=D-1){
		assert(l<=r);
		if(l==0&&r+1==((r+1)&-(r+1))){
			for(int &i=alltop;i<D&&((r>>i)&1);a[i++]=r);
			return;
		}
		if(l==r)return ins(l^xsum,hb);
		for(int i=hb;i>=alltop;i--){
			if((r>>i)^(l>>i)){
				ins(1ll<<i,r,xsum,i);
				ins(l,(1ll<<i)-1,xsum,i);
				return;
			}else{
				if((xsum>>i)&1){
					l^=1ll<<i,r^=1ll<<i,xsum^=1ll<<i;
				}
				if((l>>i)&1){
					if(a[i]){
						xsum^=a[i];
					}else{
						a[i]=l^xsum;
						fmt();
						ins(l+1,r,xsum,i);
						return;
					}
				}
				if((xsum>>i)&1){
					l^=1ll<<i,r^=1ll<<i,xsum^=1ll<<i;
				}
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("manger.in","r",stdin);
	freopen("manger.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		lint l=next_num<lint>(),r=next_num<lint>();
		lb::init();
		lb::ins(l,r);
		printf("%lld\n",lb::gans());
	}
	return 0;
}
