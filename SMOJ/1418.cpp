#include <iostream>
#include <cstdio>
#include <cstring>
#define L 1010
using namespace std;
int stop=0;
char s[L],stk[L];
inline bool judge(){
	stop=0;
	for(int i=0;s[i];i++){
		if(s[i]=='('||s[i]=='{'||s[i]=='['){
			stk[stop++]=s[i];
		}else{
			stop--;
			if(stop<0){
				return false;
			}
			switch(s[i]){
				case ')':{
					if(stk[stop]!='('){
						return false;
					}
					break;
				}
				case ']':{
					if(stk[stop]!='['){
						return false;
					}
					break;
				}
				case '}':{
					if(stk[stop]!='{'){
						return false;
					}
					break;
				}
			}
		}
	}
	return stop==0;
}
int main(){
	freopen("1418.in","r",stdin);
	freopen("1418.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--){
		stop=0;
		scanf("%s",s);
		if(judge()){
			printf("yes\n");
		}else{
			printf("no\n");
		}
	}
}
