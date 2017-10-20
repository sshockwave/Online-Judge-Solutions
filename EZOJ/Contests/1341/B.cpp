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
int vec[2][N],vs=0;
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
	for(int i=n;i>=1;i--){
		a[i]-=a[i-1];
	}
	for(int i=1;i<=n;i++){
		if(a[i]==2){
			vec[0][vs]=i;
			vec[1][vs]=i;
			vs++;
		}else if(a[i]==-2){
			if(vs==0){
				puts("NO");
				return 0;
			}
			vs--;
			p[vec[0][vs]]=i;
			p[i]=vec[1][vs];
		}else if(a[i]==0){
			p[i]=i;
		}else{
			puts("NO");
			return 0;
		}
	}
	if(vs){
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i=1;i<=n;i++){
		printf("%d ",p[i]);
	}
	putchar('\n');
	return 0;
}
