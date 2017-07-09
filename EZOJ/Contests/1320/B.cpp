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
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=100010,W=76;
bool type[N];//A:0 B:1
int val[N];
struct SegmentTree{
	typedef SegmentTree* node;
	int lend,rend,mid;
	node lson,rson;
	struct Info{
		int ans,bl,br,posa;//don't count posa!
		bool l2r,r2l;
		int al[W],ar[W];
		inline void init(int x,bool d){
			ans=0;
			l2r=d,r2l=!d;
			memset(al,0,sizeof(al));
			memset(ar,0,sizeof(ar));
			if(type[x]){
				bl=val[x],br=d?0:val[x];
				posa=0;
			}else{
				bl=br=0;
				if(d){
					posa=x;
				}else{
					al[val[x]]=1;
					posa=0;
				}
			}
		}
		inline void up(const Info &l,const Info &r){
			ans=l.ans+r.ans;
			{//copy a
				memcpy(al,l.al,sizeof(al));
				memcpy(ar,r.ar,sizeof(ar));
				for(int i=0;i<r.bl;i++){
					ans+=l.ar[i];
				}
				if(r.l2r){
					for(int i=r.bl;i<W;i++){
						ar[i]+=l.ar[i];
					}
				}
				for(int i=0;i<l.br;i++){
					ans+=r.al[i];
				}
				if(l.r2l){
					for(int i=l.br;i<W;i++){
						al[i]+=r.al[i];
					}
				}
				posa=0;
				if(l.posa){
					if(val[l.posa]<r.bl){
						ans++;
					}else if(r.l2r){
						posa=l.posa;
					}else{
						al[val[l.posa]]++;
					}
				}
				if(r.posa){
					if(val[r.posa]<l.br){
						ans++;
					}else if(l.r2l){
						assert(posa==0);
						posa=r.posa;
					}else{
						ar[val[r.posa]]++;
					}
				}
			}
			{//copy b
				bl=l.bl,br=r.br;
				if(l.l2r){
					apmax(bl,r.bl);
				}
				if(r.r2l){
					apmax(br,l.br);
				}
			}
			{//con
				l2r=l.l2r&&r.l2r;
				r2l=l.r2l&&r.r2l;
			}
		}
	}info[2],*cur,*bak;
	bool tag;
	inline void up(){
		assert(lson&&rson);
		cur->up(*lson->cur,*rson->cur);
		bak->up(*lson->bak,*rson->bak);
	}
	inline void down(){
		assert(lson&&rson);
		if(tag){
			lson->tag=!lson->tag,swap(lson->cur,lson->bak);
			rson->tag=!rson->tag,swap(rson->cur,rson->bak);
			tag=false;
		}
	}
	void rev(int l,int r){
		if(lend==l&&rend==r){
			swap(cur,bak);
			tag=!tag;
			return;
		}
		down();
		if(r<=mid){
			lson->rev(l,r);
		}else if(l>mid){
			rson->rev(l,r);
		}else{
			lson->rev(l,mid);
			rson->rev(mid+1,r);
		}
		up();
	}
	void upd(int x){
		if(lend==rend){
			cur->init(x,cur==info);
			bak->init(x,bak==info);
		}else{
			down();
			(x<=mid?lson:rson)->upd(x);
			up();
		}
	}
	void build(int l,int r){
		static node n=new SegmentTree[N*2];
		lend=l,rend=r,mid=(l+r)>>1;
		cur=info,bak=info+1,tag=false;
		if(l==r){
			cur->init(l,1);
			bak->init(l,0);
		}else{
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
			up();
		}
	}
}seg;
int main(){
#ifndef ONLINE_JUDGE
	freopen("emerald.in","r",stdin);
	freopen("emerald.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		val[i]=ni,type[i]=nc()=='B';
	}
	seg.build(1,n);
	while(tot--){
		char op=nc();
		int x=ni,y=ni;
		if(op=='U'){
			val[x]=y;
			seg.upd(x);
		}else if(x<y){
			seg.rev(x,y-1);
		}
		printf("%d\n",seg.cur->ans);
	}
}
