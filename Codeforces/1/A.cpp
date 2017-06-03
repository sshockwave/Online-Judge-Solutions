#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
	long long m,n,a,result=0;
	cin>>m>>n>>a;
	result+=n/a+(n%a!=0);
	result*=m/a+(m%a!=0);
	cout<<result;
}