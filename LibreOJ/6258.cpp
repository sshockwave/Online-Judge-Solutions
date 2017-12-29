#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <queue>
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
const int N=100010;
struct food{
	int tim,id;
	inline friend bool operator < (const food &a,const food &b){
		return a.tim>b.tim;
	}
};
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int sum;
		inline void up(){
			sum=lson->sum+rson->sum;
		}
	}pool[N<<1];
	node rt,ns;
	node build(int l,int r){
		node x=ns++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->sum=0;
		if(l==r){
			x->lson=x->rson=NULL;
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	int ask(node x,int l,int r){
		if(x->l==l&&x->r==r)return x->sum;
		if(r<=x->m)return ask(x->lson,l,r);
		if(l>x->m)return ask(x->rson,l,r);
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
	void add(node x,int p,int v){
		if(x->l==x->r){
			x->sum+=v;
		}else{
			add(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	int gfirst(node x){
		assert(x->sum);
		if(x->l==x->r)return x->l;
		if(x->lson->sum)return gfirst(x->lson);
		return gfirst(x->rson);
	}
}
int all[N],ripe[N];
priority_queue<food>q;
priority_queue<int>raw[N];
int len[N];
inline void Main(){
	int n=ni;
	for(int i=1;i<=n;i++){
		len[i]=ni;
		all[i]=0,ripe[i]=0;
		for(;!raw[i].empty();raw[i].pop());
	}
	for(;!q.empty();q.pop());
	seg::ns=seg::pool,seg::rt=seg::build(1,n);
	for(int tot=ni;tot--;){
		int tim=ni;
		for(;!q.empty()&&q.top().tim<=tim;q.pop()){
			int id=q.top().id;
			assert(raw[id].top()+q.top().tim==0);
			raw[id].pop();
			ripe[id]++;
			seg::add(seg::rt,id,1);
		}
		int op=ni;
		if(op==0){
			int id=ni;
			all[id]++;
			raw[id].push(-(tim+len[id]));
			q.push((food){tim+len[id],id});
		}else if(op==1){
			if(seg::rt->sum==0){
				puts("Yazid is angry.");
				continue;
			}
			int id=seg::gfirst(seg::rt);
			printf("%d\n",id);
			ripe[id]--,all[id]--;
			seg::add(seg::rt,id,-1);
		}else if(op==2){
			int id=ni;
			if(all[id]==0){
				puts("YJQQQAQ is angry.");
				continue;
			}
			if(ripe[id]){
				puts("Succeeded!");
				ripe[id]--,all[id]--;
				seg::add(seg::rt,id,-1);
				continue;
			}
			printf("%d\n",-raw[id].top()-tim);
		}else if(op==3){
			int l=ni,r=ni;
			printf("%d\n",seg::ask(seg::rt,l,r));
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("hotpot.in","r",stdin);
	freopen("hotpot.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
