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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=100010;
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	sort(a+1,a+n+1);
	bool win=true;
	a[0]=a[1];
	for(int i=1,j=0,k=0;i<=n;i++){
		if(k>=a[j]-1){
			j++;
			win=!win||((a[j]-a[j-1])&1);
		}else{
			win=((a[j]-++k)&1)==0;
		}
	}
	puts(win?"First":"Second");
	return 0;
}
