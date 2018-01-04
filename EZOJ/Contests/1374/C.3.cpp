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
const int N=1000000;
char s[N];
bool bit[N];
struct way{
	lint cnt;
	int prestate;
	int op;
	inline friend bool operator < (const way &a,const way &b){
		return a.cnt<b.cnt;
	}
}f[N][2];
int main(){
#ifndef ONLINE_JUDGE
	freopen("num3.tmp","r",stdin);
	freopen("num3.out","w",stdout);
#endif
	scanf("%s",s);
	int n=strlen(s);
	for(int i=1;i<=n;i++){
		bit[i]=s[n-i]-'0';
	}
	memset(f,127,sizeof(f));
	f[0][0].cnt=0;
	for(int i=1;i<=n+1;i++){
		if(bit[i]){
			f[i][0]=(way){f[i-1][0].cnt+1,0,1};
			f[i][1]=min((way){f[i-1][1].cnt,1,0},(way){f[i-1][0].cnt+1,0,-1});
		}else{
			f[i][0]=min((way){f[i-1][0].cnt,0,0},(way){f[i-1][1].cnt+1,1,1});
			f[i][1]=(way){f[i-1][1].cnt+1,1,-1};
		}
	}
	cout<<"ans="<<f[n+1][0].cnt<<endl;
	printf("%lld\n",f[n+1][0].cnt);
	int curstate=0;
	for(int i=n+1;i>=1;i--){
		if(f[i][curstate].op>0){
			printf("%d\n",i);
		}else if(f[i][curstate].op<0){
			printf("%d\n",-i);
		}
		curstate=f[i][curstate].prestate;
	}
	return 0;
}
