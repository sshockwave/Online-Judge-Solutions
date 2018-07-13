#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <set>
using namespace std;
typedef set<int>si;
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
const int N=100010;
int fa[N];
int cnt[N];
int dep[N];
int pos[N];
int nx[N];
int m;
int soncnt[N];
struct soncnt_cmp{
	inline bool operator () (int a,int b){
		return soncnt[a]!=soncnt[b]?soncnt[a]<soncnt[b]:a<b;
	}
};
set<int,soncnt_cmp>lst[N];
int dj_nx(int x){
	if(lst[x].size()==(size_t)m){
		apmax(nx[x],x+1);
	}
	return nx[x]!=x?nx[x]=dj_nx(nx[x]):x;
}
inline void alt_son(int x,int v){
	if(v==0)return;
	if(x==0)return;
	lst[pos[x]].erase(x);
	soncnt[x]+=v;
	lst[pos[x]].insert(x);
}
void del(int x){
	assert(x);
	if(x==0)return;
	if(fa[x]&&pos[fa[x]]==pos[x]-1){
		alt_son(fa[x],-1);
	}
	lst[pos[x]].erase(x);
}
void ins_at(int x,int _i){
	//when you enter this function,
	//fa didn't count x
	pos[x]=_i;
	assert(dep[x]<=pos[x]);
	assert(pos[fa[x]]<=pos[x]);
	assert(lst[pos[x]].size()<(size_t)m);
	if(fa[x]&&pos[fa[x]]==pos[x]){
		assert(lst[pos[x]-1].size()==(size_t)m);
		const int y=*lst[pos[x]-1].begin();
		assert(soncnt[y]==0);
		del(y);
		del(fa[x]);
		ins_at(y,pos[x]);
		ins_at(fa[x],pos[x]-1);
	}
	assert(lst[pos[x]].size()<(size_t)m);
	assert(pos[fa[x]]<pos[x]);
	lst[pos[x]].insert(x);
	if(fa[x]&&pos[fa[x]]==pos[x]-1){
		alt_son(fa[x],1);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("todotree.in","r",stdin);
	freopen("todotree.out","w",stdout);
#endif
	const int n=ni;
	m=ni;
	mset(cnt+1,0,n);
	dep[0]=0;
	++cnt[dep[1]=dep[fa[1]=0]+1];
	for(int i=2;i<=n;i++){
		++cnt[dep[i]=dep[fa[i]=ni]+1];
	}
	int ans=0;
	int sum=0;
	for(int i=n;i>=1;i--){
		sum+=cnt[i];
		if(cnt[i]){
			apmax(ans,i+(sum+m-1)/m-1);
		}
	}
	printf("%d\n",ans);
	for(int i=1;i<=ans;i++){
		nx[i]=i;
	}
	ins_at(1,1);
	mset(soncnt+1,0,n);
	for(int x=2;x<=n;x++){
		ins_at(x,dj_nx(max(pos[fa[x]],dep[x])));
		/*for(int i=2;i<=x;i++){
			//cout
			assert(pos[fa[i]]<pos[i]);
		}*/
	}
	for(int i=1;i<=ans;i++){
		printf("%d ",int(lst[i].size()));
		for(si::iterator it=lst[i].begin(),ti=lst[i].end();it!=ti;++it){
			printf("%d ",*it);
		}
		putchar('\n');
	}
	return 0;
}
