#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
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
const int N=1010;
inline lint lb(lint x){
	return x&-x;
}
inline lint hb(lint x){
	for(;x!=lb(x);x^=lb(x));
	return x;
}
lint a[N];
bool d[N];
bool dfs(int x,lint fl,lint fr){
	if(x==0){
		assert(fl==0&&fr==0);
		return true;
	}
	if(a[x]<=lb(fl)){
		d[x]=0;
		if(fl==lb(fl)){
			lint tmp=hb(fl-a[x]);
			if(!(tmp&fr)){
				lint nfr=fr^fl^tmp,nfl=hb(nfr)|(fl-a[x]);
				if(dfs(x-1,nfl,nfr)){
					return true;
				}
			}
		}else if(dfs(x-1,fl-a[x],fr)){
			return true;
		}
	}
	if(fl!=fr&&a[x]<=lb(fr)){
		d[x]=1;
		if(fr==lb(fr)){
			lint tmp=hb(fr-a[x]);
			if(!(tmp&fl)){
				lint nfl=fl^fr^tmp,nfr=hb(nfl)|(fr-a[x]);
				if(dfs(x-1,nfl,nfr)){
					return true;
				}
			}
		}else if(dfs(x-1,fl,fr-a[x])){
			return true;
		}
	}
	return false;
}
inline void Main(){
	int n=ni;
	lint sum=0;
	for(int i=1;i<=n;i++){
		a[i]=nl;
		sum+=a[i];
	}
	if(sum==lb(sum)&&dfs(n,sum,sum)){
		for(int i=1;i<=n;i++){
			putchar(d[i]?'r':'l');
		}
		putchar('\n');
	}else{
		puts("no");
	}
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("2048.in","r",stdin);
	freopen("2048.out","w",stdout);
#endif
	for(int tot=ni;tot--;Main());
	return 0;
}
