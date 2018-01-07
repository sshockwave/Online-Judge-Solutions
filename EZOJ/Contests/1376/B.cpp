#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
const int N=110,INF=0x7f7f7f7f;
struct Pt{
	int x,y,yrnk;
	inline friend bool operator < (const Pt &a,const Pt &b){
		return a.x!=b.x?a.x<b.x:a.y<b.y;
	}
}pt[N];
int f[N][N][N],mxsize;
inline int F(int l,int r,int k){//sanitized
	if(k==INF)return 0;
	if(~f[l][r][k])return f[l][r][k];
	vector<int>vec,mn_;
	int mxhei=pt[l].x==pt[r].x?INF:mxsize/(pt[r].x-pt[l].x);
	int sql=0,sqr=0,sqk=INF;
	for(int i=l;i<=r;i++){
		if(pt[i].yrnk>=k){
			vec.push_back(i);
			if(pt[i].y>mxhei){
				apmin(sqk,pt[i].yrnk);
				if(sql==0){
					sql=i;
				}
				sqr=i;
			}
		}
	}
	assert(!vec.empty());
	mn_.resize(vec.size());
	int curmn=INF;
	for(int i=vec.size()-1;i>=0;i--){
		apmin(curmn,pt[vec[i]].yrnk);
		mn_[i]=curmn;
	}
	int ans=INF;
	if(sql!=l||sqr!=r){
		apmin(ans,F(sql,sqr,sqk)+1);
	}
	curmn=pt[vec[0]].yrnk;
	for(int i=1,ti=vec.size();i<ti;i++){
		apmin(ans,F(vec[0],vec[i-1],curmn)+F(vec[i],vec[ti-1],mn_[i]));
		apmin(curmn,pt[vec[i]].yrnk);
	}
	assert(ans<INF);
	return f[l][r][k]=ans;
}
int *yval[N];
inline bool ycmp(int* a,int * b){
	return *a<*b;
}
inline int Main(){
	int n=ni;
	mxsize=ni;
	for(int i=1;i<=n;i++){
		pt[i]=(Pt){ni,ni};
		pt[i].yrnk=pt[i].y;
		yval[i]=&pt[i].yrnk;
	}
	sort(pt+1,pt+n+1);
	sort(yval+1,yval+n+1,ycmp);
	for(int i=1,j=0,k=0;i<=n;i++){
		if(*yval[i]!=k){
			j++;
			k=*yval[i];
		}
		*yval[i]=j;
	}
	memset(f,-1,sizeof(f));
	return F(1,n,1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("scene.in","r",stdin);
	freopen("scene.out","w",stdout);
#endif
	for(int tot=ni;tot--;){
		printf("%d\n",Main());
	}
	return 0;
}
