#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	// input a signed integer
	template <class I>
		inline void gi (I &x) {
			for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;
			for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
		}
	// print a signed integer
	template <class I>
		inline void print (I x) {
			if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
			while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
			while (qr) putc (qu[qr --]);
		}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
template<class T>inline T next_num(){
	T i=0;char c;
	using namespace io;
	while(!isdigit(c=gc())&&c!='-');
	bool neg=c=='-';
	neg?c=gc():0;
	while(i=i*10-'0'+c,isdigit(c=gc()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,sizeof(a[0])*n);}
const int N=3010;
int vis[N][N],tim=0;
int x0,y0,x1,y1;
inline bool valid(int i,int j){
	return i>=x0&&i<=x1&&j>=y0&&j<=y1&&((i&j)==0)&&vis[i][j]<tim;
}
void dfs(int x,int y){
	vis[x][y]=tim;
	const static int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
	for(int d=0;d<4;d++){
		const int tx=x+dx[d],ty=y+dy[d];
		if(valid(tx,ty)){
			dfs(tx,ty);
		}
	}
}
inline lint Main(){
	++tim;
	x0=ni-1,y0=ni-1,x1=ni-1,y1=ni-1;
	int ans=0;
	for(int i=x0;i<=x1;i++){
		for(int j=y0;j<=y1;j++){
			if(valid(i,j)){
				++ans;
				dfs(i,j);
			}
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("wall.in","r",stdin);
	freopen("wall.out","w",stdout);
#endif
	for(int tot=ni;tot--;io::print(Main()),io::putc('\n'));
	return 0;
}
