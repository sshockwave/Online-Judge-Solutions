#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline lint _sqr(lint n){
	return n*(n+1)/2*((n<<1)+1)/3;
}
const int N=100010;
int inix[N],iniy[N];
struct SegmentTree{
	typedef SegmentTree node;
	struct Info{
		lint x,y,xy,xx;
		bool tag2,tag3;
		int s2,t2,s3,t3;
		inline friend Info operator + (Info a,Info b){
			return (Info){a.x+b.x,a.y+b.y,a.xy+b.xy,a.xx+b.xx};
		}
		inline Info trans2(int l,int r,int s,int t){
			//x+=s,y+=t
			lint len=r-l+1;
			Info tmp=(Info){x+len*s,y+len*t,xy+y*s+x*t+len*s*t,xx+x*s*2+len*s*s};
			tmp.tag2=true;
			tmp.tag3=false;
			tmp.s2=s;
			tmp.t2=t;
			return tmp;
		}
		inline Info trans3(int l,int r,int s,int t){
			//x=s+i,y=t+i
			lint len=r-l+1,sigi=(l+r)*len/2,sigi2=_sqr(r)-_sqr(l-1);
			Info tmp=(Info){len*s+sigi,len*t+sigi,len*s*t+sigi*(s+t)+sigi2,len*s*s+sigi*s*2+sigi2};
			tmp.tag2=false;
			tmp.tag3=true;
			tmp.s3=s;
			tmp.t3=t;
			return tmp;
		}
		inline double cal(int l,int r){
			int n=r-l+1;
			return (xy-(double)x/n*y)/(xx-(double)x/n*x);
		}
	}info;
	int lend,rend,mid;
	node *lson,*rson;
	inline void up(){
		assert(lend!=rend);
		info=lson->info+rson->info;
	}
	inline void down(){
		if(lend==rend){
			info.tag2=info.tag3=false;
		}
		if(info.tag2){
			assert(!info.tag3);
			lson->cover2(info.s2,info.t2);
			rson->cover2(info.s2,info.t2);
			info.tag2=false;
		}
		if(info.tag3){
			assert(!info.tag2);
			lson->cover3(info.s3,info.t3);
			rson->cover3(info.s3,info.t3);
			info.tag3=false;
		}
	}
	void build(int l,int r){
		static node *n=new node[N];
		lend=l,rend=r,mid=(l+r)>>1;
		if(l==r){
			info=(Info){inix[l],iniy[l],(lint)inix[l]*iniy[l],(lint)inix[l]*inix[l],0,0};
		}else{
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
			up();
		}
	}
	inline void cover2(int s,int t){
		info=info.trans2(lend,rend,s,t);
	}
	inline void cover3(int s,int t){
		info=info.trans3(lend,rend,s,t);
	}
	void alter(int l,int r,int s,int t,int type){
		assert(lend<=l&&r<=rend);
		down();
		if(lend==l&&rend==r){
			if(type==2){
				cover2(s,t);
			}else{
				assert(type==3);
				cover3(s,t);
			}
			return;
		}
		if(r<=mid){
			lson->alter(l,r,s,t,type);
		}else if(l>mid){
			rson->alter(l,r,s,t,type);
		}else{
			lson->alter(l,mid,s,t,type);
			rson->alter(mid+1,r,s,t,type);
		}
		up();
	}
	Info ask(int l,int r){
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			return info;
		}
		down();
		if(r<=mid){
			return lson->ask(l,r);
		}
		if(l>mid){
			return rson->ask(l,r);
		}
		return lson->ask(l,mid)+rson->ask(mid+1,r);
	}
}seg;
int main(){
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		inix[i]=ni;
	}
	for(int i=1;i<=n;i++){
		iniy[i]=ni;
	}
	seg.build(1,n);
	while(tot--){
		int op=ni,l=ni,r=ni;
		if(op==1){
			printf("%.10lf\n",seg.ask(l,r).cal(l,r));
		}else{
			int s=ni,t=ni;
			seg.alter(l,r,s,t,op);
		}
	}
}
