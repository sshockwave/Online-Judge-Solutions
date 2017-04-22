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
int main(){
	int n=ni,sum=0;
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
	}
	for(int i=1;i<=n;i++){
		sum+=ni;
	}
	for(int tot=ni;tot--;){
		if(ni==1){
			int x=ni,y=ni,t=ni;
			sum+=t;
		}else{
			int x=ni,y=ni;
			printf("%d\n",sum);
		}
	}
}
