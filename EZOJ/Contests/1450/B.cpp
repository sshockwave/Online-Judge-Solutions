#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=100010;
int n,nrt;
int lst[N],ls=0;
namespace seg{
	const int N=::N*20*2;
	struct Node;
	typedef Node* node;
	node null;
	struct Node{
		node lson,rson;
		int cnt;
	}pool[N],Null;
	node ppt[N],*npt=ppt;
	inline node nn(node x=null){
		return **npt=*x,*(npt++);
	}
	inline void del(node x){
		*--npt=x;
	}
	inline void init(){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
		for(int i=0;i<N;i++){
			ppt[i]=pool+i;
		}
	}
	void ins(node &x,const int p,const int l=1,const int r=n){
		if(x==null){
			x=nn(x);
		}
		++x->cnt;
		if(l!=r){
			const int m=(l+r)>>1;
			if(p<=m){
				ins(x->lson,p,l,m);
			}else{
				ins(x->rson,p,m+1,r);
			}
		}
	}
	void rm(node &x,const int p,const int l=1,const int r=n){
		assert(x!=null);
		--x->cnt;
		if(l!=r){
			const int m=(l+r)>>1;
			if(p<=m){
				rm(x->lson,p,l,m);
			}else{
				rm(x->rson,p,m+1,r);
			}
		}
		if(x->cnt==0){
			del(x);
			x=null;
		}
	}
	int rnk(node x,int p,int l=1,int r=n){
		if(x==null)return 0;
		if(p==r)return x->cnt;
		const int m=(l+r)>>1;
		if(p<=m)return rnk(x->lson,p,l,m);
		return x->lson->cnt+rnk(x->rson,p,m+1,r);
	}
	void getlstaft(node x,int p,int l=1,int r=n){
		if(x->cnt==0)return;
		assert(p<=r);
		if(l==r){
			lst[++ls]=p;
			return;
		}
		const int m=(l+r)>>1;
		if(p>m)return getlstaft(x->rson,p,m+1,r);
		getlstaft(x->lson,p,l,m);
		getlstaft(x->rson,m+1,m+1,r);
	}
}
int a[N];
seg::node col[N],accu[N];
set<int>bigele;
inline void ins_ele(int i){
	if(bigele.count(a[i]))return seg::ins(col[a[i]],i);
	if(col[a[i]]->cnt>=nrt*2){
		ls=0;
		seg::getlstaft(col[a[i]],1);
		for(int j=1;j<=col[a[i]]->cnt;j++){
			seg::rm(accu[j],lst[j]);
		}
		seg::ins(col[a[i]],i);
		bigele.insert(a[i]);
		return;
	}
	const int nrk=seg::rnk(col[a[i]],i);
	ls=0;
	seg::getlstaft(col[a[i]],i);
	for(int j=1;j<=ls;j++){
		seg::rm(accu[nrk+j],lst[j]);
		seg::ins(accu[nrk+j+1],lst[j]);
	}
	seg::ins(col[a[i]],i);
	seg::ins(accu[nrk+1],i);
}
inline void del_ele(int i){
	if(bigele.count(a[i])){
		seg::rm(col[a[i]],i);
		if(col[a[i]]->cnt<nrt){
			ls=0;
			seg::getlstaft(col[a[i]],1);
			for(int j=1;j<=col[a[i]]->cnt;j++){
				seg::ins(accu[j],lst[j]);
			}
			bigele.erase(a[i]);
		}
		return;
	}
	const int rk=seg::rnk(col[a[i]],i);
	seg::rm(col[a[i]],i);
	seg::rm(accu[rk],i);
	ls=0;
	seg::getlstaft(col[a[i]],i);
	for(int j=1;j<=ls;j++){
		seg::rm(accu[rk+j],lst[j]);
		seg::ins(accu[rk+j-1],lst[j]);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("password.in","r",stdin);
	freopen("password.out","w",stdout);
#endif
	n=ni;
	for(nrt=1;nrt*nrt<=n;nrt++);
	seg::init();
	const int mxv=10000;
	for(int i=1;i<=mxv;i++){
		col[i]=seg::null;
	}
	for(int i=1;i<=n;i++){
		accu[i]=seg::null;
	}
	for(int i=1;i<=n;i++){
		a[i]=ni;
		ins_ele(i);
	}
	for(int tot=ni;tot--;){
		if(ni==1){//alt
			const int v=ni,i=ni;
			del_ele(i);
			a[i]=v;
			ins_ele(i);
		}else{//ask
			const int x=ni,y=ni;
			if(x==1){
				printf("%d\n",a[y]);
			}else{
				const int rk=seg::rnk(col[a[y]],y);
				if(x&1){
					int ans=seg::rnk(accu[rk],y);
					for(set<int>::iterator it=bigele.begin(),ti=bigele.end();it!=ti;++it){
						ans+=seg::rnk(col[*it],y)>=rk;
					}
					printf("%d\n",ans);
				}else{
					printf("%d\n",rk);
				}
			}
		}
	}
	return 0;
}
