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
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline int apmin(int &a,const int &b){
	if(a>b){
		a=b;
	}
}
inline int apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=50010,D=2;
int dim,a,b,c;
inline bool check(int x,int y){
	return (lint)a*x+(lint)b*y<c;
}
struct Node{
	int x[D],val,lson,rson,mn[D],mx[D];
	lint sum;
	inline friend bool operator < (const Node &a,const Node &b){
		return a.x[dim]<b.x[dim];
	}
	inline bool cover(){
		return check(mn[0],mn[1])&&check(mn[0],mx[1])&&check(mx[0],mn[1])&&check(mx[0],mx[1]);
	}
}pt[N];
struct KDTree{
	inline void up(int x){
		int tx;
		memcpy(pt[x].mn,pt[x].x,D<<2);
		memcpy(pt[x].mx,pt[x].x,D<<2);
		pt[x].sum=pt[x].val;
		if(tx=pt[x].lson){
			pt[x].sum+=pt[tx].sum;
			for(int i=0;i<D;i++){
				apmin(pt[x].mn[i],pt[tx].mn[i]);
				apmax(pt[x].mx[i],pt[tx].mx[i]);
			}
		}
		if(tx=pt[x].rson){
			pt[x].sum+=pt[tx].sum;
			for(int i=0;i<D;i++){
				apmin(pt[x].mn[i],pt[tx].mn[i]);
				apmax(pt[x].mx[i],pt[tx].mx[i]);
			}
		}
	}
	int build(int l,int r){
		if(l>r){
			return 0;
		}
		int x=(l+r)>>1;
		nth_element(pt+l,pt+x,pt+r);
		dim=dim^1;
		pt[x].lson=build(l,x-1);
		pt[x].rson=build(x+1,r);
		up(x);
		return x;
	}
	lint ask(int x){
		if(x==0){
			return 0;
		}
		if(pt[x].cover()){
			return pt[x].sum;
		}
		return ask(pt[x].lson)+ask(pt[x].rson)+(check(pt[x].x[0],pt[x].x[1])?pt[x].val:0);
	}
}kd;
int main(){
	memset(pt,0,sizeof(pt));
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Node){ni,ni,ni};
	}
	dim=0;
	int root=kd.build(1,n);
	while(tot--){
		a=ni,b=ni,c=ni;
		printf("%lld\n",kd.ask(root));
	}
}
