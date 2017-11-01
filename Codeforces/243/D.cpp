#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=1001,N2=N*N,INF=0x7f7f7f7f;
int vx,vy;
inline int crs(int x,int y){return x*vy-y*vx;}
inline int dot(int x,int y){return x*vx+y*vy;}
int pt[N2],ps=0;
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		int h;
		inline void down(){
			apmax(lson->h,h);
			apmax(rson->h,h);
		}
		inline void up(){
			h=min(lson->h,rson->h);
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N2<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->h=0;
		if(l!=r){
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
		}
		return x;
	}
	int l,r,h;
	int ins(node x){
		if(l<pt[x->l]&&r>=pt[x->r]){
			int tmp=x->h;
			apmax(x->h,h);
			return tmp;
		}
		x->down();
		int ans=INF;
		if(l<pt[x->m])apmin(ans,ins(x->lson));
		if(r>pt[x->m])apmin(ans,ins(x->rson));
		x->up();
		return ans;
	}
}
int lst[N2],qh[N2],ql[N2],qr[N2],qd[N2],ls=0;
inline bool lcmp(const int &a,const int &b){
	return qd[a]<qd[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("cube.in","r",stdin);
	freopen("cube.out","w",stdout);
#endif
	int n=ni;
	vx=ni,vy=ni;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			pt[i*(n+1)+j]=crs(i,j);
		}
	}
	sort(pt,pt+(n+1)*(n+1));
	for(int i=0,ti=(n+1)*(n+1);i<ti;ps++){
		pt[ps]=pt[i];
		for(;i<ti&&pt[ps]==pt[i];i++);
	}
	seg::rt=seg::build(1,ps-1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			qh[ls]=ni;
			ql[ls]=min(min(crs(i-1,j),crs(i,j-1)),min(crs(i-1,j-1),crs(i,j)));
			qr[ls]=max(max(crs(i-1,j),crs(i,j-1)),max(crs(i-1,j-1),crs(i,j)));
			qd[ls]=min(min(dot(i-1,j),dot(i,j-1)),min(dot(i-1,j-1),dot(i,j)));
			lst[ls]=ls;
			ls++;
		}
	}
	sort(lst,lst+ls,lcmp);
	lint ans=0;
	for(int i=0,j;j=lst[i],i<ls;i++){
		seg::h=qh[j],seg::l=ql[j],seg::r=qr[j];
		ans+=max(qh[j]-seg::ins(seg::rt),0);
	}
	printf("%I64d\n",ans);
	return 0;
}
