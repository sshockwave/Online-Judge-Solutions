#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=200010,M=100,E=N*2,D=N*2,INF=0x7f7f7f7f;
int cval[M];
struct Tree{
	int to[E],bro[E],color[E],head[N];
	Tree(){
		memset(head,-1,sizeof(head));
	}
	inline void add_edge(int u,int v,int c){
		static int etop=0;
		to[etop]=v;
		bro[etop]=head[u];
		color[etop]=c;
		head[u]=etop++;
	}
}T;
int n,m,l,r;
namespace solve34{
	struct SegmentTree{
		typedef SegmentTree node;
		int lend,rend,mid,mn;
		node *lson,*rson;
		inline void up(){
			assert(lend!=rend);
			mn=min(lson->mn,rson->mn);
		}
		void build(int l,int r){
			static node *n=new node[D];
			lend=l,rend=r,mid=(l+r)>>1;
			if(l!=r){
				(lson=n++)->build(l,mid);
				(rson=n++)->build(mid+1,r);
			}
		}
		void set(int x,int val){
			assert(lend<=x&&x<=rend);
			if(lend==rend){
				mn=val;
			}else{
				(x<=mid?lson:rson)->set(x,val);
				up();
			}
		}
		int ask(int l,int r){
			assert(l<=r);
			assert(lend<=l&&r<=rend);
			if(lend==l&&rend==r){
				return mn;
			}
			if(r<=mid){
				return lson->ask(l,r);
			}
			if(l>mid){
				return rson->ask(l,r);
			}
			return min(lson->ask(l,mid),rson->ask(mid+1,r));
		}
	}seg;
	int du[N];
	int pt[N],color[N];//i to i+1's color
	inline int getst(){
		for(int i=1;i<=n;i++){
			if(du[i]==1){
				return i;
			}
		}
	}
	inline void getpt(){
		pt[0]=0;
		for(int x=getst(),i=1;i<=n;i++){
			pt[i]=x;
			for(int j=T.head[x];~j;j=T.bro[j]){
				if(T.to[j]!=pt[i-1]){
					color[i]=T.color[j];
					x=T.to[j];
					break;
				}
			}
		}
	}
	int pre[N],bef[N];
	inline int work(){
		getpt();
		pre[1]=color[0]=0;
		seg.build(1,n);
		for(int i=2;i<=n;i++){
			pre[i]=pre[i-1];
			if(color[i-1]!=color[i-2]){
				pre[i]+=cval[color[i-1]];
			}
			seg.set(i,pre[i]);
		}
		int c=0;
		for(int i=1;i<=n;i++){
			if(c!=color[i-1]){
				bef[i]=i-1;
				c=color[i-1];
			}else{
				bef[i]=bef[i-1];
			}
		}
		int ans=-INF;
		for(int i=l+1;i<=n;i++){
			if(max(i-r,1)<=min(i-l,bef[i])){
				apmax(ans,pre[i]-seg.ask(max(i-r,1),min(i-l,bef[i])));
			}
			if(max(max(i-r,1),bef[i]+1)<=i-l){
				apmax(ans,pre[i]-seg.ask(max(max(i-r,1),bef[i]+1),i-l)+cval[color[i-1]]);
			}
		}
		return ans;
	}
}
int main(){
	n=ni,m=ni,l=ni,r=ni;
	for(int i=1;i<=m;i++){
		cval[i]=ni;
	}
	int mxdu=0;
	for(int i=1;i<n;i++){
		int u=ni,v=ni,c=ni;
		T.add_edge(u,v,c);
		T.add_edge(v,u,c);
		apmax(mxdu,++solve34::du[u]);
		apmax(mxdu,++solve34::du[v]);
	}
	if(mxdu<=2){
		printf("%d\n",solve34::work());
		return 0;
	}
}
