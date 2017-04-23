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
	T i=0;char c;bool flag=false;
	while(!isdigit(c=getchar())&&c!='-');
	if(c=='-'){
		flag=true;
		c=getchar();
	}
	while(i=i*10-'0'+c,isdigit(c=getchar()));
	return flag?-i:i;
}
const int N=55;
char s[N][N*2],forbid[N][N*2];
char stk[N*2];
int n,m,l,len[N];
inline bool match(char s[],char t[]){
	for(int i=0;t[i];i++){
		if(s[i]!=t[i]){
			return false;
		}
	}
	return true;
}
inline bool findmatch(char s[]){
	for(int i=0;i<l;i++){
		if(match(stk+i,s)){
			return true;
		}
	}
	return false;
}
inline bool checkvalid(){
	for(int i=1;i<=m;i++){
		if(findmatch(forbid[i])){
			return false;
		}
	}
	return true;
}
int dfs(char cur[],int rest){
	if(rest==0){
		cur[0]=0;
		return checkvalid();
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(len[i]<=rest){
			memcpy(cur,s[i],len[i]);
			ans+=dfs(cur+len[i],rest-len[i]);
		}
	}
	return ans;
}
int main(){
	n=ni,m=ni,l=ni;
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]);
		len[i]=strlen(s[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%s",forbid[i]);
	}
	printf("%d\n",dfs(stk,l));
}
