#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define N 100010
using namespace std;
vector<int>con[N];
int walk[N][20],logt[N],dfn[N],pos[N],dtop=1,
	l[N*3],r[N*3],mid[N*3],rest[N*3];
void build(int x,int a,int b){
	l[x]=a,r[x]=b,mid[x]=(a+b)/2;
	rest[x]=b-a+1;
	if(a!=b){
		build(x<<1,a,mid[x]);
		build((x<<1)|1,mid[x]+1,b);
	}
}
inline bool query(int x,int a){
	while(l[x]!=r[x]&&rest[x]!=0){
		x<<=1;
		if(a>mid[x]){
			x++;
		}
	}
	return rest[x]==0;
}
inline void change(int x,int a){
	while(rest[x]++,l[x]!=r[x]){
		if(rest[x]==1){
			rest[x<<1]=0,rest[(x<<1)|1]=0;
		}
		x<<=1;
		if(a>mid[x]){
			x++;
		}
	}
}
int occupy(int x,int amt){//return the offset from l[x]
	rest[x]-=amt;
	if(rest[x]==0){
		if(l[x]==r[x]){
			return 0;
		}
		return mid[x]-l[x]+1+occupy((x<<1)|1,rest[(x<<1)|1]);
	}
	if(amt<=rest[x<<1]){
		return occupy(x<<1,amt);
	}else{
		int tmp=occupy((x<<1)|1,amt-rest[x<<1])+mid[x]-l[x]+1;
		rest[x<<1]=0;
		return tmp;
	}
}
int dfs(int x){
	for(int &i=logt[x];walk[x][i];i++){
		walk[x][i+1]=walk[walk[x][i]][i];
	}
	sort(con[x].begin(),con[x].end());
	for(vector<int>::iterator it=con[x].begin();it!=con[x].end();it++){
		if((*it)!=walk[x][0]){
			walk[*it][0]=x;
			dfs(*it);
		}
	}
	dfn[x]=dtop++;
	pos[dfn[x]]=x;
}
int main(){
	int n,t,x,y;
	scanf("%d%d",&n,&t);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		con[x].push_back(y);
		con[y].push_back(x);
	}
	memset(walk,0,sizeof(walk));
	memset(logt,0,sizeof(logt));
	dfs(1);
	build(1,1,n);
	while(t--){
		scanf("%d%d",&y,&x);
		if(y==1){
			printf("%d\n",pos[occupy(1,x)+1]);
		}else{
			int at=x,cnt=0;
			for(int i=logt[x];i>=0;i--){
				if(walk[at][i]!=0&&query(1,dfn[walk[at][i]])){
					cnt|=(1<<i);
					at=walk[at][i];
				}
			}
			change(1,dfn[at]);
			printf("%d\n",cnt);
		}
	}
}
