#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
char s[1000010],t[10010];
int next[10010];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tot,k,l,cnt;
	for(cin>>tot;tot--;){
		cin>>t>>s;
		cnt=0;
		next[0]=-1;
		for(int i=0,j=-1;t[i];){
			if(j==-1||t[i]==t[j]){
				next[++i]=++j;
			}else{
				j=next[j];
			}
		}
		for(int i=0,j=0;s[i];){
			if(j==-1||s[i]==t[j]){
				i++,j++;
				if(t[j]==0){
					cnt++;
					j=next[j];
				}
			}else{
				j=next[j];
			}
		}
		cout<<cnt<<endl;
	}
}
