#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(int &a,int b){
	if(a>b){
		a=b;
	}
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=100010,M=N,E=N*2,logN=20;
int to[E],bro[E],head[N];
inline void add_edge(int u,int v){
	static int etop=0;
	to[etop]=v;
	bro[etop]=head[u];
	head[u]=etop++;
}
int color[N],fa[N][logN],ldep[N],dep[N];
int d1[M],d2[M],diam[M];
void dfs1(int x,int f){
	fa[x][0]=f;
	for(int &j=ldep[x];fa[x][j+1]=fa[fa[x][j]][j];j++);
	for(int i=head[x],v;~i;i=bro[i]){
		if((v=to[i])!=f){
			dep[v]=dep[x]+1;
			dfs1(v,x);
		}
	}
}
inline int go_up(int x,int n){
	if(n<0){
		return x;
	}
	for(int j=ldep[x];j>=0;j--){
		if((n>>j)&1){
			x=fa[x][j];
		}
	}
	return x;
}
inline int lca(int u,int v){
	if(dep[u]!=dep[v]){
		if(dep[u]>dep[v]){
			u=go_up(u,dep[v]-dep[u]);
		}else{
			v=go_up(v,dep[u]-dep[v]);
		}
	}
	if(u==v){
		return u;
	}
	for(int j=min(ldep[u],ldep[v]);j>=0;j--){
		if(fa[u][j]&&fa[v][j]&&fa[u][j]!=fa[v][j]){
			u=fa[u][j];
			v=fa[v][j];
		}
	}
	assert(fa[u][0]==fa[v][0]);
	return fa[u][0];
}
inline int dist(int u,int v){
	return dep[u]+dep[v]-2*dep[lca(u,v)];
}
void dfs2(int x,int f){
	int c=color[x];
	if(d1[c]==0){
		d1[c]=x;
	}else if(d2[c]==0){
		d2[c]=x;
		diam[c]=dist(x,d1[c]);
	}else{
		int nd1=dist(x,d1[c]),nd2=dist(x,d2[c]);
		if(nd1>nd2){
			if(nd1>diam[c]){
				diam[c]=nd1,d2[c]=x;
			}
		}else{
			if(nd2>diam[c]){
				diam[c]=nd2,d1[c]=x;
			}
		}
	}
	for(int i=head[x],v;~i;i=bro[i]){
		if((v=to[i])!=f){
			dfs2(v,x);
		}
	}
}
inline int calc(int x,int c){
	if(d2[c]){
		return max(dist(x,d1[c]),dist(x,d2[c]));
	}else{
		return dist(x,d1[c]);
	}
}
int dval[E],mids[N],ccnt=0;
inline void mark(int x1,int x2){
	int len=dist(x1,x2);
	if(dep[x1]<dep[x2]){
		swap(x1,x2);
	}
	if((len&1)==0){
		mids[go_up(x1,len>>1)]+=2;
	}else{
		int mid1=go_up(x1,len>>1),mid2=fa[mid1][0];
		mids[mid1]++;
		mids[mid2]++;
	}
}
int dfs3(int x,int f){
	int cnt=mids[x],cur;
	for(int i=head[x],v;~i;i=bro[i]){
		v=to[i];
		if(v!=f){
			cur=dfs3(v,x);
			dval[i]=ccnt-cur;
			cnt+=cur;
		}
	}
	return cnt;
}
int ans[N];
void dfs4(int x,int val){
	ans[x]=val;
	for(int i=head[x],v;~i;i=bro[i]){
		v=to[i];
		if(v!=f){
			dfs4(v,val+dval[i]);
		}
	}
}
int main(){
	memset(ldep,0,sizeof(ldep));
	memset(head,-1,sizeof(head));
	memset(d1,0,sizeof(d1));
	memset(d2,0,sizeof(d2));
	memset(diam,0,sizeof(diam));
	int n=ni(),m=ni();
	for(int i=1;i<=n;i++){
		color[i]=ni();
	}
	for(int i=1;i<n;i++){
		int u=ni(),v=ni();
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;
	dfs1(1,0),dfs2(1,0);
	memset(mids,0,sizeof(mids));
	memset(dval,0,sizeof(dval));
	for(int i=1;i<=m;i++){
		if(d1[i]){
			ccnt++;
			if(d2[i]){
				mark(d1[i],d2[i]);
			}else{
				mids[d1[i]]+=2;
			}
		}
	}
	dfs3(1,0),dfs4(1,0);
	for(int i=1;i<=n;i++){
		ans[i]-=calc(i,color[i]);
		printf("%d\n",ans[i]);
	}
}
