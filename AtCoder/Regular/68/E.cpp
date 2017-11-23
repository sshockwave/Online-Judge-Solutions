#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int N=300010;
namespace B{
	int c[N],n;
	inline void init(int _n){
		memset(c+1,0,(n=_n)<<2);
	}
	inline void add(int x,int v){
		for(;x<=n;c[x]+=v,x+=x&-x);
	}
	inline int sum(int x){
		int ans=0;
		for(;x;ans+=c[x],x^=x&-x);
		return ans;
	}
}
vector<int>fact[N],ev[N];
int ans[N];
int main(){
	int tot=ni,n=ni;
	B::init(n);
	memset(ans,0,sizeof(ans));
	while(tot--){
		int l=ni,r=ni;
		ans[1]++,ans[r-l+2]--;
		ev[l].push_back(r-l+2);
		ev[r+1].push_back(-(r-l+2));
	}
	for(int i=1;i<=n;i++){
		ans[i]+=ans[i-1];
		for(int j=i;j<=n;j+=i){
			fact[j].push_back(i);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0,tj=ev[i].size();j<tj;j++){
			if(ev[i][j]>0){
				B::add(ev[i][j],1);
			}else{
				B::add(-ev[i][j],-1);
			}
		}
		for(int j=0,tj=fact[i].size();j<tj;j++){
			ans[fact[i][j]]+=B::sum(fact[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
