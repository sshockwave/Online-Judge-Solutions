#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=1000010;
int rest[N],sg[N];
int prime[N],ps=0;
bool np[N];
lint num[10000];
class TheDivisionGame{
	public:
		long long countWinningIntervals(int L,int R){
			memset(np,0,sizeof(np));
			int n=min(R,100000);
			for(int i=2;i<=n;i++){
				if(!np[i]){
					prime[ps++]=i;
				}
				for(int j=0,cur=2;j<ps&&i*cur<=n;cur=prime[++j]){
					np[i*cur]=true;
					if(i%cur==0){
						break;
					}
				}
			}
			for(int i=L;i<=R;i++){
				rest[i-L]=i;
			}
			memset(sg,0,sizeof(sg));
			for(int j=0,cur=2;j<ps&&cur<=R;cur=prime[++j]){
				for(int i=cur*(L/cur+(L%cur!=0));i<=R;i+=cur){
					for(;rest[i-L]%cur==0;rest[i-L]/=cur,sg[i-L]++);
				}
			}
			memset(num,0,sizeof(num));
			lint ans=(lint)(R-L+1)*(R-L+2)>>1;
			int pre=0;
			num[pre]=1;
			for(int i=L;i<=R;i++){
				if(rest[i-L]!=1){
					sg[i-L]++;
				}
				pre^=sg[i-L];
				ans-=num[pre];
				num[pre]++;
			}
			return ans;
		}
};
int main(){
	cout<<TheDivisionGame().countWinningIntervals(12566125,12567777)<<endl;
}
