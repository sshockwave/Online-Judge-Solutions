#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 11
#define INF 0x7f7f7f7f
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline int abs(int a){
	return a>0?a:-a;
}
int f[N][N],_g[N],digit[N];
inline int cal(int n){
	if(n==0){
		return 1;
	}
	int ret,dtop=0;
	for(dtop=0;n;dtop++,n/=10){
		digit[dtop]=n%10;
	}
	ret=_g[dtop-1];
	for(int i=dtop-1,last=INF;i>=0;i--){
		for(int j=(i==dtop-1)?1:0;j<digit[i]+(!i);j++){
			if(abs(j-last)>=2){
				ret+=f[i+1][j];
			}
		}
		if(abs(digit[i]-last)<2){
			break;
		}
		last=digit[i];
	}
	return ret;
}
int main(){
	for(int i=0;i<10;i++){
		f[1][i]=1;
	}
	_g[0]=1;
	_g[1]=10;
	for(int i=2;i<N;i++){
		_g[i]=_g[i-1];
		for(int j=0;j<10;j++){
			f[i][j]=0;
			for(int k=0;k<10;k++){
				if(abs(j-k)>=2){
					f[i][j]+=f[i-1][k];
				}
			}
			if(j){
				_g[i]+=f[i][j];
			}
		}
	}
	int a=cal(ni()-1),b=cal(ni());
	printf("%d",b-a);
}
