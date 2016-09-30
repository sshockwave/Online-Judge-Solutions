#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
long long extended_gcd(long long a,long long b,long long &x,long long &y){
	if(b==0){
		x=1;y=0;
		return a;
	}
	int t=extended_gcd(b,a%b,y,x);
	y-=a/b*x;
	return t;
}
int main(){
	long long a,b,d,x,y;
	cin>>a>>b;
	d=extended_gcd(a,b,x,y);
	cout<<(x/d%b+b)%b;
}
