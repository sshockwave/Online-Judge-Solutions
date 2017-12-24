#include <iostream>
#include <cstdio>
#include <cstring>
#define NDEBUG
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
template<class T>inline T sqr(const T &x){return x*x;}
const int N=110,K=90,O=1000000007;
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
int n,tot;
lint f[2][N][5];
struct trans{
	int j,k,mul;
}pool[N*5*81],*ps,*vec[N][5],*endd[N][5];
inline void puttrans(int j1,int k1,int j2,int k2,int mul){
	trans* &head=vec[j1][k1];
	for(trans* i=head;i<ps;i++){
		if(i->j==j2&&i->k==k2){
			i->mul+=mul;
			return;
		}
	}
	*ps++=(trans){j2,k2,mul};
}
int cnt[9];
inline int putcnt(int x,int pos,int i,int j){
	int pos2;
	memset(cnt,0,sizeof(cnt));
	cnt[0]=pos-1-i,cnt[1]=i;
	cnt[7]=n-x-i,cnt[6]=n-pos-cnt[7];
	if(j==4){
		cnt[pos2=5]=1;
	}else{
		cnt[3+(j&1)]=1;
		cnt[pos2=(j>>1)*6+2]=1;
		if(j<2){
			if(j&1){
				if(cnt[7]==0||cnt[0]==0)return -1;
				cnt[7]--,cnt[0]--,cnt[6]++;
			}else{
				if(cnt[0]==0)return -1;
				cnt[0]--;
			}
		}else{
			if(j&1){
				if(cnt[7]==0)return -1;
				cnt[7]--;
			}else{
				if(cnt[6]==0)return -1;
				cnt[6]--;
			}
		}
	}
	return pos2;
}
int dp(int x,int pos){
	int frj=max(pos-x,0),toj=min(pos-1,n-x);
	ps=pool;
	for(int i=frj;i<=toj;i++){
		for(int j=0;j<5;j++){
			vec[i][j]=ps;
			int pos2=putcnt(x,pos,i,j);
			if(pos2==-1){
				endd[i][j]=ps;
				continue;
			}
			for(int a=0;a<9;a++){
				if(cnt[a]){
					assert(cnt[a]>0);
					for(int b=0;b<9;b++){
						if(cnt[b]){
							assert(cnt[b]>0);
							int ma=a%3,mb=b%3;
							int ta=b-mb+ma,tb=a-ma+mb;
							int npos=ma==2?ta:mb==2?tb:pos2;
							int mul=cnt[a]*cnt[b];
							cnt[a]--,cnt[ta]++;
							cnt[b]--,cnt[tb]++;
							puttrans(i,j,cnt[1],npos==5?4:((npos>3)<<1)|cnt[4],mul);
							cnt[a]++,cnt[ta]--;
							cnt[b]++,cnt[tb]--;
						}
					}
				}
			}
			endd[i][j]=ps;
		}
	}
	bool r=0;
	int memsize=sizeof(f[!r][0])*(toj-frj+1);
	for(int i=1;i<=tot;i++,r=!r){
		memset(f[!r]+frj,0,memsize);
		for(int j=frj;j<=toj;j++){
			for(int k=0;k<5;k++){
				lint F=f[r][j][k];
				if(F==0)continue;
				F%=O;
				for(trans* i=vec[j][k];i<endd[j][k];i++){
					f[!r][i->j][i->k]+=F*i->mul;
				}
			}
		}
	}
	return f[r][0][4]%O;
}
int a[N],pos[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
#endif
	n=ni,tot=ni;
	for(int i=1;i<=n;i++){
		pos[a[i]=ni]=i;
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		int cnt=0;
		for(int j=1;j<=i;j++){//i at pos j
			int stat;
			if(pos[i]==j){
				stat=4;
			}else if(pos[i]<j){
				if(a[j]<i){
					stat=0;
				}else{
					stat=1;
				}
			}else{
				if(a[j]<i){
					stat=2;
				}else{
					stat=3;
				}
			}
			memset(f[0],0,sizeof(f[0][0])*n);
			f[0][cnt][stat]=1;
			ans+=dp(i,j);
			cnt+=a[j]>i;
		}
	}
	printf("%lld\n",ans%O*fpow(inv(n),tot<<1)%O);
	return 0;
}
