#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline int nl(){
	lint i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=200010,MOD=1000000007;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline int sub(int a,int b){
	return add(a,MOD-b);
}
inline int mul(int a,int b){
	return (lint)a*b%MOD;
}
inline void apadd(int &a,int b){
	a=add(a,b);
}
int n;
char s[N];
struct SegmentTree{
	typedef SegmentTree node;
	int lend,rend,mid,pos,sum,isum;
	node *lson,*rson;
	void build(int,int,bool);
	inline void up(){
		assert(lend!=rend);
		sum=lson->sum+rson->sum;
		isum=lson->isum+rson->isum;
	}
	void alter(int x,int val){
		assert(lend<=x&&x<=rend);
		if(lend==rend){
			sum=val,isum=pos*val;
		}else{
			(x<=mid?lson:rson)->alter(x,val);
			up();
		}
	}
	int ask_sum(int l,int r){
		assert(lend<=l&&r<=rend);
		if(l==lend&&r==rend){
			return sum;
		}
		if(r<=mid){
			return lson->ask_sum(l,r);
		}
		if(l>mid){
			return rson->ask_sum(l,r);
		}
		return add(lson->ask_sum(l,mid),rson->ask_sum(mid+1,r));
	}
	int ask_isum(int l,int r){
		assert(lend<=l&&r<=rend);
		if(l==lend&&r==rend){
			return isum;
		}
		if(r<=mid){
			return lson->ask_isum(l,r);
		}
		if(l>mid){
			return rson->ask_isum(l,r);
		}
		return add(lson->ask_isum(l,mid),rson->ask_isum(mid+1,r));
	}
}seg[2],pool[N*2];
void SegmentTree::build(int l,int r,bool d){
	static node* n=pool;
	lend=l,rend=r,mid=(l+r)>>1;
	if(l==r){
		pos=(l<<1)|d;
		sum=s[pos]-'0',isum=pos*sum;
	}else{
		(lson=n++)->build(l,mid,d);
		(rson=n++)->build(mid+1,r,d);
		up();
	}
}
inline int ask_sum(int l,lint r){//gap=2
	assert((l&1)==(r&1));
	bool d=l&1;
	if(r<n){
		return seg[d].ask_sum(l>>1,r>>1);
	}
	int ans=seg[d].ask_sum(l>>1,seg[d].rend);
	lint sec=r/n-1;
	if(n&1){
		apadd(ans,mul((sec>>1)%MOD,add(seg[0].sum,seg[1].sum)));
		if(sec&1){
			apadd(ans,seg[!d].sum);
			assert(((r%n)&1)==(l&1));
			apadd(ans,seg[d].ask_sum(0,(r%n)>>1));
		}else{
			assert(((r%n)&1)!=(l&1));
			apadd(ans,seg[!d].ask_sum(0,(r%n)>>1));
		}
	}else{
		apadd(ans,mul(sec%MOD,seg[d].sum));
		apadd(ans,seg[d].ask_sum(0,(r%n)>>1));
	}
	return ans;
}
inline int ask_isum(int l,lint r){
	assert((l&1)==(r&1));
	bool d=l&1;
	if(r<n){
		return seg[d].ask_isum(l>>1,r>>1);
	}
	int ans=seg[d].ask_isum(l>>1,seg[d].rend);
	lint sec=r/n-1;
	static int rev2=(MOD>>1)+1;
	if(n&1){
		lint half=sec>>1;
		apadd(ans,mul(half%MOD,add(seg[0].isum,seg[1].isum)));
		apadd(ans,mul(seg[!d].rend+1,mul(mul(half%MOD,half%MOD),n)));
		apadd(ans,mul(seg[d].rend+1,mul(mul(half%MOD,(half+1)%MOD),n)));
		if(sec&1){
			apadd(ans,seg[!d].isum);
			apadd(ans,mul(seg[!d].rend+1,mul(sec%MOD,n)));
			assert(((r%n)&1)==(l&1));
			apadd(ans,seg[d].ask_isum(0,(r%n)>>1));
			apadd(ans,mul(((r%n)>>1)+1,mul((sec+1)%MOD,n)));
		}else{
			assert(((r%n)&1)!=(l&1));
			apadd(ans,seg[!d].ask_isum(0,(r%n)>>1));
			apadd(ans,mul(((r%n)>>1)+1,mul((sec+1)%MOD,n)));
		}
	}else{
		apadd(ans,mul(sec%MOD,seg[d].isum));
		apadd(ans,mul(seg[d].rend+1,mul(mul((sec+1)%MOD,sec%MOD),mul(n,rev2))));
		apadd(ans,seg[d].ask_isum(0,(r%n)>>1));
		apadd(ans,mul(((r%n)>>1)+1,mul((sec+1)%MOD,n)));
	}
	return ans;
}
int main(){
	freopen("B.in","r",stdin);
	n=ni();
	scanf("%s",s);
	seg[0].build(0,(n-1)>>1,0);
	seg[1].build(0,(n>>1)-1,1);
	for(int tot=ni();tot--;){
		if(ni()==1){
			int pos=ni()-1;
			seg[pos&1].alter(pos>>1,ni());
		}else{
			lint l=nl(),r=nl(),qr=r-((r-l)&1);
			r-=l--,l%=n,r+=l;
			printf("%d\n",sub(mul((r+1)%MOD,ask_sum(l,qr)),ask_isum(l,qr)));
		}
	}
}
