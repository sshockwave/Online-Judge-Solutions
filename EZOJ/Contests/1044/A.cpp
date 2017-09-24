#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010;
lint gcd(lint a,lint b){
	return b?gcd(b,a%b):a;
}
typedef map<lint,vector<int> >mp;
mp m;
lint a[N],val[N],_xor[N];
int que[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("opening.in","r",stdin);
	freopen("opening.out","w",stdout);
#endif
	int n=ni,t=0;
	_xor[0]=0;
	for(int i=1;i<=n;i++){
		_xor[i]=(a[i]=nl)^_xor[i-1];
	}
	lint num=nl;
	que[t]=0,val[t]=1,t++;
	for(int i=1,j,k;i<=n;i++){
		que[t]=i,val[t]=a[i],t++;
		m[_xor[i-1]].push_back(i);
		for(j=0,k=t,t=0;j<k;t++){
			val[t]=gcd(a[i],val[j]);
			for(;j<k&&gcd(a[i],val[j])==val[t];que[t]=que[j++]);
			if(num%val[t]==0){
				mp::iterator it=m.find((num/val[t])^_xor[i]);
				if(it!=m.end()){
					vector<int>::iterator p=upper_bound(it->second.begin(),it->second.end(),t?que[t-1]:0);
					if(p!=it->second.end()&&*p<=que[t]){
						printf("%d %d\n",*p,i);
						return 0;
					}
				}
			}
		}
	}
	puts("no solution");
	return 0;
}
