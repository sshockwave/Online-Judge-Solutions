#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
const int N=30;
int pri[N];
lint *idx,*mx,*size;
int main(){
#ifndef ONLINE_JUDGE
	freopen("h.in","r",stdin);
	freopen("h.out","w",stdout);
#endif
	set<lint>s;
	const int ps=ni;
	s.insert(next_num<lint>());
	for(int i=1;i<=ps;i++){
		const int p=pri[i]=ni;
		for(set<lint>::reverse_iterator it=s.rbegin();it!=s.rend();++it){
			s.insert(*it/p);
		}
	}
	const int len=s.size();
	idx=new lint[len];
	size=new lint[len];
	mx=new lint[len];
	{
		set<lint>::iterator it=s.begin();
		for(int i=0;i<len;i++,++it){
			idx[i]=*it;
			size[i]=i>0;
			mx[i]=i>0;
		}
	}
	for(int i=1;i<=ps;i++){
		const int p=pri[i];
		for(int j=1,k=0;j<len;j++){
			lint tval=idx[j]/p;
			for(;idx[k]<tval;k++);
			assert(idx[k]==tval);
			size[j]+=size[k];
			apmax(mx[j],mx[k]*p);
		}
	}
	printf("%lld\n%lld\n",mx[len-1],size[len-1]);
	return 0;
}
