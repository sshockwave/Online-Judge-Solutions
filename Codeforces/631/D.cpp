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
const int N=200010;
inline void getkmp(int n,char s[],lint c[],int fail[]){
	fail[0]=-1,fail[1]=0;
	for(int i=1,j=0;i<n;){
		if(j==-1||(s[i+1]==s[j+1]&&(c[i+1]==c[j+1]||(j==0&&c[i+1]>=c[1])))){
			fail[++i]=++j;
		}else{
			j=fail[j];
		}
	}
}
inline int readstr(int n,char s[],lint c[]){
	for(int i=1;i<=n;i++){
		scanf("%I64d-%c",c+i,s+i);
		if(s[i]==s[i-1]){
			c[i-1]+=c[i];
			i--,n--;
		}
	}
	return n;
}
char s[N],t[N];
lint cs[N],ct[N];
int fail[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
#endif
	int n=ni,m=ni;
	n=readstr(n,s,cs);
	m=readstr(m,t,ct);
	if(m==1){
		lint cnt=0;
		for(int i=1;i<=n;i++){
			if(s[i]==t[1]&&cs[i]>=ct[1]){
				cnt+=cs[i]-ct[1]+1;
			}
		}
		printf("%I64d\n",cnt);
		return 0;
	}
	getkmp(m,t,ct,fail);
	int cnt=0;
	for(int i=0,j=0;i<n;){
		if(j==m-1&&s[i+1]==t[j+1]&&cs[i+1]>=ct[j+1]){
			cnt++;
		}
		if(j==-1||(s[i+1]==t[j+1]&&(cs[i+1]==ct[j+1]||(j==0&&cs[i+1]>=ct[1])))){
			i++,j++;
		}else{
			j=fail[j];
		}
	}
	printf("%d\n",cnt);
	return 0;
}
