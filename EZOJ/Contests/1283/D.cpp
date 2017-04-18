#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline lint nl(){
	lint i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
inline void apmin(lint &a,lint b){
	if(a>b){
		a=b;
	}
}
inline void apmax(lint &a,lint b){
	if(a<b){
		a=b;
	}
}
const int N=1010;
lint val[N],_val[N],f[N];
inline void brute(int n){
	lint mx=nl(),sum=0,ans=0,curmx=0;
	for(int i=1;i<=n;i++){
		lint cur=nl();
		if(sum+cur>mx){
			ans+=curmx;
			curmx=sum=0;
		}
		sum+=cur;
		apmax(curmx,cur);
	}
	printf("%lld\n",ans+curmx);
}
int main(){
	int n=ni();
	if(n>3000){
		brute(n);
		return 0;
	}
	lint lim=nl(),sum;
	_val[0]=0;
	memset(f,127,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++){
		val[i]=nl();
		_val[i]=_val[i-1]+val[i];
		lint mx=val[i];
		for(int j=i-1;j>=0&&_val[i]-_val[j]<=lim;j--){
			apmin(f[i],mx+f[j]);
			apmax(mx,val[j]);
		}
	}
	printf("%lld\n",f[n]);
}
