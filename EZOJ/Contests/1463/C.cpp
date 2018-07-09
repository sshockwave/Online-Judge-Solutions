#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
namespace IO {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
	int f, qr=0;
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush(){
		fwrite(obuf,1,oS-obuf,stdout);
		oS=obuf;
	}
	inline void putc(char x){
		*oS++=x;
		if(oS==oT)flush();
	}
	template<class I>inline void print(I x){
		if(x){
			for(;x;qu[++qr]=x%10+'0',x/=10);
			for(;qr;putc(qu[qr--]));
		}else putc('0');
	}
	struct Flusher{~Flusher(){flush();}}__flusher__;
}
template<class T>inline T next_num(){
	T i=0;char c;
	using namespace IO;
	for(;!isdigit(c=gc())&&c!='-';);
	while(i=i*10-'0'+c,isdigit(c=gc()));
	return i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
inline bool mat(const int x,const int y){
	return (x&y)==0;
}
void calc(const int r,const int x,int &cnt_nd,int &cnt_cm){//excludes r
	if(r==0)return cnt_nd=cnt_cm=0,void();
	calc(r>>1,x>>1,cnt_nd,cnt_cm);
	if(x&1){
		cnt_cm=cnt_nd;
	}else{
		cnt_nd<<=1;
	}
	if(r&1){
		if(mat(x,r-1)){
			++cnt_nd;
			if(r==1||!mat(x,r-2)){
				++cnt_cm;
			}
		}
	}
	assert(cnt_nd<=r);
}
inline int calc(int x,int l,int r){
	int ans=0;
	int cnt_nd,cnt_cm;
	calc(r+1,x,cnt_nd,cnt_cm);
	ans+=cnt_cm;
	if(l){
		calc(l,x,cnt_nd,cnt_cm);
		ans-=cnt_cm;
		ans+=mat(x,l-1)&&mat(x,l);
	}
	return ans;
}
inline int Main(){
	const int x0=ni-1,y0=ni-1,x1=ni-1,y1=ni-1;
	return calc(x0,y0,y1)+calc(y0,x0,x1)-mat(x0,y0);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("wall.in","r",stdin);
	freopen("wall.out","w",stdout);
#endif
	for(int tot=ni;tot--;IO::print(Main()),IO::putc('\n'));
	return 0;
}
