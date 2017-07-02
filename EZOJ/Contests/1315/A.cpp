#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=30000010;
inline void input(int a[],int n){
	int S=ni,B=ni,C=ni,D=ni;
	for(int i=1;i<=n;i++){
		a[i]=i;
		S=((lint)S*B+C)%D;
		swap(a[i],a[S%i+1]);
	}
}
int a[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
#endif
	int n=ni;
	input(a,n);
	int ans=0;
	for(int i=1;i<=n;i++){
		if(i>a[i]){
			apmax(ans,i-a[i]);
		}
	}
	printf("%d\n",ans);
}
