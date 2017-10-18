#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
inline char nc(){
	char c;
	while(!isalpha(c=getchar()));
	return c;
}
const int N=500010,L=900010;
char s[L];
namespace T{
	const int N=L;
	typedef int arr[N];
	arr lson,rson,size;
	ull mark[N];
	int rt=0;
	inline void init(){
		memset(lson,0,sizeof(lson));
		memset(rson,0,sizeof(rson));
		mark[0]=0;
	}
	inline bool strcmp(int a,int b){
		return s[a]!=s[b]?s[a]<s[b]:mark[a-1]<mark[b-1];
	}
	int lst[N],ls;
	void dfs(int x){
		if(x==0){
			return;
		}
		dfs(lson[x]),lst[++ls]=x,dfs(rson[x]);
	}
	int reb(int l,int r,ull ml,ull mr){
		if(l>r){
			return 0;
		}
		int m=(l+r)>>1,x=lst[m];
		mark[x]=(ml+mr)>>1;
		lson[x]=reb(l,m-1,ml,mark[x]-1);
		rson[x]=reb(m+1,r,mark[x]+1,mr);
		size[x]=size[lson[x]]+size[rson[x]]+1;
		return x;
	}
	inline void ins(int n){
		ull l=1,r=(1ull<<63)-1;
		if(rt==0){
			rt=n;
			mark[n]=(l+r)>>1;
			size[n]=1;
			return;
		}
		int *x=&rt,*node=0;
		ull nl,nr;
		size[rt]++;
		for(int *y;*x!=n;x=y){
			y=(strcmp(n,*x)?lson:rson)+*x;
			if(*y==0){
				*y=n;
			}
			size[*y]++;
			if(node==0&&(size[lson[*x]]*10>size[*x]*7||size[rson[*x]]*10>size[*x]*7)){
				node=x,nl=l,nr=r;
			}
			if(strcmp(n,*x)){
				r=mark[*x]-1;
			}else{
				l=mark[*x]+1;
			}
		}
		mark[n]=(l+r)>>1;
		if(node){
			ls=0,dfs(*node),*node=reb(1,ls,nl,nr);
		}
	}
}
int a[N];
namespace seg{
	inline int mmin(int x,int y){
		return T::mark[a[x]]<=T::mark[a[y]]?x:y;
	}
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int mn;
		inline void up(){
			mn=mmin(lson->mn,rson->mn);
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			a[l]=ni,x->mn=l;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->up();
		}
		return x;
	}
	void alt(node x,int p,int v){
		if(x->l==x->r){
			a[p]=v;
		}else{
			alt(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	int ask(node x,int l,int r){
		if(x->l==l&&x->r==r){
			return x->mn;
		}
		if(r<=x->m){
			return ask(x->lson,l,r);
		}
		if(l>x->m){
			return ask(x->rson,l,r);
		}
		return mmin(ask(x->lson,l,x->m),ask(x->rson,x->m+1,r));
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("phorni.in","r",stdin);
	freopen("phorni.out","w",stdout);
#endif
	int n=ni,tot=ni,len=ni;
	scanf("%s",s+1);
	reverse(s+1,s+len+1);
	for(int i=1;i<=len;i++){
		T::ins(i);
	}
	seg::rt=seg::build(1,n);
	for(int ans=0,l,r;tot--;){
		switch(nc()){
			case 'I':
				s[++len]=(ni^ans)+'a';
				T::ins(len);
				break;
			case 'C':
				l=ni,r=ni;
				seg::alt(seg::rt,l,r);
				break;
			case 'Q':
				l=ni,r=ni;
				printf("%d\n",ans=seg::ask(seg::rt,l,r));
				break;
		}
	}
	return 0;
}
