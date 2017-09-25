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
const int N=200010,INF=0x7f7f7f7f;
int vis[N];
bool used[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int mn;
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->mn=vis[l]?INF:l;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->mn=min(x->lson->mn,x->rson->mn);
		}
		return x;
	}
	void set(node x,int p){
		if(x->l==x->r){
			x->mn=INF;
		}else{
			set(p<=x->m?x->lson:x->rson,p);
			x->mn=min(x->lson->mn,x->rson->mn);
		}
	}
}
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
#endif
	int n=ni;
	memset(vis,0,sizeof(vis));
	memset(used,0,sizeof(used));
	for(int i=1;i<=n;i++){
		a[i]=ni;
		vis[a[i]]++;
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			cnt++;
		}
	}
	printf("%d\n",cnt);
	seg::rt=seg::build(1,n);
	for(int i=1;i<=n;i++){
		int alt=seg::rt->mn;
		if((vis[a[i]]>1&&alt<a[i])||used[a[i]]){
			printf("%d ",alt);
			seg::set(seg::rt,alt);
		}else{
			printf("%d ",a[i]);
			used[a[i]]=true;
		}
		vis[a[i]]--;
	}
	putchar('\n');
	return 0;
}
