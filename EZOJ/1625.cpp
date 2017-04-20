#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
using namespace std;
typedef long long lint;
#define ni (next_num<int>())
#define nl (next_num<lint>())
template<typename T>inline T next_num(){
	T i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline void apmax(int &a,int b){
	if(a<b){
		a=b;
	}
}
const int N=2000010;
char s[N];
int rad[N];
int main(){
	int n=0,ans=0;
	s[n++]='{';
	s[n++]='#';
	char c;
	while(isalpha(s[n++]=getchar())){
		s[n++]='#';
	}
	s[n-1]='#';
	s[n]='}';
	memset(rad,0,sizeof(rad));
	for(int i=1,j,p=0,mx=0;i<n;i++){
		if(mx>i){
			j=min(min(i-p,mx-i),rad[(p<<1)-i]);
		}else{
			j=0;
		}
		for(;s[i-j]==s[i+j];j++);
		rad[i]=--j;
		if(i+j>mx){
			mx=i+j,p=i;
		}
		apmax(ans,rad[i]);
	}
	printf("%d\n",ans);
}
