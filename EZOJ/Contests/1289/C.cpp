#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <ctime>
using namespace std;
typedef long long lint;
typedef long double ld;
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
const int N=100010;
int inix[N],iniy[N];
inline lint _sqr(lint x){
	return x*(x+1)*(x*2+1)/6;
}
struct SegmentTree{
	typedef SegmentTree node;
	struct Info{
		ld x,y,xx,xy;
		inline friend Info operator + (const Info &a,const Info &b){
			return (Info){a.x+b.x,a.y+b.y,a.xx+b.xx,a.xy+b.xy};
		}
		inline void trans2(int l,int r,int s,int t){
			lint n=r-l+1;
			ld tx=x,ty=y;
			x+=n*s;
			y+=n*t;
			xx+=tx*s*2+n*s*s;
			xy+=ty*s+tx*t+n*s*t;
		}
		inline void trans3(int l,int r,int s,int t){
			lint n=r-l+1,sigi=n*(l+r)/2,sigi2=_sqr(r)-_sqr(l-1);
			x=n*s+sigi;
			y=n*t+sigi;
			xx=n*s*s+sigi*s*2+sigi2;
			xy=n*s*t+sigi*(s+t)+sigi2;
		}
		inline ld cal(int l,int r){
			int n=r-l+1;
			return (xy*n-x*y)/(xx*n-x*x);
		}
	}info;
	int lend,rend,mid,s,t;
	bool tag2,tag3;
	node *lson,*rson;
	inline void up(){
		assert(lend!=rend);
		info=lson->info+rson->info;
	}
	inline void down(){
		if(lend!=rend&&(tag2||tag3)){
			assert((tag2&&!tag3)||(!tag2&&tag3));
			lson->cover(s,t,3-tag2);
			rson->cover(s,t,3-tag2);
			tag2=tag3=false;
		}
	}
	void build(int l,int r){
		static node *n=new node[N*2];
		lend=l,rend=r,mid=(l+r)>>1;
		tag2=tag3=false;
		if(l==r){
			info.x=inix[l];
			info.y=iniy[l];
			info.xx=info.x*info.x;
			info.xy=info.x*info.y;
		}else{
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
			up();
		}
	}
	inline void cover(int s,int t,int type){
		if(type==2){
			info.trans2(lend,rend,s,t);
			if(tag2||tag3){
				this->s+=s,this->t+=t;
			}else{
				tag2=true;
				this->s=s,this->t=t;
			}
		}else{
			info.trans3(lend,rend,s,t);
			tag2=false;
			tag3=true;
			this->s=s,this->t=t;
		}
	}
	void alter(int l,int r,int s,int t,int type){
		assert(lend<=l&&r<=rend);
		if(lend==l&&rend==r){
			cover(s,t,type);
			return;
		}
		down();
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
			printf("%.10lf\n",(double)seg.ask(l,r).cal(l,r));
		}else{
			int s=ni,t=ni;
			seg.alter(l,r,s,t,op);
		}
	}
}
