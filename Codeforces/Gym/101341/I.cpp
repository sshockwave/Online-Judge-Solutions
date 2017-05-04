#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <ctime>
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
const int N=1010,MOD=1000000007;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
int n;
struct Matrix{
	int mat[N][N];
	inline void input(){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				mat[i][j]=ni();
			}
		}
	}
	
}a,b,c;
int vec1[N],vec2[N];
inline int lrand(){
	return (rand()<<15)|rand();
}
inline void genvec(){
	for(int i=0;i<n;i++){
		vec1[i]=vec2[i]=lrand()%MOD;
	}
}
inline void vectimes(const Matrix &m,int *vec){
	static int *tmp=new int[N];
	memcpy(tmp,vec,n<<2);
	memset(vec,0,n<<2);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			apadd(vec[i],mul(m.mat[i][j],tmp[j]));
		}
	}
}
inline bool check(){
	genvec();
	vectimes(b,vec1),vectimes(a,vec1);
	vectimes(c,vec2);
	for(int i=0;i<n;i++){
		if(vec1[i]!=vec2[i]){
			return false;
		}
	}
	return true;
}
int main(){
	srand(time(NULL));
	rand();
	n=ni();
	a.input(),b.input(),c.input();
	for(int i=0;i<10;i++){
		if(!check()){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
}
