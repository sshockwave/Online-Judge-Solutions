#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[10],n;
inline bool judge(){
	if(n%2){
		return true;
	}
	sort(a,a+n);
	for(int i=0;i<n;i+=2){
		if(a[i]!=a[i+1]){
			return true;
		}
	}
	return false;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	while(n){
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		cout<<judge()<<endl;
		cin>>n;
	}
}
