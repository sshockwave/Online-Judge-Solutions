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
	bool neg=c=='-';
	neg?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return neg?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
template<class T>inline void mset(T a,int v,int n){memset(a,v,n*sizeof(a[0]));}
const int L=110,O=1000000007;
struct pii{
	lint a,b;//a>=b
	pii(lint _a,lint _b):a(_a),b(_b){
		assert(a>=b);
	};
};
typedef vector<pii>vi;
vi sed[L];
lint f[L];
inline bool psh(int k,lint a,lint b){
	if(a<b){
		swap(a,b);
	}
	assert(k>=2);
	if(a>=f[k+1]+f[k-2])return false;
	sed[k].push_back(pii(a,b));
	return true;
}
inline void pre_work(){
	f[1]=2,f[0]=1;
	int tlev;
	for(int &i=tlev=2;f[i-1]<=3000000000000000000ll;i++){
		f[i]=f[i-1]+f[i-2];
	}
	sed[1].push_back(pii(2,1));
	sed[1].push_back(pii(3,1));
	sed[1].push_back(pii(4,1));
	sed[1].push_back(pii(5,1));
	for(int i=1;i<tlev;i++){
		for(vi::iterator it=sed[i].begin(),ti=sed[i].end();it!=ti;++it){
			lint a=it->a,b=it->b;
			for(lint c=a+b;psh(i+1,c,a);c+=a);
		}
	}
}
inline int work(vi &vec,lint A,lint B){
	int cnt=0;
	for(vi::iterator it=vec.begin(),ti=vec.end();it!=ti;++it){
		lint a=it->a,b=it->b;
		//k*a+b,a
		if(a>B)continue;
		if(b>A)continue;
		cnt=(cnt+(A-b)/a)%O;
	}
	return cnt;
}
int ans,anscnt;
inline void Main(){
	lint a=next_num<lint>(),b=next_num<lint>();
	if(a<b){
		swap(a,b);
	}
	ans=1;
	for(;a>=f[ans+1]&&b>=f[ans];++ans);
	if(ans==1){
		anscnt=a*b%O;
	}else{
		anscnt=(work(sed[ans-1],a,b)+work(sed[ans-1],b,a))%O;
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("gcd.in","r",stdin);
	freopen("gcd.out","w",stdout);
#endif
	pre_work();
	for(int tot=ni;tot--;){
		Main();
		printf("%d %d\n",ans,anscnt);
	}
	return 0;
}
