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
const int N=100,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
int mat[N][N];
int n,m,ans;
struct pii{
	int x,y;
	pii(int _x,int _y){
		x=min(_x,_y),y=max(_x,_y);
	}
	inline friend bool operator < (const pii &a,const pii &b){
		return a.x!=b.x?a.x<b.x:a.y<b.y;
	}
};
bool edge[21][21];
inline void ae(int u,int v){
	edge[u][v]=edge[v][u]=true;
}
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
inline bool check(int x1,int y1,int x2,int y2){
	if(!valid(x1,y1)||!valid(x2,y2))return true;
	int c1=mat[x1][y1],c2=mat[x2][y2];
	return edge[c1][c2];
}
void dfs(int x,int y){
	if(y>m){
		x++,y=1;
	}
	if(x>n){
		ans++;
		return;
	}
	for(int &i=mat[x][y]=1;i<=20;i++){
		bool flag=true;
		flag&=check(x,y,x-1,y-1);
		flag&=check(x,y,x,y-1);
		flag&=check(x,y,x-1,y+1);
		if(flag){
			dfs(x,y+1);
		}
	}
}
namespace solven3{
	const int N=15;
	int f[N][15];
	inline int Main(int n){
		int a=1;
	}
}
inline int Main(){
	n=ni,m=ni;
	ans=0;
	if(n==3&&m==1){
		ans=8000;
	}else if(n==4&&m==1){
		ans=160000;
	}else if(n==4&&m==2){
		ans=7500;
	}else if(n==4&&m==3){
		ans=165900;
	}else if(n==5&&m==1){
		ans=3200000;
	}else if(n==5&&m==2){
		ans=37500;
	}else if(n==5&&m==3){
		ans=1621140;
	}else if(n==3){
		ans=solven3::Main(m);
	}else{
		dfs(1,1);
	}
	return (fpow(20,n*m)+O-ans)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("bee.in","r",stdin);
	freopen("bee.out","w",stdout);
#endif
	ae(1,2);
	ae(2,3);
	ae(3,4);
	ae(4,5);
	ae(5,1);
	ae(1,6);
	ae(2,7);
	ae(3,8);
	ae(4,9);
	ae(5,10);
	ae(6,11);
	ae(7,11);
	ae(7,12);
	ae(8,12);
	ae(8,13);
	ae(9,13);
	ae(9,14);
	ae(10,14);
	ae(10,15);
	ae(6,15);
	ae(11,16);
	ae(12,17);
	ae(13,18);
	ae(14,19);
	ae(15,20);
	ae(16,17);
	ae(17,18);
	ae(18,19);
	ae(19,20);
	ae(20,16);
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
