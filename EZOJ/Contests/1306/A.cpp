#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(a>b){a=b;}
}
const int N=300010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
namespace B{
	lint c[N],n;
	inline void init(){
		memset(c,0,sizeof(c));
	}
	inline int lowbit(int x){
		return x&(-x);
	}
	inline void add(int x,lint v){
		for(;x<=n;c[x]+=v,x+=lowbit(x));
	}
	inline lint sum(int x){
		lint ans=0;
		for(;x;ans+=c[x],x^=lowbit(x));
		return ans;
	}
	inline lint ask(int l,int r){
		assert(l);
		return sum(r)-sum(l-1);
	}
}
lint *num[N];
int ns=0;
inline bool ncmp(lint *a,lint *b){
	return (*a)<(*b);
}
struct Point{
	lint x,y,p;
	inline void in(){
		x=nl,y=nl,p=nl;
		num[ns++]=&x;
	}
	inline friend bool operator < (const Point &a,const Point &b){
		return a.y<b.y;
	}
}pt[N];
struct Ask{
	lint l,r,ans;
	inline void fir(){
		ans=-B::ask(l,r);
	}
	inline void sec(){
		ans+=B::ask(l,r);
	}
}ak[N];
struct Query{
	int id;
	lint y;
	inline friend bool operator < (const Query &a,const Query &b){
		return a.y<b.y;
	}
}q[N];
int main(){
	int n=ni,tot=ni,qs=0;
	for(int i=1;i<=n;i++){
		pt[i].in();
	}
	lint y1,y2;
	for(int i=1;i<=tot;i++){
		ak[i].l=nl,y1=nl,ak[i].r=nl,y2=nl;
		num[ns++]=&ak[i].l;
		num[ns++]=&ak[i].r;
		q[qs++]=(Query){-i,y1-1};
		q[qs++]=(Query){i,y2};
	}
	sort(num,num+ns,ncmp);
	lint last=-LINF;
	B::init(),B::n=0;
	for(int i=0;i<ns;i++){
		if((*num[i])!=last){
			last=*num[i];
			B::n++;
		}
		*num[i]=B::n;
	}
	sort(pt+1,pt+n+1),sort(q,q+qs);
	for(int i=0,j=1;i<qs;i++){
		for(;j<=n&&pt[j].y<=q[i].y;B::add(pt[j].x,pt[j].p),j++);
		int id=q[i].id;
		(id<0)?ak[-id].fir():ak[id].sec();
	}
	for(int i=1;i<=tot;i++){
		printf("%lld\n",ak[i].ans);
	}
}