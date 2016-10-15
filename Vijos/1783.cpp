#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 50010
using namespace std;
int to[N<<1],bro[N<<1],val[N<<1],head[N],etop=0,walk[N][20],logt[N],
	que[N],qhead,qtail,son[N],stop=0,army[N],bln[N];
long long f[N][20],dis[N],l=0,r=0,mid;
bool block[N];
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	head[u]=etop++;
}
inline bool soncmp(const int &a,const int &b){
	return dis[a]<dis[b];
}
inline bool armycmp(const int &a,const int &b){
	return dis[a]>dis[b];
}
void dfs(int x){
	for(int i=head[x];~i;i=bro[i]){
		if(x!=walk[x][0]){
			block[x]=true;
			if(!block[to[i]]){
				dfs(to[i]);
				if(!block[to[i]]){
					block[x]=false;
					return;
				}
			}
		}
	}
}
int main(){
	memset(head,-1,sizeof(head));
	int n,m,u,v,w,x;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	qhead=qtail=0;
	que[qtail++]=1;
	dis[1]=f[1][0]=f[0][0]=bln[1]=walk[1][0]=walk[0][0]=0;
	cout<<"BFS"<<endl;
	while(qhead<qtail){
		x=que[qhead++];
		cout<<"Cur:"<<x<<endl;
		logt[x]=0;
		for(int &i=logt[x];walk[x][i];i++){
			walk[x][i+1]=walk[walk[x][i]][i];
			f[x][i+1]=f[x][i]+f[walk[x][i]][i];
		}
		if(dis[x]>r){
			r=dis[x];
		}
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]!=walk[x][0]){
				walk[to[i]][0]=x;
				f[to[i]][0]=val[i];
				dis[to[i]]=dis[x]+val[i];
				if(bln[x]==0){
					bln[to[i]]=to[i];
				}else{
					bln[to[i]]=bln[x];
				}
				que[qtail++]=to[i];
			}
		}
	}
	for(int &i=head[1];~i;i=bro[i]){
		son[stop++]=to[i];
	}
	sort(son,son+stop,soncmp);
	scanf("%d",&m);
	if(m<stop){
		printf("-1");
		return 0;
	}
	for(int i=0;i<m;i++){
		scanf("%d",army+i);
	}
	army[m]=-1;
	sort(army,army+m,armycmp);
	r<<=1;
	while(l<r){
		cout<<"("<<l<<","<<r<<")"<<endl;
		mid=(l+r)/2;
		for(int i=1;i<=n;i++){
			block[i]=false;
		}
		int i=0,j;
		for(;i<m;i++){
			if(dis[army[i]]>mid){
				int x=army[i];
				long long rest=mid;
				for(j=logt[x];j>=0;j--){
					if(f[x][j]<=rest){
						rest-=f[x][j];
						x=walk[x][j];
					}
				}
				block[x]=true;
			}else{
				break;
			}
		}
		dfs(1);
		for(j=0;j<stop&&i<m;j++){
			if(block[j]){
				continue;
			}
			for(;i<m;i++){
				if(!block[bln[army[i]]]){
					block[bln[army[i]]]=true;
				}else if(mid-dis[army[i]]>=dis[son[j]]){
					break;
				}
			}
			if(i==m){
				break;
			}
		}
		if(j==stop){//OK
			r=mid;
		}else{
			l=mid+1;
		}
	}
	cout<<l;
}
