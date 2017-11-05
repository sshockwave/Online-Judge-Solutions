#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=16,INF=0x7f7f7f7f,MINF=-2139062144;
int dis[N][N];
int ans=0;
int inter[1<<N];
int f[N][1<<N],lnode[N][1<<N],g[1<<N];
int vec[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("stable.in","r",stdin);
	freopen("stable.out","w",stdout);
#endif
	int n=ni,sum=0,ts=1<<n;
	memset(dis,0,sizeof(dis));
	for(int tot=ni,u,v;tot--;u=ni,v=ni,sum+=dis[u][v]=dis[v][u]=ni);
	for(int s=0;s<ts;s++){
		inter[s]=0;
		for(int i=0;i<n;i++){
			if((s>>i)&1){
				for(int j=0;j<i;j++){
					if((s>>j)&1){
						inter[s]+=dis[i+1][j+1];
					}
				}
			}
		}
	}
	memset(f,128,sizeof(f));
	assert(f[1][1]==MINF);
	f[1][1]=0;
	int ans=0;
	for(int s=0;s<ts;s++){
		for(int i=1;i<=n;i++){
			if((s>>(i-1))&1){
				for(int j=1;j<=n;j++){
					if(((s>>(j-1))&1)&&dis[i][j]&&f[j][s^(1<<(i-1))]>MINF){
						int tmp=f[j][s^(1<<(i-1))]+dis[i][j];
						if(tmp>f[i][s]){
							f[i][s]=tmp;
							lnode[i][s]=j;
						}
					}
				}
			}
		}
		if(f[n][s]>MINF){
			int vs=0;
			int curs=s;
			for(int x=n;x!=1;curs^=1<<(x-1),x=lnode[x][curs^(1<<(x-1))]){
				vec[vs++]=x;
			}
			vec[vs++]=1;
			reverse(vec,vec+vs);
			for(int trans=(ts-1)^s,s2=trans;s2;s2=trans&(s2-1)){
				g[s2]=MINF;
			}
			g[0]=0;
			for(int i=0;i<vs;i++){//dp
				for(int trans=(ts-1)^s,s2=trans;s2;s2=trans&(s2-1)){
					int tmp=s2|(1<<(vec[i]-1));
					for(int s3=s2;s3;s3=s2&(s3-1)){
						if(g[s3]>MINF){
							apmax(g[s2],g[s3]+inter[tmp^s3]);
						}
					}
					if(g[0]>MINF){
						apmax(g[s2],g[0]+inter[tmp]);
					}
				}
			}
			apmax(ans,g[(ts-1)^s]+f[n][s]);
		}
	}
	printf("%d\n",sum-ans);
	return 0;
}
