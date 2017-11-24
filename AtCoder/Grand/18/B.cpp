#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
typedef unsigned int uint;
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
const int N=310;
int a[N][N],n,m;
int pt[N];
vector<int>stu[N];
bool vis[N];
inline bool check(uint mx){
	for(int i=1;i<=m;i++){
		stu[i].clear();
		vis[i]=false;
	}
	for(int i=1;i<=n;i++){
		pt[i]=1;
		stu[a[i][1]].push_back(i);
	}
	while(true){
		int x=1;
		for(;x<=m&&stu[x].size()<=mx;x++);
		if(x>m)return true;
		vis[x]=true;
		for(int i=0,ti=stu[x].size();i<ti;i++){
			int cur=stu[x][i];
			for(int &j=pt[cur];j<=m&&vis[a[cur][j]];j++);
			if(pt[cur]>m)return false;
			stu[a[cur][pt[cur]]].push_back(cur);
		}
		stu[x].clear();
	}
}
int main(){
	n=ni,m=ni;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i][j]=ni;
		}
	}
	int l=1,r=n;
	while(l<r){
		int m=(l+r)>>1;
		if(check(m)){
			r=m;
		}else{
			l=m+1;
		}
	}
	printf("%d\n",l);
	return 0;
}
