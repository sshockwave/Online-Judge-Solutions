#include <iostream>
#include <cstdio>
#include <cstring>
#define M 10000
using namespace std;
int digit[M],rev[M],n,dtop;
char s[M];
inline void getrev(){
	for(int i=0;i<dtop;i++){
		rev[dtop-i-1]=digit[i];
	}
}
inline bool judge(){
	for(int i=0;i<dtop;i++){
		if(digit[i]!=rev[i]){
			return false;
		}
	}
	return true;
}
inline void addup(){
	for(int i=0;i<dtop;i++){
		digit[i]+=rev[i];
		digit[i+1]+=digit[i]/n;//=  =>  +=
		digit[i]%=n;
	}
	for(;digit[dtop];dtop++);
}
int main(){
	memset(digit,0,sizeof(digit));
	cin>>n>>s;
	dtop=strlen(s);
	int cnt=0;
	for(int i=0;s[i];i++){
		if(s[i]>='A'){
			digit[dtop-i-1]=s[i]-'A'+10;
		}else{
			digit[dtop-i-1]=s[i]-'0';
		}
	}
	while(getrev(),!judge()&&cnt<=30){
		addup();
		cnt++;
	}
	if(cnt>30){
		cout<<"Impossible!";
	}else{
		cout<<"STEP="<<cnt;
	}
}
