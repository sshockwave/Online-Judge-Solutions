#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
double fpow(double x,int y){//x**y
	if(y==0){
		return 1;
	}
	double tmp=fpow(x,y>>1);
	return tmp*tmp*(y&1?x:1);
}
int main(){
	
}
