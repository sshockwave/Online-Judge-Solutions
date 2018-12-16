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
template<class T>inline void mset(T a[],int v,int n){memset(a,v,n*sizeof(T));}
template<class T>inline void mcpy(T a[],T b[],int n){memcpy(a,b,n*sizeof(T));}
template<class T>inline T gcd(const T &a,const T &b){return b?gcd(b,a%b):a;}
const int N=1000010;
char s[N];
namespace bsgs{
	const int O=1000000009,M=100007;
	const int rt=31622;
	map<int,int>mp[M];
	inline int fpow(int x,int n){
		int a=1;
		for(;n;n>>=1,x=(lint)x*x%O){
			if(n&1){
				a=(lint)a*x%O;
			}
		}
		return a;
	}
	inline int inv_pow(int x){
		return fpow(x,O-2);
	}
	inline void ins(int x,int v){
		int t=x;
		t^=234123445;
		t%=M;
		mp[t][x]=v;
	}
	inline int ask(int x){
		int t=x;
		t^=234123445;
		t%=M;
		map<int,int>::iterator it=mp[t].find(x);
		if(it==mp[t].end())return -1;
		return it->second;
	}
	inline int main(int b){
		for(int i=0;i<M;i++){
			mp[i].clear();
		}
		int g=29,ig=inv_pow(g);
		assert((lint)g*ig%O==1);
		int pwg=b;
		for(int i=0,pw=1;i<rt;i++){
			ins(pw,i);
			pw=(lint)pw*ig%O;
			pwg=(lint)pwg*g%O;
		}
		int ppw=1;
		int ans;
		for(int i=0;i*rt<O;i++){
			int t=ask(ppw);
			if(t!=-1){
				ans=(i*rt+t)%(O-1);
			}
			ppw=(lint)ppw*pwg%O;
		}
		return ans;
	}
}
inline bool Main(){
	scanf("%s",s);
	const int k=ni;
	int num=0;
	for(int i=0;s[i];i++){
		num=(num*10ll+s[i]-'0')%bsgs::O;
	}
	int b=bsgs::main(num);
	return b%gcd(k,bsgs::O-1)==0;
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
#endif
	/*for(int g=2;;g++){
	  int w=1;
	  bool flag=true;
	  for(int i=1;i<bsgs::O-1;i++){
	  w=(lint)w*g%bsgs::O;
	  if(w==1){
	  cout<<"g="<<g<<"\tfail on "<<i<<endl;
	  flag=false;
	  break;
	  }
	  }
	  if(flag){
	  cout<<"g="<<g<<" "<<"ok!!!!!"<<endl;
	  }
	  }*/
	for(int tot=ni;tot--;){
		puts(Main()?"Y":"N");
	}
	return 0;
}
