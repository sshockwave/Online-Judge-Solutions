#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=100010,D=10,INF=0x7f7f7f7f;
char s[N];
int pre[N],nxt[N];
inline void del(int x){
	pre[nxt[x]]=pre[x];
	nxt[pre[x]]=nxt[x];
}
struct Num{
	int cnt[D];
	Num(){
		memset(cnt,0,sizeof(cnt));
	}
	inline void out(){
		for(int i=0;i<D;i++){
			printf("%d ",cnt[i]);
		}
		putchar('\n');
	}
	inline friend Num operator - (const Num &a,const Num &b){
		Num c;
		for(int i=0;i<D;i++){
			c.cnt[i]=a.cnt[i]-b.cnt[i];
		}
		return c;
	}
}sum[N*D];
int pos[N*D],f[N],g[N],h[N];
struct SegmentTree{
	typedef SegmentTree *node;
	node lson,rson;
	int lend,rend,mid,mn;
	void build(int l,int r){
		static node n=new SegmentTree[N*D*2];
		lend=l,rend=r,mid=(l+r)>>1;
		if(l==r){
			mn=pos[l];
		}else{
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
			mn=min(lson->mn,rson->mn);
		}
	}
	inline int ask(int l,int r,int v){//first time < v
		assert(rend==r);
		if(mn>=v||lend==rend){
			return lend;
		}
		if(l<=mid){
			int p=lson->ask(l,mid,v);
			return pos[p]<v?p:rson->ask(mid+1,r,v);
		}
		return rson->ask(l,r,v);
	}
}seg;
int main(){
	int n=ni,tot=ni;
	s[0]='>',scanf("%s",s+1);
	nxt[0]=1,pre[n+1]=n;
	for(int i=1;i<=n;i++){
		nxt[i]=i+1;
		pre[i]=i-1;
	}
	memset(pos,0,sizeof(pos));
	int tim=1;
	for(int i=1,j=1,*pt=nxt;pos[j]=i,i<=n;i=pt[i],j++){
		tim=j;
		sum[j]=sum[j-1];
		if(isdigit(s[i])){
			sum[j].cnt[s[i]-'0']++;
			if(s[i]=='0'){
				del(i);
			}else{
				s[i]--;
			}
		}else{
			pt=s[i]=='>'?nxt:pre;
			if(i&&!isdigit(s[pt[i]])){
				del(i);
			}
		}
	}
	seg.build(1,tim+2);
	for(int i=1,j=1,k=1;i<=n;i++){//j->f,k->h
		for(;pos[j]<i;j++);
		assert(pos[j]==i);
		f[i]=j;
		g[i]=seg.ask(j,tim+2,i)-1;
		apmax(k,j+1);
		for(;pos[k]<=i;k++);
		h[i]=k-1;
	}
	while(tot--){
		int l=ni,r=ni;
		(sum[min(g[l],h[r])]-sum[f[l]-1]).out();
	}
}