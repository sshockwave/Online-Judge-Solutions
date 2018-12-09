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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010,O=1e9+7;
int s[N];
int ext[N];
int n,k;
inline int calc(){
	ext[1]=0;
	int ans=0;
	for(int i=2,j=1;i<=n;i++){
		ext[i]=max(min(j+ext[j]-i,ext[i-j+1]),0);
		for(int &k=ext[i];i+k<=n&&s[1+k]==s[i+k];k++);
		if(i+ext[i]>j+ext[j]){
			j=i;
		}
		apmax(ans,ext[i]);
	}
	return ans;
}
lint ans;
void dfs(int x){
	if(x>n){
		ans+=calc();
		return;
	}
	for(int i=1;i<=k;i++){
		s[x]=i;
		dfs(x+1);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	n=ni,k=ni;
	ans=0;
	dfs(1);
	printf("%lld\n",ans%O);
	/*
	for(k=1;k<=10;k++){
		cout<<"k="<<k<<endl;
		cout<<"\t";
		for(n=1;n<=10;n++){
			ans=0;
			dfs(1);
			cout<<ans<<" ";
		}
		cout<<endl;
	}*/
	return 0;
}
