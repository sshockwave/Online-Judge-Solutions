#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <queue>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
#define cout cerr
#define ni (next_num<int>())
#define nu (next_num<uint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=30010;
priority_queue<uint,vector<uint>,greater<uint> >q1;
priority_queue<uint,vector<uint>,less<uint> >q2;
uint a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("name.in","r",stdin);
	freopen("name.out","w",stdout);
#endif
	int n=ni,m=ni;
	for(int i=1;i<=n;i++){
		a[i]=nu;
	}
	for(int i=1,j=1;i<=m;i++){
		int cur=ni;
		for(;j<=cur;j++){
			if(!q2.empty()&&a[j]<q2.top()){
				q1.push(q2.top());
				q2.pop();
				q2.push(a[j]);
			}else{
				q1.push(a[j]);
			}
		}
		printf("%u\n",q1.top());
		q2.push(q1.top()),q1.pop();
	}
	return 0;
}
