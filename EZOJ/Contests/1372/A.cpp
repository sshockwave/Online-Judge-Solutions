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
const int N=1000010;
namespace trie{
	int n=0;
	inline int nn(){
		return ++n;
	}
	const int D=26;
	int son[N][D],fail[N],dep[N]={0};
	int rt;
	int same[N];
	inline void init(){
		memset(son,0,sizeof(son));
		memset(same,0,sizeof(same));
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
	int stk[N],ss=0;
	int que[N];
	int bfs(){
		int qh=0,qt=0;
		que[qt++]=rt;
		fail[rt]=0;
		while(qh<qt){
			int x=que[qh++];
			ss=0;
			for(int p=x;p;p=fa[p]){
				stk[ss++]=p;
			}
			for(int p=fail[x];dep[p];p=fail[p]){
				same[stk[dep[p]]]++;
			}
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
	trie::fail[trie::rt]=0;
	int size=trie::bfs()-1;
	lint ans=(lint)size*size;
	for(int x=2;x<=trie::n;x++){
		using namespace trie;/*
		for(int p=x;p=fail[p],dep[p];){
			ans-=same[p];
		}*/
		int p=fail[x];
		for(;dep[fail[p]];p=fail[p]);
		cout<<"x="<<x<<"\tp="<<p<<"\tsame="<<same[x]<<"\tfail="<<fail[x]<<endl;
		if(dep[p]){
			ans-=same[p];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
