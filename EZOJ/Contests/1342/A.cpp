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
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T>inline T cabs(T x){
	return x>=0?x:-x;
}
const int N=500010;
int mv[N],pos[N];
bool ans[N];
struct intv{
	int l,r;
	inline friend bool operator < (const intv &a,const intv &b){
		return a.l!=b.l?a.l<b.l:a.r<b.r;
	}
};
vector<intv>vec,tmp;
inline void psh(int l,int r){
	if(l<0){
		l=0;
	}
	if(r>pos[0]){
		r=pos[0];
	}
	if(l<=r){
		tmp.push_back((intv){l,r});
	}
}
inline void work(){
	vec.clear();
	sort(tmp.begin(),tmp.end());
	for(int i=0,j=0,n=tmp.size();i<n;i=j){
		int l=tmp[i].l,r=tmp[i].r;
		for(;j<n&&tmp[j].l<=r+1;j++){
			if(tmp[j].r>r){
				r=tmp[j].r;
			}
		}
		vec.push_back((intv){l,r});
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("alice.in","r",stdin);
	freopen("alice.out","w",stdout);
#endif
	int n=ni;
	pos[0]=ni;
	for(int i=1;i<=n;i++){
		mv[i]=ni;
		pos[i]=min(pos[i-1],cabs(pos[i-1]-mv[i]));
	}
	if(pos[n]){
		for(int tot=ni;tot--;puts("YES"));
		return 0;
	}
	memset(ans,0,sizeof(ans));
	vec.push_back((intv){0,0});
	for(int i=n;i>=1;i--){
		ans[i]=pos[i-1]>vec[0].r;
		tmp.clear();
		for(int j=0;j<(int)vec.size();j++){
			int l=vec[j].l,r=vec[j].r;
			psh(l,min(mv[i]>>1,r));
			psh(max((mv[i]+1)>>1,mv[i]-r),mv[i]-l);
			psh(max((mv[i]+1)>>1,mv[i]+l),mv[i]+r);
		}
		work();
	}
	for(int tot=ni;tot--;puts(ans[ni]?"YES":"NO"));
	return 0;
}
