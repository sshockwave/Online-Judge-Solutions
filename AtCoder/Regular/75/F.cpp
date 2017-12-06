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
	flag?c=getchar():0;
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
template<class T1,class T2>inline void apmax(T1 &a,const T2 &b){if(a<b)a=b;}
template<class T1,class T2>inline void apmin(T1 &a,const T2 &b){if(b<a)a=b;}
const int N=25;
lint f[N][2][2];//[left need one][right has one]
int num[N],del,ns;
inline lint work(int d){
	if(d==1)return 0;
	memset(f,0,sizeof(f));
	f[0][0][0]=1;
	int l=0,r=d-1,t=0;
	for(;l<r;l++,r--,t++){
		for(int a=0;a<2;a++){
			for(int b=0;b<2;b++){
				lint F=f[t][a][b];
				if(F==0)continue;
				for(int lnum=0;lnum<=9;lnum++){
					for(int rnum=l==0;rnum<=9;rnum++){
						int tmpl=lnum+num[l]+b;
						int tmpr=rnum+num[r]-a*10;
						int na=0,nb=tmpl/10;
						if(tmpr<0){
							tmpr+=na=1;
						}
						if(tmpr<0||tmpr>9)continue;
						tmpl%=10;
						if(rnum!=tmpl)continue;
						if(lnum!=tmpr){
							tmpr+=1-na;
							na=1;
						}
						if(lnum!=tmpr)continue;
						f[t+1][na][nb]+=F;
					}
				}
			}
		}
	}
	if(l>r)return f[t][0][0]+f[t][1][1];
	return (num[l]==0)*10*f[t][0][0]+(num[l]==9)*10*f[t][1][1];
}
inline lint Main(){
	del=ni;
	for(int &i=ns=0,t=del;t;num[i]=t%10,t/=10,i++);
	lint ans=0;
	for(int i=ns;i<=20;i++){
		ans+=work(i);
	}
	return ans;
}
int main(){
	printf("%lld\n",Main());
	return 0;
}
