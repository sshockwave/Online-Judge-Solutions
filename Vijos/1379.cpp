#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int p1,p2,p3;
char s[10010];
inline bool isdigit(char c){
	return c>='0'&&c<='9';
}
inline bool isletter(char c){
	return c>='a'&&c<='z';
}
inline void apply1(char c){
	if(p1==2){
		c-=32;
	}else if(p1==3){
		c='*';
	}
	cout<<c;
}
inline void apply2(char c){
	for(int i=0;i<p2;i++){
		apply1(c);
	}
}
inline void apply3(char a,char b){
	if(p3==1){
		for(;a<=b;a++){
			apply2(a);
		}
	}else if(p3==2){
		for(;a<=b;b--){
			apply2(b);
		}
	}
}
int main(){
	cin>>p1>>p2>>p3>>s;
	for(int i=0;s[i];i++){
		if(s[i]=='-'&&i&&s[i+1]&&s[i-1]<s[i+1]&&((isdigit(s[i-1])&&isdigit(s[i+1]))||(isletter(s[i-1])&&isletter(s[i+1])))){//missed brackets
			if(s[i-1]+1!=s[i+1]){
				apply3(s[i-1]+1,s[i+1]-1);
			}
		}else{
			cout<<s[i];
		}
	}
}
