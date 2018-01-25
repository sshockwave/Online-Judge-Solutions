#include <bits/stdc++.h>
#include <termio.h>
using namespace std;
const int N=1000010;
char str[N];
inline int work(){
	ofstream fout("./cff.out");
	fout<<str<<endl;
	cout<<"current string:"<<str<<endl;
	int a=system("./checker");
	cout<<"Check complete"<<endl;
	return a>>8;
}

int getch(){
	struct termios tm, tm_old;
	int fd = 0, ch;
	if (tcgetattr(fd, &tm) < 0) {
		return -1;
	}
	tm_old = tm;
	cfmakeraw(&tm);
	if (tcsetattr(fd, TCSANOW, &tm) < 0) {
		return -1;
	}
	ch = getchar();
	if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
		return -1;
	}
	return ch;
}
inline void gethistory(){
	ifstream fin("./cff.out");
	fin>>str;
}
int main(){
	gethistory();
	int len=strlen(str);
	int state=work();
	while(true){
		char c=getch();
		cout<<"Input char:"<<c<<" ascii="<<(int)c<<endl;
		int bef=len;
		if(c==3)break;
		if(c==127){
			if(len==0){
				cout<<"already none"<<endl;
			}else{
				str[--len]=0;
			}
		}else if(c==27){
			getch();
			c=getch();
			char dir='A';
			for(int i=len-1;i>=0;i--){
				if(str[i]=='W'||str[i]=='S'||str[i]=='D'||str[i]=='A'){
					if(str[i]=='W'){
						dir='A';
					}else if(str[i]=='S'){
						dir='B';
					}else if(str[i]=='D'){
						dir='C';
					}else if(str[i]=='A'){
						dir='D';
					}
					break;
				}
			}
			if(c!=dir){
				dir=c;
				if(c=='A'){
					str[len++]='W';
				}else if(c=='B'){
					str[len++]='S';
				}else if(c=='C'){
					str[len++]='D';
				}else if(c=='D'){
					str[len++]='A';
				}
			}
			if((state>>(dir=='A'?0:dir=='B'?1:dir=='C'?3:2))&1){
				str[len++]='Q';
			}else{
				str[len++]='E';
			}
		}else{
			str[len++]=c;
		}
		str[len]=0;
		state=work();
		if(state>31){
			cout<<endl;
			len=bef;
			str[len]=0;
			state=work();
			cout<<"########## Error ##########"<<endl;
		}
	}
}
