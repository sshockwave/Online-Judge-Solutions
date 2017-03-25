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
const int N=100010,L=300010,D=2000000;
int start[N],last[N],n;
char s[L];
struct SegmentTree{
	#define lson(x) son[x][0]
	#define rson(x) son[x][1]
	int son[D][2],sum[D],root[N],ntop;
	SegmentTree(){
		sum[0]=root[0]=0;
		ntop=1;
		memset(son,0,sizeof(son));
	}
	int alter(int org,int l,int r,int p){
		assert(l<=p&&p<=r);
		int x=ntop++,mid=(l+r)>>1;
		lson(x)=lson(org),rson(x)=rson(org);
		sum[x]=sum[org]+1;
		if(l==r){
			return x;
		}
		if(p<=mid){
			lson(x)=alter(lson(x),l,mid,p);
		}else{
			rson(x)=alter(rson(x),mid+1,r,p);
		}
		return x;
	}
	int query(int x1,int x2,int l,int r,int k){
		assert(x2!=0);
		assert(k<=r-l+1);
		if(l==r){
			assert(k==1);
			return l;
		}
		int diff=sum[lson(x2)]-sum[lson(x1)],mid=(l+r)>>1;
		assert(diff>=0);
		if(diff>=k){
			return query(lson(x1),lson(x2),l,mid,k);
		}else{
			return query(rson(x1),rson(x2),mid+1,r,k-diff);
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
	inline void insert(int id){//rev!
		int x=0,i=-1;
		while(s[++i]);
		while((--i)>=0){
			int &to=son[x][s[i]-'a'];
			if(to==-1){
				to=ntop++;
			}
			x=to;
		}
		add_edge(x,id);
	}
	void dfs(int x){
		int st=dfn;
		for(int i=head[x];~i;i=bro[i]){
			seg.root[dfn]=seg.alter(seg.root[dfn-1],1,n,to[i]);
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
	return seg.query(seg.root[start[i]-1],seg.root[last[i]-1],1,n,k);
}
int main(){
	n=ni();
	char c;
	for(int i=1,s;i<=n;i++){
		scanf("%s",s);
		trie.insert(i);
	}
	trie.dfs(0);
	for(int i=1;i<=n;i++){
		printf("%d\n",work(i,ni()));
	}
}
