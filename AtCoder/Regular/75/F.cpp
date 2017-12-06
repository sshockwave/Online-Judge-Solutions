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
lint f[12][2][2];//[left need one][right has one]
int num[10],del,ns;
inline lint work(int d){
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
						int tmpr=rnum+num[r];
						if((tmpr>9)!=a)continue;
						int na,nb=tmpl/10;
						tmpl%=10,tmpr%=10;
						if(rnum!=tmpl)continue;
						if(lnum==tmpr+1){
							na=1;
						}else if(lnum==tmpr){
							na=0;
						}else continue;
						f[t+1][na][nb]+=F;
					}
				}
			}
		}
	}
	if(l>r)return f[t][0][0]+f[t][1][1];
	return (9-num[l])*f[t][0][0]+(8-num[l])*f[t][0][1]+num[l]*f[t][1][0]+(num[l]+1)*f[t][1][1];
}
inline lint Main(){
	del=ni;
	for(int &i=ns=0,t=del;t;num[i]=t%10,t/=10,i++);
	lint ans=0;
	for(int i=ns;i<=9;i++){
		ans+=work(i);
	}
	return ans;
}
int main(){
	printf("%lld\n",Main());
	return 0;
}
