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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=300010,D=26;
namespace trie{
	int size[N];
	int son[N][D],n=0;
	bool end[N];
	int rt=++n;
	inline void init(){
		memset(size,0,sizeof(size));
		memset(son,0,sizeof(son));
		memset(end,0,sizeof(end));
	}
	void ins(int x,char *s){
		if((*s)==0){
			end[x]=true;
			return;
		}
		if(son[x][(*s)-'a']==0){
			son[x][(*s)-'a']=++n;
		}
		ins(son[x][(*s)-'a'],s+1);
	}
	void dfs(int x){
		if(x==0){
			return;
		}
		if(end[x]){
			size[x]++;
		}
		for(int i=0;i<D;i++){
			dfs(son[x][i]);
			size[x]+=size[son[x][i]];
		}
	}
}
char s[N],t[N];
inline bool match(){
	for(int i=0;s[i];i++){
		bool flag=true;
		for(int j=0;t[j];j++){
			if(s[i+j]!=t[j]){
				flag=false;
				break;
			}
		}
		if(flag){
			return true;
		}
	}
	return false;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("loop.in","r",stdin);
	freopen("loop.out","w",stdout);
#endif
	scanf("%s",s);
	trie::init();
	int n=strlen(s);
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			memcpy(t,s+i+1,j-i);
			t[j-i]=s[i];
			t[j-i+1]=0;
			if(match()){
				trie::ins(trie::rt,t);
			}
		}
	}
	trie::dfs(trie::rt);
	printf("%d\n",trie::size[trie::rt]);
	return 0;
}
