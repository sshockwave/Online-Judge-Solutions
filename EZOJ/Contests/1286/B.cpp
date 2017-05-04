#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <ctime>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
const int N=1000010,INF=0x7f7f7f7f;//tocheck
int sigma,n,m,s[N],t[N],fail[N];
bool valid[N];
inline void getbef(int *s,int n){
	static int *last=new int[N];//nxt[color]
	memset(last+1,-1,sigma<<2);
	int cur;
	for(int i=1;i<=n;i++){
		s[i]=last[cur=s[i]]==-1?INF:(i-last[cur]);
		last[cur]=i;
	}
}
inline void calkmp(int *s,int n){
	fail[1]=0;
	for(int i=1,j=0;i<=n;){
		if(j==0||(s[i]>=j?INF:s[i])==s[j]){
			fail[++i]=++j;
		}else{
			j=fail[j];
		}
	}
}
inline int kmp(){
	int match=0;
	for(int i=1,j=1;i<=n;){
		if(j==0||(s[i]>=j?INF:s[i])==t[j]){
			i++,j++;
			if(j>m){
				match++;
				valid[i-m]=true;
				j=fail[j];
			}
		}else{
			j=fail[j];
		}
	}
	return match;
}
int main(){
	int tot=ni;
	sigma=ni;
	while(tot--){
		n=ni,m=ni;
		for(int i=1;i<=n;i++){
			s[i]=ni;
		}
		for(int i=1;i<=m;i++){
			t[i]=ni;
		}
		memset(valid,0,sizeof(valid));
		getbef(s,n);
		getbef(t,m);
		calkmp(t,m);
		printf("%d\n",kmp());
		for(int i=1,_=n-m+1;i<=_;i++){
			if(valid[i]){
				printf("%d ",i);
			}
		}
		putchar('\n');
	}
}
