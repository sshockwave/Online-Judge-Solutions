#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
	if(a>b){a=b;}
}
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7fll;
lint t[N];
int b[N],n;//Cost of C:t[i]
lint A,B,C;
namespace AB{
	int a[N];
	inline lint work(int t){
		assert(A<B);
		memcpy(a,b,n<<2);
		lint cnta=0,cntb=0;
		int i=0,j=n-1;
		while(i<j&&a[i]<t&&a[j]>t){//get part A
			int d=min(t-a[i],a[j]-t);
			a[i]+=d,a[j]-=d;
			cnta+=d;
			if(a[i]==t){
				i++;
			}
			if(a[j]==t){
				j--;
			}
		}
		for(;j>=0&&a[j]>t;cntb+=a[j]-t,j--);
		return A*cnta+B*cntb;
	}
}
int mxt=0;
namespace BLA{
	lint t2[N];
	inline lint solve(){
		memset(t2,0,sizeof(t2));
		for(int i=0;i<n;i++){
			if(b[i]){
				t2[b[i]-1]++;
			}
		}
		for(int i=mxt-1;i>=0;i--){
			t2[i]+=t2[i+1];
		}
		for(int i=mxt-1;i>=0;i--){
			t2[i]+=t2[i+1];
		}
		lint ans=LINF;
		for(int i=0;i<=mxt;i++){
			apmin(ans,B*t2[i]+C*t[i]);
		}
		return ans;
	}
}
inline lint calc(int tim){
	return C*t[tim]+AB::work(tim);
}
int mnt=N;
inline lint solve(){
	if(B<=A){
		return BLA::solve();
	}
	if(n<=2100&&mxt<=2100){
		lint ans=LINF;
		for(int i=0;i<=mxt;i++){
			apmin(ans,C*t[i]+AB::work(i));
		}
		return ans;
	}
	if(C>=10000000000){
		return AB::work(mnt);
	}
	int l=0,r=mxt;
	while(r-l>5){
		int m1=((l<<1)+r)/3,m2=(l+(r<<1))/3;
		lint v1=calc(m1),v2=calc(m2);
		if(v1>v2){
			l=m1;
		}else{
			r=m2;
		}
	}
	lint ans=LINF;
	for(int i=l;i<=r;i++){
		apmin(ans,calc(i));
	}
	return ans;
}
int main(){
	A=nl,B=nl,C=nl;
	int tot=ni;
	n=ni;
	memset(t,0,sizeof(t));
	while(tot--){
		int cur=ni;
		apmax(mxt,cur);
		apmin(mnt,cur);
		t[cur+1]++;
	}
	for(int i=1;i<N;i++){
		t[i]+=t[i-1];
	}
	for(int i=1;i<N;i++){
		t[i]+=t[i-1];
	}
	for(int i=0;i<n;i++){
		b[i]=ni;
	}
	sort(b,b+n);
	apmax(mxt,b[n-1]);
	printf("%lld\n",solve());
}