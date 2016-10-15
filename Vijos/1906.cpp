#include <iostream>
#include <cstdio>
#include <cstring>
#define N 200010
#define MOD 10007
using namespace std;
int u[N],v[N],w[N],sum[N],most[N][2];
inline void update(int x,int val){
	if(most[x][0]){
		if(most[x][0]<val){
			most[x][1]=most[x][0];
			most[x][0]=val;
		}else{
			if(most[x][1]){
				if(most[x][1]<val){
					most[x][1]=val;
				}
			}else{
				most[x][1]=val;
			}
		}
	}else{
		most[x][0]=val;
	}
}
int main(){
	int n,total=0,maxw=0;
	memset(most,0,sizeof(most));
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",u+i,v+i);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",w+i);
	}
	for(int i=1;i<n;i++){
		sum[u[i]]=(sum[u[i]]+w[v[i]])%MOD;
		sum[v[i]]=(sum[v[i]]+w[u[i]])%MOD;
		update(u[i],w[v[i]]),update(v[i],w[u[i]]);
	}
	for(int i=1;i<=n;i++){
		if(maxw<most[i][0]*most[i][1]){
			maxw=most[i][0]*most[i][1];
		}
	}
	for(int i=1;i<n;i++){
		total=(total+(sum[u[i]]-w[v[i]])*w[v[i]]+(sum[v[i]]-w[u[i]])*w[u[i]])%MOD;
	}
	printf("%d %d",maxw,total);
}
