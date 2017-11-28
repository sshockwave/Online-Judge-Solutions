#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <cstdlib>
#include <algorithm>
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
const lint LINF=10000000010ll;
inline lint mul(lint a,lint b,lint O){
	const static int one=(1<<20)-1;
	return (a*(b>>20)%O*(1<<20)%O+a*(b&one)%O)%O;
}
inline lint sqr(lint x,lint O){
	return mul(x,x,O);
}
inline lint gcd(lint a,lint b){
	return b?gcd(b,a%b):a;
}
inline lint fpow(lint x,lint n,lint O){
	lint ans=1;
	for(;n;n>>=1,x=sqr(x,O)){
		if(n&1){
			ans=mul(ans,x,O);
		}
	}
	return ans;
}
int mnp[N],prime[N],ps=0;
bool isp[N];
inline void gmath(int n){
	memset(isp,true,sizeof(isp));
	for(int i=2;i<=n;i++){
		if(isp[i]){
			prime[ps++]=i;
			mnp[i]=i;
		}
		for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
			isp[i*cur]=false;
			mnp[i*cur]=cur;
			if(i%cur==0)break;
		}
	}
}
inline bool miller_rabin(lint O){
	const static int a[]={2,3,5,7,11};
	lint t=O-1;
	int cnt2=0;
	for(;(t&1)==0;t>>=1,cnt2++);
	for(int i=0;i<5;i++){
		lint w=fpow(a[i],t,O);
		bool isp=w==1;
		for(int j=0;!isp&&j<cnt2;j++,w=sqr(w,O)){
			isp=w==O-1;
		}
		if(!isp)return false;
	}
	return true;
}
lint fact[N];
int fs;
void factorize(lint O){
	if(O<N){
		for(;O!=1;fact[fs++]=mnp[O],O/=mnp[O]);
		return;
	}
	if(miller_rabin(O)){
		fact[fs++]=O;
		return;
	}
	//pollard-rho
	lint x1=rand()%O,x2=x1,c=2;
	lint d;
	do{
		x1=(sqr((sqr(x1,O)+c)%O,O)+c)%O;
		x2=(sqr(x2,O)+c)%O;
		if(x1==x2)return factorize(O);
	}while(d=gcd((x2-x1+O)%O,O),d==1);
	assert(d<O&&O%d==0);
	factorize(d),factorize(O/d);
}
lint a[N];
map<lint,lint>m;
int main(){
	gmath(N-1);
	int n=ni;
	int ans=0;
	for(int i=1;i<=n;i++){
		fs=0,factorize(next_num<lint>());
		sort(fact,fact+fs);
		a[i]=1;
		lint b=1;
		bool flag=true;
		for(int j=0,k=0;j<fs;j=k){
			for(;k<fs&&fact[j]==fact[k];k++);
			if(fact[j]>1000000ll){
				flag=false,i--,n--,ans++;
				break;
			}
			int tmp=(k-j)%3;
			if(tmp){
				a[i]*=tmp==1?fact[j]:fact[j]*fact[j];
				b*=fact[j];
				if(b>LINF){
					flag=false,i--,n--,ans++;
					break;
				}
				if(tmp==1){
					b*=fact[j];
					if(b>LINF){
						flag=false,i--,n--,ans++;
						break;
					}
				}
			}
		}
		if(flag){
			m[a[i]]=b;
		}
	}
	sort(a+1,a+n+1);
	for(int i=1,j=1;i<=n;i=j){
		for(;j<=n&&a[i]==a[j];j++);
		lint b=m[a[i]];
		if(a[i]==b){
			ans++;
		}else{
			lint* l=lower_bound(a+1,a+n+1,b);
			lint* r=lower_bound(a+1,a+n+1,b+1);
			if(l==r){
				ans+=j-i;
			}else if(a+i<l){
				ans+=max((int)(j-i),(int)(r-l));
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
