#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
const int SH=6,O=998244353;
inline int fpow(int x,int n){
	int a=1;
	for(;n;n>>=1,x=(lint)x*x%O){
		if(n&1){
			a=(lint)a*x%O;
		}
	}
	return a;
}
inline int inv(int x){
	return fpow(x,O-2);
}
int statecnt;
struct bignum{
	const static int N=2600,D=N/9,M=1000000000;
	int a[D],as;
	inline void input(){
		static char s[N];
		scanf("%s",s);
		int i=strlen(s)-1;
		as=1;
		memset(a,0,sizeof(a));
		for(int j=1;i>=0;i--){
			a[as-1]+=j*(s[i]-'0');
			j*=10;
			if(j==M){
				as++,j=1;
			}
		}
	}
	inline bool zero(){
		return as==0;
	}
	inline bool div2(){
		bool r=false;
		for(int i=as-1;i>=0;i--){
			if(r){
				a[i]+=M;
			}
			r=a[i]&1;
			a[i]>>=1;
		}
		for(;as>=1&&a[as-1]==0;as--);
		return r;
	}
}lend,rend;
struct Mat{
	const static int D=37;
	int a[D][D];
	inline int det(){
		lint d=1;
		const static int &n=statecnt;
		for(int i=0;i<=n;i++){
			int j=i;
			for(;j<=n&&a[j][i]==0;j++);
			if(j>n)return 0;
			if(i!=j){
				d=O-d;
				for(int k=i;k<=n;k++){
					swap(a[i][k],a[j][k]);
				}
			}
			d=d*a[i][i]%O;
			lint r=inv(a[i][i]);
			for(int k=i;k<=n;k++){
				a[i][k]=r*a[i][k]%O;
			}
			for(j=i+1;j<=n;j++){
				if(a[j][i]==0)continue;
				r=O-a[j][i];
				for(int k=i;k<=n;k++){
					a[j][k]=(a[j][k]+(lint)r*a[i][k])%O;
				}
			}
		}
		return d;
	}
}trans;
struct Vec{
	const static int D=37;
	int a[D];
	inline void clr(){
		memset(a,0,sizeof(a));
	}
	inline void gmul(const Mat &x,const Vec &y){
		const int &n=statecnt;
		for(int i=0;i<=n;i++){
			lint cur=0;
			for(int j=0;j<=n;j++){
				cur+=(lint)x.a[i][j]*y.a[j];
				const static lint OO=(lint)O*O;
				if(cur>=OO){
					cur-=OO;
				}
			}
			a[i]=cur%O;
		}
	}
};
namespace poly{
	const int N=43;
	int x[N],y[N],f[N],n;
	int tmpf[N];
	inline void interpol(){
		for(int i=1;i<=n;i++){
			if(y[i]==0)continue;
			int ds=0;
			lint c=1;
			tmpf[0]=1;
			for(int j=1;j<=n&&c;j++){
				if(i==j)continue;
				for(int k=++ds;k>=0;k--){
					lint cur=0;
					if(k<ds){
						cur=-(lint)tmpf[k]*x[j];
					}
					if(k){
						cur+=tmpf[k-1];
					}
					tmpf[k]=(cur%O+O)%O;
				}
				c=c*(x[i]-x[j])%O;
			}
			if(c){
				c=(lint)inv((c+O)%O)*y[i]%O;
				for(int j=0;j<=ds;j++){
					f[j]=(f[j]+tmpf[j]*c)%O;
				}
			}
		}
	}
	Mat mat;
	inline void genmat(int lam){
		for(int i=0;i<=statecnt;i++){
			for(int j=0;j<=statecnt;j++){
				mat.a[i][j]=(O-trans.a[i][j])%O;
				if(i==j){
					mat.a[i][j]=(mat.a[i][j]+lam)%O;
				}
			}
		}
	}
	inline void main(){
		n=statecnt+2;
		for(int i=1;i<=n;i++){
			genmat(i);
			x[i]=i,y[i]=mat.det();
		}
		interpol();
		for(;n>=1&&f[n-1]==0;n--);
		assert(n>0);
		if(f[n-1]!=1){
			lint r=inv(f[n-1]);
			for(int i=0;i<n;i++){
				f[i]=f[i]*r%O;
			}
		}
	}
	int res[N],tmp[N<<1];
	inline void modtmp(int i){
		for(;i>=n-1;i--){
			if(tmp[i]==0)continue;
			lint r=(O-tmp[i])%O;
			for(int j=0;j<n;j++){
				tmp[i-j]=(tmp[i-j]+f[n-j-1]*r)%O;
			}
		}
	}
	inline void fpow(bignum &e){
		if(e.zero()){
			memset(res,0,n<<2);
			res[0]=1;
			return;
		}
		bool r=e.div2();
		fpow(e);
		memset(tmp,0,n<<3);
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				tmp[i+j]=(tmp[i+j]+(lint)res[i]*res[j])%O;
			}
		}
		modtmp(n*2-2),memcpy(res,tmp,n<<2);
		if(r){
			for(int i=n;i>=1;i--){
				tmp[i]=res[i-1];
			}
			tmp[0]=0;
			modtmp(n),memcpy(res,tmp,n<<2);
		}
	}
	inline int gpow(bignum &e){
		fpow(e);
		Vec a;
		a.clr();
		a.a[0]=1;
		lint cur=0;
		for(int i=0;i<n;i++){
			cur+=(lint)a.a[statecnt]*res[i]%O;
			Vec tmp;
			tmp.gmul(trans,a);
			a=tmp;
		}
		return cur%O;
	}
}
namespace prob{
	const int N=1<<SH;
	lint trans[N][N];
	int rep[N];
	bool self[N];
	int s1,s2;
	int rev[N];
	void dfs(int x,int s,bool sd,int curs,int curf){
		if(x<0){
			if(sd)return;
			trans[s][curs]+=curf;
			return;
		}
		if(sd){
			if((s>>x)&1)return;
			return dfs(x-1,s,0,curs,curf);
		}
		if((s>>x)&1)return dfs(x-1,s,0,curs,curf);
		dfs(x-1,s,1,curs,(lint)curf*s2%O);//go right
		dfs(x-1,s,0,curs|(1<<x),(lint)curf*s1%O);//go down
	}
	inline void main(){
		int n=ni;
		s1=ni,s2=ni;
		memset(trans,0,sizeof(trans));
		int ts=1<<n;
		for(int s=0;s<ts;s++){
			dfs(n-1,s,0,0,1);
		}
		rev[0]=0;
		for(int i=1;i<ts;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(n-1));
		}
		memset(rep,-1,sizeof(rep));
		statecnt=0;
		for(int i=0;i<ts;i++){
			if(rep[rev[i]]==-1){
				self[i]=true,rep[i]=statecnt++;
			}else{
				self[i]=false,rep[i]=rep[rev[i]];
			}
		}
		memset(&::trans,0,sizeof(::trans));
		for(int i=0;i<ts;i++){
			if(!self[i])continue;
			for(int j=0;j<ts;j++){
				int &f=::trans.a[rep[j]][rep[i]];
				f=(f+trans[i][j])%O;
			}
		}
		::trans.a[statecnt][0]=::trans.a[statecnt][statecnt]=1;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("decoration.in","r",stdin);
	freopen("decoration.out","w",stdout);
#endif
	lend.input(),rend.input();
	prob::main();
	poly::main();
	rend.a[0]++;
	printf("%d\n",(poly::gpow(rend)-poly::gpow(lend)+O)%O);
	return 0;
}
