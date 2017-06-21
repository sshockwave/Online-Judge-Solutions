#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
const int N=55;
lint f[N][N*2];
class MonstersValley{
	public:
	int minimumPrice(vector<lint>dread,vector<int>price){
		int n=dread.size();
		memset(f,-1,sizeof(f));
		memset(f[0],0,sizeof(f[0]));
		int sum=0;
		for(int i=1;i<=n;i++){
			int w=price[i-1];
			lint d=dread[i-1];
			sum+=w;
			for(int j=0;j<=sum;j++){
				if(j){
					f[i][j]=f[i][j-1];
				}
				if(f[i-1][j]>=d){
					apmax(f[i][j],f[i-1][j]);
				}
				if(j>=w&&~f[i-1][j-w]){
					apmax(f[i][j],f[i-1][j-w]+d);
				}
			}
		}
		int ans=0;
		for(;f[n][ans]==-1;ans++);
		return ans;
	}
};