#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
uint x0,x1,a,b,c,n,m;
uint now=1,tot=0;
uint s[10000010];
uint nxt(){
	uint t=x0*a+x1*b+c;
	x0=x1;
	x1=t;
	return x0>>2;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("contest.in","r",stdin);
	freopen("contest.out","w",stdout);
#endif
	cin>>n>>m>>x0>>x1>>a>>b>>c;
	for(uint i=0;i<n;i++){
		s[i]=2147483647;
	}
	int minp=0;
	for(uint i=1;i<=m;i++){
		int f=nxt();
		int g=nxt();
		int ps=f%n;
		uint oldval=s[minp];
		s[ps]=g;
		if(s[ps]<s[minp]){
			minp=ps;
		}else if(ps==minp&&s[minp]>oldval){
			for(uint j=0;j<n;j++){
				if(s[j]<s[minp]){
					minp=j;
				}
			}
		}
		uint ans=s[minp];
		now*=10099;
		tot+=now*ans;
	}
	cout<<tot<<endl;
	return 0;
}
