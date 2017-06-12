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
	if(a<b){
		a=b;
	}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=100010,INF=0x7f7f7f7f;
namespace T{
	#define lson(x) son[0][x]
	#define rson(x) son[1][x]
	typedef int info[N];
	int n=0,root=0;
	info son[2],fa,side,key,val,delta,mnval,mnode[2];
	inline void up(int x){
		mnode[0][x]=lson(x)?mnode[0][lson(x)]:x;
		mnode[1][x]=rson(x)?mnode[1][rson(x)]:x;
		mnval[x]=val[x];
		if(lson(x)){
			apmin(mnval[x],mnval[lson(x)]);
		}
		if(rson(x)){
			apmin(mnval[x],mnval[rson(x)]);
		}
	}
	inline void all(int x,int d){
		if(x){
			val[x]+=d,delta[x]+=d,mnval[x]+=d;
		}
	}
	inline void down(int x){
		if(delta[x]){
			all(lson(x),delta[x]),all(rson(x),delta[x]),delta[x]=0;
		}
	}
	inline void rot(int x){
		assert(~x);
		down(fa[x]),down(x);
		bool d=!side[x];
		son[!d][fa[x]]=son[d][x];
		if(son[d][x]){
			fa[son[d][x]]=fa[x],side[son[d][x]]=!d;
		}
		son[d][x]=fa[x],side[x]=side[fa[x]],fa[x]=fa[fa[x]];
		side[son[d][x]]=d,fa[son[d][x]]=x;
		if(~side[x]){
			son[side[x]][fa[x]]=x;
		}else{
			root=x;
		}
		up(son[d][x]),up(x);
	}
	inline void splay(int x){
		while(~side[x]){
			if(side[fa[x]]==-1){
				rot(x);
			}else if(side[fa[x]]==side[x]){
				rot(fa[x]),rot(x);
			}else{
				rot(x),rot(x);
			}
		}
	}
	inline void insert(int x,int k){
		if(x==0){
			key[++n]=k,fa[n]=0;side[n]=-1,val[n]=1,root=n,up(n);
			return;
		}
		for(int s;s=son[k>key[x]][x];x=s);
		key[++n]=k,fa[n]=x,side[n]=k>key[x],val[n]=INF,son[side[n]][x]=n,up(n),splay(n);
		int a=mnode[1][lson(n)],b=mnode[0][rson(n)];
		val[n]=max(val[splay(a),a],val[splay(b),b])+1,splay(n);
	}
	inline void delroot(){
		assert(lson(root)==0||rson(root)==0);
		root=lson(root)|rson(root);
		if(root){
			side[root]=-1;
			all(root,-1);
		}
	}
	inline void init(){
		memset(son,0,sizeof(son));
		memset(delta,0,sizeof(delta));
		val[0]=mnode[0][0]=mnode[1][0]=0,side[0]=-1;
	}
	int find(int x,int v,bool d){
		if(x==0){
			return 0;
		}
		down(x);
		if(son[d][x]==0||mnval[son[d][x]]>v){
			if(val[x]>v){
				if(son[!d][x]){
					return find(son[!d][x],v,d);
				}
				splay(x);
				return 0;
			}else{
				splay(x);
				return x;
			}
		}
		return find(son[d][x],v,d);
	}
	int work(int op){
		switch(op){
			case 1:{
				insert(root,ni);
				return val[root];
			}
			case 2:case 3:{
				op-=2;
				splay(mnode[op][root]),down(root);
				int ret=val[root];
				int x=find(son[!op][root],ret,op);
				if(x){
					assert(x==root);
					all(x,1),down(x),all(son[op][x],-1);
				}
				x=mnode[op][root];
				splay(x),down(x),val[x]=1,up(x);
				return ret;
			}
			case 4:case 5:{
				int ret=work(op-2);
				delroot();
				return ret;
			}
		}
		return -1;
	}
}
int main(){
	T::init();
	for(int tot=ni;tot--;){
		printf("%d\n",T::work(ni));
	}
}