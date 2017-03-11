#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#define M 100010
#define N 110
#define D (M*2)
#define lson(x) son[x][0]
#define rson(x) son[x][1]
#define INF 0x7f7f7f7f
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
struct edge{
	int u,v,c;
}e[M];
ostream & operator << (ostream & out,edge e){
	printf("(%d,%d)[%d] ",e.u,e.v,e.c);
	return out;
}
struct kruskal{
	int fa[N],rank[N];
	int root(int x){
		if(fa[x]){
			return fa[x]=root(fa[x]);
		}
		return x;
	}
	bool uni(edge e){
		int u=root(e.u),v=root(e.v);
		if(u==v){
			return false;
		}
		if(rank[u]>rank[v]){
			swap(u,v);
		}
		fa[u]=v;
		if(rank[u]==rank[v]){
			rank[v]++;
		}
		return true;
	}
	void join(int *sa,int *sb,int *ans){
		memset(fa,0,sizeof(fa));
		memset(rank,0,sizeof(rank));
		int id;
		while((*sa)&&(*sb)){
			if(e[*sa].c<e[*sb].c){
				id=*(sa++);
			}else{
				id=*(sb++);
			}
			if(uni(e[id])){
				*(ans++)=id;
			}
		}
		if(*sb){
			sa=sb;
		}
		for(;*sa;sa++){
			if(uni(e[*sa])){
				*(ans++)=*sa;
			}
		}
		*ans=0;
	}
}kru;
struct segtree{
	int lend[D],rend[D],mid[D],son[D][2],seq[D][N],cal[M][N],root,ntop,ctop;
	inline void init(){
		memset(son,-1,sizeof(son));
		ntop=ctop=0;
	}
	int build(int l,int r){
		int x=ntop++;
		lend[x]=l,rend[x]=r,mid[x]=(l+r)>>1;
		if(l==r){
			seq[x][0]=l;
			seq[x][1]=0;
			return x;
		}
		lson(x)=build(l,mid[x]);
		rson(x)=build(mid[x]+1,r);
		kru.join(seq[lson(x)],seq[rson(x)],seq[x]);
		return x;
	}
	int* query(int x,int l,int r){
		if(lend[x]==l&&rend[x]==r){
			return seq[x];
		}
		if(r<=mid[x]){
			return query(lson(x),l,r);
		}
		if(l>mid[x]){
			return query(rson(x),l,r);
		}
		int *ret=cal[ctop++];
		kru.join(query(lson(x),l,mid[x]),query(rson(x),mid[x]+1,r),ret);
		return ret;
	}
}seg;
int main(){
	int n=ni(),m=ni(),tot=ni(),l,r,*seq,ans;
	for(int i=1;i<=m;i++){
		e[i].u=ni(),e[i].v=ni(),e[i].c=ni();
	}
	seg.init();
	seg.root=seg.build(1,m);
	while(tot--){
		l=ni(),r=ni();
		seg.ctop=0;
		seq=seg.query(seg.root,l,r);
		ans=0;
		for(int i=0;seq[i];i++){
			ans+=e[seq[i]].c;
		}
		printf("%d\n",ans);
	}
}
