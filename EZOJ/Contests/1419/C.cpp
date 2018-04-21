#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
#include <set>
#include <queue>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=400010,INF=0x7f7f7f7f;
int a[N],rt;
struct Block{
	priority_queue<int>val;
	vector<int>tag;
	int l,r;
	inline void build(){
		val=priority_queue<int>(a+l,a+r+1);
	}
	inline int puttag(int v){
		tag.push_back(-v);
		val.push(v);
		v=val.top();
		val.pop();
		return v;
	}
	inline void upd(){
		if(tag.empty())return;
		priority_queue<int>tag(this->tag.begin(),this->tag.end());
		this->tag.clear();
		for(int i=l;i<=r;i++){
			tag.push(-a[i]);
			a[i]=-tag.top();
			tag.pop();
		}
	}
}blk[N];
inline int work(int l,int r,int v){
	int bl=(l-1)/rt+1;
	int br=(r-1)/rt+1;
	assert(blk[bl].l<=l&&l<=blk[bl].r);
	assert(blk[br].l<=r&&r<=blk[br].r);
	if(bl==br){
		blk[bl].upd();
		for(int i=l;i<=r;i++){
			if(a[i]>v){
				swap(a[i],v);
			}
		}
		blk[bl].build();
		return v;
	}
	if(blk[bl].l<l){
		blk[bl].upd();
		for(int i=l;i<=blk[bl].r;i++){
			if(a[i]>v){
				swap(a[i],v);
			}
		}
		blk[bl].build();
	}else{
		v=blk[bl].puttag(v);
	}
	for(int i=bl+1;i<br;i++){
		v=blk[i].puttag(v);
	}
	if(r<blk[br].r){
		blk[br].upd();
		for(int i=blk[br].l;i<=r;i++){
			if(a[i]>v){
				swap(a[i],v);
			}
		}
		blk[br].build();
	}else{
		v=blk[br].puttag(v);
	}
	return v;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("sushi.in","r",stdin);
	freopen("sushi.out","w",stdout);
#endif
	int n=ni,q=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	rt=max((int)(sqrt(n)),2);
	int bs=0;
	for(int i=0;i*rt+1<=n;i++){
		bs++;
		blk[bs].l=i*rt+1;
		blk[bs].r=min((i+1)*rt,n);
		blk[bs].build();
	}
	for(int i=1;i<=q;i++){
		int s=ni,t=ni,v=ni;
		if(s<=t){
			v=work(s,t,v);
		}else{
			v=work(1,t,work(s,n,v));
		}
		printf("%d\n",v);
		if(i%1000==0){
			cout<<i<<endl;
		}
	}
	return 0;
}
