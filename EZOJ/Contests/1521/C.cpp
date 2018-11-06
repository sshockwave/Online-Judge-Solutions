#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=100010;
char s[N];
namespace seg{
	struct Node;
	typedef Node* node;
	typedef vector<node>vn;
	struct Node{
		node lson,rson;
		int rnk;
	}pool[N*20];
	inline int idx(int l,int r){
		return (l+r)|(l!=r);
	}
	inline node nn(node x){
		static node n=pool;
		return *n=*x,n++;
	}
	vn vec[N<<1];
	node build(int l,int r){
		node x=nn(pool);
		const int m=(l+r)>>1;
		if(l==r){
			x->rnk=s[m]-'a'+1;
		}else{
			vec[idx(l,r)].push_back(x);
			x->lson=build(l,m);
			x->rson=build(m+1,r);
		}
		return x;
	}
	void upd(node &x,int p,int v,int l,int r){
		x=nn(x);
		if(l==r){
			x->rnk=v;
			return;
		}
		vec[idx(l,r)].push_back(x);
		const int m=(l+r)>>1;
		if(p<=m){
			upd(x->lson,p,v,l,m);
		}else{
			upd(x->rson,p,v,m+1,r);
		}
	}
	node lst[N],lst2[N];
	int cnt[N];
	inline bool rnkcmp(node u,node v){
		return u->lson->rnk!=v->lson->rnk?u->lson->rnk<v->lson->rnk:u->rson->rnk<v->rson->rnk;
	}
	void seg_sort(int l,int r){
		if(l==r)return;
		const int m=(l+r)>>1;
		seg_sort(l,m),seg_sort(m+1,r);
		const int x=idx(l,r),rsize=max<int>(vec[idx(m+1,r)].size(),26);
		const int n=vec[x].size();
		mset(cnt+1,0,rsize);
		for(vn::iterator it=vec[x].begin(),ti=vec[x].end();it!=ti;++it){
			++cnt[(*it)->rson->rnk];
		}
		for(int i=1,ti=rsize;i<=ti;i++){
			cnt[i]+=cnt[i-1];
		}
		for(vn::reverse_iterator it=vec[x].rbegin(),ti=vec[x].rend();it!=ti;++it){
			lst[cnt[(*it)->rson->rnk]--]=*it;
		}
		int nsize=max(n,26);
		mset(cnt+1,0,nsize);
		for(int i=1;i<=n;i++){
			++cnt[lst[i]->lson->rnk];
		}
		for(int i=1;i<=nsize;i++){
			cnt[i]+=cnt[i-1];
		}
		for(int i=n;i>=1;i--){
			lst2[cnt[lst[i]->lson->rnk]--]=lst[i];
		}
		for(int i=1,j=0;i<=n;i++){
			if(j==0||rnkcmp(lst2[i-1],lst2[i])){
				++j;
			}
			lst2[i]->rnk=j;
		}
	}
}
seg::node rt[N];
int cnt[N],lst[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("z.in","r",stdin);
	freopen("z.out","w",stdout);
#endif
	const int n=ni,m=ni;
	scanf("%s",s+1);
	seg::cnt[0]=0;
	rt[1]=seg::build(1,m);
	for(int i=2;i<=n;i++){
		int fa=ni,pos=ni;
		char c;
		scanf("%c",&c);
		seg::upd(rt[i]=rt[fa],pos,c-'a'+1,1,m);
	}
	seg::seg_sort(1,m);
	int nsize=max(n,26);
	mset(cnt,0,nsize+1);
	for(int i=1;i<=n;i++){
		++cnt[rt[i]->rnk];
	}
	for(int i=1;i<=nsize;i++){
		cnt[i]+=cnt[i-1];
	}
	for(int i=n;i>=1;i--){
		lst[cnt[rt[i]->rnk]--]=i;
	}
	for(int i=1;i<=n;i++){
		printf("%d ",lst[i]);
	}
	putchar('\n');
	return 0;
}
