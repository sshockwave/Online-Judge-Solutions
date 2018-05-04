#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int SH=13,N=1<<SH;
bool mat[SH*2][N];
int fa[N],oppo[N],col[N];
int grt(int x){
	return fa[x]!=x?fa[x]=grt(fa[x]):x;
}
inline int _mg(int u,int v){
	if(u==-1||v==-1)return u!=-1?u:v;
	u=grt(u),v=grt(v);
	fa[u]=v;
	return v;
}
inline void upd(int a,int b){
	if(a!=-1){
		oppo[a]=b;
	}
}
inline void mg_same(int u,int v){
	u=grt(u),v=grt(v);
	assert(oppo[u]!=v&&oppo[v]!=u);
	int b=_mg(oppo[u],oppo[v]),a=_mg(u,v);
	upd(a,b),upd(b,a);
}
inline void mg_oppo(int u,int v){
	u=grt(u),v=grt(v);
	assert(u!=v);
	int b=_mg(oppo[u],v),a=_mg(u,oppo[v]);
	upd(a,b),upd(b,a);
}
int pos2[N];
void solve(int _x,int _y,const int sh,int pos[]){
	if(sh==0)return;
	const int n=1<<sh;
	for(int i=0;i<n;i++){
		fa[i]=i,oppo[i]=-1,col[i]=-1;
	}
	for(int i=0;i<n;i++){
		if((i^pos[i])&1){
			mg_oppo(i>>1,(pos[i]>>1)|(1<<(sh-1)));
		}else{
			mg_same(i>>1,(pos[i]>>1)|(1<<(sh-1)));
		}
	}
	bool * const ans[2]={mat[_x+1]+_y,mat[_x+sh*2-1]+_y};
	for(int i=0;i<n;i++){
		int x=grt(i);
		if(col[x]==-1){
			col[x]=0;
			if(oppo[x]!=-1){
				assert(fa[oppo[x]]==oppo[x]);
				col[oppo[x]]=1;
			}
		}
		ans[i>>(sh-1)][i&((1<<(sh-1))-1)]=col[x];
	}
	if(sh==1)return;
	for(int i=0;i<n;i++){
		pos2[(((i&1)^ans[0][i>>1])<<(sh-1))|(i>>1)]=pos[i]>>1;
	}
	memcpy(pos,pos2,n*sizeof(pos[0]));
	solve(_x+1,_y,sh-1,pos);
	solve(_x+1,_y+(n>>2),sh-1,pos+(n>>1));
}
int pos[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("left.in","r",stdin);
	freopen("left.out","w",stdout);
#endif
	for(int sh;sh=ni,sh;){
		int n=1<<sh;
		for(int i=0;i<n;i++){
			pos[ni]=i;
		}
		solve(0,0,sh,pos);
		for(int i=1;i<=sh*2-1;i++){
			for(int j=0;j<(n>>1);j++){
				putchar('0'+mat[i][j]);
			}
			putchar('\n');
		}
	}
	return 0;
}
