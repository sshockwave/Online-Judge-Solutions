#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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
const int N=100010;
long long f[N][2][2];//f[i][len[i]-len[i-1]][len[i+1]-len[i]]
char s[N];
int bef[N],nf[N];
inline void pr(int i,int j,int k,int w){
	cout<<"("<<i<<","<<i-1<<")="<<i-1<<",("<<i<<","<<i<<")="<<i-1+j<<",("<<i<<","<<i+1<<")="<<i-1+j+k<<"     "<<w<<endl;
}
inline void dp(int i,char c,long long delta){
	for(int t=i;t<=i+2;t++){
		if(c==s[t]){
			nf[t]=bef[t-1]+1;
		}else{
			nf[t]=max(nf[t-1],bef[t]);
		}
	}
	if(nf[i]<i){
		return;
	}
	cout<<"\tChar=";
	if(c){
		cout<<c;
	}else{
		cout<<"E";
	}
	cout<<" Add to:";
	pr(i+1,nf[i+1]-nf[i],nf[i+2]-nf[i+1],delta);
	f[i+1][nf[i+1]-nf[i]][nf[i+2]-nf[i+1]]+=delta;
}
int main(){
//	freopen("B.in","r",stdin);
	int n=ni(),m=ni();
	if(n==1){
		printf("%d",m-1);
		return 0;
	}
	scanf("%s",s+1);
	if(s[1]==s[2]){
		f[1][0][0]=m-1;
		f[1][0][1]=0;
		f[1][1][0]=1;
		f[1][1][1]=0;
	}else{
		f[1][0][0]=m-2;
		f[1][0][1]=1;
		f[1][1][0]=1;
		f[1][1][1]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				if(f[i][j][k]==0){
					continue;
				}
				pr(i,j,k,f[i][j][k]);
				bef[i-1]=i-1,bef[i]=i-1+j,bef[i+1]=i-1+j+k,bef[i+2]=0;
				nf[i-1]=0;
				if(s[i-1]){
					dp(i,s[i-1],f[i][j][k]);
				}
				if(s[i]!=s[i-1]){
					dp(i,s[i],f[i][j][k]);
				}
				if(s[i+1]!=s[i]&&s[i+1]!=s[i-1]){
					dp(i,s[i+1],f[i][j][k]);
				}
				dp(i,0,f[i][j][k]*max(0,m-(s[i-1]!=0)-(s[i]!=s[i-1])-(s[i+1]!=s[i-1]&&s[i+1]!=s[i])));
			}
		}
	}
	printf("%lld",f[n][0][0]+f[n][0][1]);
}
