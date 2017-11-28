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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7f;
lint dval[N],ddval[N];
int main(){
	int n=ni,m=ni;
	memset(dval,0,sizeof(dval));
	memset(ddval,0,sizeof(ddval));
	int last=ni;
	for(int i=2;i<=n;i++){
		int cur=ni;
		if(last<cur){
			dval[1]+=cur-last;
			ddval[last+2]--;
			ddval[cur+1]++;
			dval[cur+1]+=cur-last-1;
		}else if(cur<last){
			dval[1]+=cur;
			ddval[2]--;
			ddval[cur+1]++;
			dval[cur+1]+=cur+m-last-1;
			ddval[last+2]--;
		}else assert(false);
		last=cur;
	}
	lint val=0,d=0,ans=LINF;
	for(int i=1;i<=m;i++){
		d+=ddval[i];
		val+=d+dval[i];
		apmin(ans,val);
	}
	printf("%lld\n",ans);
	return 0;
}
