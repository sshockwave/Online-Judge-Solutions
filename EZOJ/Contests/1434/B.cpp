#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
const int N=52010,logN=20,INF=0x7f7f7f7f;
int nxt[logN][N];
int sd[logN][N];
struct Edge{
	int u,v;
}edg[N],lst1[N],lst2[N];
int _cnt[N];
namespace seg{
	struct Node;
	typedef Node* node;
	int ask(node x,int u,int v);
	struct Node{
		node lson,rson;
		int dep,n;
		int u,v;
		map<int,int>xsd;
		map<int,Edge>xtofa;
		inline int pre_init(int el,int er){//get sd,nxt,em,n
			n=0;
			for(int i=u;n==0||i!=u;++n,i=nxt[dep][i]){
				_cnt[i]=n;
			}
			if(n==3)return assert(el>er),-1;
			int em,bal=INF;
			for(int i=el;i<=er;i++){
				int u=edg[i].u,v=edg[i].v;
				if(_cnt[u]>_cnt[v]){
					swap(u,v);
				}
				int nbal=max(_cnt[v]-_cnt[u],_cnt[u]+n-_cnt[v]);
				if(nbal<bal){
					em=i,bal=nbal;
				}
			}
			u=edg[em].u,v=edg[em].v;
			if(_cnt[u]>_cnt[v]){
				swap(u,v);
			}
			sd[dep][u]=-1,sd[dep][v]=-2;
			for(int p=u;p=nxt[dep][p],p!=v;){
				sd[dep][p]=0,nxt[dep+1][p]=nxt[dep][p];
			}
			for(int p=v;p=nxt[dep][p],p!=u;){
				sd[dep][p]=1,nxt[dep+1][p]=nxt[dep][p];
			}
			for(int p=u,t=0;t==0||p!=u;++t,p=nxt[dep][p]){
				xsd[p]=sd[dep][p];
			}
			int ls1=0,ls2=0;
			Edge tmp=edg[em];
			for(int i=el;i<=er;i++){
				if(i==em)continue;
				if(sd[dep][edg[i].u]==0||sd[dep][edg[i].v]==0){
					lst1[ls1++]=edg[i];
				}else{
					assert(sd[dep][edg[i].u]==1||sd[dep][edg[i].v]==1);
					lst2[ls2++]=edg[i];
				}
			}
			memcpy(edg+el,lst1,ls1*sizeof(edg[0]));
			edg[em=el+ls1]=tmp;
			memcpy(edg+el+ls1+1,lst2,ls2*sizeof(edg[0]));
			nxt[dep+1][u]=nxt[dep][u],nxt[dep+1][v]=u;//next for lson
			return em;
		}
		inline void reroute_nxt(){
			nxt[dep+1][u]=v,nxt[dep+1][v]=nxt[dep][v];//next for rson
		}
		inline void post_init(){//get tofa
			if(n==3)return;
			for(int i=u,t=0;t==0||i!=u;++t,i=nxt[dep][i]){
				const node s=sd[dep][i]==0?lson:rson;
				xtofa[i]=(Edge){ask(s,i,u),ask(s,i,v)};
				//cout<<"dis["<<i<<"]["<<u<<"]="<<xtofa[i].u<<endl;
				//cout<<"dis["<<i<<"]["<<v<<"]="<<xtofa[i].v<<endl;
			}
		}
	}pool[N<<1];
	int ask(node x,int u,int v){
		if(u==v)return 0;
		if(x->n==3)return 1;
		const Edge du=x->xtofa[u];
		const Edge dv=x->xtofa[v];
		const int sdu=x->xsd[u],sdv=x->xsd[v];
		if(sdu==sdv)return ask(sdu==0?x->lson:x->rson,u,v);
		return min(min(du.u+dv.u,du.v+dv.v),min(du.u+dv.v,du.v+dv.u)+1);
	}
	node build(int el,int er,int stnd,int d){
		static node n=pool;
		node x=n++;
		x->dep=d,x->u=stnd;
		int em=x->pre_init(el,er);
		if(x->n>3){
			x->lson=build(el,em-1,x->u,d+1);
			x->reroute_nxt();
			x->rson=build(em+1,er,x->v,d+1);
		}
		x->post_init();
		return x;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("bsh.in","r",stdin);
	freopen("bsh.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n-3;i++){
		edg[i]=(Edge){ni,ni};
	}
	for(int i=1;i<=n;i++){
		nxt[0][i]=i<n?i+1:1;
	}
	seg::node rt=seg::build(1,n-3,1,0);
	for(int tot=ni;tot--;printf("%d\n",seg::ask(rt,ni,ni)));
	return 0;
}
