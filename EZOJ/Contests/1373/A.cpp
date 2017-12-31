#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
#include <vector>
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
const int N=5010;
int fa[N];
int c[N],d[N];
struct pii{
	int v,w;
	inline friend bool operator < (const pii &a,const pii &b){
		return a.v!=b.v?a.v>b.v:a.w<b.w;
	}
}item[N];
vector<pii>vec[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("shop.in","r",stdin);
	freopen("shop.out","w",stdout);
#endif
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		item[i]=(pii){ni,ni};
	}
	for(int i=1;i<=n;i++){
		fa[i]=i==1?0:ni;
	}
	int mx=0;
	for(int i=1;i<=m;i++){
		c[i]=ni;
		apmax(mx,c[i]);
	}
	vec[0].push_back((pii){0,0});
	for(int i=1;i<=n;i++){
		priority_queue<pii>q;
		for(vector<pii>::iterator it=vec[fa[i]].begin(),ti=vec[fa[i]].end();it!=ti;it++){
			q.push(*it);
		}
		int last=-1;
		while(!q.empty()){
			pii t=q.top();
			q.pop();
			assert(t.v<=mx);
			if(t.w<=last)continue;
			last=t.w;
			vec[i].push_back(t);
			if(t.v+item[i].v<=mx){
				q.push((pii){t.v+item[i].v,t.w+item[i].w});
			}
		}
	}
	for(int i=1;i<=m;i++){
		int tmp=ni;
		vector<pii>&vc=vec[tmp];
		int l=0,r=vc.size()-1;
		while(l<r){
			int m=((l+r)>>1)+1;
			if(vc[m].v<=c[i]){
				l=m;
			}else{
				r=m-1;
			}
		}
		printf("%d\n",vc[l].w);
	}
	return 0;
}
