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
const int N=200010,D=26;
char s[N];
int ext[N];
struct ccnt{
	lint cnt[26];
	inline void operator += (const ccnt &b){
		for(int i=0;i<D;i++){
			cnt[i]+=b.cnt[i];
		}
	}
}_cnt[N],f[N];
lint g[N];
inline ccnt work(lint x){
	assert(x>=0);
	if(x<=g[1]){
		return _cnt[x];
	}
	int t=0;
	for(;g[t]<=x;t++);
	assert(t);
	ccnt ans=f[t-1];
	ans+=work(x-g[t-1]);
	return ans;
}
int main(){
	scanf("%s",s+1);
	int n=strlen(s+1)>>1;
	s[n+1]=0;
	memset(ext,0,sizeof(ext));
	for(int i=2,j=0;i<=n+1;i++){
		ext[i]=max(min(ext[i-j+1],j+ext[j]-i),0);
		for(;s[1+ext[i]]==s[i+ext[i]];ext[i]++);
		if(i+ext[i]>j+ext[j]){
			j=i;
			if(i+ext[i]>n){
				g[0]=i-1;
				break;
			}
		}
	}
	memset(_cnt,0,sizeof(_cnt[0]));
	for(int i=1;i<=n;i++){
		_cnt[i]=_cnt[i-1];
		_cnt[i].cnt[s[i]-'a']++;
	}
	f[0]=_cnt[g[0]];
	g[1]=n,f[1]=_cnt[n];
	lint l=next_num<lint>(),r=next_num<lint>();
	for(int i=2;g[i-1]<=r;i++){
		g[i]=g[i-1]+g[i-2];
		f[i]=f[i-1];
		f[i]+=f[i-2];
	}
	ccnt ansl=work(l-1),ansr=work(r);
	for(int i=0;i<D;i++){
		printf("%lld ",ansr.cnt[i]-ansl.cnt[i]);
	}
	putchar('\n');
	return 0;
}
