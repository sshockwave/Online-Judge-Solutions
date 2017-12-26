#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=400010;
namespace T{
	struct Node;
	typedef Node* node;
	struct Node{
		union{
			struct{
				node lson,rson;
			};
			node son[2];
		};
		node fa;
		int size;
		bool rev;
		map<int,int>m;
		int hei[2],cnt[2];
		int thei,tcnt;
		inline void putinfo(node x){
			if(x->cnt[0]==0)return;
			m[x->hei[0]]+=x->cnt[0];
			map<int,int>::iterator it=--m.end();
			thei=it->first+1;
			tcnt=it->second;
		}
		inline void delinfo(node x){
			if(x->cnt[0]==0)return;
			m[x->hei[0]]-=x->cnt[0];
			map<int,int>::iterator it;
			for(;it=--m.end(),it->second==0;m.erase(it));
			thei=it->first+1;
			tcnt=it->second;
		}
		inline void putrev(){
			swap(hei[0],hei[1]);
			swap(cnt[0],cnt[1]);
			swap(lson,rson);
			rev=!rev;
		}
		inline void down(){
			if(rev){
				rev=false;
				lson->putrev();
				rson->putrev();
			}
		}
		inline void up(){
			size=lson->size+1+rson->size;
			for(int d=0;d<2;d++,swap(lson,rson)){
				hei[d]=lson->hei[d];
				cnt[d]=lson->cnt[d];
				int lsize=lson->size;
				if(thei+lsize>hei[d]){
					hei[d]=thei+lsize;
					cnt[d]=0;
				}
				if(thei+lsize==hei[d]){
					cnt[d]+=tcnt;
				}
				if(rson->cnt[d]){
					lsize++;
					if(rson->hei[d]+lsize>hei[d]){
						hei[d]=rson->hei[d]+lsize;
						cnt[d]=0;
					}
					if(rson->hei[d]+lsize==hei[d]){
						cnt[d]+=rson->cnt[d];
					}
				}
			}
		}
		inline int side(){
			return fa->lson==this?0:fa->rson==this?1:-1;
		}
		inline void rot(){
			bool d=!side();
			son[d]->fa=fa,fa->son[!d]=son[d],son[d]=fa;
			int g=fa->side();
			if(~g){
				fa->fa->son[g]=this;
			}
			fa=fa->fa,son[d]->fa=this;
			son[d]->up(),up();
		}
		inline void splay();
	}pool[N],Null;
	node null=&Null;
	inline ostream & operator << (ostream & out,node b){
		if(b==null){
			out<<"null";
		}else{
			out<<(b-pool);
		}
		return out;
	}
	void draw(node x){
		if(x!=null){
			draw(x->fa),x->down();
		}
	}
	inline void Node::splay(){
		draw(this);
		for(int d,g;d=side(),~d;){
			g=fa->side();
			g==d?fa->rot(),rot():g==!d?rot(),rot():rot();
		}
	}
	inline void acc(node x){
		for(node s=null;x!=null;s=x,x=x->fa){
			x->splay();
			x->putinfo(x->rson);
			x->delinfo(s);
			x->rson=s;
			x->up();
		}
	}
	inline node nn(node x=null){
		static node n=pool;
		return *n=*x,n++;
	}
	inline void init(){
		memset(null,0,sizeof(Null));
		null->fa=null->lson=null->rson=null;
	}
}
T::node node[N];
int fa[N];
int ans=0;
int main(){
#ifndef ONLINE_JUDGE
	freopen("darkforest.in","r",stdin);
	freopen("darkforest.out","w",stdout);
#endif
	int n=ni,tot=ni;
	T::init();
	{
		T::node tmp=T::nn();
		tmp->cnt[0]=1;
		tmp->hei[0]=-1;
		for(int i=1;i<=n;i++){
			node[i]=T::nn();
			node[i]->putinfo(tmp);
			node[i]->up();
		}
	}
	for(int i=1;i<=n;i++){
		T::node f=node[fa[i]=ni];
		if(fa[i]!=0){
			T::acc(f);
			f->splay();
			node[i]->splay();
			node[i]->fa=f;
			f->rson=node[i];
			f->up();
		}
	}
	for(int i=1;i<=n;i++){
		if(fa[i]==0){
			T::acc(node[i]);
			node[i]->splay();
			ans+=node[i]->cnt[0];
		}
	}
	while(printf("%d\n",ans),tot--){
		if(ni==1){
			T::node x=node[ni],y=node[ni];
			T::acc(x);
			x->splay();
			ans-=x->cnt[0];
			x->putrev();//chroot x
			T::acc(y);
			y->splay();
			ans-=y->cnt[0];
			x->fa=y;
			y->rson=x;
			y->up();
			ans+=y->cnt[0];
		}else{
			T::node x=node[ni];
			T::acc(x);
			x->splay();
			if(x->lson!=T::null){
				ans-=x->cnt[0];
				ans+=x->lson->cnt[0];
				x->lson=x->lson->fa=T::null;
				x->up();
				ans+=x->cnt[0];
			}
		}
	}
	return 0;
}
