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
lint O;
inline lint mul(lint a,lint b){
	const static lint hO=100000;
	return (a/hO*b%O*hO%O+a%hO*b%O)%O;
}
inline lint _n1(lint n){
	return n&1?mul(n,(n+1)>>1):mul(n>>1,n+1);
}
inline lint _n2(lint n){
	lint a=n,b=n+1,c=(n<<1)+1;
	if(a&1){
		b>>=1;
	}else{
		a>>=1;
	}
	(a%3==0?a:b%3==0?b:c)/=3;
	return mul(a,mul(b,c));
}
inline lint work(int x,int y){
	if(x==0||y==0){
		return 0;
	}
	lint w=min(x,y),ans=_n1(mul(w,w));
	if(w<=x){
		(ans+=mul((_n2(x-1)-_n2(w-1)+O)%O,y)+mul(_n1(y),x-w))%=O;
	}
	if(w<=y){
		(ans+=mul((_n2(y)-_n2(w)+O)%O,x)+mul(_n1(x-1),(w-y+O)%O))%=O;
	}
	return ans;
}
inline void Main(){
	int x1=ni,y1=ni,x2=ni,y2=ni;
	swap(x1,y1),swap(x2,y2);
	O=10000000000ll;
	lint ans1=(work(x2,y2)-work(x1-1,y2)-work(x2,y1-1)+work(x1-1,y1-1)+O)%O;
	O=10298157053ll;
	lint ans2=(work(x2,y2)-work(x1-1,y2)-work(x2,y1-1)+work(x1-1,y1-1)+O)%O;
	printf(ans1==ans2?"%I64d\n":"...%010I64d\n",ans1);
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("endless.in","r",stdin);
	freopen("endless.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
