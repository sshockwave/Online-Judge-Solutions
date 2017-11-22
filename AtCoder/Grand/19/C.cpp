#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cmath>
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
const int N=200010;
int x[N],y[N];
int b[N],lst[N],len=0;
inline int lcmp(int a,int b){
	return x[a]<x[b];
}
inline int binfind(int cury){
	int l=0,r=len;
	while(l<r){
		int m=((l+r)>>1)+1;
		if(y[b[m]]>cury){
			r=m-1;
		}else{
			l=m;
		}
	}
	return l;
}
int main(){
	int x1=ni,y1=ni,x2=ni,y2=ni;
	bool flag1=x1>x2,flag2=y1>y2;
	int n=ni;
	if(flag1){
		x1=-x1,x2=-x2;
	}
	if(flag2){
		y1=-y1,y2=-y2;
	}
	for(int i=1;i<=n;i++){
		x[i]=ni,y[i]=ni;
		if(flag1){
			x[i]=-x[i];
		}
		if(flag2){
			y[i]=-y[i];
		}
		if(!(x1<=x[i]&&x[i]<=x2&&y1<=y[i]&&y[i]<=y2)){
			n--,i--;
		}
		lst[i]=i;
	}
	sort(lst+1,lst+n+1,lcmp);
	for(int i=1;i<=n;i++){
		int j=lst[i],k=binfind(y[j]);
		if(k==len||y[j]<y[b[k+1]]){
			b[k+1]=j;
			if(k==len){
				len++;
			}
		}
	}
	printf("%.20lf\n",100ll*(x2-x1+y2-y1)-20*len+M_PI*5*(len+(len==min(x2-x1,y2-y1)+1)));
	return 0;
}
