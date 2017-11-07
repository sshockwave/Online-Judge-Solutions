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
const int N=300010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int a[N],b[N];
bool mark[N];
int opls[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("max.in","r",stdin);
	freopen("max.out","w",stdout);
#endif
	memset(mark,0,sizeof(mark));
	int cnt=0,ls=0;
	for(int i=1,tot=ni;i<=tot;i++){
		int op=ni;
		if(op==1){
			cnt++;
			a[ls]=ni;
			b[ls]=ni;
			opls[i]=ls++;
		}else if(op==2){
			cnt--;
			mark[opls[ni]]=true;
		}else{
			lint x=ni,ans=-LINF;
			if(cnt==0){
				puts("EMPTY SET");
				continue;
			}
			for(int i=0;i<ls;i++){
				if(!mark[i]){
					apmax(ans,x*a[i]+b[i]);
				}
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
