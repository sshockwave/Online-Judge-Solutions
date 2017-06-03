#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
bool judge(char s[50]){
	if(s[0]=='R'){
		if(s[1]>'Z'||s[1]<'A'){
			int l=strlen(s);
			for(int i=2;i<l;i++){
				if(s[i]=='C'){
					return true;
				}
			}
		}
	}
	return false;
}
int main(){
	int n,l;
	cin>>n;
	char s[50];
	while(n--){
		cin>>s;
		l=strlen(s);
		if(judge(s)){
			int m=0,n=0,i;
			for(i=1;s[i]!='C';i++){
				m=10*m+s[i]-'0';
			}
			for(i++;i<l;i++){
				n=10*n+s[i]-'0';
			}
			int o[100];
			memset(o,0,sizeof(o));
			i=0;
			while(n>0){
				o[i]=(n-1)%26+'A';
				n=(n-1)/26;
				i++;
			}
			for(i--;i>=0;i--){
				cout<<(char)o[i];
			}
			cout<<m<<endl;
		}else{
			int m=0,n=0,i;
			for(i=0;s[i]<='Z'&&s[i]>='A';i++){
				n=n*26+s[i]-'A'+1;
			}
			for(;i<l;i++){
				m=10*m+s[i]-'0';
			}
			cout<<"R"<<m<<"C"<<n<<endl;
		}
	}
}