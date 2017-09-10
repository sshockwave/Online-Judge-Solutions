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
const int N=100010,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int mul(const int &a,const int &b){
	return a*b%MOD;
}
struct Mat{
	int a[2][2];
	inline friend Mat operator + (const Mat &a,const Mat &b){
		Mat c;
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				c.a[i][j]=add(a.a[i][j],b.a[i][j]);
			}
		}
		return c;
	}
	inline friend Mat operator * (const Mat &a,const Mat &b){
		Mat c;
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				c.a[i][j]=add(mul(a.a[i][0],b.a[0][j]),mul(a.a[i][1],b.a[1][j]));
			}
		}
		return c;
	}
	inline void operator ^= (int n){
		static Mat tmp;
		if(n==0){
			tmp=*this;
			*this=(Mat){1,0,0,1};
			return;
		}
		*this^=n>>1;
		*this=(*this)*(*this);
		if(n&1){
			*this=(*this)*tmp;
		}
	}
}id=(Mat){1,0,0,1},trans=(Mat){1,1,1,0};
namespace seg{
	struct Node{
		int lend,rend,mid;
		Mat sum,offset;
		bool tag;
		Node *lson,*rson;
	};
	typedef Node* node;
	inline void down(node x){
		assert(x->lend!=x->rend);
		if(x->tag){
			x->lson->tag=true,x->lson->offset=x->offset*x->lson->offset;
			x->rson->tag=true,x->rson->offset=x->offset*x->rson->offset;
			x->tag=false,x->offset=id;
		}
	}
	inline void up(node x){
		assert(x->lend!=x->rend);
		assert(!x->tag);
		x->sum=x->lson->sum+x->rson->sum;
	}
	node build(int l,int r){
		static node n=new Node[N*2];
		node x=n++;
		x->lend=l,x->rend=r,x->mid=(l+r)>>1;
		x->offset=id,x->tag=false;
		if(l==r){
			x->sum=trans;
			x->sum^=ni;
		}else{
			x->lson=build(l,x->mid);
			x->rson=build(x->mid+1,r);
			up(x);
		}
		return x;
	}
	int ql,qr;
	void mul(node x,const Mat &m){
		if(ql<=x->lend&&x->rend<=qr){
			x->tag=true;
			x->offset=m*x->offset;
			x->sum=m*x->sum;
			return;
		}
		down(x);
		if(ql<=x->mid){
			mul(x->lson,m);
		}
		if(qr>x->mid){
			mul(x->rson,m);
		}
		up(x);
	}
	Mat ask(node x){
		if(ql<=x->lend&&x->rend<=qr){
			return x->sum;
		}
		Mat ans=(Mat){0,0,0,0};
		down(x);
		if(ql<=x->mid){
			ans=ans+ask(x->lson);
		}
		if(qr>x->mid){
			ans=ans+ask(x->rson);
		}
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
#endif
	int n=ni,tot=ni;
	seg::node root=seg::build(1,n);
	while(tot--){
		int op=ni;
		seg::ql=ni,seg::qr=ni;
		if(op==1){
			Mat tmp=trans;
			tmp^=ni;
			seg::mul(root,tmp);
		}else{
			printf("%d\n",seg::ask(root).a[0][1]);
		}
	}
	return 0;
}
