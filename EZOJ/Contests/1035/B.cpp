#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
#include <cassert>
#include <cctype>
#include <map>
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
const int N=16,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
int n;
struct state{
	int to[N];
	inline friend bool operator < (const state &a,const state &b){
		for(int i=1;i<=n;i++){
			if(a.to[i]!=b.to[i]){
				return a.to[i]<b.to[i];
			}
		}
		return false;
	}
	inline void gen(int u,int v){
		for(int i=1;i<=n;i++){
			if((to[i]>>u)&1){
				to[i]|=to[v];
			}
		}
	}
};
typedef map<state,int>mp;
mp pre,cur;
int main(){
#ifndef ONLINE_JUDGE
	freopen("scon.in","r",stdin);
	freopen("scon.out","w",stdout);
#endif
	n=ni;
	state tmp;
	for(int i=1;i<=n;i++){
		tmp.to[i]=1<<i;
	}
	cur[tmp]=1;
	for(int tot=ni;tot--;){
		int u=ni,v=ni;
		pre=cur;
		for(mp::iterator it=pre.begin();it!=pre.end();it++){
			tmp=it->first;
			tmp.gen(u,v);
			mp::iterator it2=cur.find(tmp);
			if(it2==cur.end()){
				cur[tmp]=it->second;
			}else{
				apadd(it2->second,it->second);
			}
		}
	}
	for(int i=1,t=((1<<n)-1)<<1;i<=n;i++){
		tmp.to[i]=t;
	}
	mp::iterator it=cur.find(tmp);
	printf("%d\n",it==cur.end()?0:it->second);
	return 0;
}
