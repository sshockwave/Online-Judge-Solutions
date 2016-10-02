#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int n;
int cal(int x){
	if(x==1){
		return 10%n;
	}
	int tmp=cal(x/2);
	tmp=(tmp*tmp)%n;
	if(x%2==1){
		tmp*=10;
	}
	tmp%=n;
	return tmp;
}
int main(){
	int m,k,x;
	scanf("%d%d%d%d",&n,&m,&k,&x);
	//cal:(x+m*(10^k))%n
	cout<<(x+m*cal(k))%n<<endl;
}
