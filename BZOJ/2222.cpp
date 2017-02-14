#include <iostream>
#include <cstdio>
#include <cstring>
#define N 310
#define INF 0x7f7f7f7f
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int next_int(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	for(;is_num(c);i=i*10-'0'+c,c=getchar());
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
int f[N][N][N];
int main(){
	int n=next_int();
	for(int i=1;i<=n;i++){
		f[i][i][i]=0;
	}
	for(int i=1;i<n;i++){
		f[i][i][i+1]=f[i][i+1][i+1]=1;
	}
	for(int i=3;i<=n;i++){//length
		for(int l=1,r=i;r<=n;l++,r++){//left
			for(int j=l;j<=r;j++){
				int &F=f[l][j][r];
				F=INF;
				for(int k=l;k<j;k++){
					apmin(F,max(f[l][k][j],f[k][j][r]));
				}
				for(int k=j+1;k<=r;k++){
					apmin(F,max(f[l][j][k],f[j][k][r]));
				}
				F++;
				cout<<"f["<<l<<"]["<<j<<"]["<<r<<"]="<<F<<endl;
			}
		}
	}
	
}
