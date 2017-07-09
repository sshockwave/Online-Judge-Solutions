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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010,W=77;
int tim=0;
struct BIT{
	int c[W],tag[W];
#define lowbit(x) (x&(-x))
	inline void clr(){
		memset(c,0,sizeof(c));
	}
	inline void renew(int x){
		if(tag[x]<tim){
			tag[x]=tim;
			c[x]=0;
		}
	}
	inline void add(int x,int v){
		for(;x<W;renew(x),c[x]+=v,x+=lowbit(x));
	}
	inline int sum(int x){
		int ans=0;
		for(;x;renew(x),x+=c[x],x^=lowbit(x));
		return ans;
	}
};
int val[N];
bool mark[N];
int main(){
}
