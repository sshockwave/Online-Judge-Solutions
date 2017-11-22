#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
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
const int N=1010,O=1000000007;
struct Mat{
	const static int D=3;
	int a[D][D];
	inline friend Mat operator * (const Mat &a,const Mat &b){
		Mat c;
		for(int i=0;i<D;i++){
			for(int j=0;j<D;j++){
				lint tmp=0;
				for(int k=0;k<D;k++){
					tmp+=(lint)a.a[i][k]*b.a[k][j]%O;
				}
				c.a[i][j]=tmp%O;
			}
		}
		return c;
	}
	inline void fpow(Mat &res,int n){
		if(n==0){
			res=(Mat){1,0,0,0,1,0,0,0,1};
			return;
		}
		fpow(res,n>>1);
		res=res*res;
		if(n&1){
			res=res**this;
		}
	}
}trans1={1,2,1,0,1,1,1,2,2},trans2=(Mat){1,2,1,0,1,1,0,0,1};
int main(){
	int n=ni,m=ni,x=0;
	Mat ans,tmp;
	tmp.fpow(ans,0);
	for(int i=1,j;i<=m;i++){
		trans1.fpow(tmp,(j=ni)-x-1);
		ans=trans2*tmp*ans;
		x=j;
	}
	trans1.fpow(tmp,n-x-1);
	ans=tmp*ans;
	printf("%lld\n",((lint)ans.a[0][2]+(ans.a[1][2]<<1)+ans.a[2][2])%O);
	return 0;
}
