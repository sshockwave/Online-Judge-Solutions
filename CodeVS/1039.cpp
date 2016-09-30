#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int dfs(int n,int k,int i){
	if(n==0||k==0){
		return n==0&&k==0;
	}
	int sum=0;
	for(;i<=n;i++){
		sum+=dfs(n-i,k-1,i);
	}
	return sum;
}
int main(){
	int n,k;
	cin>>n>>k;
	cout<<dfs(n,k,1)<<endl;
}
