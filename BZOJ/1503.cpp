#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef long long lint;
#define cout cerr
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
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=200010;
namespace T{
#define lson(x) son[x][0]
#define rson(x) son[x][1]
	int son[N][2],fa[N],size[N],val[N],wei[N],n=0,root=0;
	inline void init(){
		memset(son,0,sizeof(son));
		size[0]=0;
		memset(fa,0,sizeof(fa));
	}
	inline int nn(int v,int f){
		n++,fa[n]=f,size[n]=1,val[n]=v,wei[n]=rand();
		return n;
	}
	inline bool side(int x){
		assert(fa[x]);
		return rson(fa[x])==x;
	}
	inline void up(int x){
		size[x]=size[lson(x)]+size[rson(x)]+1;
	}
	inline void rot(int x){
		bool d=side(x);
		int f=fa[x],g=fa[f],s=son[x][!d];
		if(s){fa[s]=f;}son[f][d]=s,son[x][!d]=f;
		if(g){son[g][side(f)]=x;}else{root=x;}
		fa[x]=g,fa[f]=x;
		up(f),up(x);
	}
	inline void carry(int x){
		for(;fa[x]&&wei[fa[x]]>wei[x];rot(x));
	}
	inline void insert(int v){
		if(root==0){
			root=nn(v,0);
			return;
		}
		for(int x=root;;x=son[x][v>val[x]]){
			size[x]++;
			if(son[x][v>val[x]]==0){
				carry(son[x][v>val[x]]=nn(v,x));
				return;
			}
		}
	}
	inline int kth(int x,int k){//return node
		if(x==0){
			return 0;
		}
		if(k<=size[lson(x)]){
			return kth(lson(x),k);
		}
		if(k>size[lson(x)]+1){
			return kth(rson(x),k-size[lson(x)]-1);
		}
		return x;
	}
	inline void split(int k){
		insert(k),wei[n]=-1,carry(n);
		assert(n==root);
		fa[lson(n)]=fa[rson(n)]=0;
	}
}
int main(){
	srand(2344553);
	int cnt=0;
	for(int tot=ni,mn=ni,delta=0,val;tot--;){//real=val+delta
		switch(nc()){
			case 'I':
				val=ni;
				if(val>=mn){
					T::insert(val-delta);
				}
				break;
			case 'A':
				delta+=ni;
				break;
			case 'S':
				delta-=ni;
				T::split(mn-delta);
				cnt+=T::size[T::son[T::root][0]];
				T::root=T::son[T::root][1];
				break;
			case 'F':
				int node=T::kth(T::root,T::size[T::root]+1-ni);
				printf("%d\n",node?(T::val[node]+delta):-1);
				break;
		}
	}
	printf("%d\n",cnt);
}
