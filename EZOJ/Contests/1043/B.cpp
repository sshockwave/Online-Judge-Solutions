#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
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
const int T=20,MOD=100000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
struct Mat{
	const static int N=16;
	int a[N][N];
	inline friend Mat operator * (const Mat &a,const Mat &b){
		Mat c;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				lint sum=0;
				for(int k=0;k<N;k++){
					sum+=mul(a.a[i][k],b.a[k][j]);
				}
				c.a[i][j]=sum%MOD;
			}
		}
		return c;
	}
	inline void operator ^= (lint n){
		static Mat tmp;
		if(n==0){
			tmp=*this;
			for(int i=0;i<N;i++){
				for(int j=0;j<N;j++){
					a[i][j]=i==j;
				}
			}
			return;
		}
		*this^=n>>1;
		*this=*this**this;
		if(n&1){
			*this=*this*tmp;
		}
	}
	inline friend ostream & operator << (ostream & out,const Mat &b){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				out<<b.a[i][j]<<" ";
			}
			out<<endl;
		}
		return out;
	}
}trans;
int dx[4]={1,0,MOD-1,0},dy[4]={0,1,0,MOD-1};
inline int Main(){
	lint tot=nl;
	int S=ni,L=ni,R=ni;
	memset(&trans,0,sizeof(trans));
	for(int d=0;d<4;d++){
		int c=d<<2,x=c|1,y=c|2,xy=c|3;
		//go ahead
		trans.a[c][c]=S;
		trans.a[x][c]=mul(S,dx[d]);
		trans.a[y][c]=mul(S,dy[d]);
		trans.a[xy][c]=mul(S,mul(dx[d],dy[d]));
		trans.a[x][x]=S;
		trans.a[xy][x]=mul(S,dy[d]);
		trans.a[y][y]=S;
		trans.a[xy][y]=mul(S,dx[d]);
		trans.a[xy][xy]=S;
		//turn left
		trans.a[((d+1)&3)<<2][c]=L;
		trans.a[(((d+1)&3)<<2)|1][x]=L;
		trans.a[(((d+1)&3)<<2)|2][y]=L;
		trans.a[(((d+1)&3)<<2)|3][xy]=L;
		//turn right
		trans.a[((d+3)&3)<<2][c]=R;
		trans.a[(((d+3)&3)<<2)|1][x]=R;
		trans.a[(((d+3)&3)<<2)|2][y]=R;
		trans.a[(((d+3)&3)<<2)|3][xy]=R;
	}
	trans^=tot;
	lint ans=0;
	for(int i=3;i<16;i+=4){
		ans+=trans.a[i][0];
	}
	return ans%MOD;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("fox.in","r",stdin);
	freopen("fox.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
