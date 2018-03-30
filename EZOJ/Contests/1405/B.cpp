#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
#define cout cerr
#define ni (next_num<int>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool f=c=='-'&&(c=getchar());
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return f?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const lint LINF=0x7f7f7f7f7f7f7f7fll;
typedef multiset<lint>st;
typedef st::iterator iter;
st s;
inline bool check(vector<lint>&odd,vector<lint>&tmx,lint O,int sh){
	int a=1,b=0;
	for(int ta=odd.size();a<ta;a++,b++){
		if(tmx[b]%O!=odd[a]){
			if(tmx[b]==(1ll<<sh))return false;
			b++;
		}
		if(tmx[b]%O!=odd[a])return false;
		if(b>a)return false;
	}
	if(b<a){
		if(tmx[b]==(1ll<<sh))return false;
	}
	return true;
}
inline lint Main2(){
	if(s.count(1)>1){
		lint ans=LINF;
		for(iter it=s.begin();it!=s.end();it++){
			if(s.find((*it)<<1)==s.end()){
				apmin(ans,((*it)<<1)-1);
			}
		}
		return ans;
	}
	vector<lint>odd,tmx;
	int sh=0;
	for(;s.find(1ll<<sh)!=s.end();sh++);
	assert(sh>0);
	while(!s.empty()){
		lint t=*s.begin();
		odd.push_back(t);
		assert((t&1));
		for(iter it;it=s.find(t),it!=s.end();s.erase(it),t<<=1);
		tmx.push_back(t);
	}
	if(odd.size()==2)return (1ll<<sh)-odd[1];
	sort(odd.begin(),odd.end());
	sort(tmx.begin(),tmx.end());
	assert(odd.size()==tmx.size());
	assert(odd.size()>=2);
	assert(odd[0]==1);
	lint ans=tmx[0]-odd[1];
	if(check(odd,tmx,ans,sh))return ans;
	ans=tmx[1]-odd[1];
	if(check(odd,tmx,ans,sh))return ans;
	assert(false);
}
inline lint Main(){
	for(int tot=ni;tot--;s.insert(next_num<lint>()));
	lint mx=*s.rbegin();
	if(mx==0)return 1;
	if(s.count(0))return mx<<1;
	int sh=0;
	for(iter it;it=s.find(1ll<<sh),it!=s.end();s.erase(it),sh++);
	if(s.empty())return mx+1;//all in form 2^k
	lint g=0;
	for(iter it=s.begin();it!=s.end();it++){
		g=gcd(g,*it);
	}
	g=g&(-g);
	st tmp;
	for(iter it=s.begin();it!=s.end();it++){
		tmp.insert(*it/g);
	}
	for(int i=0;i<sh;i++){
		if((1ll<<i)>=g){
			tmp.insert((1ll<<i)/g);
		}
	}
	s=tmp;
	return Main2()*g;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("pow.in","r",stdin);
	freopen("pow.out","w",stdout);
#endif
	printf("%lld\n",Main());
	return 0;
}
