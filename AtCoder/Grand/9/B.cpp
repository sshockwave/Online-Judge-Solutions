#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
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
	int f[N];
	inline void init(){
		memset(head,-1,sizeof(head));
	}
	inline void ae(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
	}
	int dfs(int x){
		vector<int>vec;
		for(int i=head[x];~i;i=bro[i]){
			vec.push_back(dfs(to[i]));
		}
		sort(vec.begin(),vec.end());
		int ans=0;
		for(int i=0,n=vec.size();i<n;i++){
			apmax(ans,vec[i]+n-i);
		}
		return ans;
	}
}
int main(){
	int n=ni;
	T::init();
	for(int i=2;i<=n;T::ae(ni,i),i++);
	printf("%d\n",T::dfs(1));
	return 0;
}
