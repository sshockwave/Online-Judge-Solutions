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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int INF=0x7f7f7f7f;
struct Result{
	int f[4];
};
namespace T{
	const int N=1010*33;
	int son[N][2][2],n=0,rt=0;
	int ch[N];
	inline void init(){
		memset(son,0,sizeof(son));
		memset(ch,-1,sizeof(ch));
	}
	inline int nn(){
		return ++n;
	}
	inline void ins(int x,int y,int k,int c){
		int *nd=&rt;
		for(int i=k-1;i>=0;i--){
			if(nd[0]==0){
				*nd=nn();
			}
			nd=&son[*nd][(x>>i)&1][(y>>i)&1];
		}
		if(nd[0]==0){
			*nd=nn();
		}
		ch[*nd]=c;
	}
	Result solve(const int x){
		Result ans=(Result){0,0,0,0};
		if(x==0)return ans;
		if(ch[x]!=-1){
			for(int i=0;i<3;i++){
				if(ch[x]!=i){
					ans.f[i]=1;
				}
			}
			return ans;
		}
		Result rs[4];
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				const int t=(i<<1)|j;
				rs[t]=solve(son[x][i][j]);
				for(int k=0;k<3;k++){
					ans.f[k]+=rs[t].f[k];
				}
			}
		}
		ans.f[3]=INF;
		int perm[4]={0,1,2,3};
		do{
			int cur=0;
			for(int i=0;i<4;i++){
				cur+=rs[i].f[perm[i]];
			}
			apmin(ans.f[3],cur);
		}while(next_permutation(perm,perm+4));
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	T::init();
	const int k=ni;
	for(int tot=ni;tot--;){
		const int x=ni,y=ni;
		char c;
		while(!isalpha(c=getchar()));
		T::ins(x-1,y-1,k,c=='J'?0:c=='O'?1:2);
	}
	printf("%d\n",T::solve(T::rt).f[3]);
	return 0;
}
