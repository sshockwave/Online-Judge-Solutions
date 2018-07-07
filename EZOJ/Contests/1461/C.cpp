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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=55,C=110,O=1000000007;
int a[N*C];
int cnt[N];
lint ans=0;
int n;
void dfs(int x){
	bool flag=false;
	for(int &i=a[x]=1;i<=n;i++){
		if(cnt[i]){
			flag=true;
			--cnt[i];
			dfs(x+1);
			++cnt[i];
		}
	}
	if(!flag){
		int cur=1;
		int i=1;
		for(;i<x&&a[i]==a[1];i++);
		int cnt=1,last=-1;
		for(int tt=1;tt<x;tt++,i++){
			i=(i-1)%(x-1)+1;
			if(a[i]==last){
				++cnt;
			}else{
				cur=(lint)cur*cnt%O;
				cnt=1;
				last=a[i];
			}
		}
		cur=(lint)cur*cnt%O;
		ans+=cur;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
#endif
	n=ni;
	for(int i=1;i<=n;i++){
		cnt[i]=ni;
	}
	dfs(1);
	printf("%lld\n",ans%O);
	return 0;
}
