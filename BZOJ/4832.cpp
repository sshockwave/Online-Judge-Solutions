#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int K=51,B=31,N=8;
double f[K][B][N][N][N];
int main(){
	memset(f,0,sizeof(f));
	for(int k=1;k<K;k++){
		for(int l=0;l<B;l++){
			for(int a=0;a<N;a++){
				for(int b=0,_=N-a;b<_;b++){
					for(int c=0,_=N-a-b;c<_;c++){
						if(a+b+c==7){
							if(l){
								
							}else{
								
							}
						}else{
							
						}
					}
				}
			}
		}
	}
	for(int tot=ni;tot--;){
		int k=ni,a=ni,b=ni,c=ni;
		printf("%lf\n",f[k][a][b][c]);
	}
}
