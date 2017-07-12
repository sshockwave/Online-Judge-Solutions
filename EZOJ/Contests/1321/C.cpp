#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <set>
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
const int N=100010,C=N<<1;
int n;
struct Line{
	int l,r,v;
	Line(int _l,int _r,int _v):l(_l),r(_r),v(_v){}
	inline void del();
	inline void ins();
	inline void put();
	inline friend bool operator < (const Line &a,const Line &b){
		return a.r>b.r;
	}
};
struct Treap{
	typedef Treap* node;
	int val,wei,size;
#define lson son[0]
#define rson son[1]
	node son[2],*pt;
	static Treap null;
	inline void up(){
		size=lson->size+rson->size+1;
	}
	inline node rot(bool d){
		node fa=son[!d];
		if(fa!=&null){
			fa->pt=pt,*pt=fa,pt=fa->son+d;
			(son[!d]=*pt)->pt=son+(!d),*pt=this;
			up(),fa->up();
		}
		return fa;
	}
	void ins(int v,node *p){
		if(this==&null){
			static node n=new Treap[N*30];
			*(*p=n++)=(Treap){v,rand(),1,&null,&null,p};
		}else{
			size++;
			assert(val!=v);
			son[v>val]->ins(v,son+(v>val));
			if(son[v>val]->wei>wei){
				rot(v<val);
			}
		}
	}
	void del(int v){
		assert(this!=&null);
		if(val==v){
			for(node fa;fa=rot(lson->val>rson->val),fa!=&null;fa->size--);
			*pt=&null;
		}else{
			size--;
			(v<val?lson:rson)->del(v);
		}
	}
	int ask(int v){//>v
		if(this==&null){
			return 0;
		}else{
			return v<val?lson->ask(v)+rson->size+1:rson->ask(v);
		}
	}
};
Treap Treap::null={0,0,0,&null,&null,NULL};
namespace BIT{
	Treap* t[N];
	int c[N];
	inline void init(){
		memset(c+1,0,n<<2);
		for(int i=1;i<=n;i++){
			t[i]=&Treap::null;
		}
	}
	inline int bit(int x){
		return x&(-x);
	}
	inline void add(int x,int v){
		if(v==n+1){
			for(;x<=n;c[x]++,x+=bit(x));
		}else{
			for(;x<=n;t[x]->ins(v,t+x),x+=bit(x));
		}
	}
	inline void del(int x,int v){
		if(v==n+1){
			for(;x<=n;c[x]--,x+=bit(x));
		}else{
			for(;x<=n;t[x]->del(v),x+=bit(x));
		}
	}
	inline int sum(int x,int v){//>v
		int ans=0;
		for(;x;ans+=c[x]+t[x]->ask(v),x^=bit(x));
		return ans;
	}
}
set<Line>a,b[C];
typedef set<Line>::iterator iter;
inline void Line::del(){
	a.erase(*this);
	iter it=b[v].find(*this),pre=it,nxt=it;
	pre++,nxt--;
	BIT::del(r,nxt->l);
	if(pre!=b[v].end()){
		BIT::del(pre->r,l);
		BIT::add(pre->r,nxt->l);
	}
	b[v].erase(it);
}
inline void Line::put(){
	if(l<=r){
		a.insert(*this);
		iter it=b[v].insert(*this).first,pre=it,nxt=it;
		pre++,nxt--;
		if(pre!=b[v].end()){
			BIT::del(pre->r,nxt->l);
			BIT::add(pre->r,l);
		}
		BIT::add(r,nxt->l);
	}
}
inline void Line::ins(){
	iter it_l=a.lower_bound(Line(r,r,0));
	iter it_r=a.upper_bound(Line(l,l,0));
	if(it_l==it_r){
		iter it=it_l;
		Line cur=*(--it);
		if(cur.v!=v){
			cur.del();
			Line(cur.l,l-1,cur.v).put();
			Line(r+1,cur.r,cur.v).put();
			put();
		}
		return;
	}
	assert(it_l!=a.end());
	{
		iter it=it_l;
		Line cur=*--it;
		assert(cur.r>r);
		if(cur.l<=r){
			cur.del();
			Line(r+1,cur.r,cur.v).put();
		}
	}
	for(iter i=it_l;i!=it_r;){
		Line cur=*i++;
		cur.del();
		if(cur.l<l){
			if(cur.v==v){
				Line(cur.l,r,v).put();
				return;
			}else{
				Line(cur.l,l-1,cur.v).put();
			}
		}
	}
	put();
}
namespace I{
	struct Query{
		int op,l,r,x;
	}q[N];
	int *num[N*2],ns=0;
	inline bool numcmp(int* a,int* b){
		return *a<*b;
	}
	int arr[N],m;
	inline void get(){
		m=ni;
		for(int i=1;i<=n;i++){
			arr[i]=ni;
			num[ns++]=arr+i;
		}
		for(int i=1;i<=m;i++){
			q[i]=(Query){ni,ni,ni};
			if(q[i].op==1){
				q[i].x=ni;
				num[ns++]=&q[i].x;
			}
		}
		sort(num,num+ns,numcmp);
		Line end(n+1,n+1,0);
		a.insert(end);
		for(int i=0,j=0,v=0;i<ns;i++){
			if(v!=*num[i]){
				v=*num[i];
				b[++j].insert(end);
			}
			*num[i]=j;
		}
		arr[0]=0;
		for(int r=n,l=n;r>=1;r=l){
			for(;arr[l]==arr[r];l--);
			Line(l+1,r,arr[r]).put();
		}
	}
	inline void put(){
		for(int i=1;i<=m;i++){
			if(q[i].op==1){
				Line(q[i].l,q[i].r,q[i].x).ins();
			}else{
				int ans=1;
				iter it=a.upper_bound(Line(q[i].r,q[i].r,0));
				if(it!=a.end()&&it->r>=q[i].l){
					ans+=BIT::sum(it->r,q[i].r)-BIT::sum(q[i].l-1,q[i].r);
				}
				printf("%d\n",ans);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
#endif
	n=ni;
	BIT::init();
	I::get();
	I::put();
}
