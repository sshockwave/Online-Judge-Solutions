#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <ctime>
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
inline long long nl(){
	long long i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
const int INF=0x7f7f7f7f,N=1010,K=65,T=400010;
long long cal(int k,int t){//ask how many n meets f[k][n]<=t
	if(k==0||t==0){
		return 1;
	}
	if(k==1){
		return t+1;
	}
	return cal(k,t-1)+cal(k-1,t-1);
}
int solve2(long long n){
	long long ans=(sqrt(n*8+1)-1)/2;
	for(;ans*(ans+1)/2<n;ans++);
	return ans;
}
int f[K][N];
long long C[K][T];
int solveall(long long n,int k){
	int l=0,r=T-1,mid;
	while(l<r){
		mid=(l+r)>>1;//t=mid
		if(C[k][mid]>0&&C[k][mid]<=n){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	return l;
}
int main(){
	//t=0
	memset(C,0,sizeof(C));
	for(int k=0;k<K;k++){
		C[k][0]=1;
	}
	for(int t=1;t<T;t++){
		C[0][t]=1;
		C[1][t]=t+1;
		for(int k=2;k<K;k++){
			C[k][t]=C[k-1][t-1]+C[k][t-1];
		}
	}
	memset(f[0],127,sizeof(f[0]));
	f[0][0]=0;
	for(int k=1;k<K;k++){
		f[k][0]=0;
		for(int i=1;i<N;i++){
			f[k][i]=i-1;
			int p=1;
			for(int j=1;j<=i;j++){
				if(f[k][i]>max(f[k-1][j-1],f[k][i-j])){
					p=j;
				}
				apmin(f[k][i],max(f[k-1][j-1],f[k][i-j]));
			}
			f[k][i]++;
		}
	}
	for(int tot=ni();tot--;){
		long long n=nl();
		int k=ni();
		if(n==0){
			puts("0");
		}else if(k==1){
			printf("%lld\n",n);
		}else if(n<=1000){
			printf("%d\n",f[k][n]);
		}else if(k==2){
			printf("%d\n",solve2(n));
		}else{
			printf("%d\n",solveall(n,k));
		}
	}
}
