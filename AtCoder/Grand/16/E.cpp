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
const int N=410,M=100010;
struct Edge{
	int u,v;
}e[M];
int n,m;
inline bool gs(bool s[]){
	for(int i=m;i>=1;i--){
		if(s[e[i].u]&&s[e[i].v])return false;
		if(s[e[i].u]||s[e[i].v]){
			s[e[i].u]=s[e[i].v]=true;
		}
	}
	return true;
}
bool live[N];
bool s[N][N];
inline int Main(){
	n=ni,m=ni;
	for(int i=1;i<=m;i++){
		e[i]=(Edge){ni,ni};
	}
	memset(s,0,sizeof(s));
	for(int i=1;i<=n;i++){
		s[i][i]=true;
		live[i]=gs(s[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(!live[i])continue;
		for(int j=1;j<i;j++){
			if(!live[j])continue;
			ans++;
			for(int k=1;k<=n;k++){
				if(s[i][k]&&s[j][k]){
					ans--;
					break;
				}
			}
		}
	}
	return ans;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
