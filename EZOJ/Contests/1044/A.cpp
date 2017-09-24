#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <map>
#include <vector>
using namespace std;
typedef long long lint;
typedef long double ld;
#define cout cerr
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
const int N=100010;
const lint LINF=0x7f7f7f7f7f7f7f7f;
lint gcd(lint a,lint b){
	return b==0?a:gcd(b,a%b);
}
lint a[N];
typedef map<lint,vector<int> > mlv;
mlv m;
int stk[N],ss=0;
lint val[N];
lint _xor[N];
int main(){
#ifndef ONLINE_JUDGE
	freopen("opening.in","r",stdin);
	freopen("opening.out","w",stdout);
#endif
	int n=ni;
	_xor[0]=0;
	for(int i=1;i<=n;i++){
		a[i]=nl;
		_xor[i]=a[i]^_xor[i-1];
	}
	lint target=nl;
	int l=-1,r=-1;
	stk[ss]=n+1,val[ss]=1,ss++;
	for(int i=n;i>=1;i--){
		for(;gcd(val[ss-1],a[i])!=val[ss-1];ss--);
		stk[ss]=i,val[ss]=a[i],ss++;
		m[_xor[i]].push_back(i);
		for(int j=ss-1;j;j--){
			if(target%val[j]==0){
				mlv::iterator it=m.find((target/val[j])^_xor[i-1]);
				if(it!=m.end()){
					int mn=stk[j],mx=stk[j-1];
					for(int k=it->second.size();k>=0;k++){
						if(it->second[k]>=mn&&it->second[k]<mx){
							l=i,r=it->second[k];
							break;
						}
					}
				}
			}
		}
	}
	if(~l){
		printf("%d %d\n",l,r);
	}else{
		puts("no solution");
	}
	return 0;
}
