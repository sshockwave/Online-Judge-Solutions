#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
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
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=100010,TN=N*40,INF=0x7f7f7f7f;//tocheck
int tim=0;
#define lson(x) son[x][0]
#define rson(x) son[x][1]
#define clr(x) memset((x),0,sizeof(x))
namespace W{
	int son[TN][2],tag[TN],val[TN],n=0;
	inline void init(){
		clr(son),clr(val);
		memset(tag,-1,sizeof(tag));
	}
	inline void up(int x){
		assert(tag[x]==tim);
		val[x]=val[lson(x)]+val[rson(x)];
	}
	inline int renew(int x){
		if(tag[x]<tim){
			n++,lson(n)=lson(x),rson(n)=rson(x),tag[n]=tim,val[n]=x,x=n;
		}
		return x;
	}
	int set(int x,int p,int lend,int rend){
		x=renew(x);
		if(lend==rend){
			assert(p==lend);
			val[x]=1;
		}else{
			int mid=(lend+rend)>>1;
			if(p<=mid){
				lson(x)=set(lson(x),p,lend,mid);
			}else{
				rson(x)=set(rson(x),p,mid+1,rend);
			}
			up(x);
		}
		return x;
	}
	int del(int x,int p,int lend,int rend){
		assert(x&&val[x]);
		if(val[x]==1){
			return 0;
		}
		x=renew(x);
		int mid=(lend+rend)>>1;
		if(p<=mid){
			lson(x)=del(lson(x),p,lend,mid);
		}else{
			rson(x)=del(rson(x),p,mid+1,rend);
		}
		up(x);
		return x;
	}
	int pre(int x,int p,int lend,int rend){
		if(val[x]==0){
			return 0;
		}
		int mid=(lend+rend)>>1;
		if(p<=mid){
			return pre(lson(x),p,lend,mid);
		}
		int res=pre(rson(x),p,mid+1,rend);
		return res?res:pre(lson(x),p,lend,mid);
	}
	int mxval;
	int nxt(int x,int p,int lend,int rend){
		if(val[x]==0){
			return mxval;
		}
		int mid=(lend+rend)>>1;
		if(p>mid){
			return nxt(rson(x),p,mid+1,rend);
		}
		int res=nxt(lson(x),p,lend,mid);
		return res==mxval?nxt(rson(x),p,mid+1,rend):res;
	}
}
namespace R{
	int son[TN][2],tag[TN],val[TN],n=0;
	int root[N];
	inline void init(){
		clr(son),clr(val),clr(root);
		memset(tag,-1,sizeof(tag));
	}
	inline int renew(int x){
		if(tag[x]<tim){
			n++,lson(n)=lson(x),rson(n)=rson(x),tag[n]=tim,val[n]=x,x=n;
		}
		return x;
	}
	int set(int x,int p,int v,int lend,int rend){
		x=renew(x);
		if(lend==rend){
			assert(lend==p);
			val[x]=v;
			return x;
		}
		int mid=(lend+rend)>>1;
		if(p<=mid){
			lson(x)=set(lson(x),p,v,lend,mid);
		}else{
			rson(x)=set(rson(x),p,v,mid+1,rend);
		}
		return x;
	}
	int ask(int x,int p,int lend,int rend){
		if(lend==rend){
			return val[x];
		}
		int mid=(lend+rend)>>1;
		if(p<=mid){
			return ask(lson(x),p,lend,mid);
		}else{
			return ask(rson(x),p,mid+1,rend);
		}
	}
}
namespace T{
	int son[TN][2],tag[TN],color[TN],nxt[TN],n=0;
	lint sum[TN],diff[TN];
	int root[N];
	inline void init(){
		clr(son),clr(color),clr(nxt),clr(nxt),clr(root);
		memset(tag,-1,sizeof(tag));
	}
	lint ask(int x,int v,int lend,int rend){//get sum after limit
		if(lend==rend){
			assert(diff[x]==0);
			return min(sum[x],(lint)v);
		}
		int mid=(lend+rend)>>1;
		if(nxt[rson(x)]<=v){
			assert(nxt[x]==nxt[rson(x)]);
			return ask(rson(x),v,mid+1,rend)+sum[lson(x)]+diff[x];
		}else{
			assert(nxt[x]==nxt[lson(x)]);
			return ask(lson(x),v,lend,mid)+(((v<<1)-rend-(mid+1))*(rend-mid)>>1);
		}
	}
	inline void up(int x,int lend,int rend){
		assert(lson(x)&&rson(x));
		assert(tag[x]==tim);
		nxt[x]=min(nxt[lson(x)],nxt[rson(x)]);
		int mid=(lend+rend)>>1;
		if(nxt[lson(x)]<=nxt[rson(x)]){
			nxt[x]=nxt[lson(x)];
			sum[x]=ask(lson(x),nxt[rson(x)],lend,mid)+sum[rson(x)];
		}else{
			nxt[x]=nxt[rson(x)];
			sum[x]=sum[rson(x)]+((((lint)nxt[x]<<1)-lend-mid)*(mid-lend+1)>>1);
		}
		diff[x]=sum[x]-sum[lson(x)]-sum[rson(x)];
	}
	inline int renew(int x){
		if(tag[x]<tim){
			n++;
			lson(n)=lson(x),rson(n)=rson(x);
			tag[n]=tim;
			color[n]=color[x];
			nxt[n]=nxt[x];
			sum[n]=sum[x],diff[n]=diff[x];
			x=n;
		}
		return x;
	}
	int set(int x,int p,int v,int val[],int lend,int rend){
		x=renew(x);
		if(lend==rend){
			assert(lend==p);
			val[x]=v;
			if(val==nxt){
				diff[x]=0;
				sum[x]=v-lend;
			}
		}else{
			int mid=(lend+rend)>>1;
			if(p<=mid){
				lson(x)=set(lson(x),p,v,val,lend,mid);
			}else{
				rson(x)=set(rson(x),p,v,val,mid+1,rend);
			}
			if(val==nxt){
				up(x,lend,rend);
			}
		}
		return x;
	}
	int build(int x,int lend,int rend,int a[],int _nxt[]){
		x=renew(x);
		if(lend==rend){
			color[x]=a[lend];
			nxt[x]=_nxt[lend];
			diff[x]=0;
			sum[x]=nxt[x]-lend;
		}else{
			int mid=(lend+rend)>>1;
			lson(x)=build(lson(x),lend,mid,a,_nxt);
			rson(x)=build(rson(x),mid+1,rend,a,_nxt);
			up(x,lend,rend);
		}
		return x;
	}
	int col(int x,int p,int lend,int rend){
		if(lend==rend){
			return color[x];
		}
		int mid=(lend+rend)>>1;
		if(p<=mid){
			return col(lson(x),p,lend,mid);
		}else{
			return col(rson(x),p,mid+1,rend);
		}
	}
}
namespace Q{
	struct Info{
		int nxt;
		lint sum,diff;
	}info[TN];
	lint lim(int x,int v,int l,int lend,int rend){
		assert(l<=rend&&l>=lend);
		if(lend==rend){
			return min(info[x].sum,(lint)v);
		}
		int mid=(lend+rend)>>1;
		if(l>mid){
			return lim(T::rson(x),v,l,mid+1,rend);
		}
		if(info[T::rson(x)].nxt<=v){
			return lim(T::rson(x),v,mid+1,mid+1,rend)+info[T::lson(x)].sum+info[x].diff;
		}else{
			return lim(T::lson(x),v,l,lend,mid)+((((lint)v<<1)-rend-(mid+1))*(rend-mid)>>1);
		}
	}
	int mxnxt;
	void ask(int x,int l,int r,int lend,int rend){
		if(lend==rend){
			assert(l==lend&&r==rend);
			assert(T::diff[x]==0);
			info[x].nxt=min(T::nxt[x],mxnxt);
			info[x].sum=info[x].nxt-lend;
			info[x].diff=0;
			return;
		}
		int mid=(lend+rend)>>1,lc=T::lson(x),rc=T::rson(x);
		if(r<=mid){
			ask(lc,l,r,lend,mid);
			info[x]=info[lc];
			info[x].diff=0;
		}else if(l>mid){
			ask(rc,l,r,mid+1,rend);
			info[x]=info[rc];
			info[x].diff=0;
		}else{
			ask(lc,l,mid,lend,mid);
			ask(rc,mid+1,r,mid+1,rend);
			if(info[lc].nxt<=info[rc].nxt){
				info[x].sum=lim(lc,info[rc].nxt,l,lend,mid);
			}else{
				info[x].sum=((lint)(info[rc].nxt<<1)-l-mid)*(mid-l+1)>>1;
			}
			info[x].nxt=min(info[lc].nxt,info[rc].nxt);
			info[x].diff=info[x].sum-info[lc].sum;
			info[x].sum+=info[rc].sum;
		}
	}
}
int main(){
	W::init(),R::init(),T::init();
	int n=ni;
	W::mxval=n+1;
	{
		int a[N],nxt[N],root[N];
		memset(root,0,sizeof(root));
		for(int i=1;i<=n;i++){
			a[i]=ni;
			root[a[i]]=W::set(root[a[i]],i,1,n);
		}
		for(int i=1;i<=n;i++){
			if(root[i]){
				R::root[tim]=R::set(R::root[tim],i,root[i],1,n);
			}
			root[i]=n+1;
		}
		for(int i=n;i>=1;i--){
			nxt[i]=root[a[i]];
			root[a[i]]=i;
		}
		T::root[tim]=T::build(T::root[tim],1,n,a,nxt);
	}
	lint ans=0;
	for(int tot=ni;tot--;){
		int id=ni,t=ni,a=(ni+ans)%n+1,b=(ni+ans)%n+1;
//		int l=ni,r=ni;
		if(id==1){//alt
			tim++;
			int oldc=T::col(T::root[t],a,1,n),newc=b;
			if(oldc==newc){
				continue;
			}
			int oldr=R::ask(R::root[t],oldc,1,n),newr=R::ask(R::root[t],newc,1,n);
			//start setting
			T::root[tim]=T::set(T::root[t],a,W::nxt(newr,a,1,n),T::nxt,1,n);
			R::root[tim]=R::set(R::set(R::root[t],newc,W::set(newr,a,1,n),1,n),oldc,W::del(oldr,a,1,n),1,n);
			int pre=W::pre(oldr,a,1,n);
			if(pre){
				T::root[tim]=T::set(T::root[tim],a,W::nxt(oldr,pre,1,n),T::nxt,1,n);
			}
		}else{//ask
			Q::mxnxt=b;
			Q::ask(T::root[t],a,b,1,n);
			printf("%lld\n",Q::info[T::root[t]].sum);
		}
	}
}