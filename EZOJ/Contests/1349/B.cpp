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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=5,M=8,K=10,O=12345678;
char mat[N][M];
int sur[N][M];
int n,m;
inline bool valid(int x,int y){
	return x>=1&&x<=n&&y>=1&&y<=m;
}
int posx[K],posy[K],ps;
int vis[N][M],tim=0;
int rest[1<<K];
lint f[1<<K];
inline int dp(){
	for(int s=0,ts=1<<ps;s<ts;s++){
		rest[s]=n*m;
		tim++;
		for(int i=0;i<ps;i++){
			if(((s>>i)&1)==0){
				rest[s]++;
				for(int x=posx[i]-1;x<=posx[i]+1;x++){
					for(int y=posy[i]-1;y<=posy[i]+1;y++){
						if(valid(x,y)&&vis[x][y]<tim){
							vis[x][y]=tim;
							rest[s]--;
						}
					}
				}
			}
		}
	}
	memset(f,0,(1<<ps)<<3);
	f[0]=1;
	for(int i=1,ti=n*m;i<=ti;i++){
		for(int s=0,ts=1<<ps;s<ts;s++){
			(f[s]*=max(rest[s]-(i-1),0))%=O;
			for(int t=s;t;t^=t&-t){
				f[s]+=f[s^(t&-t)];
			}
		}
	}
	return f[(1<<ps)-1];
}
int dfs(int x,int y){
	if(y>m){
		x++,y=1;
	}
	if(x>n){
		return dp();
	}
	try{
		for(int i=x-1;i<=x+1;i++){
			for(int j=y-1;j<=y+1;j++){
				if(valid(i,j)&&mat[i][j]=='X'){
					throw 0;
				}
			}
		}
		mat[x][y]='X',posx[ps]=x,posy[ps]=y,ps++;
		int ans=dfs(x,y+1);
		mat[x][y]='.',ps--;
		return (dfs(x,y+1)-ans+O)%O;
	}catch(int err){
		return dfs(x,y+1);
	}
}
inline int Main(){
	n=ni,m=ni;
	memset(sur,0,sizeof(sur));
	for(int i=1;i<=n;i++){
		scanf("%s",mat[i]+1);
		for(int j=1;j<=m;j++){
			for(int ti=i-1;ti<=i+1;ti++){
				for(int tj=j-1;tj<=j+1;tj++){
					if(valid(ti,tj)&&(ti!=i||tj!=j)){
						sur[i][j]++;
					}
				}
			}
		}
	}
	return dfs(1,1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("garden.in","r",stdin);
	freopen("garden.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
