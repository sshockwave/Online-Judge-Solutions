#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[30];
int line=0;
struct scope{
	bool init[26],reach;
	scope(){
		memset(init,0,sizeof(init));
		reach=true;
	}
};
inline void error1(char c,scope &p){
	if(!p.init[c-'A']){
		cout<<"Line "<<line<<": variable "<<c<<" might not have been initialized"<<endl;
	}
}
inline void expect(scope &p){
	bool warned[26]={0};
	for(int i=0;s[i];i++){
		if(s[i]>='A'&&s[i]<='Z'&&!warned[s[i]-'A']){
			error1(s[i],p);
			warned[s[i]-'A']=true;
		}
	}
}
scope process(scope p){
	while(line++,cin>>s){
		if(s[0]=='E'&&s[1]){//else and endif
			if(s[1]=='N'){
				cin>>s;
			}
			return p;
		}
		if(!p.reach){
			cout<<"Line "<<line<<": unreachable code"<<endl;
			cin.getline(s,30);
			continue;
		}
		if(s[1]==0){//assignment
			int tmp=s[0]-'A';
			cin.getline(s,30);
			expect(p);
			p.init[tmp]=true;
			continue;
		}
		switch(s[0]){
			case 'I':{
				cin>>s;
				expect(p);
				cin>>s>>s;
				expect(p);
				cin>>s;
				scope t=process(p);
				if(s[1]=='E'){//else
					scope f=process(p);
					p.reach=t.reach||f.reach;
					for(int i=0;i<26;i++){
						p.init[i]=t.init[i]&&f.init[i];
					}
				}
				break;
			}
			case 'R':{//return
				cin.getline(s,30);
				expect(p);
				p.reach=false;
				break;
			}
			case 'P':{
				cin.getline(s,30);
				for(int i=0;s[i];i++){
					if(s[i]>='A'&&s[i]<='Z'){
						p.init[s[i]-'A']=true;
					}
				}
				break;
			}
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	process(scope());
}
