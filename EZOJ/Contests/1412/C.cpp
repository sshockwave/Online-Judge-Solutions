#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
using namespace std;
typedef long long lint;
typedef long double db;
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
int n;
inline db fpow(db x,int n){
	db a=1;
	for(;n;n>>=1,x*=x){
		if(n&1){
			a*=x;
		}
	}
	return a;
}
namespace solve1{
	inline db main(){
		return (db)(n+1)/2;
	}
}
namespace solve2{//cout
	const int M=1000000;
	inline db P(int a){
		return fpow((db)(M-a+1)/M,n)-fpow((db)(M-a)/M,n);
	}
	inline db main(){/*
		db ans=0;
		for(int i=1;i<=M;i++){
			ans+=P(i)*i;
		}*/
		db ans=0;
		for(int i=0;i<M;i++){
			ans+=fpow((db)(M-i)/M,n);
		}
		return ans;
	}
}
namespace solve3{
	inline db main(){
		db ans=0;
		for(int i=1;i<=n;i++){
			ans+=(db)n/i;
		}
		return ans;
	}
}
namespace solve4{
	inline db main(){
		db ans=1;
		for(int i=1;i<=n;i++){
			ans=ans*i/n+1;
		}
		return ans;
	}
}
namespace solve5{
	struct Info{
		db sum,lsum,rsum;
	};
	inline int segcnt(int l,int r,int a,int b){
		int cnt=1;
		if(a<=l&&r<=b)return cnt;
		int m=(l+r)>>1;
		if(a<=m){
			cnt+=segcnt(l,m,a,b);
		}
		if(b>m){
			cnt+=segcnt(m+1,r,a,b);
		}
		return cnt;
	}
	inline db calcans(int l,int r){
		lint allcnt=0;
		lint allsum=0;
		for(int i=l;i<=r;i++){
			for(int j=i;j<=r;j++){
				allcnt++;
				allsum+=segcnt(l,r,i,j);
			}
		}
		return (db)allsum/allcnt;
	}
	inline Info solve(int l,int r){
		if(l==r)return (Info){1,1,1};
		int m=(l+r)>>1;
		Info lx=solve(l,m),rx=solve(m+1,r);
		lint n=r-l+1,lenl=m-l+1,lenr=r-m;
		Info ans;
		ans.lsum=(lenl*lx.lsum+lenr*(rx.lsum+1)-2)/n+1;
		ans.rsum=(lenr*rx.rsum+lenl*(lx.rsum+1)-2)/n+1;
		lint allcnt=n*(n+1)/2;
		lint lcnt=lenl*(lenl+1)/2;
		lint rcnt=lenr*(lenr+1)/2;
		lint rest=allcnt-lcnt-rcnt;
		ans.sum=(lx.sum*lcnt+rx.sum*rcnt+(lx.rsum+rx.lsum)*rest-2)/allcnt+1;
		return ans;
	}
	inline db main(){
		return solve(1,n).sum;
	}
}
namespace solve6{
	inline db main(){
		db cur=0,sum=0;
		for(int i=1;i<=n;i++){
			sum+=cur;
			cur=n+sum*2/n;
		}
		return cur;
	}
}
namespace solve7{
	const int N=10010;
	db f[N];
	inline db main(){
		if(n>N)return n*0.9995;
		for(int i=0;i<N;i++){
			f[i]=0;
		}
		db all=(db)26*26*26*26*26;
		for(int i=1;i<=n;i++){
			for(int j=0;j<=n;j++){
				f[j]=(j*f[j]+(all-j)*(f[j+1]+1))/all;
			}
		}
		return f[0];
	}
}
namespace solve8{
	const int N=1000010;
	int cnt[N];
	int a[N];
	inline db main(){
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j+=i){
				cnt[j]++;
			}
		}
		for(int i=1;i<=n;i++){
			a[cnt[i]]++;
		}
		db ans2=0;
		for(int i=1;i<=n;i++){
			ans2+=(db)a[i]/i;
		}
		return ans2;
		db ans=0;
		for(int i=1;i<=n;i++){
			ans+=(db)1/cnt[i];
		}
		return ans;
	}
}
namespace solve9{
	inline db main(){
		return 1;
	}
}
namespace solve10{
	const int M=100000;
	inline db main(){
		return 1-(db)1/M;
	}
}
db Main(int tp){
	n=ni;
	if(tp==1)return solve1::main();
	if(tp==2)return solve2::main();
	if(tp==3)return solve3::main();
	if(tp==4)return solve4::main();
	if(tp==5)return solve5::main();
	if(tp==6)return solve6::main();
	if(tp==7)return solve7::main();
	if(tp==8)return solve8::main();
	if(tp==9)return solve9::main();
	if(tp==10)return solve10::main();
	return -1;
}
int main(int argc,char *args[]){
	int tp=atoi(args[1]);
	freopen("random.in","r",stdin);
	freopen((string("random")+args[1]+string(".out")).c_str(),"w",stdout);
	for(int tot=10;tot--;){
		printf("%.10Lf\n",Main(tp));
	}
}
