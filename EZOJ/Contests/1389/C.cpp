#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include "lost.h"
#include <vector>
using namespace std;
typedef long long lint;
#define cout cerr
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=1410;
int place[N];
inline void pshans(int u,int v){
	assert(u!=v);
	if(u>v){
		swap(u,v);
	}
	Answer(u,v);
}
namespace T1{
	inline void Main(int n){
		memset(place,0,n<<2);
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				place[i]=place[j]=1;
				if(Ask(i,j,place)){
					Answer(i,j);
				}
				place[i]=place[j]=0;
			}
		}
	}
}
namespace T3{
	int tag[N],tim=0;
	int que[N];
	int fa[N];
	int n;
	inline void clr(){
		memset(place,0,n<<2);
	}
	inline void mark(int l,int r){
		for(int i=l;i<=r;i++){
			place[que[i]]=1;
		}
	}
	inline void Main(int _n){
		n=_n;
		int qh=0,qt=0;
		que[qt++]=0;
		memset(fa,-1,sizeof(fa));
		fa[0]=0;
		while(qt<n){
			int oldqt=qt;
			for(int i=0;i<n;i++){
				if(fa[i]==-1){
					clr();
					mark(0,oldqt-1);
					place[i]=1;
					if(Ask(0,i,place)){
						que[qt++]=i;
					}
				}
			}
			if(oldqt==qt){
				assert(qt==n);
			}
			for(int i=oldqt;i<qt;i++){
				int x=que[i];
				int l=qh,r=oldqt-1;
				while(l<r){
					int m=(l+r)>>1;
					clr();
					mark(0,qh-1);
					mark(l,m);
					place[x]=1;
					bool ans=Ask(0,x,place);
					if(Ask(0,x,place)){
						r=m;
					}else{
						l=m+1;
					}
				}
				fa[x]=que[l];
			}
			qh=oldqt;
		}
		for(int i=1;i<n;i++){
			pshans(i,fa[i]);
		}
	}
}
void Detect(int T,int N){
	if(T==1||T==5)return T1::Main(N);
	return T3::Main(N);
}
