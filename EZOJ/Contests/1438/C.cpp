#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <algorithm>
using namespace std;
typedef set<int>si;
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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=300010,O=1000000007;
namespace gmath{
	int fac[N];
	inline void main(int n){
		fac[0]=1;
		for(int i=1;i<=n;i++){
			fac[i]=(lint)fac[i-1]*i%O;
		}
	}
}
namespace mem{
	si arr[N];
	si* pt[N];
	int n;
	inline void init(){
		n=0;
		for(int i=0;i<N;i++){
			pt[i]=arr+i;
		}
	}
	inline si* New(){
		pt[n]->clear();
		return pt[n++];
	}
	inline void del(si* x){
		pt[--n]=x;
	}
}
int lst[N];
namespace sieve{
	bool np[N];
	int pri[N],ps=0;
	int mnfact[N],nxt[N];
	int iso[N];
	inline void main(int n){
		mset(np+1,0,n);
		iso[1]=1;
		for(int i=2;i<=n;i++){
			if(!np[i]){
				pri[ps++]=i;
				mnfact[i]=i;
				iso[i]=i;
				nxt[i]=1;
			}
			for(int j=0,p,t;j<ps&&(p=pri[j],t=i*p,t<=n);j++){
				np[t]=true;
				mnfact[t]=p;
				if(i%p){
					nxt[t]=i;
					iso[t]=iso[i]*p;
				}else{
					nxt[t]=nxt[i];
					iso[t]=iso[i];
					break;
				}
			}
		}
	}
	inline si* factorize(int n){
		si* s=mem::New();
		if(n==1){
			s->insert(1);
		}else for(;n!=1;n=nxt[n]){
			s->insert(mnfact[n]);
		}
		return s;
	}
	inline int factorize_arr(int n){
		int ls=0;
		if(n==1){
			lst[++ls]=1;
		}else for(;n!=1;n=nxt[n]){
			lst[++ls]=mnfact[n];
		}
		return ls;
	}
}
inline si* inters(si* a,si* b){
	if(a->size()>b->size()){
		swap(a,b);
	}
	si* c=mem::New();
	for(si::iterator it=a->begin(),ti=a->end(),nxt;it!=ti;it=nxt){
		nxt=it,++nxt;
		si::iterator it2=b->find(*it);
		if(it2!=b->end()){
			c->insert(*it);
			a->erase(it),b->erase(it2);
		}
	}
	return c;
}
int a[N];
si* bel[N];
inline bool bel_cmp(int a,int b){
	return bel[a]<bel[b];
}
int isocnt[N];
inline int Main(){
	mem::init();
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	bel[1]=mem::New();
	bel[1]->insert(1);
	for(int i=0,cur,las=-1;i<sieve::ps&&sieve::pri[i]<=n;i++,las=cur){
		const int p=sieve::pri[i];
		cur=n/p;
		if(cur==1){
			bel[p]=bel[1];
		}else if(cur==las){
			bel[p]=bel[sieve::pri[i-1]];
		}else{
			bel[p]=mem::New();
		}
		bel[p]->insert(p);
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0)continue;
		int ls=sieve::factorize_arr(i);
		si* tmp=sieve::factorize(a[i]);
		if(ls!=int(tmp->size()))return 0;
		sort(lst+1,lst+ls+1,bel_cmp);
		for(int l=1,r;l<=ls;l=r){
			si * const org=bel[lst[l]];
			for(r=l;r<=ls&&org==bel[lst[r]];r++);
			//[l,r)
			int len=r-l;
			si * const nset=inters(org,tmp);
			if(int(nset->size())!=len)return 0;
			if(org->empty()){
				mem::del(org);
			}
			if(tmp->empty()){
				mem::del(tmp);
			}
			for(int j=l;j<r;j++){
				bel[lst[j]]=nset;
			}
		}
	}
	mset(isocnt+1,0,n);
	for(int i=1;i<=n;i++){
		++isocnt[sieve::iso[i]];
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0)continue;
		--isocnt[sieve::iso[a[i]]];
	}
	int ans=1;
	for(int i=1;i<=n;i++){
		if(isocnt[i]){
			ans=(lint)ans*gmath::fac[isocnt[i]]%O;
		}
	}
	for(int i=1;i<=n;i++){
		if(!(i==1||!sieve::np[i]))continue;
		if(bel[i]->size()==0)continue;
		ans=(lint)ans*gmath::fac[bel[i]->size()]%O;
		bel[i]->clear();
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("perm.in","r",stdin);
	freopen("perm.out","w",stdout);
#endif
	gmath::main(N-1);
	sieve::main(N-1);
	for(int tot=ni;tot--;printf("%d\n",Main()));
	return 0;
}
