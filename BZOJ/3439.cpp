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
int start[N],last[N],n;
char pool[L],*s[N];
struct SegmentTree{
	#define lson(x) son[x][0]
	#define rson(x) son[x][1]
	int lend[D],rend[D],mid[D],son[D][2],sum[D],root[N],ntop;
	SegmentTree(){
		sum[0]=root[0]=0;
		ntop=1;
		memset(son,0,sizeof(son));
	}
	void alter(int &x,int l,int r,int p){
		assert(l<=p&&p<=r);
		lson(ntop)=lson(x),rson(ntop)=rson(x);
		sum[ntop]=sum[x]+1;
		x=ntop++;
		lend[x]=l,rend[x]=r,mid[x]=(l+r)>>1;
		if(l==r){
			return;
		}
		if(p<=mid[x]){
			alter(lson(x),l,mid[x],p);
		}else{
			alter(rson(x),mid[x]+1,r,p);
		}
	}
	int query(int x1,int x2,int k){
		assert(x2);
		assert(k<=rend[x2]-lend[x2]+1);
		if(lend[x2]==rend[x2]){
			assert(k==1);
			return lend[x2];
		}
		int diff=sum[lson(x2)]-sum[lson(x1)];
		assert(diff>=0);
		if(diff>=k){
			return query(lson(x1),lson(x2),k);
		}else{
			return query(rson(x1),rson(x2),k-diff);
		}
	}
}seg;
struct Trie{
	int son[L][26],ntop,to[N],bro[N],head[L],etop,dfn;
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
			insert(c,s+1,id);
		}else{
			add_edge(x,id);
		}
	}
	void dfs(int x){
		int st=dfn;
		for(int i=head[x];~i;i=bro[i]){
			seg.alter(seg.root[dfn]=seg.root[dfn-1],1,n,to[i]);
			dfn++;
		}
		for(int i=0;i<26;i++){
			if(~son[x][i]){
				dfs(son[x][i]);
			}
		}
		for(int i=head[x];~i;i=bro[i]){
			start[to[i]]=st,last[to[i]]=dfn;
		}
	}
}trie;
inline int work(int i,int k){
	if(k<=0||last[i]-start[i]<k){
		return -1;
	}
	return seg.query(seg.root[start[i]-1],seg.root[last[i]-1],k);
}
int main(){
	n=ni();
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
		printf("%d\n",work(i,ni()));
	}
}
