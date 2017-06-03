#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
	int d,sum,summin=0,summax=0;
	cin>>d>>sum;
	int mint[d],maxt[d];
	for(int i=0;i<d;i++){
		cin>>mint[i]>>maxt[i];
		summin+=mint[i];
		summax+=maxt[i];
	}
	if(sum>summax||sum<summin){
		cout<<"NO";
		return 0;
	}
	cout<<"YES"<<endl;
	int day[d];
	for(int i=0;i<d;i++){
		day[i]=mint[i];
	}
	sum-=summin;
	for(int i=0;i<d&&sum>0;i++){
		if(sum>=maxt[i]-mint[i]){
			day[i]=maxt[i];
			sum-=maxt[i]-mint[i];
		}else{
			day[i]+=sum;
			sum=0;
		}
	}
	for(int i=0;i<d;i++){
		cout<<day[i]<<' ';
	}
}