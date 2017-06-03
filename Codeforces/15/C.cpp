#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
long long xorto(long long n){
	long long from=n-(n%4),result=0;
	for(;from<=n;from++){
		result^=from;
	}
	return result;
}
int main(){
	int n;
	long long x,m,re=0;
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x>>m;
		re=re^xorto(x-1)^xorto(x+m-1);
	}
	if(re){
		cout<<"tolik"<<endl;
	}else{
		cout<<"bolik"<<endl;
	}
}