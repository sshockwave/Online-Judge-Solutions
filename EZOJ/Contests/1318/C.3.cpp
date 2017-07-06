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
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){
	if(b<a){a=b;}
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){
	if(a<b){a=b;}
}
const int N=40000000;
int phi[N],prime[N],ps=0;
bool np[N];
inline void sieve(){
	memset(np,0,sizeof(np));
	for(int i=2;i<N;i++){
		if(!np[i]){
			prime[ps++]=i;
			phi[i]=i-1;
		}
		for(int j=0,cur=2;j<ps&&i*cur<N;cur=prime[++j]){
			np[i*cur]=true;
			if(i%cur==0){
				phi[i*cur]=phi[i]*cur;
				break;
			}else{
				phi[i*cur]=phi[i]*phi[cur];
			}
		}
	}
}
lint f[N];
lint mzz(lint n)
{
	if(n==1)return 1;
	lint t=phi[n];
	for(lint i=1;i<n;i++)
		if(n%i==0)
			t-=f[i]*(n/i);
	return t;
}
lint rzz(lint n,lint s)
{
	lint t=0;
	for(lint i=1;i<=n;i++)
		if(f[i]==s)t++;
	return t;
}
int main(){
	sieve();
	for(int i=0;i<10000;i++){
		f[i]=mzz(i);
	}
	for(int tot=ni;tot--;){
		lint m,fr,to;
		cin>>m;
		fr=to=0;
		for(int i=1;i<=m;i++)
			fr=min(fr,f[i]),to=max(to,f[i]);
		for(lint s=fr,k;s<=to;s++)
		{
			for(k=1;rzz(k,s)<=m;k++)
				if(rzz(k,s)==m)break;
			cout<<k;
			if(s==to)cout<<endl;
			else cout<<' ';
		}
	}
}
