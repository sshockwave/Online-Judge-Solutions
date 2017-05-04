#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int N=12,MOD=1000000007,W=10010;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
inline int sub(int a,int b){
	return add(a,MOD-b);
}
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
struct Rectangle{
	int x1,y1,x2,y2,v,size;
	inline bool contain(Rectangle b){
		return b.x1>=x1&&b.y1>=y1&&b.x2<=x2&&b.y2<=y2;
	}
	inline void getsize(){
		size=(x2-x1+1)*(y2-y1+1);
	}
}rec[N],pool[N*N*4];
bool xsplit[W],ysplit[W],con[N*N*4][N];
int xque[N*2],yque[N*2],f[N*N*4][1<<N];
inline int add(bool *split,int *que){
	int qtail=0;
	for(int i=0;i<W;i++){
		if(split[i]){
			que[qtail++]=i;
		}
	}
	return qtail;
}
int main(){
	for(int tot=ni(),h,w,m,n;tot--;){
		memset(xsplit,0,sizeof(xsplit));
		memset(ysplit,0,sizeof(ysplit));
		h=ni(),w=ni(),m=ni(),n=ni();
		xsplit[0]=xsplit[h]=true;
		ysplit[0]=ysplit[w]=true;
		for(int i=0;i<n;i++){
			rec[i]=(Rectangle){ni(),ni(),ni(),ni(),ni()};
			rec[i].getsize();
			xsplit[rec[i].x1-1]=xsplit[rec[i].x2]=true;
			ysplit[rec[i].y1-1]=ysplit[rec[i].y2]=true;
		}
		int x=add(xsplit,xque),y=add(ysplit,yque),ptop=0;
		memset(con,0,sizeof(con));
		for(int i=1;i<x;i++){
			for(int j=1;j<y;j++){
				pool[++ptop]=(Rectangle){xque[i-1]+1,yque[j-1]+1,xque[i],yque[j],m};
				pool[ptop].getsize();
				for(int k=0;k<n;k++){
					if(con[ptop][k]=rec[k].contain(pool[ptop])){
						apmin(pool[ptop].v,rec[k].v);
					}
				}
			}
		}
		memset(f,0,sizeof(f));
		f[0][0]=1;
		for(int i=1,pw=1<<n;i<=ptop;i++){
			int *F=f[i-1],*NF=f[i];
			int mor=fpow(pool[i].v,pool[i].size);
			int les=fpow(pool[i].v-1,pool[i].size);
			int g=sub(mor,les),to=0;
			for(int j=0;j<n;j++){
				if(con[i][j]&&rec[j].v==pool[i].v){
					to|=1<<j;
				}
			}
			for(int j=0;j<pw;j++){
				apadd(NF[j],mul(F[j],les));
				apadd(NF[j|to],mul(F[j],g));
			}
		}
		printf("%d\n",f[ptop][(1<<n)-1]);
	}
}
