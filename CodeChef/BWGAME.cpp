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
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=100010;
int root[N],val[N];
namespace LT{
	int lson[N],rson[N],hei[N];
	inline void init(){
		memset(lson,0,sizeof(lson));
		memset(rson,0,sizeof(rson));
		memset(hei,0,sizeof(hei));
	}
	inline int ins(int x,int n){
		assert(lson[n]==0&&rson[n]==0);
		if(x==0){
			hei[n]=1;
			return n;
		}
		if(val[x]>=val[n]){
			lson[n]=x;
			hei[n]=1;
			return n;
		}
		rson[x]=ins(rson[x],n);
		if(hei[rson[x]]>hei[lson[x]]){
			swap(lson[x],rson[x]);
		}
		return x;
	}
	int merge(int u,int v){
		if(u==0||v==0){
			return u+v;
		}
		if(val[u]>val[v]){
			swap(u,v);
		}
		rson[u]=merge(rson[u],v);
		if(hei[rson[u]]>hei[lson[u]]){
			swap(lson[u],rson[u]);
		}
		hei[u]=hei[rson[u]]-1;
		return u;
	}
	inline int del(int x){
		return merge(lson[x],rson[x]);
	}
}
inline int det(int n){
	int sig=0;
	for(int i=1;i<=n;i++){
		if(root[i]==0){
			return 0;
		}
		int v=val[root[i]];
		if(root[i]!=i){
			sig++;
		}
		root[i]=LT::del(root[i]);
		if(val[root[i]]==v){
			return 0;
		}
		root[v+1]=LT::merge(root[i],root[v+1]);
	}
	return (sig&2)?-1:1;
}
int main(){
	for(int tot=ni;tot--;){
		int n=ni;
		memset(root,0,sizeof(root));
		LT::init();
		for(int i=1;i<=n;i++){
			int l=ni;
			val[i]=ni;
			root[l]=LT::ins(root[l],i);
		}
		int ans=det(n);
		if(ans>0){
			puts("Alex");
		}else if(ans<0){
			puts("Fedya");
		}else{
			puts("Draw");
		}
	}
}