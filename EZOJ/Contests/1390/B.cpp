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
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=1010,D=26,O=1000000007;
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
int n;
char s[N<<1];
namespace ex_kmp{
	const int N=::N<<1;
	int bor[N];
	inline void Main(int n){
		for(int i=2,j=0;i<=n;i++){
			bor[i]=i<j+bor[j]?min(bor[i-j+1],j+bor[j]-i):0;
			for(;s[1+bor[i]]==s[i+bor[i]];bor[i]++);
			if(i+bor[i]>j+bor[j]){
				j=i;
			}
		}
	}
	inline void work(){
		memcpy(s+n+1,s+1,n);
		Main(n<<1);
		int pos=n*2+1;//change i
		for(int i=n;i>=2;i--){
			apmin(bor[i],n);
			if(pos<i+bor[i]||s[i+bor[i]]-(pos==i+bor[i])<s[1+bor[i]]){
				pos=i-1;
			}
		}
		if(pos<n){
			assert(s[pos]>'a');
			s[pos]--,memset(s+pos+1,'z',n-pos);
		}
		s[n+1]=0;
	}
}
namespace dp{
	int f[N][N];//f[len][from state]
	inline void Main(){
		f[0][0]=1,memset(f[0]+1,0,n*sizeof(f[0][0]));
		for(int i=1;i<=n;i++){//len
			for(int j=0;j<=n-i;j++){//from state
				f[i][j]=((lint)f[i-1][0]*('z'-s[j+1])+f[i-1][j+1])%O;
			}
		}
	}
}
namespace kmp{
	int fail[N],go[N][D];
	inline void Main(){
		fail[0]=-1,fail[1]=0;
		memset(go[0],0,sizeof(go[0]));
		go[0][s[1]-'a']=1;
		for(int i=1,j=0;i<n;){
			if(j==-1||s[i+1]==s[j+1]){
				memcpy(go[i],go[fail[i]],sizeof(go[i]));
				go[i][s[i+1]-'a']=i+1;
				fail[++i]=++j;
			}else{
				j=fail[j];
			}
		}
	}
}
inline int work(int n){
	lint ans=0,w=1;
	using dp::f;
	for(int i=n;i>=1;i--,w=w*D%O){//pos of r
		lint cur=0;
		for(int j=0;j<i;j++){
			cur+=(lint)f[j][0]*(s[i-j]-'a');
		}
		ans+=cur%O*w%O;
	}
	for(int i=1;i<n;i++){//val of k
		using kmp::go;
		for(int j=0,k=0;i+j<n;j++,k=go[k][s[i+j]-'a']){//m=i+j
			if(s[k+1]<s[i+j+1]){
				assert(k<n);
				ans+=f[n-i-j-1][k+1];
				ans+=(lint)f[n-i-j-1][0]*(s[i+j+1]-s[k+1]-1);
			}
		}
	}
	using kmp::fail;
	ans+=n%(n-fail[n])==0?n-fail[n]:n;
	return ans%O;
}
int f[N];
inline int Main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	ex_kmp::work();
	dp::Main(),kmp::Main();
	for(int i=1;i<=n;i++){
		if(n%i==0){
			f[i]=work(i);
		}
	}
	lint ans=0;
	for(int i=1;i<=n;i++){
		ans+=f[gcd(i,n)];
	}
	return ans%O*inv(n)%O;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
