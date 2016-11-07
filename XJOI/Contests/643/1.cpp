#include <iostream>
#include <cstdio>
#include <cstring>
#define DIV 1000000000
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	long long a,b;
	while(cin>>a>>b){
		if((a<DIV&&a>=-DIV)||a+b==DIV){
			cout<<"no"<<endl;
		}else if(a==DIV){
			if(b==0){
				cout<<"no"<<endl;
			}else{
				cout<<"yes"<<endl;
			}
		}else{
			cout<<"yes"<<endl;
		}
	}
}
