#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
inline lint cnt2(int n,int k){
	if(k>n){
		return 0;
	}
	lint ans=0;
	if(k&1){
		ans+=max(0,n-k);
	}
	ans+=(k+1)/2;
	return ans;
}
class AlternateColors2{
	public:
	lint countWays(int n,int k){
		lint ans=0;
		//destroyed in part 1
		if(k%3==1){
			ans+=max(0ll,(lint)(n-k)*(n-k-1)/2);
		}
		for(int i=0;i*3<k;i++){
			ans+=cnt2(n-i*3,k-i*3)*2-1;
		}
		return ans;
	}
};