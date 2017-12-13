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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=60,INF=0x7f7f7f7f;
struct BIT{
	int c[N],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		int ans=0;
		for(;x;ans+=c[x],x^=x&-x);
		return ans;
	}
	inline int ask(int l,int r){
		return sum(r)-sum(l-1);
	}
}B1,B2;
struct pii{
	int a,b;
	inline friend bool operator < (const pii &a,const pii &b){
		return a.a!=b.a?a.a<b.a:a.b<b.b;
	}
}intv[N];
int ans,its;
void dfs(int x,int cur){
	if(cur>ans)return;
	if(x>its)return ans=cur,void();
	int l=intv[x].a,r=intv[x].b;
	B1.add(r,1);
	dfs(x+1,cur+min(B1.ask(l+1,r-1),B1.ask(r+1,B1.n)+B2.ask(l+1,B2.n)));
	B1.add(r,-1);
	B2.add(r,1);
	dfs(x+1,cur+min(B2.ask(l+1,r-1),B2.ask(r+1,B2.n)+B1.ask(l+1,B1.n)));
	B2.add(r,-1);
}
int last[N];
inline int Main(){
	int n=ni;
	memset(last+1,0,n<<2);
	B1.init(n),B2.init(n);
	its=0;
	for(int i=1;i<=n;i++){
		int cur=ni;
		if(last[cur]){
			intv[++its]=(pii){last[cur],i};
		}else{
			last[cur]=i;
		}
	}
	if(its==0)return 0;
	sort(intv+1,intv+its+1);
	B1.add(intv[1].b,1);
	ans=INF;
	dfs(2,0);
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("subway.in","r",stdin);
	freopen("subway.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
