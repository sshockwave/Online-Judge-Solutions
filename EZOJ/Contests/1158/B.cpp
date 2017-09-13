#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){
		a=b;
	}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){
		a=b;
	}
}
const int N=1000010;
int c[N],a[N],aend[N];
inline void read(int a[],int n){
	for(int i=1;i<=n;i++){
		a[i]=ni;
	}
}
int pos[N];
inline void work(int n,int len,int cend[]){
	memset(cend,0,(len+1)<<2);
	memset(pos,-1,sizeof(pos));
	for(int i=1;i<=len;i++){
		aend[i]=n+1;
		pos[a[i]]=i;
	}
	for(int i=n;i>=1;i--){
		aend[len+1]=i;
		int t=pos[c[i]];
		if(~t){
			aend[t]=aend[t+1];
		}
		cend[i]=aend[1];
	}
}
int cend1[N],cend2[N];
int fir[N],las[N];
int diff[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("prz.in","r",stdin);
	freopen("prz.out","w",stdout);
#endif
	int n=ni,k=ni;
	read(c,n);
	int len1=ni,len2=ni;
	read(a,len1);
	work(n,len1,cend1);
	read(a,len2);
	reverse(c+1,c+n+1);
	work(n,len2,cend2);
	reverse(c+1,c+n+1);
	reverse(cend2+1,cend2+n+1);
	for(int i=1;i<=n;i++){
		cend2[i]=n+1-cend2[i];
	}
	memset(fir,0,sizeof(fir));
	memset(las,0,sizeof(las));
	memset(diff,0,sizeof(diff));
	for(int i=1;i<=n;i++){
		las[c[i]]=i;
	}
	for(int i=n;i>=1;i--){
		fir[c[i]]=i;
	}
	for(int i=1;i<=k;i++){
		if(fir[i]){
			assert(las[i]);
			int l=cend1[fir[i]],r=cend2[las[i]];
			if(l<=r){
				diff[l]++,diff[r+1]--;
			}
		}
	}
	int ans=0;
	for(int i=1,t=a[len2];i<=n;i++){
		diff[i]+=diff[i-1];
		if(diff[i]>0&&c[i]==t){
			ans++;
		}
	}
	printf("%d\n",ans);
	for(int i=1,t=a[len2];i<=n;i++){
		if(diff[i]>0&&c[i]==t){
			printf("%d ",i);
		}
	}
	putchar('\n');
	return 0;
}
