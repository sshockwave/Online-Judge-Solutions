#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=12,M=10010;
const lint LINF=0x7f7f7f7f7f7f7f7f;
int n,m;
int mat[N][M];
namespace G{
	int tim=0;
	int tag[N][M];
	inline void init(){
		memset(tag,0,sizeof(tag));
	}
	struct state{
		int x,y;
		lint d;
		inline friend bool operator < (const state &a,const state &b){
			return a.d>b.d;
		}
	};
	int dx[]={-1,0,1,0},dy[]={0,1,0,-1};
	inline void dij(lint *dis[N],int sx,int sy,int l,int r){
		priority_queue<state>q;
		tim++;
		tag[sx][sy]=tim,dis[sx][sy]=mat[sx][sy],q.push((state){sx,sy,mat[sx][sy]});
		for(;!q.empty();q.pop()){
			int x=q.top().x,y=q.top().y;
			if(q.top().d>dis[x][y]){
				continue;
			}
			for(int d=0;d<4;d++){
				int tx=x+dx[d],ty=y+dy[d];
				if(1<=tx&&tx<=n&&l<=ty&&ty<=r&&(tag[tx][ty]!=tim||dis[tx][ty]>dis[x][y]+mat[tx][ty])){
					tag[tx][ty]=tim,dis[tx][ty]=dis[x][y]+mat[tx][ty],q.push((state){tx,ty,dis[tx][ty]});
				}
			}
		}
	}
}
namespace arr{
	lint pol[N*N*M*15];
	inline lint* New(int len){
		static lint* n=pol;
		lint* tmp=n;
		n+=len;
		return tmp;
	}
}
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		lint *dis[N][N];
	}*rt;
	node build(int l,int r){
		static node nn=new Node[M<<1];
		if(l>r){
			return NULL;
		}
		node x=nn++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l!=r){
			x->lson=build(l,x->m-1);
			x->rson=build(x->m+1,r);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				x->dis[i][j]=arr::New(r-l+1)-l;
			}
			G::dij(x->dis[i],i,x->m,l,r);
		}
		return x;
	}
	lint ask(node x,int sx,int sy,int tx,int ty){
		lint ans=LINF;
		for(int i=1;i<=n;i++){
			apmin(ans,x->dis[i][sx][sy]+x->dis[i][tx][ty]-mat[i][x->m]);
		}
		if(ty<x->m){
			apmin(ans,ask(x->lson,sx,sy,tx,ty));
		}
		if(sy>x->m){
			apmin(ans,ask(x->rson,sx,sy,tx,ty));
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("route.in","r",stdin);
	freopen("route.out","w",stdout);
#endif
	n=ni,m=ni;
	int tot=ni;
	for(int j=1;j<=m;j++){
		for(int i=1;i<=n;i++){
			mat[i][j]=ni;
		}
	}
	G::init(),seg::rt=seg::build(1,m);
	while(tot--){
		int sx=ni,sy=ni,tx=ni,ty=ni;
		if(sy>ty){
			swap(sx,tx),swap(sy,ty);
		}
		printf("%lld\n",seg::ask(seg::rt,sx,sy,tx,ty));
	}
	return 0;
}
