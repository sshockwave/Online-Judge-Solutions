#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline bool is_letter(char c){
	return c>='a'&&c<='z';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
const int N=100010,L=300010,D=1700000;
int rank[N],start[N],end[N];
char pool[L],*s[N];
struct SegmentTree{
	#define lson(x) son[x][0]
	#define rson(x) son[x][1]
	int lend[D],rend[D],mid[D],son[D][2],sum[D],root[N],ntop;
	SegmentTree(){
		ntop=0;
		memset(root,-1,sizeof(root));
		memset(son,-1,sizeof(son));
	}
	void alter(int &x,int l,int r,int p){
		assert(l<=p&&p<=r);
		if(x==-1){
			x=ntop++;
			sum[x]=1;
			lend[x]=l,rend[x]=r,mid[x]=(l+r)>>1;
			if(l==r){
				return;
			}
		}else{
			lson(ntop)=lson(x),rson(ntop)=rson(x);
			sum[ntop]=sum[x]+1;
			x=ntop++;
		}
		assert(l!=r);
		if(p<=mid[x]){
			alter(lson(x),l,mid[x],p);
		}else{
			alter(rson(x),mid[x]+1,r,p);
		}
	}
	int ask_sum(int x,int l,int r){
		assert(l<=r);
		if(x==-1){
			return 0;
		}
		assert(lend[x]<=l&&r<=rend[x]);
		if(lend[x]==l&&rend[x]==r){
			return sum[x];
		}
		if(r<=mid[x]){
			return ask_sum(lson(x),l,r);
		}
		if(l>mid[x]){
			return ask_sum(rson(x),l,r);
		}
		return ask_sum(lson(x),l,mid[x])+ask_sum(rson(x),mid[x]+1,r);
	}
}seg;
struct Trie{
	int son[L][26],start[L],end[L],ntop,to[N],bro[N],head[L],etop,dfn;
	Trie(){
		memset(head,-1,sizeof(head));
		memset(son,-1,sizeof(son));
		etop=0,dfn=ntop=1;
	}
	inline void add_edge(int u,int v){
		to[etop]=v;
		bro[etop]=head[u];
		head[u]=etop++;
	}
	void insert(int x,char *s,int id){//root=0
		if((*s)){
			int &c=son[x][(*s)-'a'];
			if(c==-1){
				c=ntop++;
			}
			insert(c,s++,id);
		}else{
			add_edge(x,id);
		}
	}
	void dfs(int x){
		int st=dfn;
		for(int i=head[x];~i;i=bro[i]){
			rank[to[i]]=dfn++;
		}
		for(int i=0;i<26;i++){
			if(~son[x][i]){
				dfs(son[x][i]);
			}
		}
		for(int i=head[x];~i;i=bro[i]){
			start[to[i]]=st,end[to[i]]=dfn;
		}
	}
}trie;
inline int work(int i,int k){
	if(end[i]-start[i]<k){
		return -1;
	}
	int l=1,r=n,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(seg.ask_sum(seg.root[mid],start[i],end[i]-1)<k){
			l=mid+1;
		}else{
			r=mid;
		}
	}
	return l;
}
int main(){
	int n=ni();
	char c;
	memset(pool,0,sizeof(pool));
	for(int i=1,p=0;i<=n;i++){
		s[i]=pool+p;
		while(!is_letter(c=getchar()));
		while(pool[p++]=c,is_letter(c=getchar()));
		for(char *j=s[i],*k=pool+(p++)-1;j<k;j++,k--){
			swap(*j,*k);
		}
	}
	for(int i=n;i>0;i--){
		trie.insert(0,s[i],i);
	}
	trie.dfs(0);
	for(int i=1;i<=n;i++){
		seg.alter(seg.root[i],1,n,rank[i]);
	}
	for(int i=1,k;i<=n;i++){
		printf("%d\n",work(i,ni()));
	}
}
