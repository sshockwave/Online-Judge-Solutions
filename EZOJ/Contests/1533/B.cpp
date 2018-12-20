#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef long double db;
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=50010;
struct Pt{
	lint x,y;
	int idx;
	inline friend bool operator < (const Pt &a,const Pt &b){
		return a.x!=b.x?a.x<b.x:a.y<b.y;
	}
	inline friend Pt operator - (const Pt &a,const Pt &b){
		return (Pt){a.x-b.x,a.y-b.y,0};
	}
	inline friend db crs(const Pt &a,const Pt &b){
		return (db)a.x*b.y-(db)a.y*b.x;
	}
	inline friend bool turn_right(const Pt &a,const Pt &b,const Pt &c){
		return crs(b-a,c-a)<0;
	}
}pt1[N],pt2[N];
int nx1[N],nx2[N];
namespace hull{
	Pt stk1[N],stk2[N];
	int pos[N];
	inline void main(const Pt pt[],int nx[],int n){
		for(int i=1;i<=n;i++){
			pos[pt[i].idx]=i;
		}
		int ss1=0;
		for(int i=1;i<=n;i++){
			for(;ss1>=2&&!turn_right(stk1[ss1-2],stk1[ss1-1],pt[i]);ss1--);
			stk1[ss1++]=pt[i];
		}
		int ss2=0;
		for(int i=n;i>=1;i--){
			for(;ss2>=2&&!turn_right(stk2[ss2-2],stk2[ss2-1],pt[i]);ss2--);
			stk2[ss2++]=pt[i];
		}
		for(int i=1;i<ss1;i++){
			nx[pos[stk1[i-1].idx]]=pos[stk1[i].idx];
		}
		assert(stk1[ss1-1].idx==stk2[0].idx);
		for(int i=1;i<ss2;i++){
			nx[pos[stk2[i-1].idx]]=pos[stk2[i].idx];
		}
		assert(stk2[ss2-1].idx==stk1[0].idx);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("particles.in","r",stdin);
	freopen("particles.out","w",stdout);
#endif
	int n=ni;
	int tmplen=ni,tot=ni;
	for(int i=1;i<=n;i++){
		lint t=ni,v=ni;
		pt1[i]=(Pt){v,v*t+tmplen,i};
	}
	for(int i=1;i<=n;i++){
		lint t=ni,v=ni;
		pt2[i]=(Pt){-v,-v*t,i};
	}
	sort(pt1+1,pt1+n+1);
	sort(pt2+1,pt2+n+1);
	for(;tot--;n--){
		int p=n,q=1;
		hull::main(pt1,nx1,n);
		hull::main(pt2,nx2,n);
		for(;;){
			if(crs(pt1[p]-pt2[q],pt1[nx1[p]]-pt2[q])<=0){
				p=nx1[p];
			}else if(crs(pt1[p]-pt2[q],pt1[p]-pt2[nx2[q]])<=0){
				q=nx2[q];
			}else break;
		}
		printf("%d %d\n",pt1[p].idx,pt2[q].idx);
		for(;p<n;p++){
			pt1[p]=pt1[p+1];
		}
		for(;q<n;q++){
			pt2[q]=pt2[q+1];
		}
	}
	return 0;
}
