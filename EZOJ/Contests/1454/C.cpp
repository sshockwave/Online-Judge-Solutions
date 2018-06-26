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
const int N=30010,M=128,O=10007;
namespace gmath{
	const int N=::O;
	int inv[N];
	inline void main(int n=O-1){
		inv[1]=1;
		for(int i=2;i<=n;i++){
			inv[i]=O-(lint)O/i*inv[O%i]%O;
			assert((lint)inv[i]*i%O==1);
		}
	}
}
struct Mat{
	int a[3][3];
	inline void gmul(const Mat &x,const Mat &y){
		for(int i=0;i<2;i++){//2!!!!
			for(int j=0;j<3;j++){
				lint ans=0;
				ans+=(lint)x.a[i][0]*y.a[0][j];
				ans+=(lint)x.a[i][1]*y.a[1][j];
				ans+=(lint)x.a[i][2]*y.a[2][j];
				a[i][j]=ans%O;
			}
		}
		assert(x.a[2][0]==0&&x.a[2][1]==0&&x.a[2][2]==1);
		assert(y.a[2][0]==0&&y.a[2][1]==0&&y.a[2][2]==1);
		a[2][0]=0,a[2][1]=0,a[2][2]=1;
	}
};
int shcnt,mxv,pval[N];
void fwt(int a[],const int sh=shcnt){
	if(sh==0)return;
	const int full=1<<sh,half=full>>1;
	for(int i=0;i<mxv;i+=full){
		for(int j=i;j<i+half;j++){
			const int p=a[j],q=a[j+half];
			a[j]=(p+q)%O;
			a[j+half]=(p+O-q)%O;
		}
	}
	return fwt(a,sh-1);
}
int matval[N][M],cnt0[N][M],sumo[N][M];
int idx[N];
namespace seg{
	const int N=::N<<1;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int l,m,r;
		Mat mat[M];
		inline void init(){
			assert(l==r);
			const int x=idx[m];
			for(int i=0;i<mxv;i++){
				const int v=cnt0[x][i]?0:matval[x][i];
				mat[i].a[0][0]=v;
				mat[i].a[0][1]=0;
				mat[i].a[0][2]=v;
				mat[i].a[1][0]=v;
				mat[i].a[1][1]=1;
				mat[i].a[1][2]=(v+sumo[x][i])%O;
				mat[i].a[2][0]=0;
				mat[i].a[2][1]=0;
				mat[i].a[2][2]=1;
			}
		}
		inline void up(){
			for(int i=0;i<mxv;i++){
				mat[i].gmul(lson->mat[i],rson->mat[i]);
			}
		}
		inline void ap(int f[],int g[]){
			for(int i=0;i<mxv;i++){
				f[i]=mat[i].a[0][2];
				g[i]=mat[i].a[1][2];
			}
		}
	}pool[N];
	node build(int l,int r){
		static node n=pool;
		const node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->init();
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void upd(node x,int p){
		if(x->l==x->r){
			x->init();
		}else{
			upd(p<=x->m?x->lson:x->rson,p);
			x->up();
		}
	}
}
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e=0;
	int fa[N],son[N],size[N],top[N],tope[N],dfn[N];
	inline void init(int n){
		mset(head+1,-1,n);
		son[0]=0,fa[1]=0,size[0]=0;
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	seg::node rt[N];
	inline void psh_to_fa(int x){
		assert(top[x]==x&&fa[x]);
		static int f[M],g[M];
		rt[x]->ap(f,g);
		for(int i=0;i<mxv;i++){
			++f[i];
			if(f[i]==O){
				f[i]=0;
			}
			if(f[i]==0){
				++cnt0[fa[x]][i];
			}else{
				matval[fa[x]][i]=(lint)matval[fa[x]][i]*f[i]%O;
			}
			sumo[fa[x]][i]=(sumo[fa[x]][i]+g[i])%O;
		}
	}
	inline void del_fr_fa(int x){
		assert(top[x]==x&&fa[x]);
		static int f[M],g[M];
		rt[x]->ap(f,g);
		for(int i=0;i<mxv;i++){
			++f[i];
			if(f[i]==O){
				f[i]=0;
			}
			if(f[i]==0){
				assert(cnt0[fa[x]][i]);
				--cnt0[fa[x]][i];
			}else{
				matval[fa[x]][i]=(lint)matval[fa[x]][i]*gmath::inv[f[i]]%O;
			}
			sumo[fa[x]][i]=(sumo[fa[x]][i]+O-g[i])%O;
		}
	}
	void dfs1(int x){
		son[x]=0;
		size[x]=1;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])==fa[x])continue;
			fa[v]=x;
			dfs1(v);
			size[x]+=size[v];
			if(size[v]>size[son[x]]){
				son[x]=v;
			}
		}
	}
	inline void dfs2(){
		idx[dfn[1]=1]=1;
		const int n=size[1];
		for(int p=1;p<=n;p++){
			const int x=idx[p];
			top[x]=son[fa[x]]==x?top[fa[x]]:x;
			mset(matval[x],0,mxv);
			matval[x][pval[x]]=1;
			fwt(matval[x]);
			for(int i=0;i<mxv;i++){
				if(matval[x][i]){
					cnt0[x][i]=0;
				}else{
					matval[x][i]=1;
					cnt0[x][i]=1;
				}
				sumo[x][i]=0;
			}
			if(son[x]){
				int tim=p;
				idx[dfn[son[x]]=tim+1]=son[x],tim+=size[son[x]];
				for(int i=head[x],v;~i;i=bro[i]){
					if((v=to[i])==son[x]||v==fa[x])continue;
					idx[dfn[v]=tim+1]=v,tim+=size[v];
				}
			}else{
				tope[top[x]]=dfn[x];
			}
		}
		for(int p=n;p>=1;p--){
			const int x=idx[p];
			if(top[x]==x){
				rt[x]=seg::build(dfn[x],tope[x]);
				if(fa[x]){
					psh_to_fa(x);
				}
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
#endif
	gmath::main();
	const int n=ni;
	shcnt=0,mxv=1;
	for(int tt=ni;mxv<tt;mxv<<=1,shcnt++);
	const int iv=gmath::inv[mxv%O];
	T::init(n);
	for(int i=1;i<=n;i++){
		pval[i]=ni;
	}
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dfs1(1),T::dfs2();
	bool calc=false;
	for(int tot=ni;tot--;){
		static char str[20];
		scanf("%s",str);
		if(str[0]=='C'){//alt
			int x=ni;
			static int tmpf[M];
			mset(tmpf,0,mxv);
			tmpf[pval[x]]=1;
			fwt(tmpf);
			for(int i=0;i<mxv;i++){
				if(tmpf[i]==0){
					assert(cnt0[x][i]);
					--cnt0[x][i];
				}else{
					matval[x][i]=(lint)matval[x][i]*gmath::inv[tmpf[i]]%O;
					assert(matval[x][i]);
				}
			}
			mset(tmpf,0,mxv);
			tmpf[pval[x]=ni]=1;
			fwt(tmpf);
			for(int i=0;i<mxv;i++){
				if(tmpf[i]==0){
					++cnt0[x][i];
				}else{
					matval[x][i]=(lint)matval[x][i]*tmpf[i]%O;
					assert(matval[x][i]);
				}
			}
			using namespace T;
			for(;x;x=fa[top[x]]){
				if(fa[top[x]]){
					del_fr_fa(top[x]);
				}
				seg::upd(rt[top[x]],dfn[x]);
				if(fa[top[x]]){
					psh_to_fa(top[x]);
				}
			}
			calc=false;
		}else{//ask
			static int f[M],g[M];
			if(!calc){
				calc=true;
				T::rt[1]->ap(f,g);
				fwt(g);
				for(int i=0;i<mxv;i++){
					g[i]=(lint)g[i]*iv%O;
				}
			}
			printf("%d\n",g[ni]);
		}
	}
	return 0;
}
