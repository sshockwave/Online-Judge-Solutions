#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=3010,M=6010;
namespace BIT{
	int c[M],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline lint sum(int x){
		lint a=0;
		for(;x;a+=c[x],x^=x&-x);
		return a;
	}
	inline lint ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}
char mat[N*2][M*2];
int r,c;
lint ans=0;
int tol[2][M],tor[2][M];
vector<int>tags[M];
inline void work(){
	memset(tol,0,sizeof(tol));
	memset(tor,0,sizeof(tor));
	bool g=false;
	for(int i=1;i<=r;i++,g^=1){
		int rr=i*2-1;
		if(i&1){
			int clen=(c+1)>>1;
			BIT::init(clen);
			for(int j=1;j<=clen;j++){
				tags[j].clear();
			}
			int ext=0;
			for(int j=1;j<=clen;j++){
				int cc=j*4-3;
				tol[g][j]=mat[rr-1][cc-1]=='\\'?tol[!g][j-1]+1:0;
				tor[g][j]=mat[rr-1][cc+1]=='/'?tor[!g][j]+1:0;
				ext=mat[rr][cc-1]=='-'?ext+1:0;
				ans+=BIT::ask(j-min(ext,tol[g][j]),j);
				BIT::add(j,1);
				tags[j+tor[g][j]].push_back(j);
				for(vector<int>::iterator it=tags[j].begin();it!=tags[j].end();++it){
					BIT::add(*it,-1);
				}
			}
		}else{
			int clen=c>>1;
			BIT::init(clen);
			for(int j=1;j<=clen;j++){
				tags[j].clear();
			}
			int ext=0;
			for(int j=1;j<=clen;j++){
				int cc=j*4-1; tol[g][j]=mat[rr-1][cc-1]=='\\'?tol[!g][j]+1:0;
				tor[g][j]=mat[rr-1][cc+1]=='/'?tor[!g][j+1]+1:0;
				ext=mat[rr][cc-1]=='-'?ext+1:0;
				ans+=BIT::ask(j-min(ext,tol[g][j]),j);
				BIT::add(j,1);
				tags[j+tor[g][j]].push_back(j);
				for(vector<int>::iterator it=tags[j].begin();it!=tags[j].end();++it){
					BIT::add(*it,-1);
				}
			}
		}
	}
}
int main(){/*
#ifndef ONLINE_JUDGE
freopen("triangles3.in","r",stdin);
freopen("triangles3.out","w",stdout);
#endif*/
	r=ni,c=ni;
	for(int i=1;i<=r*2-1;i++){
		cin.getline(mat[i]+1,M*2);
	}
	if((r&1)==0){
		r++;
	}
	work();
	for(int a=1,b=r*2-1;a<b;a++,b--){
		swap(mat[a],mat[b]);
	}
	for(int i=1;i<=r*2-1;i++){
		for(int j=1;j<=c*2-1;j++){
			if(mat[i][j]=='/'){
				mat[i][j]='\\';
			}else if(mat[i][j]=='\\'){
				mat[i][j]='/';
			}
		}
	}
	work();
	printf("%lld\n",ans);
	return 0;
}
