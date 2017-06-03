#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int length[4];
bool judge(int a,int b,int c){
	return (a+b)>c&&(b+c)>a&&(a+c)>b;
}
bool judge2(int a,int b,int c){
	return (a+b)==c||(a+c)==b||(b+c)==a;
}
int main(){
	cin>>length[0]>>length[1]>>length[2]>>length[3];
	int input[3],top;
	for(int i=0;i<4;i++){
		top=0;
		for(int j=0;j<4;j++){
			if(i!=j){
				input[top++]=j;
			}
		}
		if(judge(length[input[0]],length[input[1]],length[input[2]])){
			cout<<"TRIANGLE";
			return 0;
		}
	}
	for(int i=0;i<4;i++){
		top=0;
		for(int j=0;j<4;j++){
			if(i!=j){
				input[top++]=j;
			}
		}
		if(judge2(length[input[0]],length[input[1]],length[input[2]])){
			cout<<"SEGMENT";
			return 0;
		}
	}
	cout<<"IMPOSSIBLE";
}