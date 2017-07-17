#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cassert>
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
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
const int N=10010;
namespace T{
	//shape
#define lson(x) son[x][0]
#define rson(x) son[x][1]
	int fa[N],son[N][2];
	//info
	bool rev[N];
	inline void init(){
		memset(fa,0,sizeof(fa));
		memset(son,0,sizeof(son));
		memset(rev,0,sizeof(rev));
	}
	//basic
	inline void flip(int x){
		if(x){
			rev[x]=!rev[x];
		}
	}
	inline void down(int x){
		if(rev[x]){
			swap(lson(x),rson(x));
			flip(lson(x)),flip(rson(x));
			rev[x]=false;
		}
	}
	inline int side(int x){
		down(fa[x]);
		if(lson(fa[x])==x){
			return 0;
		}
		if(rson(fa[x])==x){
			return 1;
		}
		return -1;
	}
	//splay
	inline void rot(int x){
		down(fa[x]),down(x);
		bool d=side(x);
		int f=fa[x],&s=son[x][!d];
		son[f][d]=s,fa[s]=f,s=f;
		if(~side(f)){
			son[fa[f]][side(f)]=x;
		}
		fa[x]=fa[f],fa[f]=x;
	}
	inline int splay(int x){
		while(~side(x)){
			if(side(fa[x])==-1){
				rot(x);
			}else if(side(fa[x])==side(x)){
				rot(fa[x]),rot(x);
			}else{
				rot(x),rot(x);
			}
		}
		return x;
	}
	//lct
	inline void access(int x){
		for(rson(splay(x))=0;fa[x];rot(rson(splay(fa[x]))=x));
	}
	inline void chroot(int x){
		access(x),flip(x);
	}
	inline void link(int u,int v){
		access(u),chroot(v),fa[rson(u)=v]=u;
	}
	inline void cut(int x){
		access(x),fa[lson(x)]=0,lson(x)=0;
	}
	inline bool con(int u,int v){
		access(u),access(v);
		return fa[u];
	}
	inline int par(int x){
		access(x);
		int t=lson(x);
		for(;rson(t);t=rson(t));
		return splay(t);
	}
	inline void cut(int u,int v){
		assert(par(u)==v||par(v)==u);
		cut(par(u)==v?u:v);
	}
}
int main(){
	T::init();
	ni;
	for(int tot=ni;tot--;){
		switch(nc()){
			case 'C':
				T::link(ni,ni);
				break;
			case 'D':
				T::cut(ni,ni);
				break;
			case 'Q':
				puts(T::con(ni,ni)?"Yes":"No");
				break;
		}
	}
	return 0;
}
