#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef vector<int>vi;
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
int fa[N],dep[N],hei[N];
vi son[N];
int cnt[N];
struct hei_cmp{
	inline bool operator () (const int &a,const int &b){
		return hei[a]-dep[a]<hei[b]-dep[b];
	}
};
int main(){
#ifndef ONLINE_JUDGE
	freopen("todotree.in","r",stdin);
	freopen("todotree.out","w",stdout);
#endif
	const int n=ni,m=ni;
	mset(cnt+1,0,n);
	dep[0]=0;
	for(int i=1;i<=n;i++){
		fa[i]=i!=1?ni:0;
		dep[i]=dep[fa[i]]+1;
		hei[i]=dep[i];
		++cnt[dep[i]];
		son[fa[i]].push_back(i);
	}
	for(int i=n;i>=1;i--){
		apmax(hei[fa[i]],hei[i]);
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
	priority_queue<int,vi,hei_cmp>q;
	q.push(1);
	for(int i=1;i<=ans;i++){
		printf("%d ",min<int>(m,q.size()));
		vi nxt;
		for(int t=1;t<=m&&!q.empty();t++){
			const int x=q.top();
			q.pop();
			printf("%d ",x);
			for(vi::iterator it=son[x].begin(),ti=son[x].end();it!=ti;++it){
				nxt.push_back(*it);
			}
		}
		for(vi::iterator it=nxt.begin(),ti=nxt.end();it!=ti;++it){
			q.push(*it);
		}
		putchar('\n');
	}
	assert(q.empty());
	return 0;
}
