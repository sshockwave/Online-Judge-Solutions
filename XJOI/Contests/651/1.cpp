#include <iostream>
#include <cstdio>
#include <cstring>
#define P 100010
#define K 1000010
#define MOD 998244353
using namespace std;
int seq[K],*start[P],len[P],color[P],
	f[P],fac[P];
int main(){
	int p,q,l,k,c;
	scanf("%d%d%d",&p,&q,&l);
	for(int i=0,j=0;i<q;i++){
		scanf("%d%d",len+i,color+i);
		for(start[i]=seq+j;seq+j!=start[i]+len[i];j++){
			scanf("%d",seq+j);
		}
	}
	for(int i=1;i<=p;i++){
		f[i]=i;
		fac[i]=l;
	}
	for(int i=q-1;i>=0;i--){
		int *s=start[i];
		long long sum=0,mul=1;
		for(int j=0;j<len[i];j++){
			(sum+=f[s[j]]*mul)%=MOD;
			(mul*=fac[s[j]])%=MOD;
		}
		f[color[i]]=sum;
		fac[color[i]]=mul;
	}
	printf("%d",f[1]);
}
