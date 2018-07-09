#include "hidden.hpp"
#include <iostream>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#define cout cerr
using namespace std;
typedef vector<int>vi;
typedef long long lint;
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,sizeof(a[0])*n);}
const int N=110;
int n,ZERO,ONE,cnt0,cnt1,mxlen;
inline void psh(vi &vec,int v,int tot){
	vec.reserve(vec.size()+tot);
	for(;tot--;vec.push_back(v));
}
namespace Q{
	inline bool ask(const vector<int>&v){
		return is_subsequence(v);
	}
	inline bool ask(int l,int m,int r){
		assert(l+m+r<=mxlen);
		vi vec;
		psh(vec,ONE,l);
		psh(vec,ZERO,m);
		psh(vec,ONE,r);
		return ask(vec);
	}
}
struct Val{
	int l,r;
}f[N][N];
inline void getone(){
	for(int i=1;i<=mxlen;i++){
		vi vec;
		psh(vec,1,i);
		if(!Q::ask(vec)){
			ZERO=0,ONE=1,cnt1=i-1,cnt0=n-cnt1;
			return;
		}
	}
	for(int i=1;i<=mxlen;i++){
		vi vec;
		psh(vec,0,i);
		if(!Q::ask(vec)){
			ZERO=1,ONE=0,cnt1=i-1,cnt0=n-cnt1;
			return;
		}
	}
	assert(false);
}
inline void work(){
	for(int i=0;i<=cnt1;i++){
		for(int j=i;j<=cnt1;j++){
			int &l=f[i][j].l,&r=f[i][j].r;
			l=0,r=cnt0;
			const int mxq=mxlen-(i+(cnt1-j));
			for(;l<r&&l<mxq;){
				const int m=min(((l+r)>>1)+1,mxq);
				assert(l<m&&m<=r);
				if(Q::ask(i,m,cnt1-j)){
					l=m;
				}else{
					r=m-1;
				}
			}
		}
	}
	f[0][cnt1]=(Val){cnt0,cnt0};
}
inline void floyd(){
	for(int len=2;len<=cnt1+1;len++){
		for(int l=0;l+len-1<=cnt1;l++){
			const int r=l+len-1;
			for(int i=l;i<r;i++){
				apmax(f[l][r].l,f[l][i].l+f[i+1][r].l);
				apmin(f[l][r].r,f[l][i].r+f[i+1][r].r);
			}
		}
	}
	for(int len=cnt1+1;len>=2;len--){
		for(int l=0;l+len-1<=cnt1;l++){
			const int r=l+len-1;
			const Val &v=f[l][r];
			assert(v.l<=v.r);
			for(int i=l;i<r;i++){
				apmin(f[l][i].r,v.r-f[i+1][r].l);
				apmin(f[i+1][r].r,v.r-f[l][i].l);
				apmax(f[l][i].l,v.l-f[i+1][r].r);
				apmax(f[i+1][r].l,v.l-f[l][i].r);
			}
		}
	}
}
vector<int>guess(int _n){
	n=_n,mxlen=n/2+1;
	getone();
	work();
	floyd();
	floyd();//it wouldn't hurt
	vi ans;
	for(int i=0;i<=cnt1;i++){
		assert(f[i][i].l==f[i][i].r);
		psh(ans,ZERO,f[i][i].l);
		if(i<cnt1){
			ans.push_back(ONE);
		}
	}
	return ans;
}
