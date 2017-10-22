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
const int N=100010,O=1000000007;
inline int add(const int &a,const int &b){return (a+b)%O;}
inline int sub(const int &a,const int &b){return add(a,O-b);}
const lint LINF=0x7f7f7f7f7f7f7f7f;
lint a[N];
int f[N],g[N],_f[N],_g[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("toy.in","r",stdin);
	freopen("toy.out","w",stdout);
#endif
	int n=ni;
	lint da=ni,db=ni;
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
	a[0]=-LINF,a[n+1]=LINF;
	sort(a+1,a+n+1);
	f[0]=g[0]=_f[0]=_g[0]=1;
	int al=1,bl=1,ar=0,br=0;
	for(int i=1;i<=n;i++){
		if(a[i-1]+da>a[i]){
			al=i;
		}
		if(a[i-1]+db>a[i]){
			bl=i;
		}
		for(;ar<i&&a[ar]+db<=a[i+1];ar++);
		for(;br<i&&a[br]+da<=a[i+1];br++);
		f[i]=al<=ar?sub(_g[ar-1],al>=2?_g[al-2]:0):0;
		g[i]=bl<=br?sub(_f[br-1],bl>=2?_f[bl-2]:0):0;
		_f[i]=(_f[i-1]+f[i])%O;
		_g[i]=(_g[i-1]+g[i])%O;
	}
	printf("%d\n",(f[n]+g[n])%O);
	return 0;
}
