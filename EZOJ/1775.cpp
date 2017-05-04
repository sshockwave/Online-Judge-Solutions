#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
using namespace std;
typedef long long lint;
inline bool is_num(char c){
	return c>='0'&&c<='9';
}
inline int ni(){
	int i=0;char c;
	while(!is_num(c=getchar()));
	while(i=i*10-'0'+c,is_num(c=getchar()));
	return i;
}
int main(){
	double a,b,l,r,sqrtb;
	for(int tot=ni();tot--;){
		scanf("%lf%lf%lf%lf",&l,&r,&a,&b);
		sqrtb=sqrt(b);
		printf("%.8lf\n",sqrt(a/b)*(r*sqrt(b-r*r)+b*(acos(l/sqrtb)-acos(r/sqrtb))-l*sqrt(b-l*l))/2);
	}
}
