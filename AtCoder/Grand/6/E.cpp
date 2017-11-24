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
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010;
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
inline bool getrev(int a[],int n,int mx){
	B::init(mx);
	bool ans=0;
	for(int i=n-((n&1)^1);i>=1;i-=2){
		ans^=B::sum(a[i])&1;
		B::add(a[i],1);
	}
	return ans;
}
bool vis[N];
int a[3][N],b[N];
inline bool Main(){
	int n=ni;
	for(int i=0;i<3;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=ni;
		}
	}
	memset(vis,0,sizeof(vis));
	bool revt[2]={false,false};
	for(int i=1;i<=n;i++){
		if(a[1][i]%3!=2)return false;
		b[i]=(a[1][i]+1)/3;
		if(vis[b[i]]||((i&1)!=(b[i]&1)))return false;
		vis[b[i]]=true;
		if(a[0][i]==a[1][i]-1&&a[2][i]==a[1][i]+1){
			revt[i&1]^=(((b[i]^i)>>1))&1;
		}else if(a[0][i]==a[1][i]+1&&a[2][i]==a[1][i]-1){
			revt[i&1]^=((((b[i]^i)>>1))&1)==0;
		}else return false;
	}
	revt[0]^=getrev(b,n,n);
	revt[1]^=getrev(b+1,n-1,n);
	return !revt[0]&&!revt[1];
}
int main(){
	puts(Main()?"Yes":"No");
	return 0;
}
