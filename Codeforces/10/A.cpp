#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
	int n,p1,p2,p3,t1,t2;
	cin>>n>>p1>>p2>>p3>>t1>>t2;
	int l,r,last,total=0;
	for(int i=0;i<n;i++){
		cin>>l>>r;
		if(i==0){
			last=l;
		}
		if(l-last<t1){
			total+=(l-last)*p1;
			//cout<<"total+("<<l<<"-"<<last<<")*"<<p1<<"="<<total<<endl;
		}else{
			total+=t1*p1;
			//cout<<"total+"<<t1<<"*"<<p1<<"="<<total<<endl;
			last+=t1;
			//cout<<"last="<<last<<endl;
			if(l-last<t2){
				total+=(l-last)*p2;
				//cout<<"total+("<<l<<"-"<<last<<")*"<<p2<<"="<<total<<endl;
			}else{
				total+=t2*p2;
				//cout<<"total+"<<t2<<"*"<<p2<<"="<<total<<endl;
				last+=t2;
				//cout<<"last="<<last;
				total+=(l-last)*p3;
				//cout<<"total+("<<l<<"-"<<last<<")*"<<p3<<"="<<total<<endl;
			}
		}
		total+=(r-l)*p1;
		//cout<<"total+("<<r<<"-"<<l<<")*"<<p1<<"="<<total<<endl;
		last=r;
	}
	cout<<total;
}
//10*8+5*8+10*4+2*5+50*8