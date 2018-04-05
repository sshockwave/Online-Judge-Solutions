#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int SH=8,N=(1<<SH)+10,O=998244353,bigSH=30;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int eqn[N][N];
inline void gauss(int n){//0~n
	cout<<"gauss:"<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<eqn[i][j]<<" ";
		}
		cout<<"= "<<eqn[i][n]<<endl;
	}
	for(int i=0;i<n;i++){
		int j=i;
		for(;eqn[j][i]==0;j++);
		if(i!=j){
			for(int k=i;k<=n;k++){
				swap(eqn[i][k],eqn[j][k]);
			}
		}
		lint r=inv(eqn[i][i]);
		for(int k=i;k<=n;k++){
			eqn[i][k]=eqn[i][k]*r%O;
		}
		cout<<"i="<<i<<":reved"<<endl;
		for(int k=0;k<n;k++){
			for(int j=0;j<n;j++){
				cout<<eqn[k][j]<<" ";
			}
			cout<<"= "<<eqn[k][n]<<endl;
		}
		for(j=0;j<n;j++){
			if(j!=i&&eqn[j][i]){
				r=O-eqn[j][i];
				for(int k=i;k<=n;k++){
					eqn[j][k]=(eqn[j][k]+r*eqn[i][k])%O;
				}
			}
		}
		cout<<"i="<<i<<":"<<endl;
		for(int k=0;k<n;k++){
			for(int j=0;j<n;j++){
				cout<<eqn[k][j]<<" ";
			}
			cout<<"= "<<eqn[k][n]<<endl;
		}
	}
	//ans:eqn[i][n]
}
inline int _n(int n){
	return (lint)n*(n+1)/2%O;
}
inline int work(int prob[],int n,int p){
	for(int s=0,ts=1<<n;s<ts;s++){
		eqn[s][ts]=(lint)(p+O-1)*s%O;
		for(int t=0;t<ts;t++){
			eqn[s][(s+t)&(ts-1)]=t==0?((lint)p*prob[0]+O-1)%O:((lint)p*prob[t]%O);
		}
	}
	gauss(1<<n);
	return eqn[0][1<<n];
}
char ban[bigSH];
int prob[bigSH][N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("inhibit.in","r",stdin);
	freopen("inhibit.out","w",stdout);
#endif
	int n=ni,p=ni;
	scanf("%s",ban);
	memset(prob,0,sizeof(prob));
	int probinv=inv(_n((1<<n)-1));
	for(int s=0,ts=1<<n;s<ts;s++){
		int a=0;
		for(int i=0;i<n;i++){
			a|=1<<i;
			if(ban[i]=='1'){
				int t=s&a,&F=prob[i][t/(a&-a)];
				F=(F+(lint)s*probinv)%O;
				a=0;
			}
		}
	}
	int acnt=0,st=0;
	int ans=0;
	for(int i=0;i<n;i++){
		acnt++;
		if(ban[i]=='1'){
			ans=(ans+((lint)work(prob[i],acnt,p)<<st))%O;
			acnt=0;
			st=i+1;
		}
	}
	printf("%d\n",ans);
	return 0;
}
