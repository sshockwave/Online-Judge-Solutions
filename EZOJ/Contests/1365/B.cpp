#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <utility>
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
const int N=23000010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int fac[N],invfac[N];
inline int C(int n,int k){
	return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
}
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
	}
}
struct state{
	const static int D=5;
	int a[D];
	inline state hash(int x){
		for(int i=0;i<D;i++,x>>=2){
			a[i]=x&3;
		}
		return *this;
	}
	inline int hash(){
		int ans=0;
		for(int i=0;i<D;i++){
			ans|=a[i]<<(i<<1);
		}
		return ans;
	}
};
int f[1<<(state::D<<1)];//10: 0:L wins 1:R wins
inline bool valid(int x){
	return x>=0&&x<5;
}
int dfs(int x){
	if(~f[x])return f[x];
	state cur;
	cur.hash(x);
	int *a=cur.a;
	bool win[2]={0,0};
	for(int i=0;i<5;i++){
		if(a[i]<2&&!win[a[i]]){
			int p=a[i],d=p==0?1:-1;
			if(valid(i+d)&&a[i+d]==2){
				a[i+d]=p,a[i]=2;
				win[p]|=((dfs(cur.hash())>>(1-p))&1)==0;
				a[i+d]=2,a[i]=p;
				if(win[p])continue;
			}
			if(valid(i+d)&&a[i+d]!=p&&valid(i+(d<<1))&&a[i+(d<<1)]==2){
				d<<=1;
				a[i+d]=p,a[i]=2;
				win[p]|=((dfs(cur.hash())>>(1-p))&1)==0;
				a[i+d]=2,a[i]=p;
			}
		}
	}
	return f[x]=(((int)win[1])<<1)|win[0];
}
inline int lescnt(int a,int b){//a>b
	lint ans=0;
	int sum=0;
	for(int i=0;i<=a;i++){
		ans+=(lint)C(a,i)*sum%O;
		if(i<=b){
			(sum+=C(b,i))%=O;
		}
	}
	return ans%O;
}
inline void Main(){
	int cnt[4]={0,0,0,0};
	for(int tot=ni;tot--;){
		static char s[10];
		static state stat;
		scanf("%s",s);
		for(int i=0;i<state::D;i++){
			stat.a[i]=s[i]=='L'?0:s[i]=='R'?1:2;
		}
		cnt[f[stat.hash()]]+=ni;
	}
	int same=(lint)fac[cnt[1]+cnt[2]]*invfac[cnt[1]]%O*invfac[cnt[2]]%O;
	int all=fpow(2,cnt[1]+cnt[2]);
	int awin=lescnt(cnt[1],cnt[2]);
	int bwin=((all-awin-same)%O+O)%O;
	int tmp=fpow(2,cnt[0]+cnt[3]);
	awin=(lint)awin*tmp%O;
	bwin=(lint)bwin*tmp%O;
	//0:previous wins 3:next wins
	int fir0,fir1;
	if(cnt[3]){
		fir0=fir1=fpow(2,cnt[3]-1);
	}else{
		fir0=1,fir1=0;
	}
	tmp=(lint)fpow(2,cnt[0])*same%O;
	int fwin=(lint)fir1*tmp%O,swin=(lint)fir0*tmp%O;
	printf("%d %d %d %d\n",awin,bwin,fwin,swin);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("frogs.in","r",stdin);
	freopen("frogs.out","w",stdout);
#endif
	memset(f,-1,sizeof(f));
	dfs(((state){0,0,2,1,1}).hash());
	ni;
	gmath(N-1);
	for(int tot=ni;tot--;Main());
	return 0;
}
