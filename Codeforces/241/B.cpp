#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
#include <vector>
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
const int N=50010,O=1000000007,D=31;
struct xorsum{
	int a[D],n;
	inline void clr(){
		memset(a,0,sizeof(a));
		n=0;
	}
	inline void operator += (int b){
		n++;
		for(int i=0;i<D;i++){
			a[i]+=(b>>i)&1;
		}
	}
	inline friend xorsum operator - (const xorsum &a,const xorsum &b){
		xorsum c;
		c.clr(),c.n=a.n-b.n;
		for(int i=0;i<D;i++){
			c.a[i]=a.a[i]-b.a[i];
		}
		return c;
	}
	inline friend int operator * (const xorsum &a,const xorsum &b){
		lint ans=0;
		for(int i=0;i<D;i++){
			ans+=((a.a[i]*(b.n-b.a[i])%O)<<i)%O;
			ans+=((b.a[i]*(a.n-a.a[i])%O)<<i)%O;
		}
		return ans%O;
	}
}_a[N];
int a[N];
namespace T{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,r;
		node lson,rson;
		int dep;
	}*rt;
	node build(int,int,int);
}
struct cros{
	T::node l,r;
	inline int cnt(){
		return (l->r-l->l+1)*(r->r-r->l+1);
	}
	inline int eval(){
		return (_a[l->r]-_a[l->l-1])*(_a[r->r]-_a[r->l-1]);
	}
	inline friend ostream & operator << (ostream & out,const cros &b){
		out<<"(("<<b.l->l<<","<<b.l->r<<",d="<<b.l->dep<<"),("<<b.r->l<<","<<b.r->r<<",d="<<b.r->dep<<"))";
		return out;
	}
	inline friend bool operator < (const cros &x,const cros &y){
		int d=max(x.l->dep,y.r->dep)+1;
		int vx=(a[x.l->l]^a[x.r->r])>>d;
		int vy=(a[y.l->l]^a[y.r->r])>>d;
		return vx<vy;
	}
	inline friend bool operator == (const cros &x,const cros &y){
		return !(x<y)&&!(y<x);
	}
};
priority_queue<cros>q;
inline void psh(T::node l,T::node r){
	if(l&&r){
		q.push((cros){l,r});
	}
}
int binsearch(int l,int r,int dep){
	for(int m;l<r;m=(l+r)>>1,((a[m]>>dep)&1)?(r=m):(l=m+1));
	return l;
}
T::node T::build(int l,int r,int dep){
	static node n=new Node[N*18];
	if(l>r){
		return NULL;
	}
	node x=n++;
	x->l=l,x->r=r,x->dep=dep;
	if(dep<0){
		x->lson=x->rson=NULL;
	}else{
		int m=binsearch(l,r+1,dep)-1;
		x->lson=build(l,m,dep-1);
		x->rson=build(m+1,r,dep-1);
		psh(x->lson,x->rson);
	}
	return x;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("friend.in","r",stdin);
	freopen("friend.out","w",stdout);
#endif
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	sort(a+1,a+n+1);
	_a[0].clr();
	for(int i=1;i<=n;i++){
		_a[i]=_a[i-1];
		_a[i]+=a[i];
	}
	T::rt=T::build(1,n,D-1);
	lint ans=0;
	while(m&&!q.empty()){
		vector<cros>vec;
		int cnt=0;
		lint sum=0;
		for(;!q.empty()&&(vec.empty()||q.top()==vec[0]);q.pop()){
			cros tmp=q.top();
			vec.push_back(tmp);
			cnt+=tmp.cnt();
			sum+=tmp.eval();
		}
		if(m>=cnt){
			m-=cnt;
			(ans+=sum)%=O;
			continue;
		}
		for(;!q.empty();q.pop());
		for(int i=0,n=vec.size();i<n;i++){
			psh(vec[i].l->lson,vec[i].r->lson);
			psh(vec[i].l->lson,vec[i].r->rson);
			psh(vec[i].l->rson,vec[i].r->lson);
			psh(vec[i].l->rson,vec[i].r->rson);
		}
	}
	printf("%d\n",(int)ans);
	return 0;
}
