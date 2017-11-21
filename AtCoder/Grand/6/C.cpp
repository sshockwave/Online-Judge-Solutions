#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010;
lint x[N],ans[N];
int perm[N],lst[N];
bool vis[N];
int main(){
	int n=ni;
	lint sum=0;
	for(int i=1;i<=n;i++){
		sum+=x[i]=nl-sum,perm[i]=i;
	}
	int tot=ni;
	lint K=nl;
	for(int x;tot--;x=ni,swap(perm[x],perm[x+1]));
	for(int i=1;i<=n;i++){
		int ls=0;
		for(int j=i;!vis[j];lst[ls++]=j,vis[j]=true,j=perm[j]);
		for(int j=0;j<ls;j++){
			ans[lst[j]]=x[lst[(K+j)%ls]];
		}
	}
	for(int i=1;i<=n;i++){
		printf("%lld.0\n",ans[i]+=ans[i-1]);
	}
	return 0;
}
