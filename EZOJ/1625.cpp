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
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=1000010;
char s[N<<1];
int rad[N<<1];
int main(){
#ifndef ONLINE_JUDGE
	freopen("manacher.in","r",stdin);
	freopen("manacher.out","w",stdout);
#endif
	int n=0;
	{
		static char t[N];
		scanf("%s",t);
		s[n++]='{';
		s[n++]='#';
		for(int i=0;t[i];i++){
			s[n++]=t[i],s[n++]='#';
		}
		s[n]='}';
	}
	rad[0]=0;
	int ans=0;
	for(int i=1,j=0;i<n;i++){
		rad[i]=i<j+rad[j]?min(j+rad[j]-i,rad[(j<<1)-i]):0;
		for(;s[i-rad[i]]==s[i+rad[i]];rad[i]++);
		rad[i]--;
		if(i+rad[i]>j+rad[j]){
			j=i;
		}
		apmax(ans,rad[i]);
	}
	printf("%d\n",ans);
}
