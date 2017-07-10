#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
#define ni (next_num<int>())
#define cout cerr
#define nu (next_num<uint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=10000010;
uint x[N*2],cnt[N],tag[N],tim=0;
inline void getx(int n){
	x[0]=nu,x[1]=nu;
	uint a=nu,b=nu,c=nu;
	for(int i=2;i<=n;i++){
		x[i]=a*x[i-2]+b*x[i-1]+c;
	}
	for(int i=0;i<=n;i++){
		x[i]>>=2;
	}
}
struct node{
	uint x,val,tag;
	inline friend bool operator < (const node &a,const node &b){
		return a.val>b.val;
	}
};
priority_queue<node>q;
int main(){
#ifndef ONLINE_JUDGE
	freopen("minval.in","r",stdin);
	freopen("minval.out","w",stdout);
#endif
	int n=ni,m=ni;
	getx(m<<1);
	memset(cnt,0,n<<2);
	memset(tag,0,n<<2);
	for(int i=1,tn=m<<1;i<tn;i+=2){
		cnt[x[i]%=n]++;
	}
	uint mn=2147483647u,pw=1,ans=0;
	for(int i=1,tn=m<<1;i<tn;i+=2){
		uint a=x[i],b=x[i+1];
		tag[a]=++tim;
		for(;!q.empty()&&q.top().tag<tag[q.top().x];q.pop());
		if(--cnt[a]==0){
			if(b<mn){
				mn=b;
			}
		}else{
			q.push((node){a,b,tim});
		}
		pw*=10099u;
		if(q.empty()||mn<=q.top().val){
			ans+=mn*pw;
		}else{
			ans+=q.top().val*pw;
		}
	}
	printf("%u\n",ans);
}
