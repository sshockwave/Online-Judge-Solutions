#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=1010,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
struct intv{
	int l,r,v,all,sub,invall;
	inline friend bool operator < (const intv &a,const intv &b){
		return a.v!=b.v?a.v<b.v:a.l!=b.l?a.l<b.l:a.r>b.r;
	}
	inline void work(){
		all=fpow(v,r-l+1);
		sub=v?fpow(v-1,r-l+1):0;
		invall=fpow(all,O-2);
	}
}ints[N],sep[N<<1],sani[N];
int f[N];//f[last chosen query]
bool vis[N<<1];
inline int dp(intv q[],intv sep[],int tot,int sps){//starts from 1
	for(int i=1,j=1,k;i<=tot;i++){
		for(;j<=sps&&sep[j].l<q[i].l;j++);
		if(j>sps||sep[j].l>q[i].r)return 0;
		sani[i].l=j;
		for(k=j;k<=sps&&sep[k].r<=q[i].r;k++);
		sani[i].r=k-1;
		if(sani[i].l>sani[i].r)return 0;
	}
	memset(vis+1,0,sps);
	f[0]=1;
	sani[0].r=0;
	sort(sani+1,sani+tot+1);
	for(int i=1;i<=tot;i++){
		if(i<tot&&sani[i+1].r<=sani[i].r)continue;
		int p=sani[i].r;
		lint sum=0,prod=1,prodsub=1;
		for(int j=i-1;j>=0;j--){
			for(;p>=sani[i].l&&p>sani[j].r;p--){
				if(!vis[p]){
					vis[p]=true;
					prod=prod*sep[p].all%O;
					prodsub=prodsub*sep[p].sub%O;
				}else{
					prodsub=prodsub*sep[p].invall%O*sep[p].sub%O;
				}
			}
			sum+=prodsub*f[j]%O;
			f[j]=prod*f[j]%O;
		}
		f[i]=(O-sum%O)%O;
	}
	lint ans=0;
	for(int i=0;i<=tot;i++){
		ans+=f[i];
	}
	ans%=O;
	if(ans==0)return ans;
	for(int i=1;i<=sps;i++){
		if(!vis[i]){
			ans=ans*sep[i].all%O;
		}
	}
	return ans;
}
int x[N<<1];
inline int Main(){
	int n=ni,tot=ni,mx=ni,xs=0;
	x[++xs]=0,x[++xs]=n;
	for(int i=1;i<=tot;i++){
		ints[i]=(intv){ni,ni,ni};
		x[++xs]=ints[i].l-1;
		x[++xs]=ints[i].r;
	}
	sort(x+1,x+xs+1);
	sort(ints+1,ints+tot+1);
	int sps=0;
	for(int i=1,j=1;i<=xs;i=j){
		for(;j<=xs&&x[i]==x[j];j++);
		if(j<=xs){
			sep[++sps]=(intv){x[i]+1,x[j],mx};
		}
	}
	for(int i=tot;i>=1;i--){
		for(int j=1;j<=sps;j++){
			if(ints[i].l<=sep[j].l&&sep[j].r<=ints[i].r){
				sep[j].v=ints[i].v;
			}
		}
	}
	sort(sep+1,sep+sps+1);
	for(int i=1;i<=sps;i++){
		sep[i].work();
	}
	lint ans=1;
	int i=1,j=1,k=1,l=1;
	for(;i<=tot;i=j,k=l){
		for(;j<=tot&&ints[i].v==ints[j].v;j++);
		for(;k<=sps&&sep[k].v!=ints[i].v;k++);
		if(k>sps)return 0;
		for(l=k;l<=sps&&sep[k].v==sep[l].v;l++);
		ans=ans*dp(ints+i-1,sep+k-1,j-i,l-k)%O;
	}
	for(;k<=sps;k++){
		ans=ans*sep[k].all%O;
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("rmq.in","r",stdin);
	freopen("rmq.out","w",stdout);
#endif
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
