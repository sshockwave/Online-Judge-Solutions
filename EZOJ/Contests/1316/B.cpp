#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
#include <set>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<class T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar())&&c!='-');
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=100010;
int a[N][2];
bool side[N];
namespace task2{
	struct Coin{
		int a,b;
		inline friend bool operator < (const Coin &a,const Coin &b){
			return a.a<b.a;
		}
	}coin[N];
	inline lint work(int n){
		for(int i=1;i<=n;i++){
			coin[i]=(Coin){a[i][0],a[i][1]};
		}
		set<Coin>s;
		for(int tot=ni;tot--;){
			int l=ni,r=ni,t=ni;
			vector<Coin>tmp;
			for(;s.size()&&s.begin()->a<=t;s.erase(s.begin())){
				tmp.push_back((Coin){s.begin()->b,s.begin()->a});
			}
			for(int i=0;i<tmp.size();i++){
				s.insert(tmp[i]);
			}
		}
		lint ans=0;
		for(;s.size();ans+=s.begin()->a,s.erase(s.begin()));
		return ans;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("name.in","r",stdin);
	freopen("name.out","w",stdout);
#endif
	memset(side,0,sizeof(side));
	int n=ni;
	for(int i=1;i<=n;i++){
		a[i][0]=ni;
	}
	for(int i=1;i<=n;i++){
		a[i][1]=ni;
	}
	if(n>=3000){
		printf("%lld",task2::work(n));
		return 0;
	}
	for(int tot=ni;tot--;){
		int l=ni,r=ni,t=ni;
		for(int i=l;i<=r;i++){
			if(a[i][side[i]]<=t){
				side[i]=!side[i];
			}
		}
	}
	lint sum=0;
	for(int i=1;i<=n;i++){
		sum+=a[i][side[i]];
	}
	printf("%lld\n",sum);
}
