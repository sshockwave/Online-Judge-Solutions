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
	ios::sync_with_stdio(false);
	cin.tie(0);
	long double a,b,l,r,sqrtb;
	for(int tot=ni();tot--;){
		cin>>l>>r>>a>>b;
		sqrtb=sqrt(b);
		cout<<sqrt(a/b)*(r*sqrt(b-r*r)+b*(acos(l/sqrtb)-acos(r/sqrtb))-l*sqrt(b-l*l))/2<<endl;
	}
}
