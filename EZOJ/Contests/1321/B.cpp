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
	bool flag=c=='-';
	flag?(c=getchar()):0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
inline void apmin(int &a,const int &b){
	if(b<a){
		a=b;
	}
}
const int N=4010,D=26,INF=0x7f7f7f7f;
char s[N],t[N];
int f[N][N];
struct incque{
	struct rint{
		int j;
		rint(int _j):j(_j){}
		inline friend bool operator < (const rint &a,const rint &b){
			return a.j>b.j;
		}
	};
	typedef map<rint,int>mii;
	mii m;
	inline void push(int i,int v){
		mii::iterator it=m.find(rint(i));
		if(it==m.end()){
			m[rint(i)]=v;
			it=m.find(rint(i));
		}else{
			if(it->second<=v){
				return;
			}
			it->second=v;
		}
		while(true){
			assert(it!=m.end());
			if(it==m.begin()){
				return;
			}
			it--;
			if(it->second>=v){
				m.erase(it);
			}else{
				return;
			}
			it=m.find(rint(i));
		}
	}
	inline int ask(int i){//find j<i
		mii::iterator it=m.upper_bound(rint(i));
		if(it==m.end()){
			return INF;
		}
		assert(it->first.j<i);
		return it->second;
	}
}g[D][D];
int main(){
#ifndef ONLINE_JUDGE
	freopen("string.in","r",stdin);
	freopen("string.out","w",stdout);
#endif
	int a=ni,b=ni,c=ni,d=ni,ab=a+b;
	scanf("%s%s",s+1,t+1);
	int lens=strlen(s+1),lent=strlen(t+1);
	memset(f,127,sizeof(f));
	for(int i=0;i<=lens;i++){
		f[i][0]=i*b;
	}
	for(int i=0;i<=lent;i++){
		f[0][i]=i*a;
	}
	for(int i=1;i<=lens;i++){
		for(int j=1;j<=lent;j++){
			int &F=f[i][j];
			apmin(F,f[i][j-1]+a);
			apmin(F,f[i-1][j]+b);
			if(s[i]==t[j]){
				apmin(F,f[i-1][j-1]);
			}else{
				apmin(F,f[i-1][j-1]+c);
			}
			if(d>=ab){
				continue;
			}
			int G=g[t[j]-'a'][s[i]-'a'].ask(j);
			if(G<INF){
				apmin(F,(lint)G+a*j+b*i+d-ab);
			}
			assert(F>=0);
		}
		if(d>=ab){
			continue;
		}
		if(i==lens){
			break;
		}
		for(int j=1;j<=lent;j++){
			g[s[i]-'a'][t[j]-'a'].push(j,f[i-1][j-1]-a*j-b*i);
		}
	}
	printf("%d\n",f[lens][lent]);
}
