#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=2010,INF=0x7f7f7f7f;
char a[N],b[N];
int n,ans=INF;
struct pii{
	int a,b;
	inline friend bool operator < (const pii &x,const pii &y){
		return x.a!=y.a?x.a<y.a:x.b<y.b;
	}
}ext[N];
int cnt[N];
int pre[N],nxt[N];
inline void work(){
	if(b[0]=='1'){
		pre[0]=0;
	}else for(int &i=pre[0]=1;b[n-i]=='0';i++);
	for(int i=1;i<n;i++){
		pre[i]=b[i]=='1'?0:pre[i-1]+1;
	}
	if(b[n-1]=='1'){
		nxt[n-1]=0;
	}else for(int &i=nxt[n-1]=1;b[i-1]=='0';i++);
	for(int i=n-2;i>=0;i--){
		nxt[i]=b[i]=='1'?0:nxt[i+1]+1;
	}
	for(int sh=0;sh<n;sh++){//a[i]->a[i+sh]
		int diff=0,ps=0;
		memset(cnt,0,n<<2);
		for(int i=0;i<n;i++){
			if(a[i]!=b[(i+sh)%n]){
				diff++;
				int l=pre[i],r=nxt[i];
				if(r<=sh)continue;
				ext[ps++]=(pii){l,r-sh};
				cnt[r-sh]++;
			}
		}
		sort(ext,ext+ps);
		int p=n-1;
		for(;p>0&&cnt[p]==0;p--);
		apmin(ans,sh+(p<<1)+diff);
		for(int i=0;i<ps;i++){
			cnt[ext[i].b]--;
			for(;p>0&&cnt[p]==0;p--);
			apmin(ans,sh+((ext[i].a+p)<<1)+diff);
		}
	}
}
inline int Main(){
	scanf("%s%s",a,b);
	n=strlen(a);
	bool same=true,one=false;
	for(int i=0;i<n;i++){
		same&=a[i]==b[i];
		one|=b[i]=='1';
	}
	if(same)return 0;
	if(!one)return -1;
	work();
	reverse(a,a+n);
	reverse(b,b+n);
	work();
	return ans;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
