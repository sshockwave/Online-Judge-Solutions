#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline lint nl(){
	lint i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=300010;
lint seq[N];
struct SplayTree{
	typedef int info[N];
	#define lson(x) son[x][0]
	#define rson(x) son[x][1]
	int son[N][2],root;
	info fa,side,size;
	lint val[N],delta[N];
	SplayTree(){
		memset(fa,0,sizeof(fa));
		memset(son,0,sizeof(son));
		memset(size,0,sizeof(size));
		memset(delta,0,sizeof(delta));
	}
	inline void up(int x){
		size[x]=size[lson(x)]+size[rson(x)]+1;
	}
	inline void down(int x){
		if(delta[x]){
			val[x]+=delta[x];
			if(lson(x)){
				delta[lson(x)]+=delta[x];
			}
			if(rson(x)){
				delta[rson(x)]+=delta[x];
			}
			delta[x]=0;
		}
	}
	inline void rotate(int x){
		assert(~side[x]);
		bool d=!side[x];
		down(fa[x]),down(x);
		son[fa[x]][!d]=son[x][d];
		fa[son[x][d]]=fa[x];
		side[son[x][d]]=!d;
		son[x][d]=fa[x];
		side[x]=side[fa[x]];
		fa[x]=fa[fa[x]];
		fa[son[x][d]]=x;
		side[son[x][d]]=d;
		if(side[x]==-1){
			root=x;
		}else{
			son[fa[x]][side[x]]=x;
		}
		up(son[x][d]),up(x);
	}
	inline void splay(int x){
		while(~side[x]){
			if(side[fa[x]]==-1){
				rotate(x);
			}else if(side[fa[x]]==side[x]){
				rotate(fa[x]),rotate(x);
			}else{
				rotate(x),rotate(x);
			}
		}
	}
	void insert(int x,lint a,lint b,int lsize){
		down(x);
		size[x]++;
		bool d=val[x]>a*(size[lson(x)]+lsize)+b;
		if(son[x][d]==0){
			static int n=1;
			son[x][d]=++n;
			fa[n]=x;
			side[n]=d;
			size[n]=1;
			if(d){
				val[n]=a*(size[lson(x)]+lsize+1)+b;
			}else{
				val[n]=a*lsize+b;
			}
			splay(n);
		}else if(d){
			insert(rson(x),a,b,lsize+size[lson(x)]+1);
		}else{
			insert(lson(x),a,b,lsize);
		}
	}
	void dfs(int x){
		if(x==0){
			return;
		}
		static int stop=0;
		down(x);
		dfs(lson(x));
		seq[++stop]=val[x];
		dfs(rson(x));
	}
	inline void init(lint b){
		int x=1;
		size[x]=1;
		side[x]=-1;
		val[x]=b;
		root=x;
	}
}bst;
struct Item{
	lint a,b;
}item[N];
inline bool operator < (Item a,Item b){
	return a.a<b.a;
}
lint a[N],b[N];
int main(){
	int n=ni();
	for(int i=1;i<=n;i++){
		item[i]=(Item){ni(),nl()};
	}
	sort(item+1,item+1+n);
	for(int i=1;i<=n;i++){
		a[i]=item[i].a,b[i]=item[i].b;
	}
	bst.init(b[1]);
	for(int i=2;i<=n;i++){
		bst.insert(bst.root,a[i],b[i],0);
		assert(bst.root==i);
		int rson=bst.son[bst.root][1];
		if(rson){
			bst.delta[rson]+=a[i];
		}
	}
	memset(seq,0,sizeof(seq));
	bst.dfs(bst.root);
	for(int i=1;i<=n;i++){
		seq[i]+=seq[i-1];
		printf("%lld\n",seq[i]);
	}
}
