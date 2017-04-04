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
inline int abs(int a){
	return a>0?a:-a;
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
inline bool turn_left(Point a,Point b,Point c){
	int d=det(b-a,c-b);
	if(d==0){
		return dot(b-a,c-b)>0;
	}
	return d>0;
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
		if(dot>0){
			return dot(pa,pa)<dot(pb,pb);
		}else if(dot<0){
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
int rlist[N][N],head[N][N],f[N][N];
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
			rlist[i][j]=j;
		}
		base=pt[i];
		sort(rlist[i]+1,rlist[i]+n+1,polarcmp);
		assert(rlist[i][1]==i);
		for(int j=2,k=2;j<=n;j++){
			int u=rlist[i][j];
			while(!turn_left(pt[u],base,pt[rlist[i][k]])){
				k++;
				if(k>n){
					k=2;
				}
				if(k==j){
					break;
				}
			}
			if(k!=j){
				head[u][i]=rlist[i][k];
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(f,0,sizeof(f));
		for(int j=i+1;j<=n;j++){
			f[i][j]=1;
		}
		for(int j=i,u;j<=n;j++){
			u=rlist[i][j];
			if(u<i){
				break;
			}
			for(int k=1,mx=0,v;k<=n;k++){
				v=rlist[u][k];
				if(v<i){
					break;
				}
				mx=f[u][v]=max(mx,f[u][v]);
				apmax(f[v][head[u][v]],mx+1);
			}
		}
		for(int j=i+1;j<=n;j++){
			apmax(ans,f[j][i]);
		}
	}
	printf("%d",ans);
}
