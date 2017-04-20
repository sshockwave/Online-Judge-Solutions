#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <algorithm>
using namespace std;
typedef long long lint;
inline int ni(){
	int i=0;char c;
	while(!isdigit(c=getchar()));
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return i;
}
inline void apmax(int &a,const int &b){
	if(a<b){
		a=b;
	}
}
const int N=20010;
bool valid[N];
int f[N],len[N];
int main(){
	int n=ni(),totlen=ni(),ans=0;
	for(int i=1;i<=n;i++){
		len[i]=ni();
	}
	sort(len+1,len+n+1);
	memset(valid,0,sizeof(valid));
	memset(f,0,sizeof(f));
	valid[0]=true;
	len[0]=0,len[n+1]=N;
	for(int i=1;i<=n;i++){
		apmax(ans,len[i]+len[i-1]+f[totlen-len[i]]);
		for(int j=0,top=totlen-len[i];j<=top;j++){
			f[j]=valid[j]?j:f[j-1];
		}
		for(int j=totlen-len[i]-len[i+1];j>=0;j--){
			if(valid[j]){
				valid[j+len[i]]=true;
			}
		}
	}
	printf("%d\n",ans);
}
