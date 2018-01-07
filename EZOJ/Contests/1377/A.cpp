#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
const int N=100010,INF=0x7f7f7f7f;
typedef vector<int>vi;
vi lhs[N],rhs[N];
inline bool eq(vi &a,vi &b){
	if(a.size()!=b.size())return false;
	for(int i=0,ti=a.size();i<ti;i++){
		if(a[i]!=b[i])return false;
	}
	return true;
}
set<int>fro[N];
inline void del(int u,int v){
	set<int>::iterator it=fro[v].find(u);
	if(it==fro[v].end())throw "Not enough edges.";
	fro[v].erase(it);
}
namespace T{
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lson,rson;
		int l,r;
		int dep;
		inline int len(){
			return r-l+1;
		}
		inline void up(){
			dep=max(lson->dep,rson->dep)+1;
		}
	}pool[N<<1],Null;
	node n;
	inline void init(){
		n=pool;
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
		null->dep=-1;
	}
	inline node nn(node x=null){
		return *n=*x,n++;
	}
	void dfs(node x){
		if(x==null)throw "Empty interval.";
		if(x->l!=x->r){
			dfs(x->lson);
			dfs(x->rson);
			int lenl=x->lson->len(),lenr=x->rson->len();
			if(lenl>lenr)throw "Left > right";
			for(int i=x->rson->l;i<=x->rson->r;i++){
				del(x->l+(i-x->l)%lenl,i);
			}
		}
		x->up();
	}
}
inline int gfir(int x){
	if(lhs[x].empty())throw "Supposed to have left merge";
	return *--lhs[x].end();
}
T::node solve(int l,int r){
	assert(l<=r);
	using namespace T;
	node x=null;
	for(vi::iterator it=rhs[l].begin();it!=rhs[l].end();it++){
		if(*it>r)break;
		if(gfir(*it)==l){
			node y=nn();
			y->l=l,y->r=*it-1;
			y->lson=x,y->rson=x!=null?solve(x->r+1,y->r):x;
			x=y;
		}
	}
	node y=nn();
	y->l=l,y->r=r;
	y->lson=x,y->rson=x!=null?solve(x->r+1,r):x;
	return y;
}
inline int Main(){
	int n=ni;
	for(int i=0;i<n;i++){
		lhs[i].clear(),rhs[i].clear(),fro[i].clear();
	}
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		if(u>v){
			swap(u,v);
		}
		lhs[v].push_back(u);
		rhs[u].push_back(v);
		fro[v].insert(u);
	}
	for(int i=0;i<n;i++){
		sort(lhs[i].begin(),lhs[i].end());
		sort(rhs[i].begin(),rhs[i].end());
	}
	T::init();
	try{
		T::node rt=solve(0,n-1);
		T::dfs(rt);
		for(int i=0;i<n;i++){
			if(!fro[i].empty())throw "Too many edges.";
		}
		return rt->dep;
	}catch(const char str[]){
		return -1;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("gymnastics.in","r",stdin);
	freopen("gymnastics.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
