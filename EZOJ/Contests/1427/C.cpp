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
const int N=100010,INF=0x7f7f7f7f;
struct pii{
	int d,v;
};
typedef vector<pii>vi;
namespace T{
	const int E=::N<<1;
	int to[E],bro[E],head[N],e;
	vi lg2;
	inline void init(int n){
		e=0;
		mset(head+1,-1,n);
		lg2.clear();
		lg2.push_back((pii){0,0});
		lg2.push_back((pii){1,1});
		for(int sh=0;(1<<sh)<n;sh++){
			lg2.push_back((pii){(1<<sh)+1,sh+2});
		}
		lg2.push_back((pii){INF,0});
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int dep[N];
	vi f[N];
	void dfs(int x,int fa){
		dep[x]=dep[fa]+1;
		int soncnt=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x);
				soncnt++;
			}
		}
		f[x].clear();
		if(soncnt==0){
			for(vi::iterator it=lg2.begin(),ti=lg2.end();it!=ti&&it->d<=dep[x];it++){
				f[x].push_back(*it);
			}
		}else{
			int mx1=-INF,mx2=-INF;
			int mxp1=0;
			for(int i=head[x],v;~i;i=bro[i]){
				if((v=to[i])!=fa){
					int t=f[v].front().v+1;
					if(t>mx1){
						mx2=mx1,mx1=t,mxp1=v;
					}else if(t>mx2){
						mx2=t;
					}
				}
			}
			vi &vec=f[x];
			f[mxp1].push_back((pii){INF,0});
			for(vi::iterator i=f[mxp1].begin(),j=lg2.begin();min(i->d-1,j->d)<=dep[x];){
				pii t=(pii){max(i->d-1,j->d),i->v};
				if(mx2!=-INF){
					apmax(t.v,mx2+j->v);
				}
				if(!vec.empty()&&vec.back().d==t.d){
					vec.back().v=t.v;
				}else if(vec.empty()||vec.back().v!=t.v){
					vec.push_back(t);
				}
				(i+1)->d-1<(j+1)->d?++i:++j;
			}
		}
	}
}
inline int Main(){
	int n=ni;
	T::init(n);
	for(int i=1;i<n;i++){
		T::add(ni,ni);
	}
	T::dep[0]=-1,T::dfs(1,0);
	return T::f[1].front().v;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
