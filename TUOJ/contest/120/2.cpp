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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=200010,D=26,O=998244353,logN=18;
int hb[N],n;
int cnt[N],sa2[N],tmp[N];
struct SA{
	int sa[N],rnk[N],f[logN][N];
	inline bool step(int a,int b,int j){
		return sa2[a]<sa2[b]||(b+j<=n&&(a+j>n||sa2[a+j]<sa2[b+j]));
	}
	inline void main(){
		int m=D;
		mset(cnt,0,m+1);
		mcpy(tmp+1,rnk+1,n);
		for(int i=1;i<=n;i++)++cnt[rnk[i]];
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--)sa[cnt[rnk[i]]--]=i;
		m=0;
		for(int i=1,v=0;i<=n;i++){
			rnk[sa[i]]=v<rnk[sa[i]]?v=rnk[sa[i]],++m:m;
		}
		for(int j=1;m<n;j<<=1){
			for(int i=1,p=0;i<=n;i++)if(sa[i]+j>n)sa2[++p]=sa[i];
			for(int i=n,p=n;i>=1;i--)if(sa[i]>j)sa2[p--]=sa[i]-j;
			mset(cnt+1,0,m);
			for(int i=1;i<=n;i++)++cnt[rnk[i]];
			for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
			for(int i=n;i>=1;i--)sa[cnt[rnk[sa2[i]]]--]=sa2[i];
			mcpy(sa2+1,rnk+1,n);
			rnk[sa[1]]=m=1;
			for(int i=2;i<=n;i++)rnk[sa[i]]=step(sa[i-1],sa[i],j)?++m:m;
		}
		int * const hei=f[0];
		for(int i=1,j=0;i<=n;i++){
			int &k=hei[rnk[i]]=max(j-1,0);
			if(rnk[i]<n){
				int t=sa[rnk[i]+1];
				for(;i+k<=n&&t+k<=n&&tmp[i+k]==tmp[t+k];k++);
			}
			j=k;
		}
		for(int j=0;(1<<(j+1))<=n;j++){
			for(int i=1;i+(1<<(j+1))-1<=n;i++){
				f[j+1][i]=min(f[j][i],f[j][i+(1<<j)]);
			}
		}
	}
	inline int askmin(int l,int r){
		const int j=hb[r-l+1];
		return min(f[j][l],f[j][r-(1<<j)+1]);
	}
	inline int lcp(int a,int b){
		if(a==b)return n-a+1;
		a=rnk[a],b=rnk[b];
		return a<b?askmin(a,b-1):askmin(b,a-1);
	}
}forw,bakw;
char s[N];
int len[N];
bool* ban[N];
struct Trans{
	int gap,f,r;
};
vector<Trans>vec[N];
int f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%s",s+1);
	n=strlen(s+1);
	hb[0]=-1;
	for(int i=1;i<=n;i++){
		hb[i]=hb[i-1]+(i==(i&-i));
	}
	for(int i=1;i<=n;i++){
		forw.rnk[i]=bakw.rnk[n-i+1]=s[i]-'a'+1;
	}
	forw.main(),bakw.main();
	for(int i=1;i<=n;i++){
		len[i]=(n-1)/i;
		ban[i]=new bool[len[i]];
		mset(ban[i],0,len[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<len[i];j++){
			if(ban[i][j])continue;
			const int a=j*i+1,b=a+i;
			const int p1=bakw.lcp(n+1-a,n+1-b)-1;
			const int p2=forw.lcp(a,b);
			assert(p1<i);
			const int l=a-p1,r=b+p2-1;
			for(int k=l+i*2-1;k<l+i*2-1+i*2&&k<=r;k++){
				vec[k].push_back((Trans){i*2,0,r});
			}
			for(int k=i;k*2<=r-l+1;k+=i){
				for(int p=(l-1+k-1)/k;p<len[k]&&(p+1)*k+1<=r;p++){
					ban[k][p]=true;
				}
			}
		}
	}
	f[0]=1;
	int sum=1;
	for(int i=1;i<=n;i++){
		lint cur=0;
		for(vector<Trans>::iterator it=vec[i].begin(),ti=vec[i].end();it!=ti;++it){
			cur+=it->f=(it->f+f[i-it->gap])%O;
			if(i+it->gap<=it->r){
				vec[i+it->gap].push_back(*it);
			}
		}
		vec[i].clear();
		f[i]=(sum+(O-2ll)*(cur%O))%O;
		sum=(f[i]+sum)%O;
	}
	printf("%d\n",f[n]);
	return 0;
}
