#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define N 25
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
int pre[N];
int main(){
	int n=next_int(),sum=0,cnt=0;
	for(int i=0;i<n;i++){
		sum+=next_int();
		pre[i]=sum;
	}
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			for(int k=j+1;k<n;k++){
				for(int l=k+1;l<n;l++){
					if(pre[j]-pre[i]==pre[l]-pre[k]&&pre[k]-pre[j]==pre[n-1]-pre[l]+pre[i]){
						cnt++;
					}
				}
			}
		}
	}
	printf("%d",cnt);
}
