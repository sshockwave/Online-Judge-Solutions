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
	return (lint)a*b%MOD;
}
struct Mat{
	const static int N=3;
	int a[N][N];
	inline friend Mat operator * (const Mat &a,const Mat &b){
		Mat c;
		for(int i=0;i<2;i++){
			c.a[i][0]=add(mul(a.a[i][0],b.a[0][0]),mul(a.a[i][1],b.a[1][0]));
			c.a[i][1]=add(mul(a.a[i][0],b.a[0][1]),mul(a.a[i][1],b.a[1][1]));
			c.a[i][2]=0;
		}
		for(int j=0;j<3;j++){
			lint sum=0;
			for(int k=0;k<3;k++){
				sum+=mul(a.a[2][k],b.a[k][j]);
			}
			c.a[2][j]=sum%MOD;
		}
		return c;
	}
}idt[2]={(Mat){1,0,0,1,1,0,1,0,1},(Mat){1,1,0,0,1,0,0,1,1}};
char s[N];
namespace seg{
	struct Node;
	typedef Node* node;
	struct Node{
		int l,m,r;
		node lson,rson;
		Mat pol[2],*maj,*bak;
		bool tag;
		inline void rev(){
			tag=!tag;
			swap(maj,bak);
		}
		inline void down(){
			if(tag){
				lson->rev();
				rson->rev();
				tag=false;
			}
		}
		inline void up(){
			*maj=*(rson->maj)**(lson->maj);
			*bak=*(rson->bak)**(lson->bak);
		}
	}*rt;
	node build(int l,int r){
		static node n=new Node[N<<1];
		node x=n++;
		x->l=l,x->m=(l+r)>>1,x->r=r;
		x->tag=false;
		if(l==r){
			x->pol[0]=idt[0],x->pol[1]=idt[1];
			x->maj=x->pol+(s[l]=='1');
			x->bak=x->pol+(s[l]!='1');
		}else{
			x->lson=build(l,x->m);
			x->rson=build(x->m+1,r);
			x->maj=x->pol,x->bak=x->pol+1;
			x->up();
		}
		return x;
	}
	void flip(node x,int l,int r){
		if(x->l==l&&x->r==r){
			x->rev();
			return;
		}
		x->down();
		if(r<=x->m){
			flip(x->lson,l,r);
		}else if(l>x->m){
			flip(x->rson,l,r);
		}else{
			flip(x->lson,l,x->m);
			flip(x->rson,x->m+1,r);
		}
		x->up();
	}
	Mat ask(node x,int l,int r){
		if(x->l==l&&x->r==r){
			return *(x->maj);
		}
		x->down();
		if(r<=x->m){
			return ask(x->lson,l,r);
		}
		if(l>x->m){
			return ask(x->rson,l,r);
		}
		return ask(x->rson,x->m+1,r)*ask(x->lson,l,x->m);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("seq.in","r",stdin);
	freopen("seq.out","w",stdout);
#endif
	int n=ni,tot=ni;
	scanf("%s",s+1);
	seg::rt=seg::build(1,n);
	while(tot--){
		int t=ni,l=ni,r=ni;
		if(t==1){
			seg::flip(seg::rt,l,r);
		}else{
			Mat ans=seg::ask(seg::rt,l,r);
			printf("%d\n",add(ans.a[2][0],ans.a[2][1]));
		}
	}
	return 0;
}
