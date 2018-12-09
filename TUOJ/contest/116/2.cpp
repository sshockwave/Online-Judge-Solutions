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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=40;
namespace T{
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node son[2];
		int size;
	}pool[1000000],Null;
	typedef map<pair<node,node>,node>mnn;
	inline node nn(node lson,node rson){
		static mnn mp;
		mnn::iterator it=mp.find(make_pair(lson,rson));
		if(it!=mp.end())return it->second;
		static node n=pool;
		const node x=mp[make_pair(lson,rson)]=n++;
		x->son[0]=lson,x->son[1]=rson;
		x->size=lson->size+rson->size;
		return x;
	}
	node mg(node u,node v){
		if(u==null||v==null)return u!=null?u:v;
		static mnn mp;
		if(u>v){
			swap(u,v);
		}
		mnn::iterator it=mp.find(make_pair(u,v));
		if(it!=mp.end())return it->second;
		return mp[make_pair(u,v)]=nn(mg(u->son[0],v->son[0]),mg(u->son[1],v->son[1]));
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->son[0]=null->son[1]=null;
	}
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	T::init();
	const T::node end=T::nn(T::null,T::null);
	end->size=1;
	const int n=ni;
	T::node rt=T::null;
	for(int tot=ni;tot--;){
		scanf("%s",s+1);
		T::node x=end;
		for(int i=n;i>=1;i--){
			using T::nn;
			using T::null;
			x=s[i]=='0'?nn(x,null):s[i]=='1'?nn(null,x):nn(x,x);
		}
		rt=T::mg(rt,x);
	}
	printf("%d\n",rt->size);
	return 0;
}
