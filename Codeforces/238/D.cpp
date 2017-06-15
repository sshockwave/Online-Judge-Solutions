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
struct State{
	int cnt[D];
	State(){
		memset(cnt,127,sizeof(cnt));
	}
	inline friend State operator - (const State &a,const State &b){
		State c;
		for(int i=0;i<D;i++){
			c.cnt[i]=a.cnt[i]-b.cnt[i];
		}
		return c;
	}
	inline friend bool operator < (const State &a,const State &b){
		for(int i=0;i<D;i++){
			if(a.cnt[i]!=b.cnt[i]){
				return a.cnt[i]<b.cnt[i];
			}
		}
		return false;
	}
	inline void print(){
		for(int i=0;i<D;i++){
			printf("%d ",cnt[i]);
		}
		putchar('\n');
	}
	inline bool vis(){
		return cnt[0]<INF;
	}
}ff[N],gg[N];
struct SegmentTree{
	typedef SegmentTree* node;
	int lend,rend,mid;
	node lson,rson;
	bool tag;
	State val;
	inline void up(){
		val=max(lson->val,rson->val);
	}
	void down(){
		assert(lend!=rend);
		if(tag){
			lson->apmin(lend,mid,val);
			rson->apmin(mid+1,rend,val);
			tag=false;
		}
	}
	void build(int l,int r){
		static node n=new SegmentTree[N*4];
		lend=l,rend=r,mid=(l+r)>>1;
		tag=false;
		if(l!=r){
			(lson=n++)->build(l,mid);
			(rson=n++)->build(mid+1,r);
		}
	}
	void apmin(int l,int r,const State &v){
		if(val<v){
			return;
		}
		if(l==lend&&r==rend){
			val=v;
			tag=true;
			return;
		}
		down();
		if(r<=mid){
			lson->apmin(l,r,v);
		}else if(l>mid){
			rson->apmin(l,r,v);
		}else{
			lson->apmin(l,mid,v);
			rson->apmin(mid+1,r,v);
		}
		up();
	}
	void cache(State put[]){
		if(lend==rend){
			put[lend]=val;
		}else{
			down();
			lson->cache(put);
			rson->cache(put);
		}
	}
}f,g;
char s[N];
int pre[N],nxt[N];
inline void del(int x){
	pre[nxt[x]]=pre[x];
	nxt[pre[x]]=nxt[x];
}
int main(){
	int n=ni,tot=ni;
	s[0]='>',scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		pre[i]=i-1,nxt[i]=i+1;
	}
	nxt[0]=1,pre[n+1]=n;
	int *pt=nxt;
	State cur;
	memset(&cur,0,sizeof(cur));
	f.build(1,n),g.build(1,n);
	for(int i=1;i<=n;i=pt[i]){
		if(i==0){
			pt=nxt;
			f.apmin(i,pt[i]-1,cur);
			continue;
		}
		if(isdigit(s[i])){
			cur.cnt[s[i]-'0']++;
			if(s[i]=='0'){
				del(i);
			}else{
				s[i]--;
			}
		}else{
			pt=s[i]=='<'?pre:nxt;
			if(s[pt[i]]=='<'||s[pt[i]]=='>'){
				del(i);
			}
		}
		if(pt==nxt){
			f.apmin(i,pt[i]-1,cur);
		}else{
			g.apmin(pt[i]+1,i,cur);
		}
	}
	f.cache(ff),g.cache(gg);
	memset(ff,0,sizeof(State));
	memset(&cur,127,sizeof(cur));
	while(tot--){
		int l=ni,r=ni;
		(min(ff[r],gg[l])-ff[l-1]).print();
	}
}