#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <bitset>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int MOD=123456789,N=610,D=1810;
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,x=mul(x,x)){
		if(n&1){
			ret=mul(ret,x);
		}
	}
	return ret;
}
int n,m,dx[]={2,2,1,-1,-2,-2,-1,1},dy[]={1,-1,-2,-2,-1,1,2,2};
bitset<D>stat[N][N],eqn[D];
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
inline int gauss(int n){
	int cnt=0;
	for(int i=1,j;i<=n;i++){
		for(j=i;j<=n;j++){
			if(eqn[j][i]){
				break;
			}
		}
		if(j>n){
			cnt++;
			continue;
		}
		if(i!=j){
			swap(eqn[i],eqn[j]);
		}
		for(j=i+1;j<=n;j++){
			if(eqn[j][i]){
				eqn[j]^=eqn[i];
			}
		}
	}
	return cnt;
}
int main(){
	n=ni(),m=ni();
	int xid=0;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=m;j++){
			stat[i][j].set(++xid);
		}
	}
	for(int i=3;i<=n;i++){
		stat[i][1].set(++xid);
		for(int j=2;j<=m;j++){
			stat[i][j]=stat[i-2][j-1];
			for(int d=1;d<8;d++){
				int tx=i-2+dx[d],ty=j-1+dy[d];
				if(valid(tx,ty)){
					stat[i][j]^=stat[tx][ty];
				}
			}
		}
	}
	xid=0;
	for(int i=1;i<=n;i++){
		for(int j=(i<=n-2)?m:1;j<=m;j++){
			eqn[++xid]=stat[i][j];
			for(int d=0;d<8;d++){
				int tx=i+dx[d],ty=j+dy[d];
				if(valid(tx,ty)){
					eqn[xid]^=stat[tx][ty];
				}
			}
		}
	}
	printf("%d\n",fpow(2,gauss(xid)));
}
