#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
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
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int N=16;
int n,m;
int b[N];
bool iskey[N];
struct State;
typedef map<State,lint>mp;
struct State{
	int bitmask,tb;
	int len,lst[N];
	inline friend bool operator < (const State &a,const State &b){
		if(a.bitmask!=b.bitmask)return a.bitmask<b.bitmask;
		if(a.tb!=b.tb)return a.tb<b.tb;
		if(a.len!=b.len)return a.len<b.len;
		const int len=a.len;
		for(int i=1;i<=len;i++){
			if(a.lst[i]!=b.lst[i])return a.lst[i]<b.lst[i];
		}
		return false;
	}
	inline bool valid()const{
		return len==m&&tb==m;
	}
	inline bool ext(int x){
		int tf;
		{
			int l=0,r=len;
			while(l<r){
				int m=((l+r)>>1)+1;
				if(lst[m]<x){
					l=m;
				}else{
					r=m-1;
				}
			}
			tf=l;
		}
		++tf;
		if(len<tf||lst[tf]>x){
			lst[tf]=x;
		}
		apmax(len,tf);
		if(len>m)return false;
		if(tb<m&&x==b[tb+1]){
			++tb;
			if(tf!=tb)return false;
		}
		bitmask|=1<<x;
		return true;
	}
	inline void work(lint v,mp &f)const{
		for(int i=1;i<=n;i++){
			if((bitmask>>i)&1)continue;
			if(!iskey[i]||(tb<m&&b[tb+1]==i)){
				State tmp=*this;
				if(tmp.ext(i)){
					f[tmp]+=v;
				}
			}
		}
	}
	inline friend ostream & operator << (ostream & out,const State &b){
		out<<"state({s:"<<b.bitmask<<",tb:"<<b.tb<<",len:"<<b.len<<",[";
		for(int i=1;i<=b.len;i++){
			if(i>1){
				out<<",";
			}
			out<<b.lst[i];
		}
		out<<"]}";
		return out;
	}
};
mp f[N];
inline lint Main(){
	n=ni,m=ni;
	if(m<1||m>n)return 0;
	for(int i=1;i<=m;i++){
		b[i]=ni;
		if(i>1&&!(b[i-1]<b[i]))return 0;
	}
	if(b[1]<1||b[m]>n)return 0;
	mset(iskey+1,0,n);
	for(int i=1;i<=m;i++){
		iskey[b[i]]=true;
	}
	{
		State tmp;
		tmp.bitmask=0;
		tmp.tb=0;
		tmp.len=0;
		f[0][tmp]=1;
	}
	for(int i=0;i<n;i++){
		for(mp::iterator it=f[i].begin(),ti=f[i].end();it!=ti;++it){
			it->first.work(it->second,f[i+1]);
		}
	}
	lint ans=0;
	for(mp::iterator it=f[n].begin(),ti=f[n].end();it!=ti;++it){
		if(it->first.valid()){
			ans+=it->second;
		}
	}
	return ans;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("arg.in","r",stdin);
	freopen("arg.out","w",stdout);
#endif
	printf("%lld\n",Main());
	return 0;
}
