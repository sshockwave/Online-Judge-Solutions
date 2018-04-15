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
const int N=210,L=1000010+N,INF=0x7f7f7f7f;
int ans;
void dfs(char a[],char b[],int ra,int rb,int step){
	if(step+cabs(ra-rb)>=ans)return;
	for(;a[0]&&a[0]==b[0];++a,++b);
	if(a[0]==0&&b[0]==0){
		ans=step;
		return;
	}
	if(a[0]){
		dfs(a+1,b,ra-1,rb,step+1);
	}
	if(b[0]){
		dfs(a,b+1,ra,rb-1,step+1);
	}
	if(a[0]&&b[0]){
		dfs(a+1,b+1,ra-1,rb-1,step+1);
	}
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
			ans=9;
			dfs(s[i],s[j],s[i+1]-s[i]-1,s[j+1]-s[j]-1,0);
			++cnt[ans];
		}
	}
	for(int i=1;i<=8;i++){
		printf("%d ",cnt[i]);
	}
	putchar('\n');
	return 0;
}
