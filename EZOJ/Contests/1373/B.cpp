#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
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
const int N=100010,C=17;
lint ban[C];
inline bool valid(lint x){
	for(int i=0;i<C;i++){
		if(ban[i]==x)return false;
	}
	return true;
}
lint a[N];
inline void fixup(int l,int r){
	while(true){
		bool flag=true;
		for(int i=l;i<=r;i++){
			if(!valid(a[i])){
				flag=false;
				break;
			}
		}
		if(flag)break;
		for(int i=l;i<=r;i++){
			a[i]++;
		}
	}
}
namespace brute6{
	namespace seg{
		struct Node;
		typedef Node* node;
		struct Node{
			node lson,rson;
			int l,m,r;
			bool tag;
			lint val,mx,mn,sum;
			inline void setval(lint v){
				tag=true;
				val=mx=mn=v;
				sum=v*(r-l+1);
			}
			inline void addval(lint v){
				val+=v;
				mx+=v;
				mn+=v;
				sum+=v*(r-l+1);
			}
			inline void up(){
				assert(!tag);
				assert(val==0);
				mx=max(lson->mx,rson->mx);
				mn=min(lson->mn,rson->mn);
				sum=lson->sum+rson->sum;
			}
			inline void down(){
				if(tag){
					tag=false;
					lson->setval(val);
					rson->setval(val);
					val=0;
				}else if(val){
					lson->addval(val);
					rson->addval(val);
					val=0;
				}
			}
		};
		node rt;
		node build(int l,int r){
			static node n=new Node[N<<1];
			node x=n++;
			x->l=l,x->m=(l+r)>>1,x->r=r;
			if(l==r){
				x->setval(a[l]);
			}else{
				x->lson=build(l,x->m);
				x->rson=build(x->m+1,r);
				x->val=0;
				x->tag=false;
				x->up();
			}
			return x;
		}
		void cover(node x,int l,int r,lint v){
			if(x->l==l&&x->r==r){
				x->setval(v);
				return;
			}
			x->down();
			if(r<=x->m){
				cover(x->lson,l,r,v);
			}else if(l>x->m){
				cover(x->rson,l,r,v);
			}else{
				cover(x->lson,l,x->m,v);
				cover(x->rson,x->m+1,r,v);
			}
			x->up();
		}
		void add(node x,int l,int r,lint v){
			if(x->l==l&&x->r==r){
				x->addval(v);
				return;
			}
			x->down();
			if(r<=x->m){
				add(x->lson,l,r,v);
			}else if(l>x->m){
				add(x->rson,l,r,v);
			}else{
				add(x->lson,l,x->m,v);
				add(x->rson,x->m+1,r,v);
			}
			x->up();
		}
		lint ask(node x,int l,int r){
			if(x->tag)return x->val*(r-l+1);
			if(x->l==l&&x->r==r)return x->sum;
			x->down();
			if(r<=x->m)return ask(x->lson,l,r);
			if(l>x->m)return ask(x->rson,l,r);
			return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
		}
		lint askmax(node x,int l,int r){
			if(x->tag)return x->val;
			if(x->l==l&&x->r==r)return x->mx;
			x->down();
			if(r<=x->m)return askmax(x->lson,l,r);
			if(l>x->m)return askmax(x->rson,l,r);
			return max(askmax(x->lson,l,x->m),askmax(x->rson,x->m+1,r));
		}
		lint askmin(node x,int l,int r){
			if(x->tag)return x->val;
			if(x->l==l&&x->r==r)return x->mn;
			x->down();
			if(r<=x->m)return askmin(x->lson,l,r);
			if(l>x->m)return askmin(x->rson,l,r);
			return min(askmin(x->lson,l,x->m),askmin(x->rson,x->m+1,r));
		}
	}
	inline void Main(int n,int tot){
		seg::rt=seg::build(1,n);
		while(tot--){
			int op=ni;
			if(op==1){
				int x=ni;
				printf("%lld\n",seg::ask(seg::rt,x,x));
			}else if(op==2){
				int l=ni,r=ni,v=ni;
				for(;!valid(v);v++);
				seg::cover(seg::rt,l,r,v);
			}else if(op==3){
				int l=ni,r=ni;
				seg::add(seg::rt,l,r,ni);
			}else if(op==4){
				int l=ni,r=ni;
				lint v=seg::askmax(seg::rt,l,r);
				seg::cover(seg::rt,l,r,v);
			}else if(op==5){
				int l=ni,r=ni;
				lint v=seg::askmin(seg::rt,l,r);
				seg::cover(seg::rt,l,r,v);
			}else if(op==6){
				int l=ni,r=ni;
				lint v=(long double)(seg::ask(seg::rt,l,r))/(r-l+1)+1e-9;
				seg::cover(seg::rt,l,r,v);
			}
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("operation.in","r",stdin);
	freopen("operation.out","w",stdout);
#endif
	ban[0]=233;
	for(int i=1;i<C;i++){
		ban[i]=ban[i-1]*10+3;
	}
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	if(n>4000){
		brute6::Main(n,tot);
		return 0;
	}
	for(int l,r,x;tot--;){
		lint val;
		switch(ni){
			case 1:
				printf("%lld\n",a[ni]);
				break;
			case 2:
				l=ni,r=ni,x=ni;
				for(;!valid(x);x++);
				for(int i=l;i<=r;i++){
					a[i]=x;
				}
				break;
			case 3:
				l=ni,r=ni,x=ni;
				for(int i=l;i<=r;i++){
					a[i]+=x;
				}
				fixup(l,r);
				break;
			case 4:
				l=ni,r=ni,val=a[l];
				for(int i=l+1;i<=r;i++){
					apmax(val,a[i]);
				}
				assert(valid(val));
				for(int i=l;i<=r;i++){
					a[i]=val;
				}
				break;
			case 5:
				l=ni,r=ni,val=a[l];
				for(int i=l+1;i<=r;i++){
					apmin(val,a[i]);
				}
				assert(valid(val));
				for(int i=l;i<=r;i++){
					a[i]=val;
				}
				break;
			case 6:
				l=ni,r=ni,val=0;
				for(int i=l;i<=r;i++){
					val+=a[i];
				}
				val=(long double)val/(r-l+1)+1e-9;
				for(;!valid(val);val++);
				for(int i=l;i<=r;i++){
					a[i]=val;
				}
				break;
		}
	}
	return 0;
}
