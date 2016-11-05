#include <iostream>
#include <cstdio>
#include <cstring>
#define MOD 1000000007
#define N 100010
using namespace std;
char s[N],t[N],seq[N],cnt=0;
int n,k;
bool dfs(int i,int diff){
	if(diff<0){
		return false;
	}
	if(i==n){//check
		if(diff){
			return false;
		}
		cnt=(cnt+1)%MOD;
		for(int i=0;i<n;i++){
			if(seq[i]!=t[i]){
				return false;
			}
		}
		return true;
	}
	seq[i]='a';
	for(char &c=seq[i];c<='z';c++){
		if(dfs(i+1,diff-(c!=s[i]))){
			return true;
		}
	}
	return false;
}
int main(){
	scanf("%d%d%s%s",&n,&k,s,t);
	seq[n]=0;
	dfs(0,k);
	printf("%d",cnt);
}
