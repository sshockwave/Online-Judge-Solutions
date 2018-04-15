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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline T cabs(const T &x){return x>=0?x:-x;}
const int N=100,L=1000010,INF=0x7f7f7f7f;
int f[N][20];
inline int work(const char s[],const char t[],const int lens,const int lent){
	if(cabs(lens-lent)>8)return 0;
	memset(f[0],127,sizeof(f[0]));
	f[0][8]=0;
	for(int i=0;i<lens;i++){
		memset(f[i+1],127,sizeof(f[i+1]));
		bool flag=false;
		for(int j=max(0,8-i),tj=min(16,lent-i+8);j<=tj;j++){
			int F=f[i][j];
			if(F>8)continue;
			flag=true;
			int a=i,b=i+j-8;
			if(a<lens&&b<lent){//match
				apmin(f[i+1][j],F+(s[a+1]!=t[b+1]));
			}
			if(b<lent&&j<16){//add char
				apmin(f[i][j+1],F+1);
			}
			if(a<lens&&j>0){//del char
				apmin(f[i+1][j-1],F+1);
			}
		}
		if(!flag)return 0;
	}
	int F=f[lens][lent-lens+8];
	return F<=8?F:0;
}
char pool[L],*s[N];
int cnt[10];
int main(){
#ifndef ONLINE_JUDGE
	freopen("say.in","r",stdin);
	freopen("say.out","w",stdout);
#endif
	int n=ni;
	s[1]=pool;
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]);
		for(char* &j=s[i+1]=s[i];*j;j++);
		s[i+1]++;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			cnt[work(s[i]-1,s[j]-1,s[i+1]-s[i]-1,s[j+1]-s[j]-1)]++;
		}
	}
	for(int i=1;i<=8;i++){
		printf("%d ",cnt[i]);
	}
	putchar('\n');
	return 0;
}
