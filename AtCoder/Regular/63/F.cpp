#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <algorithm>
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
const int N=300010;
int xm,ym,n,ans=0;
struct Pt{
	int x,y;
	inline friend bool operator < (const Pt &a,const Pt &b){
		return a.y!=b.y?a.y<b.y:a.x<b.x;
	}
	inline friend ostream & operator << (ostream & out,const Pt &b){
		out<<"("<<b.x<<","<<b.y<<")";
		return out;
	}
}pt[N],lstl[N],lstr[N];
int lsl,lsr;
struct intv{
	int l,r,x;
	inline friend bool operator < (const intv &a,const intv &b){
		return a.l<b.l;
	}
}*lv=new intv[N<<1],*rv=new intv[N<<1];
int lvl,lvr;
struct intvcmp2{
	inline bool operator () (const intv &a,const intv &b){
		return a.r!=b.r?a.r<b.r:a.x<b.x;
	}
};
inline void work2(){
	typedef set<intv,intvcmp2>::iterator iter;
	set<intv,intvcmp2>s;
	for(int i=1,j=1;i<=lvl;i++){
		for(;j<=lvr&&rv[j].l<=lv[i].l;j++){
			if(rv[j].r>lv[i].l){
				iter it=s.insert(rv[j]).first;
				if(it!=s.begin()){
					iter bef=it;
					bef--;
					if(bef->r+bef->x>=it->r+it->x){
						s.erase(it);
						continue;
					}
					if(bef->r==it->r){
						s.erase(bef);
					}
				}
				for(iter it2;it2=it,it2++,it2!=s.end()&&it2->r+it2->x<=it->r+it->x;s.erase(it2));
			}
		}
		for(;assert(!s.empty()),s.begin()->r<=lv[i].l;s.erase(s.begin()));
		iter it=s.lower_bound((intv){0,lv[i].r+1,-1});
		if(it!=s.end()){
			assert(it->r>lv[i].r);
			apmax(ans,it->x-lv[i].x+lv[i].r-lv[i].l);
		}
		if(it!=s.begin()){
			it--;
			assert(it->r<=lv[i].r);
			apmax(ans,it->x-lv[i].x+it->r-lv[i].l);
		}
	}
}
int stk[N],ss;
int pre[N],nxt[N];
inline void work(){
	sort(pt+1,pt+n+1);
	lsl=lsr=lvl=lvr=0;
	int m=xm>>1;
	for(int i=1;i<=n;i++){
		(pt[i].x<=m?lstl[++lsl]:lstr[++lsr])=pt[i];
	}
	{//left hand side
		lstl[0].y=0;
		stk[ss=0]=0;
		for(int i=1;i<=lsl;i++){
			if(i<lsl&&lstl[i+1].y==lstl[i].y)continue;
			for(;ss&&lstl[stk[ss]].x<=lstl[i].x;ss--);
			pre[i]=lstl[stk[ss]].y;
			stk[++ss]=i;
		}
		lstl[0].y=ym;
		stk[ss=0]=0;
		for(int i=lsl;i>=1;i--){
			if(i<lsl&&lstl[i+1].y==lstl[i].y)continue;
			for(;ss&&lstl[stk[ss]].x<=lstl[i].x;ss--);
			nxt[i]=lstl[stk[ss]].y;
			stk[++ss]=i;
		}
		int last=0;
		for(int i=1;i<=lsl;i++){
			if(i<lsl&&lstl[i+1].y==lstl[i].y)continue;
			lv[++lvl]=(intv){pre[i],nxt[i],lstl[i].x};
			lv[++lvl]=(intv){last,lstl[i].y,0};
			last=lstl[i].y;
		}
		assert(last!=ym);
		lv[++lvl]=(intv){last,ym,0};
		sort(lv+1,lv+lvl+1);
	}
	{//right hand side
		lstr[0].y=0;
		stk[ss=0]=0;
		for(int i=1;i<=lsr;i++){
			if(i>1&&lstr[i-1].y==lstr[i].y)continue;
			for(;ss&&lstr[stk[ss]].x>=lstr[i].x;ss--);
			pre[i]=lstr[stk[ss]].y;
			stk[++ss]=i;
		}
		lstr[0].y=ym;
		stk[ss=0]=0;
		for(int i=lsr;i>=1;i--){
			if(i>1&&lstr[i-1].y==lstr[i].y)continue;
			for(;ss&&lstr[stk[ss]].x>=lstr[i].x;ss--);
			nxt[i]=lstr[stk[ss]].y;
			stk[++ss]=i;
		}
		int last=0;
		for(int i=1;i<=lsr;i++){
			if(i>1&&lstr[i-1].y==lstr[i].y)continue;
			rv[++lvr]=(intv){pre[i],nxt[i],lstr[i].x};
			rv[++lvr]=(intv){last,lstr[i].y,xm};
			last=lstr[i].y;
		}
		assert(last!=ym);
		rv[++lvr]=(intv){last,ym,xm};
		sort(rv+1,rv+lvr+1);
	}
	work2();
	swap(lv,rv),swap(lvl,lvr);
	for(int i=1;i<=lvl;i++){
		lv[i].x=xm-lv[i].x;
	}
	for(int i=1;i<=lvr;i++){
		rv[i].x=xm-rv[i].x;
	}
	work2();
}
int main(){
	xm=ni,ym=ni,n=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
		if(pt[i].x==0||pt[i].x==xm||pt[i].y==0||pt[i].y==ym){
			--i,--n;
		}
	}
	work();
	swap(xm,ym);
	for(int i=1;i<=n;i++){
		swap(pt[i].x,pt[i].y);
	}
	work();
	printf("%d\n",ans<<1);
	return 0;
}
