#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#define N 1000010
using namespace std;
int euler(int n){
	int x=n;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			x-=x/i;
			while(n%i==0){
				n/=i;
			}
		}
	}
	if(n>1){//n is prime
		x-=x/n;
	}
	return x;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	for(cin>>n;n;cin>>n){
		cout<<euler(n)<<endl;
	}
}
