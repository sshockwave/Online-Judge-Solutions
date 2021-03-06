#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=200010;
int stk[N],ss=0;
int a[N],p[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("frog.in","r",stdin);
	freopen("frog.out","w",stdout);
#endif
	int n=ni;
	for(int i=1;i<n;i++){
		a[i]=ni;
	}
	a[0]=a[n]=0;
	for(int i=1;i<=n;i++){
		int d=a[i]-a[i-1];
		if(d==2){
			stk[ss++]=i;
		}else if(d==0){
			p[i]=i;
		}else if(ss&&d==-2){
			ss--;
			p[stk[ss]]=i;
			p[i]=stk[ss];
		}else{
			puts("No");
			return 0;
		}
	}
	if(ss){
		puts("No");
		return 0;
	}
	puts("Yes");
	for(int i=1;i<=n;i++){
		printf("%d ",p[i]);
	}
	putchar('\n');
	return 0;
}
