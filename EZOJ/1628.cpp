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
const int N=1000010;
char s[N],t[N];
int len[N],ext[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("kmp.in","r",stdin);
	freopen("kmp.out","w",stdout);
#endif
	scanf("%s%s",s,t);
	len[0]=0;
	for(int i=1,j=0;s[i];i++){
		len[i]=i<j+len[j]?min(len[i-j],j+len[j]-i):0;
		for(;s[len[i]]==s[i+len[i]];len[i]++);
		if(i+len[i]>j+len[j]){
			j=i;
		}
	}
	for(int i=0,j=0;s[i];i++){
		ext[i]=i<j+len[j]?min(ext[i-j],j+len[j]-i):0;
		for(;t[ext[i]]&&s[i+ext[i]]==t[ext[i]];ext[i]++);
		if(i+len[i]>j+len[j]){
			j=i;
		}
	}
	for(int tot=ni;tot--;){
		printf("%d\n",ext[ni-1]);
	}
}
