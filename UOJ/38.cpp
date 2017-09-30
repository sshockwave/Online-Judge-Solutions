#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
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
const int N=100010,MOD=19961993,P=65,PN=310;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return (lint)a*b%MOD;
}
inline void apmul(int &a,const int &b){
	a=mul(a,b);
}
inline int fpow(int x,int n){
	int ret=1;
	for(;n;n>>=1,apmul(x,x)){
		if(n&1){
			apmul(ret,x);
		}
	}
	return ret;
}
inline int inv(int x){
	return fpow(x,MOD-2);
}
int prime[P],fct[P],ps=0;
bool np[PN];
inline void sieve(int n){
	memset(np,0,sizeof(np));
	for(int i=2;i<=n;i++){
		if(!np[i]){
			prime[ps]=i;
			assert(mul(i,inv(i))==1);
			fct[ps]=mul(i-1,inv(i));
			ps++;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				break;
			}
		}
	}
}
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		struct Info{
			int prod;
			ull p;
			inline void digest(int x){
				prod=x,p=0;
				for(int j=0,cur=2;x!=1;cur=prime[++j]){
					int e=0;
					for(;x%cur==0;x/=cur,e++);
					if(e){
						p^=1ull<<j;
					}
				}
			}
			inline int phi(){
				ull t=p;
				int ans=prod;
				for(int i=0;t;i++){
					if((t>>i)&1){
						apmul(ans,fct[i]);
						t^=1ull<<i;
					}
				}
				return ans;
			}
			inline friend Info operator + (const Info &a,const Info &b){
				return (Info){mul(a.prod,b.prod),a.p|b.p};
			}
		}info;
		inline void up(){
			info=lson->info+rson->info;
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->info.digest(3);
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void set(node x,int p,int v){
		if(x->l==x->r){
			x->info.digest(v);
		}else{
			set(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	Node::Info ask(node x,int l,int r){
		assert(x->l<=l&&r<=x->r);
		if(x->l==l&&x->r==r){
			return x->info;
		}
		if(r<=x->m){
			return ask(x->lson,l,r);
		}
		if(l>x->m){
			return ask(x->rson,l,r);
		}
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("odd.in","r",stdin);
	freopen("odd.out","w",stdout);
#endif
	sieve(281);
	seg::rt=seg::build(1,100000);
	int cnt=0;
	for(int tot=ni;tot--;){
		if(ni){
			int p=ni,v=ni;
			seg::set(seg::rt,p,v);
		}else{
			int l=ni,r=ni;
			cnt++;
			if(cnt==44){
				cout<<"asking ["<<l<<","<<r<<"]"<<endl;
			}
			printf("%d\n",seg::ask(seg::rt,l,r).phi());
		}
	}
}
