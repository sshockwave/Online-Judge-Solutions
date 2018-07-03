#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=310,D=200010;
struct Pt{
	int x,y;
};
bool vis[N<<1][N<<1];
vector<Pt>ban,lst[4];
int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
int n;
inline bool valid(int x,int y){
	return x>=0&&x<n*2&&y>=0&&y<n*2;
}
int col[N<<1][N<<1];
void dfs(int x,int y,int c,int bt){
	assert(!vis[x][y]);
	vis[x][y]=true;
	col[x][y]|=c;
	for(vector<Pt>::iterator it=ban.begin(),ti=ban.end();it!=ti;++it){
		const int tx=x+it->x,ty=y+it->y;
		if(valid(tx,ty)){
			if(vis[tx][ty]){
			}else{
				dfs(tx,ty,c^bt,bt);
			}
		}
	}
}
int issqr[D];
inline void work(int d1,int btmask){
	ban.clear();
	for(int i=0;i*i<=d1;i++){
		int j=issqr[d1-i*i];
		if(j!=-1){
			ban.push_back((Pt){i,j});
			ban.push_back((Pt){i,-j});
			ban.push_back((Pt){-i,j});
			ban.push_back((Pt){-i,-j});
			if(i!=j){
				ban.push_back((Pt){j,i});
				ban.push_back((Pt){j,-i});
				ban.push_back((Pt){-j,i});
				ban.push_back((Pt){j,-i});
			}
		}
	}
	for(int i=0;i<n*2;i++){
		mset(vis[i],0,n*2);
	}
	for(int i=0;i<n*2;i++){
		for(int j=0;j<n*2;j++){
			if(!vis[i][j]){
				dfs(i,j,0,btmask);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("point.in","r",stdin);
	freopen("point.out","w",stdout);
#endif
	n=ni;
	const int d1=ni,d2=ni;
	memset(issqr,-1,sizeof(issqr));
	for(int i=0;i*i<=d1||i*i<=d2;i++){
		issqr[i*i]=i;
	}
	work(d1,1),work(d2,2);
	for(int i=0;i<n*2;i++){
		for(int j=0;j<n*2;j++){
			lst[col[i][j]].push_back((Pt){i,j});
		}
	}
	int mxp=0;
	for(int i=1;i<4;i++){
		if(lst[i].size()>lst[mxp].size()){
			mxp=i;
		}
	}
	assert(lst[mxp].size()>=(unsigned)n*n);
	for(int i=0;i<n*n;i++){
		printf("%d %d\n",lst[mxp][i].x,lst[mxp][i].y);
	}
	return 0;
}
