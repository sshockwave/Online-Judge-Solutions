#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=2003;
namespace lct{
	const int N=::N*::N;
	struct Node;
	typedef Node* node;
	node null;
	inline void draw(node);
	struct Node{
		/* Info */
		int xcor,ycor;
		/* lct */
		union{
			struct{node lson,rson;};
			node son[2];
		};
		node fa,ringnx;
		int size;
		inline void putringnx(node v){
			if(this==null)return;
			ringnx=v;
		}
		inline void dn(){
			lson->putringnx(ringnx);
			rson->putringnx(ringnx);
		}
		inline void up(){
			size=lson->size+1+rson->size;
		}
		inline int sd(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void rot(){
			bool d=!sd();
			int g=fa->sd();
			fa->son[!d]=son[d],son[d]->fa=fa,son[d]=fa;
			fa=fa->fa,son[d]->fa=this;
			if(~g)fa->son[g]=this;
			son[d]->up(),up();
		}
		inline void spa(){
			draw(this);
			for(int d,fd;d=sd(),~d;fd=fa->sd(),fd==d?fa->rot():fd==!d?rot():void(),rot());
		}
	}pool[N],Null;
	inline void draw(node x){
		static node stk[N];
		int ss=0;
		for(;;){
			stk[ss++]=x;
			if(x->sd()==-1)break;
			x=x->fa;
		}
		for(;ss;){
			stk[--ss]->dn();
		}
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->fa=null->ringnx=null;
		null->lson=null->rson=null;
	}
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x=x->fa){
			x->spa();
			x->rson=s,x->up();
		}
	}
	inline void cut(const node x){
		acc(x),x->spa();
		const node y=x->ringnx;
		if(y==null)return;
		acc(y),y->spa(),x->spa();
		if(x->fa==null){//x on ring
			x->lson->fa=y;
			x->lson=null,x->up();
		}else{
			acc(x),x->spa();
			x->lson->fa=null;
			x->lson=null,x->up();
		}
		x->ringnx=null;
	}
	inline void setfa(node x,node y){
		cut(x);
		assert(x->fa==null);
		acc(y),y->spa();
		if(x==y||x->fa!=null){//on same tree
			y->ringnx=y;
		}else{
			x->fa=y;
		}
	}
	inline node getkth(node x,int k){
		for(;;){
			assert(k<=x->size);
			if(k<=x->lson->size){
				x=x->lson;
			}else if(k>x->lson->size+1){
				k-=x->lson->size+1;
				x=x->rson;
			}else break;
		}
		x->spa();
		return x;
	}
	inline node askfa(node x,int k){
		acc(x),x->spa();
		if(k<=x->lson->size)return getkth(x,x->lson->size+1-k);
		k-=x->lson->size;
		x=x->ringnx;
		acc(x),x->spa();
		k%=x->size;
		if(k==0){
			k=x->size;
		}
		return getkth(x,x->size+1-k);
	}
}
int mat[N][N];
lct::node nd[N][N];
int r,c;
inline void work(int x,int y){
	const lct::node pre=nd[x][y];
	y=(y+1)%c;
	const int tl=r+x-1,tr=r+x+1;
	for(int i=tl;i<=tr;i++){
		if(mat[i%r][y]>mat[x][y]){
			x=i%r;
		}
	}
	lct::setfa(pre,nd[x][y]);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("ywwy.in","r",stdin);
	freopen("ywwy.out","w",stdout);
#endif
	r=ni,c=ni;
	lct::init();
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			mat[i][j]=ni;
			nd[i][j]=lct::nn();
			nd[i][j]->xcor=i;
			nd[i][j]->ycor=j;
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			work(i,j);
		}
	}
	lct::node x=nd[0][0];
	for(int tot=ni;tot--;){
		char op;
		{
			static char s[10];
			scanf("%s",s);
			op=s[0];
		}
		if(op=='m'){
			x=lct::askfa(x,ni);
			printf("%d %d\n",x->xcor+1,x->ycor+1);
		}else if(op=='c'){
			int x=ni-1,y=ni-1;
			mat[x][y]=ni;
			y=(y+c-1)%c;
			for(int i=r+x-1;i<=r+x+1;i++){
				work(i%r,y);
			}
		}
	}
	return 0;
}
