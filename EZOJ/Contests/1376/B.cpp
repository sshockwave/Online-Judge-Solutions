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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=110;
struct Pt{
	int x,y;
	inline friend bool operator < (const Pt &a,const Pt &b){
		return a.x!=b.x?a.x<b.x:a.y<b.y;
	}
}pt[N];
int f[N];
inline int Main(){
	int n=ni,size=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
	}
	sort(pt+1,pt+n+1);
	memset(f+1,127,n<<2);
	f[0]=0;
	for(int i=1;i<=n;i++){
		int mx=0;
		for(int j=i;j>=1;j--){
			apmax(mx,pt[j].y);
			if((lint)mx*(pt[i].x-pt[j].x)>size)break;
			apmin(f[i],f[j-1]+1);
		}
	}
	return f[n];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("scene.in","r",stdin);
	freopen("scene.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
