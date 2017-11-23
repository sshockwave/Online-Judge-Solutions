#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
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
const int N=100010;
int a[N],b[N],lsta[N],lstb[N];
set<int>vis;
map<int,vector<int> >to;
inline bool valid(int x){
	set<int>::iterator it=vis.find(x);
	return it==vis.end();
}
void dfs(int x){
	if(!valid(x))return;
	vis.insert(x);
	map<int,vector<int> >::iterator it=to.find(x);
	if(it==to.end())return;
	for(int i=0,n=it->second.size();i<n;i++){
		dfs(it->second[i]);
	}
}
inline int Main(){
	int n=ni,xora=0,ans=0;
	for(int i=1;i<=n;i++){
		xora^=a[i]=lsta[i]=ni;
	}
	for(int i=1;i<=n;i++){
		b[i]=lstb[i]=ni;
		if(a[i]!=b[i]){
			ans++;
			to[b[i]].push_back(a[i]);
		}
	}
	lsta[n+1]=xora;
	sort(lsta+1,lsta+n+2);
	sort(lstb+1,lstb+n+1);
	for(int i=1,j=1;i<=n;i++,j++){
		for(;j<=n+1&&lsta[j]!=lstb[i];j++);
		if(j>n+1)return -1;
	}
	dfs(xora);
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i]&&valid(b[i])){
			ans++,dfs(b[i]);
		}
	}
	return ans;
}
int main(){
	printf("%d\n",Main());
	return 0;
}
