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
const int N=1000010,MOD=1000000007;
inline int add(const int &a,const int &b){
	return (a+b)%MOD;
}
inline int sub(const int &a,const int &b){
	return add(a,MOD-b);
}
inline int mul(const int &a,const int &b){
	return a*b%MOD;
}
char s[N];
int fail[N],nxt[N],f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
#endif
	scanf("%s",s+1);
	fail[1]=0;
	for(int i=1,j=0;s[i];){
		if(j==0||s[i]==s[j]){
			fail[++i]=++j;
		}else{
			j=fail[j];
		}
	}
	f[0]=0;
	for(int i=1;s[i];i++){
		nxt[i]=s[fail[i]]==s[i]?nxt[fail[i]]:fail[i];
		f[i]=sub(mul(2,f[i-1]+1),f[nxt[i]]);
	}
	printf("%d\n",f[strlen(s+1)]);
	return 0;
}
