#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int abs(int a){
	return a>0?a:(0-a);
}
int max(int a,int b){
	return a>b?a:b;
}
int main(){
	int ax,bx,ay,by;
	char a,b,c,d;
	cin>>a>>b>>c>>d;
	ax=b,ay=a,bx=d,by=c;
	bx=ax=bx-ax;
	by=ay=ay-by;
	cout<<max(abs(ax),abs(ay))<<endl;
	while(ax!=0||ay!=0){
		if(ay>0){
			cout<<"L";
			ay--;
		}else if(ay<0){
			cout<<"R";
			ay++;
		}
		if(ax>0){
			cout<<"U";
			ax--;
		}else if(ax<0){
			cout<<"D";
			ax++;
		}
		cout<<endl;
	}
}