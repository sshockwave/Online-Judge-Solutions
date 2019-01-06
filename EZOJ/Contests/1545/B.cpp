#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef vector<lint>vi;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],const T b[],int n){memcpy(a,b,n*sizeof(T));}
const int M=210;
struct Pt{
	int x,y;
}pt[M];
int n,m;
namespace solve1{
	const int N=1050;
	vi gaplst;
	struct Info{
		lint cnt;
		lint lgap,rgap;
		inline friend Info operator + (const Info &a,const Info &b){
			if(a.cnt&&b.cnt&&(a.rgap+b.lgap>0)){
				gaplst.push_back(a.rgap+b.lgap);
			}
			return (Info){a.cnt+b.cnt,a.lgap+(a.cnt==0?b.lgap:0),(b.cnt==0?a.rgap:0)+b.rgap};
		}
	};
	int mat[N][N];
	Info solve(int x0,int y0,int n){
		if(n==0){
			return mat[x0][y0]?(Info){1,0,0}:(Info){0,1,1};
		}
		--n;
		int sn=1<<n;
		return solve(x0,y0,n)+solve(x0,y0|sn,n)+solve(x0|sn,y0,n)+solve(x0|sn,y0|sn,n);
	}
	inline void draw(Pt a,Pt b){
		if(a.x!=b.x){
			assert(a.y==b.y);
			++mat[a.x][a.y],--mat[b.x][b.y];
		}
	}
	void putmat(){
		int sn=1<<n;
		for(int j=sn-1;j>=0;j--){
			for(int i=0;i<sn;i++){
				cout<<mat[i][j];
			}
			cout<<endl;
		}
	}
	inline int main(){
		memset(mat,0,sizeof(mat));
		for(int i=2;i<=m;i++){
			draw(pt[i-1],pt[i]);
		}
		draw(pt[m],pt[1]);
		int sn=1<<n;
		for(int i=1;i<sn;i++){
			for(int j=0;j<sn;j++){
				mat[i][j]+=mat[i-1][j];
			}
		}
		for(int i=0;i<sn;i++){
			for(int j=1;j<sn;j++){
				mat[i][j]+=mat[i][j-1];
			}
		}
		Info tmp=solve(0,0,n);
		sort(gaplst.begin(),gaplst.end());
		for(int i=1;i<(int)gaplst.size();i++){
			gaplst[i]+=gaplst[i-1];
		}
		for(int tot=ni;tot--;){
			int t=ni-1;
			lint ans=tmp.cnt;
			if(t<(int)gaplst.size()){
				ans+=gaplst[gaplst.size()-t-1];
			}
			printf("%lld\n",ans);
		}
		return 0;
	}
}
namespace solve2{
	lint ans=0;
	inline void draw(Pt a,Pt b){
		if(a.x!=b.x){
			assert(a.y==b.y);
			ans+=(lint)((1<<n)-a.y)*(b.x-a.x);
		}
	}
	inline int main(){
		for(int i=2;i<=m;i++){
			draw(pt[i-1],pt[i]);
		}
		draw(pt[m],pt[1]);
		for(int tot=ni;tot--;){
			printf("%lld\n",ans);
		}
		return 0;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	n=ni,m=ni;
	for(int i=1;i<=m;i++){
		pt[i]=(Pt){ni,ni};
	}
	if(n<=10){
		return solve1::main();
	}else{
		return solve2::main();
	}
	return 0;
}
