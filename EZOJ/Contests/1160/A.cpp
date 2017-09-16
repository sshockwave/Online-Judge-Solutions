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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=1000010;
char s[N];
int pre[N],stk[N],mch[N];
#define INC 'p'
#define DEC 'j'
inline int bchop(int l,int r,int v){
	while(l<r){
		int m=(l+r)>>1;
		if(stk[m]>v){
			l=m+1;
		}else{
			r=m;
		}
	}
	return l;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("bar.in","r",stdin);
	freopen("bar.out","w",stdout);
#endif
	int n=ni,ss=0,ans=0;
	scanf("%s",s+1);
	for(int i=1;i<=n;i++){
		if(s[i]==INC){
			stk[ss++]=i;
			pre[i]=pre[i-1]+1;
		}else if(ss){
			ss--;
			mch[stk[ss]]=i;
			pre[i]=pre[i-1]-1;
		}
	}
	for(;ss;mch[stk[--ss]]=n);
	for(int i=n;i>=1;i--){
		if(s[i]==INC){
			if(s[mch[i]]==DEC&&s[mch[i]+1]==INC){
				mch[i]=mch[mch[i]+1];
			}
			stk[ss++]=i;
			apmax(ans,stk[bchop(0,ss-1,mch[i])]-i+1);
		}else for(;ss&&pre[stk[ss-1]]<pre[i-1];ss--);
	}
	printf("%d\n",ans);
	return 0;
}
