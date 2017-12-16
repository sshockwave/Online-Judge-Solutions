#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <string>
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
const int N=23000010,O=998244353,INF=0x7f7f7f7f;
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
int fac[N],invfac[N];
inline int C(int n,int k){
	return (lint)fac[n]*invfac[k]%O*invfac[n-k]%O;
}
inline void gmath(int n){
	fac[0]=1;
	for(int i=1;i<=n;i++){
		fac[i]=(lint)fac[i-1]*i%O;
	}
	invfac[n]=inv(fac[n]);
	for(int i=n;i>=1;i--){
		invfac[i-1]=(lint)invfac[i]*i%O;
	}
}
map<string,int>f;
int dfs(string s){
	if(f.find(s)!=f.end())return f[s];
	int fl=INF,fr=INF;
	int i=0,j;
	for(;s[i]!='_';i++);
	for(j=i;j>=0&&i-j<=2&&s[j]!='L';j--);
	if(j>=0&&i-j<=2){
		swap(s[i],s[j]);
		fl=dfs(s);
		swap(s[i],s[j]);
	}
	for(j=i;j<5&&j-i<=2&&s[j]!='R';j++);
	if(j<5&&j-i<=2){
		swap(s[i],s[j]);
		fr=dfs(s);
		swap(s[i],s[j]);
	}
	int ans;
	if(fl==INF&&fr==INF){
		ans=0;
	}else if(fl==INF){
		ans=fr>0?0:-2;
	}else if(fr==INF){
		ans=fl<0?0:+2;
	}else{
		ans=(fl+fr)/2;
	}
	return f[s]=ans;
}
int res[5];
inline void gpseudo(int a,int b){//1 -1
	res[1]=b?(lint)fac[a+b]*invfac[a+1]%O*invfac[b-1]%O:0;
	res[2]=(lint)fac[a+b]*invfac[a]%O*invfac[b]%O;
	res[3]=a?(lint)fac[a+b]*invfac[a-1]%O*invfac[b+1]%O:0;
	lint tmp=0;
	for(int i=0,j=0;i<=a;i++){
		tmp+=(lint)j*C(a,i)%O;
		if(i<=b){
			(j+=C(b,i))%=O;
		}
	}
	res[4]=tmp%O;
	res[0]=((lint)fpow(2,a+b)+O-res[4]+O-res[2])%O;
	(res[0]+=O-res[1])%=O;
	(res[4]+=O-res[3])%=O;
}
inline void greal(int a,int b,int c,int d){//-2 -1 0 1 2
	static int *f=new int[N<<1]+N;//diff of b,c
	f[-b-1]=0;
	for(int i=-b;i<=c;i++){
		f[i]=(C(b+c,b+i)+f[i-1])%O;
	}
	lint neg=0,pos=0;
	for(int i=-a;i<=d;i++){//2(a+d)==2i
		lint tmp=C(a+d,a+i);
		//+2i<0 => <-2i
		if(-2*i-1>=-b){
			neg+=tmp*f[min(-2*i-1,c)]%O;
		}
		//+2i>0 => >-2i
		if(-2*i<=c){
			pos+=tmp*(f[c]-f[max(-2*i,-b-1)]+O)%O;
		}
	}
	res[0]=neg%O;
	res[2]=pos%O;
	res[1]=((lint)fpow(2,a+b+c+d)+O-res[0]+O-res[2])%O;
}
inline void Main(){
	int cnt[8],tmp;
	memset(cnt,0,sizeof(cnt));
	for(int tot=ni;tot--;){
		static char s[10];
		scanf("%s",s);
		cnt[f[s]+2]+=ni;
	}
	lint ans[4]={0,0,0,0};
	greal(cnt[0],cnt[1],cnt[3],cnt[4]);
	//sum!=0:
	tmp=fpow(2,cnt[2]+cnt[5]+cnt[6]+cnt[7]);
	ans[0]=(lint)res[2]*tmp%O;
	ans[1]=(lint)res[0]*tmp%O;
	//sum=0:
	lint same=(lint)res[1]*fpow(2,cnt[2])%O;
	gpseudo(cnt[6],cnt[7]);
	int c0,c1;
	if(cnt[5]){
		c0=c1=fpow(2,cnt[5]-1);
	}else{
		c0=1,c1=0;
	}
	//*==0:|up-down|==0
	tmp=same*c0%O;
	ans[0]+=(lint)((res[3]+res[4])%O)*tmp%O;
	ans[1]+=(lint)((res[0]+res[1])%O)*tmp%O;
	ans[3]=(lint)res[2]*tmp%O;
	//*!=0:|up-down|<=1;
	tmp=same*c1%O;
	ans[0]+=(lint)res[4]*tmp%O;
	ans[1]+=(lint)res[0]*tmp%O;
	ans[2]=((lint)res[1]+res[2]+res[3])%O*tmp%O;
	for(int i=0;i<4;i++){
		printf("%lld ",ans[i]%O);
	}
	putchar('\n');
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("frogs.in","r",stdin);
	freopen("frogs.out","w",stdout);
#endif
	dfs("LL_RR");
	f["LL_RR"]=3;
	f["L_LRR"]=4;
	f["LLR_R"]=5;
	f["LRL_R"]=3;
	f["L_RLR"]=3;
	gmath(N-1);
	ni;
	for(int tot=ni;tot--;Main());
	return 0;
}
