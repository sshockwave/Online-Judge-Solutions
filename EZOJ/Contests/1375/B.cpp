#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>
using namespace std;
typedef long long lint;
typedef unsigned long long ull;
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
const int N=30010,rtN=200,M=2;
int a[N];
int pos[N];
int *lst[N];
inline bool lcmp(int* a,int* b){
	return *a<*b;
}
inline ull gen(){
	return (ull)rand()*RAND_MAX+rand();
}
ull col[N],val[N];
unordered_map<ull,int>cnt[rtN*M];
ull tag[rtN*M];
int ans=0;
inline void addm(int b,int v){
	unordered_map<ull,int>::iterator it=cnt[b].find(tag[b]);
	if(it!=cnt[b].end()){
		ans+=it->second*v;
	}
}
inline void modm(int b,ull p,int v){
	unordered_map<ull,int>::iterator it=cnt[b].find(p);
	if(it==cnt[b].end()){
		cnt[b][p]=v;
		return;
	}
	it->second+=v;
	if(it->second==0){
		cnt[b].erase(it);
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("meet.in","r",stdin);
	freopen("meet.out","w",stdout);
#endif
	srand(262526);
	int n=ni,rt;
	for(rt=1;rt*rt*M<n;rt++);
	for(int i=1;i<=n;i++){
		a[i]=ni;
		lst[i]=a+i;
	}
	sort(lst+1,lst+n+1,lcmp);
	for(int i=1,j=0,k=0;i<=n;i++){
		if(*lst[i]!=k){
			j++;
			col[j]=gen();
			k=*lst[i];
		}
		*lst[i]=j;
	}
	memset(pos,127,sizeof(pos));
	memset(val,0,sizeof(val));
	memset(tag,0,sizeof(tag));
	lint ans=0;
	for(int i=n;i>=1;i--){
		int nxt=pos[a[i]];
		pos[a[i]]=i;
		::ans++;
		modm(i/rt,tag[i/rt],1);
		if(nxt<=n){
			int nb=(nxt+rt-1)/rt;
			int cb=nxt/rt;
			ull dt=col[a[i]];
			addm(cb,-1);
			for(int j=nxt,tj=nb*rt;j<=n&&j<tj;j++){
				modm(cb,val[j],-1);
				modm(cb,val[j]^=dt,1);
			}
			addm(cb,1);
			for(int j=nb,tj=n/rt;j<=tj;j++){
				addm(j,-1);
				tag[j]^=dt;
				addm(j,1);
			}
		}
		ans+=::ans;
	}
	printf("%lld\n",ans);
	return 0;
}
