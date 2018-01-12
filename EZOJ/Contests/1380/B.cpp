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
const int N=2510,O=998244353;
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
namespace poly{
	const int SH=13,N=1<<SH;
	int sh,n,invn;
	int o[SH][N>>1],io[SH][N>>1];
	inline void init(int _n){
		for(sh=0;(1<<sh)<_n;sh++);
		n=1<<sh,invn=inv(n);
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			lint wn=fpow(3,(O-1)/full),iwn=inv(wn);
			for(int j=0,w=1,iw=1;j<half;j++,w=w*wn%O,iw=iw*iwn%O){
				o[i][j]=w,io[i][j]=iw;
			}
		}
	}
	int rev[N]={0};
	inline void ntt(int a[],int d=1){
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sh-1));
			if(i<rev[i]){
				swap(a[i],a[rev[i]]);
			}
		}
		for(int i=0;i<sh;i++){
			int half=1<<i,full=half<<1;
			for(int j=0;j<half;j++){
				lint w=(d==1?o:io)[i][j];
				for(int k=j;k<n;k+=full){
					int p=a[k],q=a[k+half]*w%O;
					a[k]=(p+q)%O;
					a[k+half]=(p+O-q)%O;
				}
			}
		}
		if(d==-1){
			for(int i=0;i<n;i++){
				a[i]=(lint)a[i]*invn%O;
			}
		}
	}
}
struct Mat{
	const static int D=8;
	int a[D][D];
	inline void clr(){
		memset(a,0,sizeof(a));
	}
	inline void gmul(const Mat &x,const Mat &y){
		for(int i=0;i<D;i++){
			for(int j=0;j<D;j++){
				lint ans=0;
				for(int k=0;k<D;k++){
					ans+=(lint)x.a[i][k]*y.a[k][j]%O;
				}
				a[i][j]=ans%O;
			}
		}
	}
	inline void id(){
		clr();
		for(int i=0;i<D;i++){
			a[i][i]=1;
		}
	}
}trans;
void fpow(Mat &m,int n){
	static Mat base,tmp;
	if(n==0){
		base=m;
		m.id();
		return;
	}
	fpow(m,n>>1);
	tmp.gmul(m,m),m=tmp;
	if(n&1){
		tmp.gmul(m,base),m=tmp;
	}
}
int mp[6];
int bitcnt[8]={0};
inline void gtrans(int w){
	static int pw[4]={1};
	for(int i=1;i<4;i++){
		pw[i]=(lint)pw[i-1]*w%O;
	}
	for(int s=0;s<8;s++){
		int ban=0;
		for(int k=0;k<3;k++){
			if((s>>k)&1){
				ban|=mp[k+3];
			}
		}
		for(int ts=0;ts<8;ts++){
			bool flag=true;
			int curs=s,curban=ban;
			for(int k=0;k<3;k++){
				if((ts>>k)&1){
					if(((curban>>(k+3))&1)||(mp[k]&curs)){
						flag=false;
						break;
					}
					curban|=mp[k];
					curs|=1<<(k+3);
				}
			}
			trans.a[ts][s]=flag?pw[bitcnt[ts]]:0;
		}
	}
}
int f[poly::N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("final.in","r",stdin);
	freopen("final.out","w",stdout);
#endif
	int n=ni,m=ni;
	if(m>n*3){
		puts("0");
		return 0;
	}
	int mask=0;
	for(int i=0;i<9;i++){
		mask|=ni<<i;
	}
	for(int s=1;s<8;s++){
		bitcnt[s]=bitcnt[s^(s&-s)]+1;
	}
	for(int i=0;i<6;i++){
		int x=i/3,y=i%3;
		int line[]={mask&7,(mask>>3)&7,(mask>>6)&7};
		if(y<=1){
			mp[i]=(line[x]>>(1-y))|((line[x+1]>>(1-y))<<3);
		}else{
			mp[i]=((line[x]<<1)&7)|(((line[x+1]<<1)&7)<<3);
		}
	}
	poly::init(n*3+1);
	for(int i=0,w=1,wn=fpow(3,(O-1)>>poly::sh);i<poly::n;i++,w=(lint)w*wn%O){
		gtrans(w);
		fpow(trans,n);
		lint ans=0;
		for(int j=0;j<Mat::D;j++){
			ans+=trans.a[j][0];
		}
		f[i]=ans%O;
	}
	poly::ntt(f,-1);
	printf("%d\n",f[m]);
	return 0;
}
