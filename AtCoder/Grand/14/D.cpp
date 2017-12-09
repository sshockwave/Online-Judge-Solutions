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
const int N=100010;
namespace T{
	const int E=N<<1;
	int to[E],bro[E],head[N],e=0;
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	inline void add(int u,int v){
		ae(u,v),ae(v,u);
	}
	int dfs(int x,int fa){
		int cnt=0;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				int tmp=dfs(v,x);
				if(tmp==-1)return -1;
				cnt+=tmp;
			}
		}
		return cnt<=1?1-cnt:-1;
	}
}
inline bool Main(){
	int n=ni;
	T::init();
	for(int i=1;i<n;T::add(ni,ni),i++);
	return T::dfs(1,0);
}
int main(){
	puts(Main()?"First":"Second");
	return 0;
}
