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
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmin(int &a,const int &b){
	if(b<a){
		a=b;
	}
}
const int N=10010,S=65,INF=0x7f7f7f7f;
int n,sh;
lint sum[N],cnt[N];
namespace DP{
	lint val[S];
	int f[N];
	inline void dp(int n,lint mx){
		sort(val+1,val+n+1);
		memset(f,127,sizeof(f));
		int i=1,x0=1;
		for(;i<=n&&val[i]==0;i++);
		for(;sum[x0];x0++);
		f[x0]=0;
		lint pre=0,cur;
		for(int j=1;i<=n;i++){
			pre+=cur=val[i];
			for(;sum[j]<pre&&sum[j]<mx;j++);
			for(int p=j,q=j;p>=x0&&q>=x0;q--){
				for(;p>=x0&&sum[p]+cur>sum[q];p--);
				if(sum[p]+cur==sum[q]&&f[p]<INF){
					apmin(f[q],i);
				}
			}
		}
	}
}
inline void work(int caseid){
	{//get sh
		lint sum=0;
		for(int i=1;i<=n;i++){
			sum+=cnt[i];
		}
		for(sh=0;(1ll<<sh)<sum;sh++);
	}
	int x=0;
	{//0
		for(;(1ll<<x)<cnt[1];x++);
		for(int i=1;i<=n;i++){
			cnt[i]>>=x;
		}
		for(int i=1;i<=x;i++){
			DP::val[i]=0;
		}
	}
	x++;
	for(int i=2;x<=sh;x++){
		for(;cnt[i]==0;i++);
		lint w=DP::val[x]=sum[i]-sum[1];
		for(int p=1,q=i;;p++){
			for(;p<=n&&cnt[p]==0;p++);
			if(p>n){
				break;
			}
			for(;q<=n&&sum[q]<sum[p]+w;q++);
			if(q>n){
				break;
			}
			assert(sum[q]==sum[p]+w);
			cnt[q]-=cnt[p];
		}
	}
	DP::dp(sh,sum[n]);
	lint cur=sum[n];
	for(int i=n;cur;){
		for(;cur<sum[i];i--);
		cur+=DP::val[DP::f[i]]=-DP::val[DP::f[i]];
	}
	for(int i=1;i<=sh;i++){
		DP::val[i]=-DP::val[i];
	}
	sort(DP::val+1,DP::val+sh+1);
	printf("Case #%d:",caseid);
	for(int i=1;i<=sh;i++){
		printf(" %lld",DP::val[i]);
	}
	putchar('\n');
}
namespace I{
	lint a[N],b[N];
	int ord[N];
	inline bool idcmp(const int &i,const int &j){
		return a[i]<a[j];
	}
	inline void narr(lint a[]){
		for(int i=1;i<=n;i++){
			a[i]=nl;
		}
	}
	inline void get(){
		narr(a),narr(b);
		for(int i=1;i<=n;i++){
			ord[i]=i;
		}
		sort(ord+1,ord+n+1,idcmp);
		for(int i=1;i<=n;i++){
			sum[i]=a[ord[i]];
			cnt[i]=b[ord[i]];
		}
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("subset.in","r",stdin);
	freopen("subset.out","w",stdout);
#endif
	for(int i=1,tot=ni;i<=tot;i++){
		n=ni;
		I::get();
		work(i);
	}
}
