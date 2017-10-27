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
const int N=100010,D=26;
struct charset{
	int cnt[D];
	inline void clr(){
		memset(cnt,0,sizeof(cnt));
	}
	inline void split(int);
	inline friend charset operator + (const charset &a,const charset &b){
		charset c;
		for(int i=0;i<D;i++){
			c.cnt[i]=a.cnt[i]+b.cnt[i];
		}
		return c;
	}
}rs1,rs2;
inline void charset::split(int x){
	int sum=0;
	rs1.clr();
	for(int i=0;i<D;i++){
		if(cnt[i]+sum<=x){
			rs1.cnt[i]=cnt[i];
			sum+=cnt[i];
		}else{
			rs1.cnt[i]=x-sum;
			break;
		}
	}
	for(int i=0;i<D;i++){
		rs2.cnt[i]=cnt[i]-rs1.cnt[i];
	}
}
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		charset sum;
		int stat;//-1:fall 0:none 1:rise
		inline void down(){
			if(stat==-1){
				lson->stat=rson->stat=-1;
				sum.split(r-m);
				lson->sum=rs2,rson->sum=rs1;
			}else if(stat==1){
				lson->stat=rson->stat=1;
				sum.split(m-l+1);
				lson->sum=rs1,rson->sum=rs2;
			}
		}
		inline void up(){
			stat=0;
			sum=lson->sum+rson->sum;
		}
	}*rt;
	node build(int l,int r,char s[]){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		if(l==r){
			x->stat=0;
			x->sum.clr();
			x->sum.cnt[s[l]-'a']=1;
		}else{
			x->lson=build(l,x->m,s);
			x->rson=build(x->m+1,r,s);
			x->up();
		}
		return x;
	}
	charset ask(node x,int l,int r){
		if(x->l==l&&x->r==r){
			return x->sum;
		}
		x->down();
		if(r<=x->m){
			return ask(x->lson,l,r);
		}
		if(l>x->m){
			return ask(x->rson,l,r);
		}
		return ask(x->lson,l,x->m)+ask(x->rson,x->m+1,r);
	}
	void set(node x,int p,int v){
		if(x->l==x->r){
			x->sum.clr();
			x->sum.cnt[v]++;
		}else{
			set(p<=x->m?x->lson:x->rson,p,v);
			x->up();
		}
	}
	void set(node x,int l,int r,charset &cs,int stat){
		if(x->l==l&&x->r==r){
			x->sum=cs,x->stat=stat;
			return;
		}
		x->down();
		if(r<=x->m){
			set(x->lson,l,r,cs,stat);
		}else if(l>x->m){
			set(x->rson,l,r,cs,stat);
		}else{
			charset lv,rv;
			if(stat==1){
				cs.split(x->m-l+1);
				lv=rs1,rv=rs2;
			}else if(stat==-1){
				cs.split(r-x->m);
				lv=rs2,rv=rs1;
			}else{
				assert(false);
			}
			set(x->lson,l,x->m,lv,stat);
			set(x->rson,x->m+1,r,rv,stat);
		}
		x->up();
	}
	void dfs(node x){
		if(x->stat||x->l==x->r){
			if(x->stat>0){
				for(int i=0;i<D;i++){
					for(int j=0;j<x->sum.cnt[i];j++){
						putchar('a'+i);
					}
				}
			}else{
				for(int i=D-1;i>=0;i--){
					for(int j=0;j<x->sum.cnt[i];j++){
						putchar('a'+i);
					}
				}
			}
		}else{
			dfs(x->lson),dfs(x->rson);
		}
	}
}
char s[N];
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int n=ni,tot=ni;
	scanf("%s",s+1);
	seg::rt=seg::build(1,n,s);
	while(tot--){
		int l=ni,r=ni;//todo
		static charset cs;
		cs=seg::ask(seg::rt,l,r);
		int cnt=0;
		for(int i=0;i<D;i++){
			cnt+=cs.cnt[i]&1;
		}
		if(cnt>((r-l+1)&1)){
			continue;
		}
		int half=(r-l+1)>>1;
		for(int i=0;i<D;i++){
			if(cs.cnt[i]&1){
				seg::set(seg::rt,l+half,i);
				cs.cnt[i]--;
			}
			cs.cnt[i]>>=1;
		}
		if(half){
			seg::set(seg::rt,l,l+half-1,cs,1);
			seg::set(seg::rt,r-half+1,r,cs,-1);
		}
	}
	seg::dfs(seg::rt);
	putchar('\n');
	return 0;
}
