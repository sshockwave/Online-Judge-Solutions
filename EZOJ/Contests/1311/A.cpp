#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=100010;
lint x[N],cnt[N],ans[N];
inline int bitchop(int l,int r,lint v){
	if(l>r){
		return 0;
	}
	while(l<r){
		int mid=((l+r)>>1)+1;
		if(x[mid]<=v){
			l=mid;
		}else{
			r=mid-1;
		}
	}
	return l;
}
int main(){
	int n=ni,tot=ni,m=0;
	lint k;
	x[0]=0,x[++m]=n;
	while(tot--){
		k=nl;
		for(;x[m]>=k;m--);
		x[++m]=k;
	}
	memset(cnt,0,sizeof(cnt));
	cnt[m]=1;
	for(int i=m,j;i>0;i--){
		k=x[i];
		j=i;
		for(;j=bitchop(1,j-1,k);k%=x[j]){
			cnt[j]+=k/x[j]*cnt[i];
		}
		ans[k]+=cnt[i];
	}
	for(int i=n;i>0;i--){
		ans[i]+=ans[i+1];
	}
	for(int i=1;i<=n;i++){
		printf("%lld ",ans[i]);
	}
	putchar('\n');
}
