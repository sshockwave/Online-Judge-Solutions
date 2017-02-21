#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100010
#define I 1000010
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
int amt[I],query[N],ans[I];
int main(){
	memset(amt,0,sizeof(amt));
	int n=next_int(),mx=0;
	for(int i=1;i<=n;i++){
		query[i]=next_int();
		amt[query[i]]++;
		apmax(mx,query[i]);
	}
	memset(ans,0,sizeof(ans));
	for(int i=1;i<=mx;i++){
		if(amt[i]){
			for(int j=i;j<=mx;j+=i){
				ans[j]+=amt[i];
			}
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[query[i]]-1);
	}
}
