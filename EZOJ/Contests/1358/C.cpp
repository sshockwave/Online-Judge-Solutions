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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline T cabs(T x){return x>=0?x:-x;}
const int N=2000010,INF=0x7f7f7f7f;
int a[N];
int buc[N<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("cycle.in","r",stdin);
	freopen("cycle.out","w",stdout);
#endif
	int n=ni;
	int ans=INF,cur=0,del=0;
	for(int i=1;i<=n;i++){
		a[i]=ni;
		if(i<=a[i]){
			cur+=a[i]-i;
			del++;
		}else{
			cur+=i-a[i];
			del--;
			buc[i-a[i]]+=2;
		}
	}
	for(int i=1,j=n;i<=n;i++,j--){//size of abberation
		cur+=del;//tocheck
		cur-=a[i]-0;
		cur+=n-a[i];
		apmin(ans,cur);
		del-=2;
		buc[i+n-a[i]]+=2;
		del+=buc[i];
	}
	printf("%d\n",ans);
	return 0;
}
