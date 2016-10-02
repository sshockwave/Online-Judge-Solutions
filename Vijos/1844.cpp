#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
	int n,cnt=0,h,last=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&h);
		if(h>last){
			cnt+=h-last;
		}
		last=h;
	}
	cout<<cnt;
}
