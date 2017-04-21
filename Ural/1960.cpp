#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<typename T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=100010,MOD=1000000007,SIGMA=26;
inline int add(int a,int b){
	return (a+b)%MOD;
}
inline void apadd(int &a,const int &b){
	a=add(a,b);
}
struct PAM{
	int lnk[N],len[N],cnt[N],go[N][SIGMA],s[N],pool,tail,n;
	PAM(){
		memset(lnk,0,sizeof(lnk));
		memset(len,0,sizeof(len));
		memset(cnt,0,sizeof(cnt));
		lnk[0]=1,len[1]=s[0]=-1,n=tail=0,pool=2;
	}
	inline int nn(int val){
		len[pool]=val;
		return pool++;
	}
	inline int fail(int p){
		for(;s[n]!=s[n-len[p]-1];p=lnk[p]);
		return p;
	}
	inline void add(int c){
		s[++n]=c;
		tail=fail(tail);
		if(go[tail][c]==0){
			int p=nn(len[tail]+2);
			lnk[p]=go[fail(lnk[tail])][c];
			go[tail][c]=p;
		}
		tail=go[tail][c];
		cnt[tail]++;
	}
	inline int size(){
		return pool-2;
	}
}pam;
char s[N];
int main(){
	scanf("%s",s);
	for(int i=0;s[i];i++){
		pam.add(s[i]-'a');
		printf("%d ",pam.size());
	}
}
