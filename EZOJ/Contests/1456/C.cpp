#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=310,D=10010;
const int logN=64;
namespace num_disc{
	const int N=::N*4;
	int *num[N],n;
	inline void init(){
		n=0;
	}
	inline void psh(int &a){
		num[++n]=&a;
	}
	inline bool ncmp(int *a,int *b){
		return *a<*b;
	}
	inline void main(){
		sort(num+1,num+n+1,ncmp);
		int v=-1,j=-1;
		for(int i=1;i<=n;i++){
			*num[i]=v!=*num[i]?v=*num[i],++j:j;
		}
	}
}
struct pii{
	int a,b,c,d;
}item[N];
struct LB{
	ull a[logN];
	inline void init(){
		mset(a,0,logN);
	}
	inline bool ins(ull x){
		for(int i=logN-1;i>=0&&x;i--){
			if(((x>>i)&1)==0)continue;
			if(a[i]){
				x^=a[i];
			}else{
				a[i]=x;
				return true;
			}
		}
		return false;
	}
}lb[N];
int ans;
ull bitmp[D];
void dfs(int x,int cnt){
	if(cnt-x>ans)return;
	if(x==0)return ans=cnt,void();
	const pii &cur=item[x];
	lb[x-1]=lb[x];
	int icnt=0;
	icnt+=lb[x-1].ins(bitmp[cur.a]^bitmp[cur.b]);
	icnt+=lb[x-1].ins(bitmp[cur.c]^bitmp[cur.d]);
	if(icnt==0)return dfs(x-1,cnt+icnt-1);
	dfs(x-1,cnt+icnt-1);
	lb[x-1]=lb[x];
	dfs(x-1,cnt);
}
inline int Main(){
	const int n=ni;
	num_disc::init();
	for(int i=1;i<=n;i++){
		item[i]=(pii){ni,ni,ni,ni};
		num_disc::psh(item[i].a);
		num_disc::psh(item[i].b);
		num_disc::psh(item[i].c);
		num_disc::psh(item[i].d);
	}
	num_disc::main();
	lb[n].init();
	ans=n;
	dfs(n,n);
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("coin.in","r",stdin);
	freopen("coin.out","w",stdout);
#endif
	for(int i=0;i<64;i++){
		bitmp[i]=1ull<<i;
	}
	for(int tot=ni;tot--;printf("%d\n",Main()*2));
	return 0;
}
