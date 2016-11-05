#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#define M 55
using namespace std;
int a[M],len,n;
set<int>s;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
int dfs(int x,int lcm){
	if(x==len){
		return (n-1)/lcm;
	}
	int tmp=a[x]/gcd(a[x],lcm)*lcm;
	if(tmp==lcm){
		return 0;
	}
	return dfs(x+1,lcm)-dfs(x+1,tmp);
}
int main(){
	int m,cur;
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d",&cur);
		s.insert(gcd(n,cur));
	}
	set<int>::iterator it=s.begin();
	len=s.size();
	for(int i=0;i<len;i++,it++){
		a[i]=(*it);
	}
	printf("%d",dfs(0,1));
}
