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
	while(!isdigit(c=getchar())&&c!='-');
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
int ans;
namespace lib{
	const int O=1000000007;
	int a=-1;
	inline int gen(){
		if(a==-1){
			a=ni;
		}else{
			a=(1714636915ll*a+1681692777)%O*((846930886ll*ans+1804289383)%O)%O;
		}
		return a;
	}
}
priority_queue<int>q1,q2;
int main(){
#ifndef ONLINE_JUDGE
	freopen("mid.in","r",stdin);
	freopen("mid.out","w",stdout);
#endif
	int n=ni;
	int prtans=0;
	for(int i=1;i<=n;i++){
		int a=lib::gen();
		if(q2.empty()){
			q1.push(a);
		}else{
			int r=-q2.top();
			if(a>=r){
				q2.push(-a);
			}else{
				q1.push(a);
			}
		}
		for(;q1.size()>(i+1)/2;q2.push(-q1.top()),q1.pop());
		for(;q1.size()<(i+1)/2;q1.push(-q2.top()),q2.pop());
		prtans^=ans=q1.top();
		if(!q1.empty()&&!q2.empty()){
			assert(q1.top()<=-q2.top());
		}
	}
	printf("%d\n",prtans);
	return 0;
}
