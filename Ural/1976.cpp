#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline void apmin(int &a,lint b){
	if(a>b){
		a=b;
	}
}
const int N=1010,EPS=1e-5;
char s[N];
int dis[N][N],lpos[N];
bool mat[N][N];
inline lint sqr(int x){
	return (lint)x*x;
}
inline double calx(int i,int j){
	return (double)(sqr(i)-sqr(j)+sqr(lpos[i])-sqr(lpos[j]))/(2*(i-j));
}
inline void getdis(int *dis,int n){
	static int *stk=new int[N];
	static double *dstk=new double[N];
	int stop=0;
	stk[++stop]=1;
	for(int i=2;i<=n;i++){
		for(;stop>1&&calx(stk[stop],i)<dstk[stop-1];stop--);
		dstk[stop]=calx(stk[stop],i);
		stk[++stop]=i;
	}
	for(int i=1,p=1;i<=n;i++){
		for(;p<stop&&i>dstk[p]+EPS;p++);
		apmin(dis[i],sqr(i-stk[p])+sqr(lpos[stk[p]]));
	}
}
inline void renew(bool *mat,int n){
	for(int i=1;i<=n;i++){
		if(mat[i]){
			lpos[i]=0;
		}else{
			lpos[i]++;
		}
	}
}
int main(){
	memset(mat,0,sizeof(mat));
	memset(dis,127,sizeof(dis));
	int n=ni(),m=ni();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		for(int j=1;j<=m;j++){
			if(s[j]=='1'){
				mat[i][j]=true;
				dis[i][j]=0;
			}
		}
	}
	memset(lpos,127,sizeof(lpos));
	for(int i=1;i<=n;i++){
		renew(mat[i],m);
		getdis(dis[i],m);
	}
	memset(lpos,127,sizeof(lpos));
	for(int i=n;i>=1;i--){
		renew(mat[i],m);
		getdis(dis[i],m);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%d",dis[i][j]);
			putchar(" \n"[j==m]);
		}
	}
}
