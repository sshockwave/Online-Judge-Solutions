#include <cstring>
#include <string>
using namespace std;
typedef long long lint;
class Entropy{
	private:
		bool odd;
		int n,half;
		char s[65];
		inline lint rev(lint x){
			lint ans=0;
			for(int i=0;i<n;i++){
				ans<<=1,ans|=(x&1)^1,x>>=1;
			}
			return ans;
		}
	public:
		lint getM(int N){
			n=N;
			odd=n&1;
			half=n>>1;
			s[n]=0;
			if(odd){
				return 1ll<<(n-1);
			}else{
				return ((1ll<<n)+(1ll<<half))>>1;
			}
		}
		string encode(lint x){
			memset(s,'0',n);
			if(odd){
				for(int i=0;i<half;i++){
					s[i]+=((x>>i)&1);
				}
				for(int i=half+1;i<n;i++){
					s[i]+=((x>>(i-1))&1);
				}
			}else if(x<(1ll<<half)){
				for(int i=0;i<half;i++){
					s[i]+=((x>>i)&1);
				}
				for(int i=half;i<n;i++){
					s[i]+=((x>>(n-i-1))&1)^1;
				}
			}else{
				x-=1ll<<half;
				lint lo=1;
				{
					lint l=1,r=1ll<<half,mid;
					while(l<r){
						mid=(l+r)>>1;
						if(x<((mid*(mid+1))>>1)){
							r=mid;
						}else{
							l=mid+1;
						}
					}
					lo=l;
					x-=lo*(lo-1)>>1;
				}
				for(int i=0;i<half;i++){
					s[i]+=(lo>>i)&1;
				}
				x=rev(x);
				for(int i=half;i<n;i++){
					s[i]+=(x>>i)&1;
				}
			}
			return string(s);
		}
		lint decode(string s){
			lint x=0;
			for(int i=n-1;i>=0;i--){
				x=(x<<1)|(s[i]-'0');
			}
			if(odd){
				if(s[half]-'0'){
					x=rev(x);
				}
				x=(x^(x>>(half+1)<<(half+1)))|(x>>(half+1)<<half);
				return x;
			}else{
				if(x==rev(x)){
					return x&((1ll<<half)-1);
				}
				lint hi=x>>half<<half,lo=x^hi;
				hi=rev(hi|((1ll<<half)-1));
				if(lo<hi){
					swap(lo,hi);
				}
				lint ans=(lo*(lo-1))>>1;
				ans+=hi;
				ans+=1ll<<half;
				return ans;
			}
			return 0;
		}
};
#include "entropy.h"
