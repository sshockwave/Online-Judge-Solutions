#include <iostream>
#include <cstdio>
#include <cstring>
#define N 50010
using namespace std;
int to[N<<1],bro[N<<1],val[N<<1],head[N],etop=0,n,
	walk[N][20],logtop[N];
long long f[N][20];
bool army[N],vis[N];
inline void add_edge(int u,int v,int w){
	to[etop]=v;
	val[etop]=w;
	bro[etop]=head[u];
	head[u]=etop++;
}
void dfs(int x){
	int &j=logtop[x];
	cout<<"Cur:"<<x<<endl<<"\twalk 1 to "<<walk[x][0]<<"\tlen="<<f[x][0]<<endl;
	for(j=1;walk[x][j-1];j++){
		walk[x][j]=walk[walk[x][j-1]][j-1];
		f[x][j]=f[x][j-1]+f[walk[x][j-1]][j-1];
		cout<<"\twalk "<<(1<<j)<<" to "<<walk[x][j]<<"\tlen="<<f[x][j]<<endl;
	}
	for(int i=head[x];~i;i=bro[i]){
		if(to[i]!=walk[x][0]){
			walk[to[i]][0]=x;
			f[to[i]][0]=val[i];
			dfs(to[i]);
		}
	}
}
bool judge_dfs(int x){
	if(vis[x]){
		return true;
	}
	bool haveson=false;
	for(int i=head[x];~i;i=bro[i]){
		if(to[i]!=walk[x][0]){
			haveson=true;
			if(!judge_dfs(to[i])){
				return false;
			}
		}
	}
	return haveson;
}
inline bool judge(int len){
	memset(vis,0,sizeof(vis));
	int sum,x;
	for(int i=2;i<=n;i++){
		if(army[i]){
			cout<<"\t"<<i<<" has army. Walking up:"<<endl;
			sum=0;
			x=i;
			for(int j=logtop[i];j>=0;j--){
				if(walk[x][j]>1&&sum+f[x][j]<=len){
					sum+=f[x][j];
					x=walk[x][j];
					cout<<"\t\tWalk to "<<x<<endl;
				}
			}
			vis[x]=true;
		}
	}
	return judge_dfs(1);
}
int main(){
	memset(head,-1,sizeof(head));
	memset(walk,0,sizeof(walk));
	memset(f,0,sizeof(f));
	memset(army,0,sizeof(army));
	int m,u,v,w,cnt=0;
	long long l=0,r=0,mid;
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&u,&v,&w);
		r+=w;
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	for(int i=head[1];~i;i=bro[i],cnt++);
	scanf("%d",&m);
	if(m<cnt){
		cout<<-1;
		return 0;
	}
	for(int i=0;i<m;i++){
		scanf("%d",&u);
		army[u]=true;
	}
	dfs(1);
	while(l<r){
		mid=(l+r)/2;
		cout<<"("<<l<<","<<r<<")"<<endl;
		if(judge(mid)){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	cout<<l;
}