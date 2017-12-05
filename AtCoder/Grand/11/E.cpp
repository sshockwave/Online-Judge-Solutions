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
const int N=500010;
char s[N];
int num[N],fa[N];
inline void subone(int x){
	num[fa[x]]--;
	if(fa[x]<x){
		int f=fa[x]++;
		num[fa[x]]=num[f]+10,fa[fa[x]]=fa[x];
		x=f;
	}
	assert(fa[x]==x);
	if(x&&num[x]==num[fa[x-1]]){
		fa[x]=fa[x-1];
	}
}
int main(){
	scanf("%s",s);
	int n=strlen(s);
	num[0]=s[0]-'0',fa[0]=0;
	for(int i=1;s[i];i++){
		num[i]=s[i]-'0',fa[i]=i;
		for(;num[fa[i-1]]>num[i];subone(i-1),num[i]+=10);
		if(num[fa[i-1]]==num[i]){
			fa[i]=fa[i-1];
		}
	}
	printf("%d\n",num[fa[n-1]]/9+(num[fa[n-1]]%9!=0));
	return 0;
}
