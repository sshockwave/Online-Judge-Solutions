#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	for(;!isdigit(c=getchar())&&c!='-';);
	bool neg=c=='-';
	neg?c=getchar():0;
	for(;i=i*10-'0'+c,isdigit(c=getchar()););
	return neg?-i:i;
}
template<class A,class B>inline void apmax(A &a,const B &b){if(a<b)a=b;}
template<class A,class B>inline void apmin(A &a,const B &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
struct Node{
	lint w;
	int len;
	inline friend bool operator < (const Node &a,const Node &b){
		return a.w!=b.w?a.w>b.w:a.len>b.len;
	}
	inline void operator += (const Node &b){
		w+=b.w,apmax(len,b.len);
	}
};
int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	priority_queue<Node>q;
	lint ans=0;
	int tot=ni;
	const int k=ni;
	for(;tot--;){
		lint w=next_num<lint>();
		q.push((Node){w,0});
	}
	for(;q.size()>1;){
		Node cur=(Node){0,0};
		int lim=(q.size()-1)%(k-1)+1;
		if(lim==1){
			lim=k;
		}
		for(int i=1;i<=lim&&!q.empty();i++){
			cur+=q.top(),q.pop();
		}
		ans+=cur.w;
		++cur.len;
		q.push(cur);
	}
	printf("%lld\n%d\n",ans,q.top().len);
	return 0;
}
