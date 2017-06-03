#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
struct letter{
	int times;
	letter* child[26];
	letter(){
		times=0;
		for(int i=0;i<26;i++){
			child[i]=0;
		}
	}
	letter* getstring(char data[35],int pos){
		if(data[pos]==0){
			return this;
		}
		if(child[data[pos]-'a']==0){
			child[data[pos]-'a']=new letter;
		}
		return (*child[data[pos]-'a']).getstring(data,pos+1);
	}
}root;
int main(){
	int n;
	cin>>n;
	bool found;
	letter* leaf;
	char cur[35];
	for(int i=0;i<n;i++){
		cin>>cur;
		leaf=root.getstring(cur,0);
		found=false;
		for(int j=0;j<i;j++){
			if((*leaf).times!=0){
				found=true;
				cout<<cur<<(*leaf).times<<endl;
				break;
			}
		}
		if(!found){
			cout<<"OK"<<endl;
		}
		(*leaf).times++;
	}
}