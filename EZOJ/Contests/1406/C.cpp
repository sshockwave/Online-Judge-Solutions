#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
	const int E=::N<<1;
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
}
namespace task4{
	const int N=5010;
	bool vis[N][N];
	int val[N];
	int stk[N],ss=0;
	bool dfs(int x,int fa,int t){
		stk[++ss]=x;
		if(x==t)return true;
		using namespace T;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				if(dfs(v,x,t))return true;
			}
		}
		ss--;
		return false;
	}
	struct scmp{
		inline bool operator () (const int &a,const int &b){
			return val[a]!=val[b]?val[a]<val[b]:a<b;
		}
	};
	set<int,scmp>s;
	inline void main(int tot){
		for(int tt=1;tt<=tot;tt++){
			int op=ni;
			if(op==1){
				int u=ni,v=ni;
				val[tt]=ni;
				s.insert(tt);
				ss=0;
				dfs(u,0,v);
				for(int i=1;i<=ss;i++){
					vis[tt][stk[i]]=true;
				}
			}else if(op==2){
				s.erase(ni);
			}else{
				int x=ni;
				set<int,scmp>::reverse_iterator it=s.rbegin();
				for(;it!=s.rend()&&vis[*it][x];it++);
				printf("%d\n",it==s.rend()?-1:val[*it]);
			}
		}
	}
}
namespace task5{
	int bln[N];
	void dfs(int x,int fa,int rt,bool flag){
		using namespace T;
		bln[x]=rt;
		for(int i=head[x],v;~i;i=bro[i]){
			if((v=to[i])!=fa){
				dfs(v,x,flag?v:rt,false);
			}
		}
	}
	int val[N];
	multiset<int>s;
	inline void main(int tot){
		dfs(1,0,1,true);
		for(int i=1;i<=tot;i++){
			int op=ni;
			if(op==1){
				int u=ni,v=ni;
				val[i]=ni;
				if(bln[u]!=bln[v]){
					val[i]=-1;
				}else{
					s.insert(val[i]);
				}
			}else if(op==2){
				int x=ni;
				if(val[x]>-1){
					s.erase(s.find(val[x]));
				}
			}else{
				printf("%d\n",s.empty()?-1:*s.rbegin());
			}
		}
	}
}
namespace task6{
	inline void main(int tot){
		//cout
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("company.in","r",stdin);
	freopen("company.out","w",stdout);
#endif
	int n=ni,m=ni;
	bool cha=true;
	T::init();
	for(int i=1;i<n;i++){
		int u=ni,v=ni;
		T::add(u,v);
		cha&=max(u,v)-min(u,v)==1;
	}
	if(n<=5000){
		task4::main(m);
	}else if(cha){
		task6::main(m);
	}else{
		task5::main(m);
	}
	return 0;
}
