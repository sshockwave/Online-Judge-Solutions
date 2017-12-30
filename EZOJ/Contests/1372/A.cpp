#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T>inline T sqr(T x){return x*x;}
const int N=1000010;
namespace trie{
	int n=0;
	inline int nn(){
		return ++n;
	}
	const int D=26;
	int son[N][D],fail[N],dep[N]={0};
	int rt;
	inline void init(){
		memset(son,0,sizeof(son));
		rt=nn();
		for(int i=0;i<D;i++){
			son[0][i]=rt;
		}
	}
	int fa[N]={0,0};
	void ins(char s[]){
		for(int x=rt,c;s[0];x=son[x][c],s++){
			c=s[0]-'a';
			if(son[x][c]==0){
				son[x][c]=nn();
				fa[son[x][c]]=x;
				dep[son[x][c]]=dep[x]+1;
			}
		}
	}
	int que[N];
	int bfs(){
		int qh=0,qt=0;
		que[qt++]=rt;
		fail[rt]=0;
		while(qh<qt){
			int x=que[qh++];
			for(int i=0;i<D;i++){
				int s=son[x][i];
				if(s==0)continue;
				for(int &p=fail[s]=fail[x];son[p][i]==0;p=fail[p]);
				fail[s]=son[fail[s]][i];
				que[qt++]=s;
			}
		}
		return qt;
	}
	int size[N];
	lint ans;
	int stk[N],ss=0;
	void dfs(int x){
		if(dep[fail[x]]){
			ans-=size[stk[ss-dep[fail[x]]]]-1;
		}
		stk[ss++]=x;
		for(int i=0;i<D;i++){
			if(son[x][i]){
				dfs(son[x][i]);
			}
		}
		ss--;
	}
	inline lint Main(){
		int n=bfs();
		ans=sqr((lint)n-1);
		memset(size,0,sizeof(size));
		for(int i=n-1;i>=1;i--){
			int x=que[i];
			size[fail[x]]+=++size[x];
		}
		dfs(rt);
		return ans;
	}
}
char s[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	trie::init();
	for(int tot=(ni,ni);tot--;){
		scanf("%s",s);
		trie::ins(s);
	}
	printf("%lld\n",trie::Main());
	return 0;
}
