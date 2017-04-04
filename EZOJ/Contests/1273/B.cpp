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
inline bool turn_left(Point a,Point b,Point c){
	cout<<"Ask turn:"<<a<<b<<c;
	int d=det(b-a,c-b);
	if(d==0){
		cout<<(dot(b-a,c-b)>0)<<endl;
		return dot(b-a,c-b)>0;
	}
	cout<<(d>0)<<endl;
	return d>0;
}
inline bool polarcmp(int a,int b){
	Point pa=pt[a]-base,pb=pt[b]-base;
	if(pa.y*pb.y<0){
		return pa.y>pb.y;
	}
	int d=det(pa,pb);
	if(d==0){
		if(pa.x*pb.x>0){
			assert(pa.y==0&&pb.y==0);
			return dot(pa,pa)<dot(pb,pb);
		}else if(pa.x*pb.x<0){
			assert(pa.y==0&&pb.y==0);
			return pa.x>pb.x;
		}
		
	}
	return d>0;
}
int rlist[N][N],head[N][N],f[N][N];
int main(){
	freopen("B.in","r",stdin);
	int n=ni();
	if(n<=3){
		printf("%d",n);
		return 0;
	}
	for(int i=1;i<=n;i++){
		scanf("%d%d",&pt[i].x,&pt[i].y);
	}
	memset(rlist,0,sizeof(rlist));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			rlist[i][j]=j;
		}
		base=pt[i];
		sort(rlist[i]+1,rlist[i]+n+1,polarcmp);
		cout<<"Sort of "<<i<<endl;
		cout<<"\tbase="<<base<<endl<<"\t";
		for(int j=1;j<=n;j++){
			cout<<pt[rlist[i][j]];
		}
		cout<<endl<<"\t=>"<<endl<<"\t";
		for(int j=1;j<=n;j++){
			cout<<pt[rlist[i][j]]-base;
		}
		cout<<endl;
		assert(rlist[i][1]==i);
		for(int j=2,k=3;j<=n;j++){
			while(k<=n&&!turn_left(pt[rlist[i][j]],pt[i],pt[rlist[i][k]])){
				k++;
			}
			head[rlist[i][j]][i]=rlist[i][k];
			cout<<"head["<<rlist[i][j]<<"]["<<i<<"]="<<rlist[i][k]<<endl;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(f,0,sizeof(f));
		for(int j=1;j<=n;j++){
			int u=rlist[i][j];
			f[u][head[i][u]]=2;
		}
		for(int j=1;j<=n;j++){
			int u=rlist[i][j],mx=0;
			for(int k=1;k<=n;k++){
				int v=rlist[u][k];
				apmax(mx,f[u][v]);
				apmax(f[u][v],mx);
				apmax(f[v][head[u][v]],mx+1);
			}
		}
		for(int j=1;j<=n;j++){
			apmax(ans,f[j][i]);
		}
	}
	printf("%d",ans);
}
