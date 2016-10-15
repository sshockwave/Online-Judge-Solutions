#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[]="0123456789ABCDEF";
inline int diymod(int a,int b){
	if(b<0){
		b=-b;
	}
	return (a%b+b)%b;
}
void printnum(int n,int a){
	if(n==0){
		return;
	}
	printnum((n-diymod(n,a))/a,a);
	cout<<s[diymod(n,a)];
}
int main(){
	for(int n,a;cin>>n>>a;){
		cout<<n<<"=";
		if(n==0){
			cout<<0;
		}else{
			printnum(n,a);
		}
		cout<<"(base "<<a<<")"<<endl;
	}
}
