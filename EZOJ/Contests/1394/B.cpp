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
const int SH=6,O=998244353;
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
				a[i]+=M>>1;
			}
			r=a[i]&1;
			a[i]>>=1;
		}
		for(;as>=1&&a[as-1]==0;as--);
		return r;
	}
}lend,rend;
struct Mat{
	const static int D=(1<<::SH)+2;
	int a[D][D];
	inline void id(){
		memset(a,0,sizeof(a));
		for(int i=0;i<=statecnt;i++){
			a[i][i]=1;
		}
	}
	inline void operator = (const Mat &x){
		for(int i=0;i<=statecnt;i++){
			for(int j=0;j<=statecnt;j++){
				a[i][j]=x.a[i][j];
			}
		}
	}
	inline void gmul(const Mat &x,const Mat &y){
		for(int i=0;i<=statecnt;i++){
			for(int j=0;j<=statecnt;j++){
				lint cur=0;
				for(int k=0;k<=statecnt;k++){
					cur+=(lint)x.a[i][k]*y.a[k][j];//cout: expand maybe?
					const static lint mod=(lint)O*O;
					if(cur>mod){
						cur-=mod;
					}
				}
				a[i][j]=cur%O;
			}
		}
	}
}trans,res,tmp;
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
	inline void Main(){
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
inline void fpow(bignum &n){
	if(n.zero())return res.id();
	bool r=n.div2();
	fpow(n);
	tmp=res;
	res.gmul(tmp,tmp);
	if(r){
		tmp=res;
		res.gmul(tmp,trans);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("decoration.in","r",stdin);
	freopen("decoration.out","w",stdout);
#endif
	lend.input(),rend.input();
	prob::Main();
	fpow(lend);
	int a=res.a[statecnt][0];
	fpow(rend);
	int b=(res.a[0][0]+res.a[statecnt][0])%O;
	printf("%d\n",(b+O-a)%O);
	return 0;
}
