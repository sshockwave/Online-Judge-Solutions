#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
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
const lint LINF=0x7f7f7f7f7f7f7f7fll;
int n;
lint a[N];
int pre[N],nxt[N],roll_pre[N],roll_nxt[N];
lint prev[N],nxtv[N],roll_prev[N],roll_nxtv[N];
lint premn[N],nxtmx[N];
bool dfs(int l,int r){
	if(premn[l]>=nxtmx[r])return true;
	while(true){
		if(prev[l]>=a[r]){
			l=pre[l];
		}else if(a[l]>=nxtv[r]){
			r=nxt[r];
		}else break;
	}
	if(premn[l]>=nxtmx[r])return true;
	if(premn[l]<a[r])return false;
	if(a[l]<nxtmx[r])return false;
	if(rand()&1){
		if(l>1&&roll_prev[l]>=a[r]&&dfs(roll_pre[l],r))return true;
		if(r<n&&a[l]>=roll_nxtv[r]&&dfs(l,roll_nxt[r]))return true;
	}else{
		if(r<n&&a[l]>=roll_nxtv[r]&&dfs(l,roll_nxt[r]))return true;
		if(l>1&&roll_prev[l]>=a[r]&&dfs(roll_pre[l],r))return true;
	}
	return false;
}
inline bool Main(){
	n=ni;
	int k=ni;
	for(int i=1;i<=n;i++){
		a[i]=a[i-1]+next_num<lint>();
	}
	if(a[1]<a[n])return false;
	for(int i=1;i<=n;i++){//premn
		premn[i]=a[i];
		if(i>1){
			apmin(premn[i],premn[i-1]);
		}
	}
	for(int i=n;i>=1;i--){//nxtmx
		nxtmx[i]=a[i];
		if(i<n){
			apmax(nxtmx[i],nxtmx[i+1]);
		}
	}
	for(int i=1;i<=n;i++){//pre
		if(i==1){
			pre[i]=i-1,prev[i]=-LINF;
		}else{
			pre[i]=i-1,prev[i]=a[i];
			for(int &j=pre[i];j>=1&&a[j]<a[i];apmin(prev[i],prev[j]),j=pre[j]);
			for(int &j=pre[i];j>=1&&prev[j]>=prev[i];j=pre[j]);
		}
	}
	for(int i=n;i>=1;i--){//nxt
		if(i==n){
			nxt[i]=i+1,nxtv[i]=LINF;
		}else{
			nxt[i]=i+1,nxtv[i]=a[i];
			for(int &j=nxt[i];j<=n&&a[j]>a[i];apmax(nxtv[i],nxtv[j]),j=nxt[j]);
			for(int &j=nxt[i];j<=n&&nxtv[j]<=nxtv[i];j=nxt[j]);
		}
	}
	for(int i=1;i<=n;i++){//roll_pre
		if(i==1){
			roll_pre[i]=i,roll_prev[i]=a[i];
		}else if(a[i-1]<a[i]){
			roll_pre[i]=roll_pre[i-1],roll_prev[i]=roll_prev[i-1];
		}else{
			roll_pre[i]=pre[i],roll_prev[i]=a[i];
		}
	}
	for(int i=n;i>=1;i--){//roll_nxt
		if(i==n){
			roll_nxt[i]=i,roll_nxtv[i]=a[i];
		}else if(a[i+1]>a[i]){
			roll_nxt[i]=roll_nxt[i+1],roll_nxtv[i]=roll_nxtv[i+1];
		}else{
			roll_nxt[i]=nxt[i],roll_nxtv[i]=a[i];
		}
	}
	return dfs(k,k);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("seven.in","r",stdin);
	freopen("seven.out","w",stdout);
#endif
	srand(990099);
	for(int tot=ni;tot--;){
		puts(Main()?"Yes":"No");
	}
	return 0;
}
