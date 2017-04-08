#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <vector>
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
inline long long nl(){
	long long i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int K=65;
const lint N=1000000000000000010ll;
vector<lint>f[K];
inline lint solve2(lint n){
	lint i=(sqrt(n*8+1)-1)/2;
	for(;i*(i+1)<n*2;i++);
	return i;
}
inline int solve(lint n,vector<lint>&f){
	int l=0,r=f.size()-1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(f[mid]<n){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	return l;
}
int main(){
	f[3].push_back(0);
	for(int i=1;f[3].back()<N;i++){
		f[3].push_back(f[3][i-1]+(lint)i*(i-1)/2+1);
	}
	for(int i=4;i<K;i++){
		f[i].push_back(0);
		for(int j=1;f[i].back()<N;j++){
			f[i].push_back(f[i][j-1]+f[i-1][j-1]+1);
		}
	}
	lint n;
	int k;
	for(int tot=ni();tot--;){
		n=nl(),k=ni();
		if(n==0){
			puts("0");
		}else if(k==1){
			printf("%lld\n",n);
		}else if(k==2){
			printf("%lld\n",solve2(n));
		}else{
			printf("%d\n",solve(n,f[k]));
		}
	}
}
