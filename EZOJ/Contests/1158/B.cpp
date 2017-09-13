#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
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
set<int>pos[N];
int c[N],a[N],mat1[N],mat2[N],pt[N];
inline bool mvpt(int n,int len){
	for(int i=1;i<=len&&pt[i]<=pt[i-1];i++){
		set<int>::iterator it=pos[a[i]].upper_bound(pt[i-1]);
		if(it==pos[a[i]].end()){
			return false;
		}
		pt[i]=*it;
	}
	return true;
}
bool calc[N];
inline void nxtpt(){
	while(!calc[++pt[0]]);
}
inline void work(int n,int k,int len,int end[]){
	for(int i=1;i<=k;i++){
		pos[i].clear();
	}
	for(int i=1;i<=n;i++){
		pos[c[i]].insert(i);
	}
	memset(pt+1,0,len<<2);
	for(int i=0;i<=n;i++){
		end[i]=n+1;
	}
	for(pt[0]=0;mvpt(n,len);nxtpt()){
		end[pt[0]]=pt[len];
	}
}
int diff[N];
inline void mark(int l,int r){
	if(l<=r){
		diff[l]++,diff[r+1]--;
	}
}
int fir[N],las[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("prz.in","r",stdin);
	freopen("prz.out","w",stdout);
#endif
	int n=ni,k=ni;
	for(int i=1;i<=k;i++){
		fir[i]=n+1,las[i]=0;
	}
	for(int i=1;i<=n;i++){
		c[i]=ni;
		apmin(fir[c[i]],i);
		apmax(las[c[i]],i);
	}
	memset(calc,0,sizeof(calc));
	for(int i=1;i<=k;i++){
		calc[fir[i]]=calc[las[i]]=true;
	}
	int len1=ni,len2=ni;
	for(int i=1;i<=len1;i++){
		a[i]=ni;
	}
	work(n,k,len1,mat1);
	for(int i=1;i<=len2;i++){
		a[i]=ni;
	}
	reverse(c+1,c+n+1);
	reverse(calc+1,calc+n+1);
	work(n,k,len2,mat2);
	reverse(c+1,c+n+1);
	reverse(mat2+1,mat2+n+1);
	for(int i=1;i<=n;i++){
		mat2[i]=n+1-mat2[i];
	}
	mat1[n+1]=n+1,mat2[0]=0;
	for(int i=1;i<=k;i++){
		mark(mat1[fir[i]],mat2[las[i]]);
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		diff[i]+=diff[i-1];
		if(diff[i]>0&&c[i]==a[len2]){
			cnt++;
		}
	}
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++){
		if(diff[i]>0&&c[i]==a[len2]){
			printf("%d ",i);
		}
	}
	putchar('\n');
	return 0;
}
