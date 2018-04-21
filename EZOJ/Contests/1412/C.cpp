#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <set>
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
namespace solve1{//okay
	inline db main(){
		return (db)(n+1)/2;
	}
}
namespace solve2{//precision
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
namespace solve3{//precision
	inline db main(){
		db ans=0;
		for(int i=1;i<=n;i++){
			ans+=(db)n/i;
		}
		return ans;
	}
}
namespace solve4{//okay
	inline db main(){
		db ans=1;
		for(int i=1;i<=n;i++){
			ans=ans*i/n+1;
		}
		return ans;
	}
}
namespace solve5{//okay
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
namespace solve6{//precision
	inline db main(){
		db cur=0,sum=0;
		for(int i=1;i<=n;i++){
			sum+=cur;
			cur=i+sum*2/i;
		}
		return cur;
	}
}
namespace solve7{
	const int N=10010;
	const int M=100003;
	int cnt[M];
	void dfs(int x,int h){
		if(x>5){
			cnt[h%M]++;
		}else for(int i=0;i<26;i++){
			dfs(x+1,((lint)h*31+i)%1000000007);
		}
	}
	inline db main(){
		dfs(1,0);
		lint n2=0,sigc=0;
		for(int i=0;i<M;i++){
			n2+=cnt[i];
			sigc+=(lint)cnt[i]*(cnt[i]-1);
		}
		lint all=n2;
		n2*=n2;
		db q=(db)(all-1)/all;
		return (n-1-(q-fpow(q,n))*all)/all*sigc+n;
	}
}
namespace solve8{//okay
	const int N=1000010;
	int cnt[N];
	int a[N];
	inline db main(){
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j+=i){
				cnt[j]++;
			}
		}
		int mx=0;
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++){
			a[cnt[i]]++;
			apmax(mx,cnt[i]);
		}
		db ans2=0;
		for(int i=1;i<=mx;i++){
			ans2+=(db)a[i]/i;
		}
		return ans2;
		db ans=0;
		for(int i=1;i<=n;i++){
			ans+=(db)1/cnt[i];
		}
		cout<<"ans="<<ans<<"\tans2="<<ans2<<endl;
		return ans;
	}
}
namespace solve9{
	const int M=10;
	int sid[M+2][M+2];
	db f[2][184756];
	int pos[M+2];
	db ans=0;
	int npos[M+2];
	inline int getid(int pos[]){
		int id=0;
		for(int i=1;i<=M;i++){
			id+=sid[i][pos[i]]-sid[i+1][pos[i]];
		}
		return id;
	}
	db cursum=0;
	void dfs(int x,int id){//trans from f[0] to f[1]
		if(x>M){
			cursum+=f[0][id];
			assert(id==getid(pos));
			for(int i=1;i<=M;i++){
				pos[i]++;
			}
			for(int i=1;i<=M;i++){//if it is i
				memcpy(npos+1,pos+1,M*sizeof(npos[0]));
				apmin(npos[1],i);
				for(int j=1;j<M;j++){
					if(npos[j]<i){
						apmin(npos[j+1],i);
					}else break;
				}
				for(int i=1;i<=M;i++){
					npos[i]--;
				}
				f[1][getid(npos)]+=f[0][id]/10;
			}
			for(int i=1;i<=M;i++){
				pos[i]--;
			}
		}else for(int &i=pos[x]=pos[x-1];i<=M;i++){
			dfs(x+1,id+sid[x][i]-sid[x+1][i]);
		}
	}
	db g[M+2];
	void dfsans(int x,int id){//put ans to `ans`
		if(x>M){
			int i=1;
			for(;i<=10&&pos[i]<10;i++);
			--i;
			g[i]+=f[1][id];
			ans+=f[1][id]*i;
			return;
		}else for(int &i=pos[x]=pos[x-1];i<=M;i++){
			dfsans(x+1,id+sid[x][i]-sid[x+1][i]);
		}
	}
	inline db main(){
		if(n>1000)return 10;
		cout<<"new case"<<endl;
		memset(sid,0,sizeof(sid));
		for(int i=M;i>=1;i--){
			for(int j=1;j<=M;j++){
				sid[i][j]=sid[i][j-1]+sid[i+1][M]+1-sid[i+1][j-1];
			}
		}
		memset(f,0,sizeof(f));
		f[1][sid[1][M]]=1;
		for(int i=1;i<=n;i++){
			memcpy(f[0],f[1],sizeof(f[0]));
			memset(f[1],0,sizeof(f[1]));
			cursum=0;
			dfs(1,0);
			cout<<"\tnow at "<<i<<endl;
		}
		ans=0;
		dfsans(1,0);
		cout<<"n="<<n<<"\tans="<<ans<<endl;
		return ans;
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
