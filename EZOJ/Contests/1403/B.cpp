#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <algorithm>
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
const int N=5010;
void dfs(int x,int dep,vector<int>son[],int* &s){
	vector<int>&vec=son[x];
	sort(son[x].begin(),son[x].end());
	*++s=dep;
	for(vector<int>::iterator it=vec.begin();it!=vec.end();it++){
		dfs(*it,dep+1,son,s);
	}
}
vector<int>son1[N],son2[N];
int s1[N],s2[N];
int f[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("iso.in","r",stdin);
	freopen("iso.out","w",stdout);
#endif
	int n=ni;
	for(int i=2;i<=n;i++){
		son1[ni].push_back(i);
	}
	int m=ni;
	for(int i=2;i<=m;i++){
		son2[ni].push_back(i);
	}
	{
		int *ss1=s1,*ss2=s2;
		dfs(1,1,son1,ss1),dfs(1,1,son2,ss2);
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=1;j--){
			if(s1[i]==s2[j]){
				apmax(f[j],f[j-1]+1);
			}
		}
		for(int j=1;j<=m;j++){
			apmax(f[j],f[j-1]);
		}
	}
	printf("%d\n",n+m-(f[m]<<1));
	return 0;
}
