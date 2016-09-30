#include <iostream>
#include <cstdio>
#include <cstring>
#define N 150010
using namespace std;
int value[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m,a,b,sum=0;
	char op;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>value[i];
	}
	while(m--){
		cin>>op>>a>>b;
		if(op=='A'){
			sum=0;
			for(int i=b;i<=n;i+=a){
				sum+=value[i];
			}
			cout<<sum<<endl;
		}else{
			value[a]=b;
		}
	}
}
