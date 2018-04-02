#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=100010,INF=0x7f7f7f7f;
typedef vector<int>vi;
typedef vi::iterator iter;
typedef vi::reverse_iterator rter;
struct Mat{
	int a[2][2];
	inline void id(){
		memset(a,0,sizeof(a));
	}
	inline void gmul(const Mat &x,const Mat &y){
		memset(a,127,sizeof(a));
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				for(int k=0;k<2;k++){
					apmin(a[i][j],x.a[i][k]+y.a[k][j]);
				}
			}
		}
	}
	inline void ap(int f[2]){
		int f0=f[0],f1=f[1];
		f[0]=min(f0+a[0][0],f1+a[1][0]);
		f[1]=min(f0+a[0][1],f1+a[1][1]);
	}
};
int n;
int bln[N];
int lend[N],rend[N];
namespace T{
	const int logN=19;
	vector<int>son[N],ldis[N],rdis[N];
	inline void ae(int u,int v){
		son[u].push_back(v);
	}
	int fa[N][logN],dep[N],ldep[N];
	Mat f[N][logN];
	void dfs(int x){
		dep[x]=dep[fa[x][0]]+1;
		for(int &j=ldep[x];fa[x][j];j++){
			fa[x][j+1]=fa[fa[x][j]][j];
			f[x][j+1].gmul(f[x][j],f[fa[x][j]][j]);
		}
		for(iter i=son[x].begin();i!=son[x].end();i++){
			if(i==son[x].begin()){
				ldis[x].push_back(lend[*i]-lend[x]);
			}else{
				ldis[x].push_back(lend[*i]-rend[*(i-1)]+*ldis[x].rbegin()+1);
			}
		}
		for(rter i=son[x].rbegin();i!=son[x].rend();i++){
			if(i==son[x].rbegin()){
				rdis[x].push_back(rend[x]-rend[*i]);
			}else{
				rdis[x].push_back(lend[*(i-1)]-rend[*i]+*rdis[x].rbegin()+1);
			}
		}
		iter pl=ldis[x].begin();
		rter pr=rdis[x].rbegin();
		for(iter i=son[x].begin();i!=son[x].end();i++,pl++,pr++){
			if(*i!=fa[x][0]){
				f[*i][0]=(Mat){min(*pl,*pr+2),min(*pl,*pr)+1,min(*pl,*pr)+1,min(*pl+2,*pr)};
				fa[*i][0]=x,dfs(*i);
			}
		}
	}
	inline int getid(vector<int>&vec,int x){
		int l=0,r=vec.size();
		while(l<r){
			int m=(l+r)>>1;
			if(x<=lend[vec[m]]){
				r=m;
			}else{
				l=m+1;
			}
		}
		return l;
	}
	inline int getdisl(int u,int f){
		int x=getid(son[f],u);
		return x>0?ldis[f][x-1]+(u-rend[son[f][x-1]])+1:(u-lend[f]);
	}
	inline int getdisr(int v,int f){
		int y=getid(son[f],v),s=son[f].size();
		return y<s?rdis[f][s-y-1]+(lend[son[f][y]]-v)+1:(rend[f]-v);
	}
	inline void gf(int x,int f[],int fa){
		int disl=getdisl(x,fa);
		int disr=getdisr(x,fa);
		f[0]=min(disl,disr+1);
		f[1]=min(disl+1,disr);
	}
	inline int calcdis(int u,int v,int f){
		if(u==v)return 0;
		if(u>v){
			swap(u,v);
		}
		int x=getid(son[f],u),y=getid(son[f],v);
		int s=son[f].size(),ans=INF;
		apmin(ans,getdisl(u,f)+getdisr(v,f)+1);
		if(x==y){
			apmin(ans,v-u);
		}else{
			assert(x<s);
			assert(y>0);
			int cur=ldis[f][y-1]+1+(v-rend[son[f][y-1]]);
			if(x>0){
				cur-=ldis[f][x-1]+1;
				cur-=u-rend[son[f][x-1]];
			}else{
				cur-=u-lend[f];
			}
			apmin(ans,cur);
		}
		return ans;
	}
	inline int work(int u,int v){
		if(bln[u]==bln[v])return calcdis(u,v,bln[u]);
		int uf[2],vf[2];
		if(dep[bln[u]]!=dep[bln[v]]){
			if(dep[bln[u]]<dep[bln[v]]){
				swap(u,v);
			}
			gf(u,uf,bln[u]),u=bln[u];
			for(int j=ldep[u];j>=0;j--){
				if(dep[fa[u][j]]>dep[bln[v]]){
					f[u][j].ap(uf);
					u=fa[u][j];
				}
			}
			if(fa[u][0]==bln[v]){
				return min(calcdis(v,lend[u],bln[v])+uf[0],calcdis(v,rend[u],bln[v])+uf[1]);
			}else{
				f[u][0].ap(uf),u=fa[u][0];
				gf(v,vf,bln[v]),v=bln[v];
			}
		}else{
			gf(u,uf,bln[u]),u=bln[u];
			gf(v,vf,bln[v]),v=bln[v];
		}
		assert(dep[u]==dep[v]);
		for(int j=ldep[u]-1;j>=0;j--){
			if(fa[u][j]!=fa[v][j]){
				f[u][j].ap(uf),u=fa[u][j];
				f[v][j].ap(vf),v=fa[v][j];
				apmin(j,ldep[u]);
			}
		}
		assert(fa[u][0]==fa[v][0]);
		int ans=INF;
		apmin(ans,uf[0]+vf[0]+calcdis(lend[u],lend[v],fa[u][0]));
		apmin(ans,uf[0]+vf[1]+calcdis(lend[u],rend[v],fa[u][0]));
		apmin(ans,uf[1]+vf[0]+calcdis(rend[u],lend[v],fa[u][0]));
		apmin(ans,uf[1]+vf[1]+calcdis(rend[u],rend[v],fa[u][0]));
		return ans;
	}
}
vector<int>vec[N];
int stk[N],ss=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("city.in","r",stdin);
	freopen("city.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n-3;i++){
		int l=ni,r=ni;
		if(l==r)continue;
		if(l>r){
			swap(l,r);
		}
		vec[l].push_back(r);
	}
	int ps=0;
	ps++,lend[ps]=0,rend[ps]=n-1,stk[++ss]=ps;
	for(int i=0;i<n;i++){
		sort(vec[i].begin(),vec[i].end());
		for(;rend[stk[ss]]<i;ss--);
		for(rter it=vec[i].rbegin();it!=vec[i].rend();it++){
			ps++,lend[ps]=i,rend[ps]=*it;
			for(;rend[stk[ss]]<rend[ps];ss--);
			T::ae(stk[ss],ps),stk[++ss]=ps;
		}
		bln[i]=stk[ss];
	}
	T::fa[1][T::ldep[1]=0]=0,T::dfs(1);
	for(int tot=ni;tot--;){
		int l=ni,r=ni;
		printf("%d\n",T::work(l,r));
	}
	return 0;
}
