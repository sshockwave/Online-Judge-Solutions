#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <vector>
using namespace std;
typedef long long lint;
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
const int N=100,O=1000000007;
const lint L=1000000000000000000ll;
lint fib[N];
inline int gstep(lint x,lint y){
	if(x>y){
		swap(x,y);
	}
	int ans=0;
	for(int &i=ans;fib[i]<=x&&fib[i+1]<=y;i++);
	return max(ans-1,1);
}
struct pii{
	lint a,b;
};
vector<pii>vec[N];
inline void Main(){
	lint x=next_num<lint>(),y=next_num<lint>();
	int step=gstep(x,y);
	printf("%d ",step);
	if(step==1){
		printf("%lld\n",x%O*(y%O)%O);
		return;
	}
	lint ans=0;
	for(int i=0,ti=vec[step-1].size();i<ti;i++){
		lint a=vec[step-1][i].a,b=vec[step-1][i].b;
		assert(a<b);
		if(b<=x){
			ans+=max((y-a)/b,0ll)%O;
		}
		if(b<=y){
			ans+=max((x-a)/b,0ll)%O;
		}
	}
	printf("%lld\n",ans%O);
}
int main(){
	fib[0]=1,fib[1]=1;
	int fibcnt;
	for(int &i=fibcnt=1;fib[i]<=L;i++){
		fib[i+1]=fib[i]+fib[i-1];
	}
	vec[0].push_back((pii){1,1});
	for(int i=0;i<fibcnt;i++){
		for(int j=0,tj=vec[i].size();j<tj;j++){
			lint x=vec[i][j].a,y=vec[i][j].b;
			assert(x<=y);
			while(x+=y,x<fib[i+3]+fib[i]){
				assert(y>=fib[i+1]&&x>=fib[i+2]);
				assert(y<fib[i+2]||x<fib[i+3]);
				vec[i+1].push_back((pii){y,x});
			}
		}
	}
	for(int tot=ni;tot--;){
		Main();
	}
	return 0;
}
