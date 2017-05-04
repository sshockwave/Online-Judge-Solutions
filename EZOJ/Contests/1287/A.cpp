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
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmin(int &a,const int &b){
	if(a>b){
		a=b;
	}
}
const int N=19,S=1<<(N-2),INF=0x7f7f7f7f;
int n,f[S][N],pre[S][N],g[S],dic[S],dis[N][N],cen[N][N],route[N*2];
inline int* expand(int arr[],int i,int j){
	int k=cen[i][j];
	if(k==0){
		return arr;
	}
	arr=expand(arr,i,k);
	arr[0]=k;
	return expand(arr+1,k,j);
}
inline void putroute(int p){
	static int *tmp=new int[N*3];
	int rtop=0;
	for(;~p;p=pre[p/n][p%n+1]){
		tmp[rtop++]=p%n+1;
	}
	int *arr=route;
	*(arr++)=tmp[0];
	for(int i=1;i<rtop;i++){
		arr=expand(arr,tmp[i-1],tmp[i]);
		*(arr++)=tmp[i];
	}
	printf("%d",(int)(arr-route-1));
	while((--arr)>=route){
		printf(" %d",*arr);
	}
	putchar('\n');
}
int main(){
	n=ni;
	int m=ni;
	memset(dis,127,sizeof(dis));
	for(int i=1;i<=n;i++){
		dis[i][i]=0;
	}
	for(int i=1;i<=m;i++){
		int u=ni,v=ni,w=ni;
		dis[u][v]=w;
		dis[v][u]=w;
	}
	memset(cen,0,sizeof(cen));
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			if(dis[i][k]!=INF){
				for(int j=1;j<=n;j++){
					if(dis[k][j]!=INF){
						if(dis[i][j]>dis[i][k]+dis[k][j]){
							dis[i][j]=dis[i][k]+dis[k][j];
							cen[i][j]=k;
						}
					}
				}
			}
		}
	}
	memset(f,127,sizeof(f));
	memset(g,127,sizeof(g));
	memset(pre,-1,sizeof(pre));
	memset(dic,-1,sizeof(dic));
	f[0][1]=0;
	g[0]=0;
	dic[0]=0;
	int full=(1<<(n-1))-1;
	for(int state=0;state<=full;state++){
		for(int i=1;i<=n;i++){
			int F=f[state][i],diff=state*n+i-1;
			if(F==INF){
				continue;
			}
			for(int j=0,_=n-1;j<_;j++){
				if(((state>>j)&1)==0){
					int to=state|(1<<j);
					if(f[to][j+2]>dis[i][j+2]+F){
						f[to][j+2]=dis[i][j+2]+F;
						pre[to][j+2]=diff;
					}
				}
			}
			if(g[state]>F){
				g[state]=F;
				dic[state]=diff;
			}
		}
		for(int sub=state;sub;sub=(sub-1)&state){
			if(g[state]<g[sub]){
				g[sub]=g[state];
				dic[sub]=dic[state];
			}
		}
	}
	int ans=INF,s1,s2;
	for(int state=0;state<=full;state++){
		if(max(g[state],g[state^full])<ans){
			ans=max(g[state],g[state^full]);
			s1=state,s2=state^full;
		}
	}
	printf("%d\n",ans);
	putroute(dic[s1]);
	putroute(dic[s2]);
}
