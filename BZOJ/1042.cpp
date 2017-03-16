#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#define S 100010
using namespace std;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
long long f[S],ans,c[4],d[4],s;
inline long long getf(int tr){
	long long sum=s;
	int sig=1;
	for(int i=0;i<4;i++){
		if((tr>>i)&1){
			sum-=(d[i]+1)*c[i];
			if(sum<0){
				return 0;
			}
			sig*=-1;
		}
	}
	return f[sum]*sig;
}
int main(){
	memset(f,0,sizeof(f));
	f[0]=1;
	for(int i=0;i<4;i++){
		c[i]=ni();
		for(int j=0;j+c[i]<S;j++){
			f[j+c[i]]+=f[j];
		}
	}
	ans=0;
	for(int tot=ni();tot--;){
		for(int i=0;i<4;i++){
			d[i]=ni();
		}
		s=ni();
		for(int i=0;i<16;i++){
			ans+=getf(i);
		}
		printf("%d\n",ans);
	}
}
