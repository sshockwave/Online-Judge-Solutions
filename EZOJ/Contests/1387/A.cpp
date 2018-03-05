#include <iostream>
#include <cstring>
#include <cstdio>
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
const int N=100010;
namespace seg{
	const int N=100010*20;
	struct Node;
	typedef Node* node;
	struct Node{
		node lson,rson;
		int cnt;
		lint sum;
		inline void up(){
			sum=lson->sum+rson->sum;
		}
	}pool[N],Null;
	node null,nd;
	int n;
	inline node nn(node x=null){
		return *nd=*x,nd++;
	}
	inline void init(int _n){
		memset(null=&Null,0,sizeof(Null));
		null->lson=null->rson=null;
		nd=pool;
		n=_n;
	}
	node add(node x,int p,lint v,int l=0,int r=n-1){
		x=nn(x);
		x->cnt++;
		x->sum+=v;
		if(l!=r){
			int m=(l+r)>>1;
			if(p<=m){
				x->lson=add(x->lson,p,v,l,m);
			}else{
				x->rson=add(x->rson,p,v,m+1,r);
			}
		}
		return x;
	}
	lint ask(node x,int k,int l=0,int r=n-1){
		if(x->cnt==k)return x->sum;
		assert(k<=x->cnt);
		int m=(l+r)>>1;
		if(k<=x->lson->cnt)return ask(x->lson,k,l,m);
		else return x->lson->sum+ask(x->rson,k-x->lson->cnt,m+1,r);
	}
}
namespace cov{
	int st[N],f[N],qt;
	inline void init(){
		qt=0;
		st[qt]=0,f[qt]=-1,qt++;
	}
	inline int ask(int x){
		return f[upper_bound(st,st+qt,x)-1-st];
	}
	inline void cov(int x,int v){
		for(;x<=st[qt-1];qt--);
		st[qt]=x,f[qt]=v,qt++;
	}
}
lint sum[N];
lint alltime;
seg::node rt[N];
int cost[N],rnk[N];
inline int work(const int len[],lint ans[],int n){
	cov::init(),seg::init(n);
	for(int i=0;i<n;i++){
		sum[i+1]=sum[i]+len[i];
		if(sum[i+1]>alltime){
			n=i+1;
			break;
		}
	}
	ans[0]=0;
	for(int i=0;i<n;i++){
		rt[i]=seg::add(i?rt[i-1]:seg::null,rnk[i],cost[i]);
		int l=1,r=i+1;
		while(l<r){
			int m=(l+r)>>1;
			int f=cov::ask(m);
			if(sum[f]+seg::ask(rt[f],m)>sum[i]+seg::ask(rt[i],m)){
				r=m;
			}else{
				l=m+1;
			}
		}
		cov::cov(l,i);
	}
	for(int i=1,j=1;i<=n;i++){
		using namespace cov;
		for(;j+1<qt&&st[j+1]<=i;j++);
		ans[i]=sum[f[j]]+seg::ask(rt[f[j]],i);
		if(ans[i]>alltime){
			n=i;
			break;
		}
	}
	return n;
}
int len[N];
lint cw[N],ccw[N];
int n;
inline int Main(){
	for(int i=0;i<n;i++){
		len[i]<<=1;
	}
	int mx1=work(len,cw,n);
	for(int i=0;i<n;i++){
		len[i]>>=1;
	}
	reverse(len,len+n),reverse(cost,cost+n),reverse(rnk,rnk+n);
	len[n]=len[0];
	int mx2=work(len+1,ccw,n);
	reverse(len,len+n),reverse(cost,cost+n),reverse(rnk,rnk+n);
	ccw[0]=-len[n-1];
	int ans=0;
	for(int i=0,j=mx2;i<=mx1;i++){
		for(;j>=0&&cw[i]+ccw[j]+len[n-1]>alltime;j--);
		if(j>=0){
			apmax(ans,i+j);
		}else break;
	}
	return ans;
}
int lst[N];
inline bool lcmp(int a,int b){
	return cost[a]<cost[b];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("decalcomania.in","r",stdin);
	freopen("decalcomania.out","w",stdout);
#endif
	n=ni,alltime=next_num<lint>();
	for(int i=0;i<n;i++){
		len[i]=ni,cost[i]=ni,lst[i]=i;
	}
	sort(lst,lst+n,lcmp);
	for(int i=0;i<n;i++){
		rnk[lst[i]]=i;
	}
	int ans=Main();
	reverse(len,len+n),reverse(cost+1,cost+n),reverse(rnk+1,rnk+n);
	printf("%d\n",max(ans,Main()));
	return 0;
}
