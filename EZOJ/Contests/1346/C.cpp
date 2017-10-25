#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <utility>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=131072;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],val[E],head[N],e=0;
	lint dep[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v,int w){
		to[e]=v,bro[e]=head[u],val[e]=w,head[u]=e++;
	}
	inline void add(int u,int v,int w){
		ae(u,v,w),ae(v,u,w);
	}
	lint mx;
	inline void psh(vector<pair<lint,lint> >&vec,pair<lint,lint>p){
		if(!vec.empty()){
			pair<lint,lint>&lp=vec[vec.size()-1];
			if(lp.second<=p.second){
				return;
			}
			if(lp.first==p.first){
				lp=p;
				return;
			}
		}
		vec.push_back(p);
	}
	void dfs(int x,int fa,vector<pair<lint,lint> >&ans){
		if(bro[head[x]]==-1){
			ans.push_back(make_pair(dep[x],dep[x]));
			return;
		}
		int son1=0,son2;
		for(int i=head[x];~i;i=bro[i]){
			if(to[i]!=fa){
				son1^=i,son2=i;
			}
		}
		son1^=son2;
		vector<pair<lint,lint> >pool[2],*vec1=pool,*vec2=pool+1,ans1,ans2;
		dep[to[son1]]=dep[x]+val[son1],dfs(to[son1],x,*vec1);
		dep[to[son2]]=dep[x]+val[son2],dfs(to[son2],x,*vec2);
		if(vec1->size()>vec2->size()){
			swap(son1,son2),swap(vec1,vec2);
		}
		for(int i=0,j=0,n2=vec2->size(),k=0,n=vec1->size();i<n;i++){
			for(;j<n2&&(*vec1)[i].second+(*vec2)[j].first-(dep[x]<<1)<=mx;j++);
			for(;k<n2&&(*vec2)[k].second+(*vec1)[i].first-(dep[x]<<1)>mx;k++);
			if(j){
				ans1.push_back(make_pair((*vec1)[i].first,(*vec2)[j-1].second));
			}
			if(k<n2){
				ans2.push_back(make_pair((*vec2)[k].first,(*vec1)[i].second));
			}
		}
		for(int i=1,n1=ans1.size(),n2=ans2.size(),j=0,k=0,n=n1+n2;i<=n;i++){
			if(k==n2||(j<n1&&ans1[j].first<ans2[k].first)){
				psh(ans,ans1[j++]);
			}else{
				psh(ans,ans2[k++]);
			}
		}
	}
}
inline bool check(lint mx){
	T::mx=mx;
	vector<pair<lint,lint> >ans;
	T::dfs(1,0,ans);
	return !ans.empty();
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("shik.in","r",stdin);
	freopen("shik.out","w",stdout);
#endif
	int n=ni;
	T::init();
	lint l=0,r=0;
	for(int i=2,u,w;i<=n;u=ni,w=ni,r+=w,T::add(i++,u,w));
	for(lint m;l<r;m=(l+r)>>1,check(m)?(r=m):(l=m+1));
	printf("%lld\n",l);
	return 0;
}
