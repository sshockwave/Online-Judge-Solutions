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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=200010;
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
int a[N],pos[N];
vector<int>q[N],d[N];
int qr[N],ans[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("division.in","r",stdin);
	freopen("division.out","w",stdout);
#endif
	int n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		pos[a[i]=ni]=i;
	}
	for(int i=1;i<=tot;i++){
		q[ni].push_back(i);
		qr[i]=ni;
	}
	B::init(n);
	for(int i=n;i>=1;i--){
		for(int j=0,tj=d[i].size();j<tj;j++){
			B::add(d[i][j],1);
		}
		for(int j=a[i];j<=n;j+=a[i]){
			if(pos[j]<i){
				d[pos[j]].push_back(i);
			}else{
				B::add(pos[j],1);
			}
		}
		for(int j=0,tj=q[i].size();j<tj;j++){
			ans[q[i][j]]=B::sum(qr[q[i][j]]);
		}
	}
	for(int i=1;i<=tot;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}
