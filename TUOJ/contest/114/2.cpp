#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
const int N=100010;
int n;
struct pii{
	int a,b;
};
typedef vector<pii>vi;
vi vec;
#ifdef local
int ans;
int lnk[N];
bool vis[N];
void dfs(int x,int cnt,int rest){
	if(cnt+(rest>>1)<=ans)return;
	if(x>n){
		ans=cnt;
		vec.clear();
		for(int i=1;i<=n;i++){
			if(lnk[i]>i){
				vec.push_back((pii){i,lnk[i]});
			}
		}
		return;
	}
	if(!lnk[x]){
		for(int i=n;i>x;i--){
			if(i+x>n)continue;
			if(!lnk[i]&&!vis[x+i]){
				vis[x+i]=true;
				lnk[x]=i,lnk[i]=x;
				dfs(x+1,cnt+1,rest-2);
				lnk[x]=0,lnk[i]=0;
				vis[x+i]=false;
			}
		}
	}
	dfs(x+1,cnt,rest-(lnk[x]==0));
}
#else
int cche[][23]={
	{0},
	{0},
	{0},
	{1,1,2},
	{1,1,2},
	{1,1,2},
	{2,1,5,2,3},
	{2,1,5,2,3},
	{3,1,6,2,4,3,5},
	{3,1,6,2,4,3,5},
	{3,1,6,2,4,3,5},
	{4,1,10,2,7,3,5,4,6},
	{4,1,10,2,7,3,5,4,6},
	{5,1,10,2,8,3,9,4,5,6,7},
	{5,1,10,2,8,3,9,4,5,6,7},
	{5,1,10,2,8,3,9,4,5,6,7},
	{6,1,15,2,11,3,9,4,10,5,6,7,8},
	{6,1,15,2,11,3,9,4,10,5,6,7,8},
	{7,1,14,2,12,3,13,4,9,5,7,6,11,8,10},
	{7,1,14,2,12,3,13,4,9,5,7,6,11,8,10},
	{7,1,14,2,12,3,13,4,9,5,7,6,11,8,10},
	{8,1,20,2,15,3,13,4,14,5,10,6,8,7,12,9,11},
	{8,1,20,2,15,3,13,4,14,5,10,6,8,7,12,9,11},
	{9,1,18,2,16,3,17,4,13,5,11,6,15,7,8,9,14,10,12},
	{9,1,18,2,16,3,17,4,13,5,11,6,15,7,8,9,14,10,12},
	{9,1,18,2,16,3,17,4,13,5,11,6,15,7,8,9,14,10,12},
	{10,1,25,2,19,3,17,4,18,5,14,6,12,7,16,8,9,10,15,11,13},
	{10,1,25,2,19,3,17,4,18,5,14,6,12,7,16,8,9,10,15,11,13},
	{11,1,22,2,20,3,21,4,17,5,15,6,19,7,11,8,18,9,10,12,16,13,14}
};
#endif
int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
#ifdef local
	cout<<"{"<<endl;
	for(n=0;n<=28;n++){
		dfs(1,0,n);
		cout<<"\t{"<<ans;
		for(int i=0;i<ans;i++){
			cout<<","<<vec[i].a<<","<<vec[i].b;
		}
		cout<<"},"<<endl;
	}
	cout<<"}"<<endl;
#else
	int n=ni;
	int i=1,j=n-1;
	for(;j-i>26;i++,j-=2){
		vec.push_back((pii){i,j});
	}
	int pn=j-i+2;
	int dt=i-1;
	for(int k=1,ti=cche[pn][0];k<=ti;k++){
		vec.push_back((pii){cche[pn][k*2-1]+dt,cche[pn][k*2]+dt});
	}
	printf("%d\n",(int)vec.size());
	for(int i=0;i<(int)vec.size();i++){
		printf("%d %d\n",vec[i].a,vec[i].b);
	}
#endif
	return 0;
}
