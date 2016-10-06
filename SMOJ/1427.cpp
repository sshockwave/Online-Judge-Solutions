#include <iostream>
#include <cstdio>
#include <cstring>
#define N 35
#define INF 2147483647
using namespace std;
int mat[N][N],mx[8]={-2,-1,1,2,2,1,-1,-2},my[8]={1,2,2,1,-1,-2,-2,-1},m,n;
bool vis[N][N];
struct status{
	int step,ways;
	bool reach;
	status(int s,int w,bool r){
		step=s,ways=w,reach=r;
	}
};
inline bool valid(int x,int y,int rest){
	return x>0&&y>0&&x<=m&&y<=n&&!vis[x][y]&&(mat[x][y]==1||(mat[x][y]==0&&rest>0)||mat[x][y]==4);
}
status dfs(int x,int y,int rest){
	if(mat[x][y]==4){
		return status(0,1,true);
	}
	vis[x][y]=true;
	status ans(INF,0,false);
	for(int i=0;i<8;i++){
		if(valid(x+mx[i],y+my[i],rest)){
			status tmp=dfs(x+mx[i],y+my[i],rest-(mat[x+mx[i]][y+my[i]]==0));
			if(tmp.reach){
				tmp.step++;
				ans.reach=true;
				if(tmp.step<ans.step){
					ans.step=tmp.step+1;
					ans.ways=tmp.ways;
				}else if(tmp.step==ans.step){
					ans.ways+=tmp.ways;
				}
			}
		}
	}
	vis[x][y]=false;
	return ans;
}
int main(){
	freopen("silvlily.in","r",stdin);
	freopen("silvlily.out","w",stdout);
	int sx,sy,l=0,r=0,mid;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&mat[i][j]);
			if(mat[i][j]==0){
				r++;
			}else if(mat[i][j]==3){
				sx=i,sy=j;
			}
		}
	}
	while(l<r){
//		cout<<"("<<l<<","<<r<<")"<<endl;
		mid=l+r>>1;
		status cur=dfs(sx,sy,mid);
		if(cur.reach){
			r=mid;
		}else{
			l=mid+1;
		}
	}
	status cur=dfs(sx,sy,l);
	printf("%d\n%d\n%d\n",l,cur.step,cur.ways);
}
