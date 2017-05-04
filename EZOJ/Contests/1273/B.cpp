#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
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
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=260;
struct Point{
	int x,y;
	Point(int a=0,int b=0){
		x=a,y=b;
	}
	inline bool iszero(){
		return x==0&&y==0;
	}
}pt[N],base;
inline Point operator - (Point a,Point b){
	return Point(a.x-b.x,a.y-b.y);
}
inline int det(Point a,Point b){
	return a.x*b.y-a.y*b.x;
}
inline int dot(Point a,Point b){
	return a.x*b.x+a.y*b.y;
}
inline ostream & operator << (ostream & out,Point a){
	out<<"("<<a.x<<","<<a.y<<")";
	return out;
}
inline bool turn_left(int a,int b,int c){
	int d=det(pt[b]-pt[a],pt[c]-pt[b]);
	if(d==0){
		return dot(pt[b]-pt[a],pt[c]-pt[b])>0;
	}
	return d>0;
}
inline bool same_direc(Point a,Point b){
	return det(a-base,b-base)==0&&dot(a-base,b-base)>0;
}
inline bool verticalcmp(Point a,Point b){
	if(a.y==b.y){
		return a.x<b.x;
	}
	return a.y<b.y;
}
inline bool polarcmp(int a,int b){
	Point pa=pt[a]-base,pb=pt[b]-base;
	if(pa.y>=0&&pb.y<0){
		return true;
	}
	if(pa.y<0&&pb.y>=0){
		return false;
	}
	if(pa.y==0&&pb.y==0){
		int d=dot(pa,pb);
		if(d>0){
			return dot(pa,pa)<dot(pb,pb);
		}else if(d<0){
			return pa.x>0;
		}
		return pa.x==0&&pb.x;
	}
	int d=det(pa,pb);
	if(d!=0){
		return d>0;
	}
	return dot(pa,pa)<dot(pb,pb);
}
int rlist[N],f[N][N],head[N][N],nxt[N][N],ind[N][N],qu[N*N],qv[N*N];
bool vis[N][N];
int main(){
	int n=ni();
	if(n<3){
		printf("%d",n);
		return 0;
	}
	for(int i=1;i<=n;i++){
		scanf("%d%d",&pt[i].x,&pt[i].y);
	}
	sort(pt+1,pt+n+1,verticalcmp);
	memset(rlist,0,sizeof(rlist));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			rlist[j]=j;
		}
		base=pt[i];
		sort(rlist+1,rlist+n+1,polarcmp);
		int j=1,k=2,u;
		while(u=rlist[++j],u>i){
			nxt[i][u]=rlist[j+1];
			for(;k<=n&&!turn_left(u,i,rlist[k]);k++);
			head[u][i]=rlist[k];
		}
		for(k=2;j<=n;j++){
			u=rlist[j];
			nxt[i][u]=rlist[j+1];
			for(;k<=n&&k<j&&!turn_left(u,i,rlist[k]);k++);
			if(k!=j){
				head[u][i]=rlist[k];
			}
		}
	}
	int ans=0;
	for(int i=1;i+ans<=n;i++){
		base=pt[i];
		memset(f,0,sizeof(f));
		memset(ind,0,sizeof(ind));
		memset(vis,0,sizeof(vis));
		int qhead=0,qtail=0;
		for(int j=i+1;j<=n;j++){
			f[i][j]=1;
			vis[i][j]=true;
			qu[qtail]=i,qv[qtail]=j,qtail++;
		}
		while(qhead<qtail){
			int u=qu[qhead],v=qv[qhead];
			qhead++;
			int H=head[u][v],X=nxt[u][v];
			if(H&&v>=i){
				ind[v][H]++;
				if(!vis[v][H]){
					vis[v][H]=true;
					qu[qtail]=v,qv[qtail]=H,qtail++;
				}
			}
			if(X){
				ind[u][X]++;
				if(!vis[u][X]){
					vis[u][X]=true;
					qu[qtail]=u,qv[qtail]=X,qtail++;
				}
			}
		}
		qhead=qtail=0;
		for(int j=i+1;j<=n;j++){
			if(ind[i][j]==0){
				qu[qtail]=i,qv[qtail]=j,qtail++;
			}
		}
		while(qhead<qtail){
			int u=qu[qhead],v=qv[qhead];
			qhead++;
			if(f[u][v]==0){
				continue;
			}
			int H=head[u][v],X=nxt[u][v];
			if(v>=i&&H){
				apmax(f[v][H],f[u][v]+1);
				if((--ind[v][H])==0){
					qu[qtail]=v,qv[qtail]=H,qtail++;
				}
			}
			if(X){
				apmax(f[u][X],f[u][v]);
				if((--ind[u][X])==0){
					qu[qtail]=u,qv[qtail]=X,qtail++;
				}
			}
		}
		for(int j=i+1;j<=n;j++){
			apmax(ans,f[j][i]);
		}
	}
	printf("%d",ans);
}
